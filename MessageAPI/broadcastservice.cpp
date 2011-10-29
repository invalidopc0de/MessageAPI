#include "messageapi.h"
#include "QtNetwork/QtNetwork"
#include "QDebug"
#include "stdio.h"
#include "broadcastservice.h"
#include "stdlib.h"

//! Broadcast Service Constructor
/*!
    This must be called before attempting to use a new BroadcastService
    \param address the IP address that the BroadcastService will run on. (default: 255.255.255.255)
    \param port the port that the BroadcastService will run on. (default: 5683)
  */
BroadcastService::BroadcastService(QString address = "255.255.255.255", qint16 port = 5683)
{
    currentIP = address;
    currentPort = port;
    startService();
}

//! Starts the Broadcast Service
/*!
    This function is called to start the BroadcastService.  It is automatically called by BroadcastService::BroadcastService
    \return A boolean value indicating if the start succeded.
  */
bool BroadcastService::startService(){
    bool didConnect = false;
    client = new QUdpSocket();
    if(client->bind(QHostAddress(currentIP), currentPort, QUdpSocket::ShareAddress) == true)
    {
        connect(client, SIGNAL(readyRead()),
                     this, SLOT(processPendingDatagrams()));
        didConnect = true;
    } else {
        didConnect = false;
    }
    emit OnServiceStarted(didConnect);
    return didConnect;
}

//! Send a message
/*!
  Use this function to send a message to everyone.
  \param message the string to be sent
  \param type a UdpMessage::UdpMessageType specifying what type the message is
 */

void BroadcastService::sendMessage(QString message, UdpMessage::UdpMessageType type){
    sendMessage(new UdpMessage(UdpUser().Anyone, message, type));
}

//! Send a message
/*!
  Use this function to send a message with an alias.
  \param message the UdpMessage to be send
  \param alias the current user's alias
  */
void BroadcastService::sendMessage(UdpMessage message, QString alias){
    message.SenderUser->Alias = alias;
    sendMessage(&message);
}

//! Send a message
/*!
  Use this function to send a UdpMessage
  \param message the UdpMessage to send
  */

void BroadcastService::sendMessage(UdpMessage* message)
{
    qDebug() << QString("Sending Message to " + message->IntendedUser->Username);
    QString currentUser;
    currentUser = UdpUser().getCurrentUser();
    message->SenderUser = new UdpUser(currentUser);
    QChar controlChar = UdpMessage().controlChar;
    QString messageData = message->IntendedUser->Username.trimmed() + controlChar +
            message->SenderUser->Username.trimmed() + controlChar +
            message->SenderUser->Alias.trimmed() + controlChar +
            (((int)message->MessageType)+0x30) + controlChar +
            message->Message.trimmed();
    QByteArray datagram = messageData.toUtf8();
    //QByteArray datagram = "Hello There!";
    qDebug() << QString("Sending Message:" + datagram);
    client->writeDatagram(datagram.data(), datagram.size(), QHostAddress::Broadcast, currentPort);
}

void BroadcastService::processPendingDatagrams(){
    while (client->hasPendingDatagrams()) {
             QByteArray datagram;
             datagram.resize(client->pendingDatagramSize());
             client->readDatagram(datagram.data(), datagram.size());
             emit OnMessageRecieved(UdpMessage().parseMessage(QString().fromUtf8(datagram.data(),datagram.size())));
    }
}

