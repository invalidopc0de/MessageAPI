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
    void sendMessage(QString, UdpMessage::UdpMessageType);
    void sendMessage(UdpMessage, QString);
    void sendMessage(UdpMessage*);
signals:
    //! BroadcastService Started
    /*!
      Emitted when the BroadcastService has sucessfully started
      */
    void OnServiceStarted(bool);
    //! Message Recieved
    /*!
      Emitted when the BroadcastService has received a message
      */
    void OnMessageRecieved(UdpMessage*);
    //! Message Send Failed
    /*!
      Emitted when a message send operation fails
      */
    void OnMessageFail();
    //! Message Send Succeded
    /*!
      Emitted when a message send operation succeeds
      */
    void OnMessageSuccess();
private slots:
    void processPendingDatagrams();
private:
    QUdpSocket *client;
    QString currentIP;
    qint16 currentPort;
};

#endif // BROADCASTSERVICE_H
