#ifndef BROADCASTSERVICE_H
#define BROADCASTSERVICE_H

#define DEFAULT_PORT 5683
#define DEFAULT_IP "255.255.255.255"
#define API_LEVEL 1

#include <QObject>
#include "udpobjects.h"

class QUdpSocket;
class QHostAddress;

class BroadcastService : public QObject {
    Q_OBJECT
public:
    //! Broadcast Service Constructor
    /*!
        This must be called before attempting to use a new BroadcastService
        \param address the IP address that the BroadcastService will run on. (default: 255.255.255.255)
        \param port the port that the BroadcastService will run on. (default: 5683)
      */
    BroadcastService(QString, qint16);

    virtual ~BroadcastService() {}

    //! Starts the Broadcast Service
    /*!
        This function is called to start the BroadcastService.  It is automatically called by BroadcastService::BroadcastService
        \return A boolean value indicating if the start succeded.
      */
    bool startService();

    //! Send a message
    /*!
      Use this function to send a message to everyone.
      \param message the string to be sent
      \param type a UdpMessage::UdpMessageType specifying what type the message is
     */
    void sendMessage(QString, UdpMessage::UdpMessageType);


    //! Send a message
    /*!
      Use this function to send a message with an alias.
      \param message the UdpMessage to be send
      \param alias the current user's alias
      */
    void sendMessage(UdpMessage, QString);

    //! Send a message
    /*!
      Use this function to send a UdpMessage
      \param message the UdpMessage to send
      */
    void sendMessage(UdpMessage*);

    //! Join a message group
    /*!
      Used to join a message group
      \param GroupName the name of the group to join
      */
    void joinGroup(QString GroupName);

    //! Leave a message group
    /*!
      Used to leave a message group
      \param GroupName the name of the group to leave
      */
    void leaveGroup(QString GroupName);

    int getApiLevel();
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
    QList<QString> messageGroups;
};

#endif // BROADCASTSERVICE_H
