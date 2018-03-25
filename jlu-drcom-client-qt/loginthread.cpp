#include "loginthread.h"
#include "mainwindow.h"
#include <iostream>
#include <string>
#include <QEventLoop>
#include <QTimer>
#include <QNetworkInterface>
#include <QStringList>
#include <QCryptographicHash>
#include <QString>
#include <QHostInfo>

QList<QString> LoginThread::logs=QList<QString>();

LoginThread::LoginThread()
{
}

void LoginThread::setExitFlagTrue()
{
    exitFlag=true;
}

QString LoginThread::getStatus()
{
    return status;
}

void LoginThread::run()
{
    initialize();
    int result=0,trytimes=5;
    while(!exitFlag){
        if(trytimes>=0&&result++>trytimes){
            status="[login] Try over times.";
            logs.append(status);
            return;
        }
        int p=sendChallengePacket(result);
        if(p==-5)return;
        if(p<0)continue;

        p=sendLoginPacket();
        if(p==-5)return;
        if(p<0)continue;
        break;
    }
    while(!exitFlag){
        clearLogs();
        result=0;
        int p;
        while(!exitFlag&&(p=sendAlivePacket()!=0)){
            if(p==-5)return;
            if(trytimes>=0&&result++>trytimes){
                status="[alive] Send alive over times.";
                logs.append(status);
                return;
            }
            for(int i=0;(!exitFlag)&&i<10;i++){
                QEventLoop loop;
                QTimer::singleShot(100,&loop,SLOT(quit()));
                loop.exec();
            }
        }
        for(int i=0;(!exitFlag)&&i<200;i++){
            QEventLoop loop;
            QTimer::singleShot(100,&loop,SLOT(quit()));
            loop.exec();
        }
    }
}

void LoginThread::readPendingDatagrams()
{
    while(udpSocket->hasPendingDatagrams()){
        buffer.resize(udpSocket->pendingDatagramSize());
        buffer.fill(0);
        receiveStatus=udpSocket->readDatagram(buffer.data(),buffer.size());

        //printBytes(buffer,buffer.size(),"receive");

    }
    if(receiveStatus<0){
        status="[receive] Receive failed.";
        logs.append(status);
        receiveStatus= -1;
    }
    if(buffer.at(0)==0x4d){
        if(buffer.at(1)==0x15){
            status="[receive] Other location logined.";
            logs.append(status);
            receiveStatus= -5;
        }
    }
    receiving=true;
}

bool LoginThread::initialize()
{
    auto cfg =MainWindow::configureReader.getCfg();
    udpSocket.reset(new QUdpSocket());
    salt.resize(4);
    salt.fill(0);
    md5a.resize(16);
    md5a.fill(0);
    tail.resize(16);
    tail.fill(0);
    flux.resize(4);
    flux.fill(0);
    quint32 ip=0;
    QList<QHostAddress> addressList=QNetworkInterface::allAddresses();
    for(auto &address:addressList){
        if(address!=QHostAddress::LocalHost&&
                address.toIPv4Address()){
            ip=address.toIPv4Address();
            hostAddress=address;
        }
    }
    if(ip==0){
        hostAddress=QHostAddress(QHostAddress::LocalHost);
        ip=hostAddress.toIPv4Address();
    }
    hostIp.resize(4);
    hostIp.fill(0);
    hostIp[3]=ip&0xff;
    ip>>=8;
    hostIp[2]=ip&0xff;
    ip>>=8;
    hostIp[1]=ip&0xff;
    ip>>=8;
    hostIp[0]=ip&0xff;
    serverAddress=QHostAddress(cfg["server"].c_str());
    quint32 serverIp=serverAddress.toIPv4Address();
    server.resize(4);
    server.fill(0);
    server[3]=serverIp&0xff;
    serverIp>>=8;
    server[2]=serverIp&0xff;
    serverIp>>=8;
    server[1]=serverIp&0xff;
    serverIp>>=8;
    server[0]=serverIp&0xff;

    udpSocket->bind(hostAddress,61440);
    connect(udpSocket.get(),SIGNAL(readyRead()),SLOT(readPendingDatagrams()));
    QString macStr=QString::fromStdString(cfg["mac"]);
    QStringList macList=macStr.split(':');
    mac.resize(6);
    mac.fill(0);
    bool ok=false;
    for(int macListIndex=0;macListIndex<6;macListIndex++){
        mac[macListIndex]=macList.at(macListIndex).toInt(&ok,16);
    }
    if(!ok){
        status="Convert MAC failed.";
        logs.append(status);
        return false;
    }
    username=QString::fromStdString(cfg["name"]).toLocal8Bit();
    password=QString::fromStdString(cfg["passwd"]).toLocal8Bit();
    return true;
}

