#ifndef BROADCASTSERVICE_H
#define BROADCASTSERVICE_H

#define DEFAULT_PORT 5683
#define DEFAULT_IP "255.255.255.255"

#include <QObject>
#include "udpobjects.h"

class QUdpSocket;
class QHostAddress;

class BroadcastService : public QObject {
    Q_OBJECT
public:
    BroadcastService(QString, qint16);
    virtual ~BroadcastService() {}
    bool startService();
    void sendMessage(QString, UdpMessage::udpMessageType);
    void sendMessage(UdpMessage, QString);
    void sendMessage(UdpMessage*);
signals:
    void OnServiceStarted(bool);
    void OnMessageRecieved(UdpMessage*);
    void OnMessageFail();
    void OnMessageSuccess();
private slots:
    void processPendingDatagrams();
private:
    QUdpSocket *client;
    QString currentIP;
    qint16 currentPort;
};

#endif // BROADCASTSERVICE_H
