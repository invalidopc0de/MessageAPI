#include "messageapi.h"
#include "QtNetwork/QtNetwork"
#include "QDebug"
#include "stdio.h"
#include "broadcastservice.h"
#include "stdlib.h"

BroadcastService::BroadcastService(QString address, qint16 port = 5683)
{
    currentIP = address;
    currentPort = port;
    startService();
}

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

void BroadcastService::sendMessage(QString message, UdpMessage::udpMessageType type){
    sendMessage(new UdpMessage(UdpUser().Anyone, message, type));
}

void BroadcastService::sendMessage(UdpMessage message, QString alias){
    message.SenderUser->Alias = alias;
    sendMessage(&message);
}

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