void LoginThread::makeKeepAlivePacket(QByteArray &data, int type, int randtimes)
{
    if(type==0){
        data.resize(38);
        data.fill(0);
        data[0]=0xff;
        memcpy(data.data()+1,md5a.data(),16);
        memcpy(data.data()+20,tail.data(),16);
        data[36]=(quint8)(randtimes>>8);
        data[37]=(quint8)(randtimes&0xffffffff);
    }else{
        data.resize(40);
        data.fill(0);
        data[0] = 0x07;
        data[1] = 0x00;
        data[2] = 0x28;
        data[4] = 0x0b;
        data[5] = (quint8)(2 * type - 1);

        data[6] = 0xdc;
        data[7] = 0x02;
        data[9] = (qint8)(randtimes >> 8);
        data[10] = (qint8)randtimes;
        memcpy(data.data()+16,flux.data(),4);
        if(type==2){
            memcpy(data.data()+28,hostIp.data(),4);
        }
    }
    logs.append("[keep-alive] Sending keep-alive"+QString::number(type)+" packet...");
}

void LoginThread::waitReceive()
{
    while(!receiving){
        QEventLoop loop;
        QTimer::singleShot(10,&loop,SLOT(quit()));
        loop.exec();
    }
    receiving=false;
}

int LoginThread::sendPacket(QByteArray data, int length)
{
    auto result= udpSocket->writeDatagram(data.data(),
                                 length,serverAddress,61440);
    udpSocket->waitForBytesWritten();
    //printBytes(data,length,"send");
    return result;
}

int LoginThread::sendAlivePacket()
{
    int randtimes=uid(randomEngine)%0xffff;
    for(int i=0;i<3;i++){
        makeKeepAlivePacket(buffer,i,randtimes);
        sendPacket(buffer,i==0?38:40);
        waitReceive();
        int result=receiveStatus;
        if(result==-5)return -5;
        if(result<0){
            status="[alive] Alive-"+QString::number(i)+" timeout.";
            logs.append(status);
            return -1;
        }
        if(buffer.at(0)!=0x07){
            status="[alive] Alive fail, unrecognized responese: "+QString::number(buffer.at(0));
            logs.append(status);
            return -1;
        }
        if(i>0){
            memcpy(flux.data(),buffer.data()+16,4);
        }
    }
    return 0;
}

int LoginThread::sendLoginPacket()
{
    makeLoginPacket(buffer);
    sendPacket(buffer,buffer.size());
    waitReceive();
    int receiveLength=receiveStatus;
    if(receiveLength==-5)return -5;
    if(receiveLength<=0){
        status="[login] Login timeout.";
        logs.append(status);
        return -1;
    }

    if(buffer.at(0)!=0x04){
        if(buffer.at(0)==0x05){
            if(buffer.at(4)==0x0b){
                status="[login] Login fail,wrong MAC address";
                logs.append(status);
            }else{
                status="[login] Login fail,wrong password or username";
                logs.append(status);
            }
        }else{
            status="[login] Login fail, unrecognized responese: "+QString::number(buffer.at(0));
            logs.append(status);
        }
        return -1;
    }
    memcpy(tail.data(),buffer.data()+23,16);
    status="success";
    logs.append("[login] Login success.");
    return 0;
}

