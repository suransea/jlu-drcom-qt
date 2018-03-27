#ifndef LOGINTHREAD_H
#define LOGINTHREAD_H
#include <QThread>
#include <QList>
#include <QtNetwork>
#include <memory>
#include <random>
#include <time.h>

class LoginThread :public QThread
{
    Q_OBJECT
public:
    static QList<QString> logs;
    LoginThread();
    ~LoginThread();
    void setExitFlagTrue();
    QString getStatus();
protected:
    void run();
private slots:
    void readPendingDatagrams();
private:
    volatile bool exitFlag=false;
    volatile bool receiving=false;
    const bool isWireless=true;
    int receiveStatus=-1;
    //std::unique_ptr<QUdpSocket> udpSocket;
    QUdpSocket *udpSocket;
    QString status="wait";
    std::default_random_engine randomEngine=std::default_random_engine(time(nullptr));
    std::uniform_int_distribution<int> uid=std::uniform_int_distribution<int>(0,32767);
    QByteArray mac;
    QByteArray server;
    QByteArray hostIp;
    QByteArray md5a;
    QByteArray salt;
    QByteArray tail;
    QByteArray flux;
    QByteArray buffer;
    QByteArray username;
    QByteArray password;
    QHostAddress serverAddress;
    QHostAddress hostAddress;

    bool initialize();
    void makeLoginPacket(QByteArray &data);
    void makeKeepAlivePacket(QByteArray &data,int type,int randtimes);
    void waitReceive();
    int sendPacket(QByteArray data, int length);
    int sendAlivePacket();
    int sendLoginPacket();
    int sendChallengePacket(int times);
    void clearLogs();
    QByteArray md5sum(QByteArray data);
    QByteArray checksum(QByteArray data);
    void printBytes(QByteArray bytes,int length,QString comment);
};

#endif // LOGINTHREAD_H
