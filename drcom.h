#ifndef LOGINTHREAD_H
#define LOGINTHREAD_H

#include <QList>
#include <QtNetwork>
#include <QRandomGenerator>

class Drcom : public QObject
{
    Q_OBJECT
public:
    Drcom();
    ~Drcom() = default;
    void login(const QString &username, const QString &passwd);
    void logout();

signals:
    void loginSuccess();
    void loginFailed(const QString &msg);

private slots:
    void on_socket_readyRead();

private:
    enum class LoginStatus
    {
        CHALLENGE,
        LOGIN,
        ALIVE
    };

    QUdpSocket socket;
    LoginStatus status;
    QRandomGenerator random;
    QByteArray mac;
    QByteArray server;
    QByteArray hostIp;
    QByteArray md5a;
    QByteArray salt;
    QByteArray tail;
    QByteArray flux;
    QByteArray username;
    QByteArray password;
    QHostAddress serverAddress;
    int aliveNumber;
    QTimer aliveTimer;

    void sendAlivePacket();
    void sendLoginPacket();
    void sendChallengePacket();
    void recvAlivePacket(const QNetworkDatagram &data);
    void recvLoginPacket(const QNetworkDatagram &data);
    void recvChallengePacket(const QNetworkDatagram &data);
};

#endif // LOGINTHREAD_H