int LoginThread::sendChallengePacket(int times)
{
    buffer.resize(20);
    buffer.fill(0);
    buffer[0]=0x01;
    buffer[1]=(quint8)(0x02+times);
    buffer[2]=(quint8)uid(randomEngine)%255;
    buffer[3]=(quint8)uid(randomEngine)%255;
    buffer[4]=0x6a;
    logs.append("[challenge] Sending challenge packet...");
    sendPacket(buffer,20);
    waitReceive();
    int resultLength=receiveStatus;
    if(resultLength==-5)return -5;
    if(resultLength<=0){
        status="[challenge] Challenge timeout.";
        logs.append(status);
        return -1;
    }
    if(buffer.at(0)!=0x02){
        status="[challenge] Challenge fail, unrecognized responese: "+QString::number(buffer.at(0));
        logs.append(status);
        return -1;
    }
    memcpy(salt.data(),buffer.data()+4,4);
    QString log="[login-salt] ";
    for(quint8 byte : salt)log+='\\'+QString::number(byte,16);
    logs.append(log);
    if(isWireless&&resultLength>=25){
        memcpy(hostIp.data(),buffer.data()+20,4);
        logs.append("[login-ip] "+hostAddress.toString());
    }
    return 0;
}

void LoginThread::clearLogs()
{
    if(logs.size()>1000)logs.clear();
}

QByteArray LoginThread::md5sum(QByteArray data)
{
    return QCryptographicHash::hash(data,QCryptographicHash::Md5);
}

QByteArray LoginThread::checksum(QByteArray data)
{
    QByteArray sum,ret;
    sum.resize(4);
    sum[0]=0x00;
    sum[1]=0x00;
    sum[2]=0x04;
    sum[3]=(quint8)0xd2;
    int length=data.size();
    int i=0;
    while(i+3<length){
        sum[0]=(quint8)((quint8)sum.at(0))^((quint8)data.at(i+3));
        sum[1]=(quint8)((quint8)sum.at(1))^((quint8)data.at(i+2));
        sum[2]=(quint8)((quint8)sum.at(2))^((quint8)data.at(i+1));
        sum[3]=(quint8)((quint8)sum.at(3))^((quint8)data.at(i));
        i+=4;
    }
    if(i<length){
        QByteArray tmp;tmp.resize(4);tmp.fill(0);
        for(int j=3;j>=0&&i<length;j--){
            tmp[j]=(quint8)data.at(i++);
        }
        for(int j=0;j<4;j++){
            sum[j]=(quint8)(((quint8)sum.at(j))^((quint8)tmp.at(j)));
        }
    }
    quint64 num=0;
    num|=(quint8)sum.at(0);
    num<<=8;
    num|=(quint8)sum.at(1);
    num<<=8;
    num|=(quint8)sum.at(2);
    num<<=8;
    num|=(quint8)sum.at(3);
    num*=1968;
    ret.resize(4);ret.fill(0);
    for(int i=0;i<4;i++){
        ret[i]=(quint8)(num&0xff);
        num>>=8;
    }
    return ret;
}

void LoginThread::printBytes(QByteArray bytes,int length, QString comment)
{
    std::cout<<comment.toStdString()<<": ";
    int len=bytes.size()<length?bytes.size():length;
    for(int i=0;i<len;i++){
        std::cout<<QString::number((quint8)bytes.at(i),16).toStdString()<<'/';
    }
    std::cout<<'\n'<<std::endl;
}

