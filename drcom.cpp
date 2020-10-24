#include "drcom.h"

#include <QEventLoop>
#include <QTimer>
#include <QNetworkInterface>
#include <QStringList>
#include <QCryptographicHash>
#include <QString>
#include <QHostInfo>
#include <QMessageBox>

#include "configmapper.h"
#include "log.h"

namespace
{

    constexpr quint16 SERVER_PORT = 61440;

    int challengeTimes = -1;

    inline QByteArray md5sum(const QByteArray &data)
    {
        return QCryptographicHash::hash(data, QCryptographicHash::Md5);
    }

    QByteArray checksum(const QByteArray &data)
    {
        QByteArray sum, ret;
        sum.resize(4);
        sum[0] = 0x00;
        sum[1] = 0x00;
        sum[2] = 0x04;
        sum[3] = (quint8)0xd2;
        int length = data.size();
        int i = 0;
        while (i + 3 < length)
        {
            sum[0] = ((quint8)sum.at(0)) ^ ((quint8)data.at(i + 3));
            sum[1] = ((quint8)sum.at(1)) ^ ((quint8)data.at(i + 2));
            sum[2] = ((quint8)sum.at(2)) ^ ((quint8)data.at(i + 1));
            sum[3] = ((quint8)sum.at(3)) ^ ((quint8)data.at(i));
            i += 4;
        }
        if (i < length)
        {
            QByteArray tmp;
            tmp.resize(4);
            tmp.fill(0);
            for (int j = 3; j >= 0 && i < length; j--)
            {
                tmp[j] = (quint8)data.at(i++);
            }
            for (int j = 0; j < 4; j++)
            {
                sum[j] = (quint8)(sum.at(j)) ^ (tmp.at(j));
            }
        }
        quint64 num = 0;
        num |= (quint8)sum.at(0);
        num <<= 8;
        num |= (quint8)sum.at(1);
        num <<= 8;
        num |= (quint8)sum.at(2);
        num <<= 8;
        num |= (quint8)sum.at(3);
        num *= 1968;
        ret.resize(4);
        ret.fill(0);
        for (int i = 0; i < 4; i++)
        {
            ret[i] = (quint8)(num & 0xff);
            num >>= 8;
        }
        return ret;
    }

} // namespace

Drcom::Drcom() : random(QDateTime::currentSecsSinceEpoch())
{
    auto &&config = ConfigMapper::instance;
    salt.resize(4);
    salt.fill(0);
    md5a.resize(16);
    md5a.fill(0);
    tail.resize(16);
    tail.fill(0);
    flux.resize(4);
    flux.fill(0);
    quint32 ip = 0;
    auto &&addresses = QNetworkInterface::allAddresses();
    for (auto &address : addresses)
    {
        if (address != QHostAddress::LocalHost && address.toIPv4Address() != 0)
        {
            ip = address.toIPv4Address();
        }
    }
    hostIp.resize(4);
    hostIp.fill(0);
    hostIp[3] = ip & 0xff;
    ip >>= 8;
    hostIp[2] = ip & 0xff;
    ip >>= 8;
    hostIp[1] = ip & 0xff;
    ip >>= 8;
    hostIp[0] = ip & 0xff;
    serverAddress = QHostAddress(config["server"]);
    quint32 serverIp = serverAddress.toIPv4Address();
    server.resize(4);
    server.fill(0);
    server[3] = serverIp & 0xff;
    serverIp >>= 8;
    server[2] = serverIp & 0xff;
    serverIp >>= 8;
    server[1] = serverIp & 0xff;
    serverIp >>= 8;
    server[0] = serverIp & 0xff;

    socket.bind(QHostAddress::LocalHost, SERVER_PORT);
    connect(&socket, &QUdpSocket::readyRead, this, &Drcom::on_socket_readyRead);
    if (config["first_run"] == "")
    {
        for (auto &net : QNetworkInterface::allInterfaces())
        {
            if (net.flags().testFlag(QNetworkInterface::IsUp) &&
                net.flags().testFlag(QNetworkInterface::IsRunning) &&
                !net.flags().testFlag(QNetworkInterface::IsLoopBack))
            {
                config.set("mac", net.hardwareAddress());
                config.set("first_run", "false");
                config.flush();
                break;
            }
        }
    }
    mac.resize(6);
    mac.fill(0);
    QString macStr = config["mac"];
    if (macStr != "")
    {
        QStringList macNumbers = macStr.split(':');
        bool ok;
        for (int i = 0; i < 6; ++i)
        {
            mac[i] = macNumbers.at(i).toInt(&ok, 16);
        }
        if (!ok)
        {
            Log::debug("[init] cannot convert MAC address.");
        }
    }
    else
    {
        Log::debug("[init] cannot obtain MAC address.");
    }
    connect(&aliveTimer, &QTimer::timeout, this, &Drcom::sendAlivePacket);
    aliveTimer.setSingleShot(true);
}

void Drcom::login(const QString &username, const QString &passwd)
{
    this->username = username.toUtf8();
    this->password = passwd.toUtf8();
    status = LoginStatus::CHALLENGE;
    sendChallengePacket();
}

void Drcom::logout()
{
    status = LoginStatus::CHALLENGE;
    if (aliveTimer.isActive())
    {
        aliveTimer.stop();
    }
}

void Drcom::on_socket_readyRead()
{
    auto &&data = socket.receiveDatagram();
    if (data.isValid() && data.data().at(0) == 0x4d && data.data().at(1) == 0x15)
    {
        QString msg = "[receive] Other location logined.";
        Log::debug(msg);
        emit loginFailed(msg);
        return;
    }
    switch (status)
    {
    case LoginStatus::CHALLENGE:
        status = LoginStatus::LOGIN;
        recvChallengePacket(data);
        break;
    case LoginStatus::LOGIN:
        status = LoginStatus::ALIVE;
        recvLoginPacket(data);
        break;
    case LoginStatus::ALIVE:
        recvAlivePacket(data);
        break;
    }
}

void Drcom::sendAlivePacket()
{
    int randtimes = random.bounded(0xffff);
    QByteArray data;
    if (aliveNumber == 0)
    {
        data.resize(38);
        data.fill(0);
        data[0] = (quint8)0xff;
        memcpy(data.data() + 1, md5a.data(), 16);
        memcpy(data.data() + 20, tail.data(), 16);
        data[36] = (quint8)(randtimes >> 8);
        data[37] = (quint8)(randtimes & 0xffffffff);
    }
    else
    {
        data.resize(40);
        data.fill(0);
        data[0] = 0x07;
        data[1] = 0x00;
        data[2] = 0x28;
        data[4] = 0x0b;
        data[5] = (quint8)(2 * aliveNumber - 1);

        data[6] = (quint8)0xdc;
        data[7] = 0x02;
        data[9] = (quint8)(randtimes >> 8);
        data[10] = (quint8)randtimes;
        memcpy(data.data() + 16, flux.data(), 4);
        if (aliveNumber == 2)
        {
            memcpy(data.data() + 28, hostIp.data(), 4);
        }
    }
    Log::debug("[keep-alive] Sending keep-alive" + QString::number(aliveNumber) + " packet...");

    socket.writeDatagram(data, serverAddress, SERVER_PORT);
}

void Drcom::recvAlivePacket(const QNetworkDatagram &data)
{
    if (!data.isValid())
    {
        QString msg = "[alive] Alive-" + QString::number(aliveNumber) + " timeout.";
        Log::debug(msg);
        emit loginFailed(msg);
        return;
    }
    if (data.data().at(0) != 0x07)
    {
        QString msg = "[alive] Alive fail, unrecognized responese: " + QString::number(data.data().at(0));
        Log::debug(msg);
        emit loginFailed(msg);
        return;
    }
    if (aliveNumber > 0)
    {
        memcpy(flux.data(), data.data().data() + 16, 4);
    }
    ++aliveNumber;
    if (aliveNumber == 3)
    {
        aliveNumber = 0;
        aliveTimer.start(20000);
        return;
    }
    sendAlivePacket();
}