void LoginThread::makeLoginPacket(QByteArray &data){
    logs.append("[login] Making login packet...");

    quint8 code=0x03;
    quint8 type=0x01;
    quint8 eof =0x00;
    quint8 controlCheck=0x20;
    quint8 adapterNum=0x05;
    quint8 ipDog=0x01;
    QByteArray primaryDNS(4,10);
    QByteArray dhcp(4,0);
    QByteArray md5b,md5c;

    int passLength=password.size();
    if(passLength>16)passLength=16;
    int dataLength=334+(passLength-1)/4*4;
    data.resize(dataLength);
    data.fill(0);

    //begin
    data[0]=code;
    data[1]=type;
    data[2]=eof;
    data[3]=(quint8)(username.size()+20);

    QByteArray md5Source;
    md5Source.append(code);
    md5Source.append(type);
    md5Source.append(salt);
    md5Source.append(password);

    //md5a
    memcpy(md5a.data(),md5sum(md5Source).data(),16);
    memcpy(data.data()+4,md5a.data(),md5a.size());

    //username
    memcpy(data.data()+20,username.data(),username.size());

    data[56]=controlCheck;
    data[57]=adapterNum;

    //md5a[0:6] xor mac
    memcpy(data.data()+58,md5a.data(),6);
    for(int i=0;i<6;i++){
        data[58+i]=((quint8)data[58+i])^((quint8)mac.at(i));
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
    md5b=md5sum(md5Source);
    memcpy(data.data()+64,md5b.data(),md5b.size());

    //ip address
    data[80]=0x01;//number of ip
    memcpy(data.data()+81,hostIp.data(),hostIp.size());
    memcpy(data.data()+85,QByteArray(12,0x00).data(),12);//ip2/3/4

    //md5c
    data[97]=0x14;//these are temp, 97:105 are md5c[0:8]
    data[98]=0x00;
    data[99]=0x07;
    data[100]=0x0b;
    QByteArray tmp;
    tmp.resize(101);
    tmp.fill(0);
    memcpy(tmp.data(),data.data(),tmp.size());
    md5c=md5sum(tmp);
    memcpy(data.data()+97,md5c.data(),8);

    data[105]=ipDog;//0x01
    QByteArray hostname;
    hostname.append(QHostInfo::localHostName());
    memcpy(data.data()+110,hostname.data(),hostname.size());
    memcpy(data.data()+142,primaryDNS.data(),4);
    memcpy(data.data()+146,dhcp.data(),4);

    //second dns: 4, delimiter: 8

    data[162]=(quint8)0x94;
    data[166]=0x06;
    data[170]=0x02;
    data[174]=(quint8)0xf0;
    data[175]=0x23;
    data[178]=0x02;

    //drcom check
    data[182]=0x44;
    data[183]=0x72;
    data[184]=0x43;
    data[185]=0x4f;
    data[186]=0x4d;
    data[187]=0x00;
    data[188]=(quint8)0xcf;
    data[189]=0x07;
    data[190]=0x6a;

    memcpy(data.data()+246,QByteArray(
               "1c210c99585fd22ad03d35c956911aeec1eb449b").data(),40);
    data[310]=0x6a;
    data[313]=(quint8)passLength;
    QByteArray ror;ror.resize(passLength);ror.fill(0);
    int x;
    for(int i=0;i<passLength;i++){
        x=(((quint8)md5a.at(i))&0xff)^(((quint8)password.at(i))&0xff);
        ror[i]=(quint8)((x<<3)+(x>>5));
    }
    memcpy(data.data()+314,ror.data(),passLength);
    data[314+passLength]=0x02;
    data[315+passLength]=0x0c;

    //checksum(data+'\x01\x26\x07\x11\x00\x00'+dump(mac))
    data[316+passLength]=0x01;
    data[317+passLength]=0x26;
    data[318+passLength]=0x07;
    data[319+passLength]=0x11;
    data[320+passLength]=0x00;
    data[321+passLength]=0x00;
    memcpy(data.data()+322+passLength,mac.data(),4);
    tmp.resize(326+passLength);
    tmp.fill(0);
    memcpy(tmp.data(),data.data(),tmp.size());
    tmp=checksum(tmp);
    memcpy(data.data()+316+passLength,tmp,4);

    data[320+passLength]=0x00;
    data[321+passLength]=0x00;

    memcpy(data.data()+322+passLength,mac.data(),mac.size());
    int zeroCount=(4-passLength%4)%4;
    for(int i=0;i<zeroCount;i++){
        data[328+passLength+i]=0x00;
    }
    data[328+passLength+zeroCount]=(quint8)(uid(randomEngine)%255);
    data[329+passLength+zeroCount]=(quint8)(uid(randomEngine)%255);
}