void Drcom::sendLoginPacket()
{
    Log::debug("[login] Making login packet...");

    const quint8 code = 0x03;
    const quint8 type = 0x01;
    const quint8 eof = 0x00;
    const quint8 controlCheck = 0x20;
    const quint8 adapterNum = 0x05;
    const quint8 ipDog = 0x01;
    QByteArray primaryDNS(4, 10);
    QByteArray dhcp(4, 0);
    QByteArray md5b, md5c;

    int passLength = password.size();
    if (passLength > 16)
        passLength = 16;
    int dataLength = 334 + (passLength - 1) / 4 * 4;
    QByteArray data(dataLength, 0);

    //begin
    data[0] = code;
    data[1] = type;
    data[2] = eof;
    data[3] = (quint8)(username.size() + 20);

    QByteArray md5Source;
    md5Source.append(code);
    md5Source.append(type);
    md5Source.append(salt);
    md5Source.append(password);

    //md5a
    md5a = md5sum(md5Source);
    memcpy(data.data() + 4, md5a.data(), md5a.size());

    //username
    memcpy(data.data() + 20, username.data(), username.size());

    data[56] = controlCheck;
    data[57] = adapterNum;

    //md5a[0:6] xor mac
    memcpy(data.data() + 58, md5a.data(), 6);
    for (int i = 0; i < 6; i++)
    {
        data[58 + i] = ((quint8)data[58 + i]) ^ ((quint8)mac.at(i));
    }

    //md5b
    md5Source.clear();
    md5Source.append(0x01);
    md5Source.append(password);
    md5Source.append(salt);
    md5Source.append((char)0x00);
    md5Source.append((char)0x00);
    md5Source.append((char)0x00);
    md5Source.append((char)0x00);
    md5b = md5sum(md5Source);
    memcpy(data.data() + 64, md5b.data(), md5b.size());

    //ip address
    data[80] = 0x01; //number of ip
    memcpy(data.data() + 81, hostIp.data(), hostIp.size());

    //md5c
    data[97] = 0x14; //these are temp, 97:105 are md5c[0:8]
    data[98] = 0x00;
    data[99] = 0x07;
    data[100] = 0x0b;
    QByteArray tmp(101, 0);
    memcpy(tmp.data(), data.data(), tmp.size());
    md5c = md5sum(tmp);
    memcpy(data.data() + 97, md5c.data(), 8);

    data[105] = ipDog; //0x01
    QByteArray hostname = QHostInfo::localHostName().toUtf8();
    memcpy(data.data() + 110, hostname.data(), hostname.size());
    memcpy(data.data() + 142, primaryDNS.data(), 4);
    memcpy(data.data() + 146, dhcp.data(), 4);

    //second dns: 4, delimiter: 8
    data[162] = (quint8)0x94;
    data[166] = 0x06;
    data[170] = 0x02;
    data[174] = (quint8)0xf0;
    data[175] = 0x23;
    data[178] = 0x02;

    //drcom check
    data[182] = 0x44;
    data[183] = 0x72;
    data[184] = 0x43;
    data[185] = 0x4f;
    data[186] = 0x4d;
    data[187] = 0x00;
    data[188] = (quint8)0xcf;
    data[189] = 0x07;
    data[190] = 0x6a;

    memcpy(data.data() + 246, "1c210c99585fd22ad03d35c956911aeec1eb449b", 40);
    data[310] = 0x6a;
    data[313] = (quint8)passLength;
    QByteArray ror(passLength, 0);
    int x;
    for (int i = 0; i < passLength; ++i)
    {
        x = ((quint8)md5a.at(i)) ^ ((quint8)password.at(i));
        ror[i] = (quint8)((x << 3) + (x >> 5));
    }
    memcpy(data.data() + 314, ror.data(), passLength);
    data[314 + passLength] = 0x02;
    data[315 + passLength] = 0x0c;

    //checksum(data+'\x01\x26\x07\x11\x00\x00'+dump(mac))
    data[316 + passLength] = 0x01;
    data[317 + passLength] = 0x26;
    data[318 + passLength] = 0x07;
    data[319 + passLength] = 0x11;
    data[320 + passLength] = 0x00;
    data[321 + passLength] = 0x00;
    memcpy(data.data() + 322 + passLength, mac.data(), 4);
    tmp.resize(326 + passLength);
    tmp.fill(0);
    memcpy(tmp.data(), data.data(), tmp.size());
    tmp = checksum(tmp);
    memcpy(data.data() + 316 + passLength, tmp, 4);

    data[320 + passLength] = 0x00;
    data[321 + passLength] = 0x00;

    memcpy(data.data() + 322 + passLength, mac.data(), mac.size());
    int zeroCount = (4 - passLength % 4) % 4;
    for (int i = 0; i < zeroCount; i++)
    {
        data[328 + passLength + i] = 0x00;
    }
    data[328 + passLength + zeroCount] = (quint8)random.bounded(255);
    data[329 + passLength + zeroCount] = (quint8)random.bounded(255);

    socket.writeDatagram(data, serverAddress, SERVER_PORT);
}

void Drcom::recvLoginPacket(const QNetworkDatagram &data)
{
    if (!data.isValid())
    {
        QString msg = "[login] Login timeout.";
        Log::debug(msg);
        emit loginFailed(msg);
        return;
    }
    if (data.data().at(0) != 0x04)
    {
        if (data.data().at(0) == 0x05)
        {
            if (data.data().at(4) == 0x0b)
            {
                QString msg = "[login] Login fail,wrong MAC address";
                Log::debug(msg);
                emit loginFailed(msg);
            }
            else
            {
                QString msg = "[login] Login fail,wrong password or username";
                Log::debug(msg);
                emit loginFailed(msg);
            }
        }
        else
        {
            QString msg = "[login] Login fail, unrecognized responese: " + QString::number(data.data().at(0));
            Log::debug(msg);
            emit loginFailed(msg);
        }
        return;
    }
    memcpy(tail.data(), data.data().data() + 23, 16);
    Log::debug("[login] Login success.");
    emit loginSuccess();
    aliveNumber = 0;
    sendAlivePacket();
}

void Drcom::sendChallengePacket()
{
    QByteArray data(20, 0);
    data[0] = 0x01;
    data[1] = (quint8)(++challengeTimes);
    data[2] = (quint8)random.bounded(255);
    data[3] = (quint8)random.bounded(255);
    data[4] = 0x6a;
    Log::debug("[challenge] Sending challenge packet...");

    socket.writeDatagram(data, serverAddress, SERVER_PORT);
}

void Drcom::recvChallengePacket(const QNetworkDatagram &data)
{
    if (!data.isValid())
    {
        QString msg = "[challenge] Challenge timeout.";
        Log::debug(msg);
        emit loginFailed(msg);
        return;
    }
    if (data.data().at(0) != 0x02)
    {
        QString msg = "[challenge] Challenge fail, unrecognized responese: " + QString::number(data.data().at(0));
        Log::debug(msg);
        emit loginFailed(msg);
        return;
    }
    memcpy(salt.data(), data.data().data() + 4, 4);
    QString msg = "[login-salt] ";
    for (quint8 byte : salt)
    {
        msg += '/' + QString::number(byte, 16);
    }
    Log::debug(msg);
    if (data.data().size() >= 25)
    {
        memcpy(hostIp.data(), data.data().data() + 20, 4);
        Log::debug("[login-ip] " + hostIp);
    }
    sendLoginPacket();
}
