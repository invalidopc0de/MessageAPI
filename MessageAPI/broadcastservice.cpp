#include "messageapi.h"
#include "QtNetwork/QtNetwork"
#include "QDebug"
#include "stdio.h"
#include "broadcastservice.h"
#include "stdlib.h"

BroadcastService::BroadcastService(QString address = "255.255.255.255", qint16 port = 5683)
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


void BroadcastService::sendMessage(QString message, UdpMessage::UdpMessageType type, QString groupname = "ALL_HOSTS"){
    sendMessage(new UdpMessage(UdpUser().Anyone, message, type, groupname));
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
    QString messageData = message->IntendedUser->Username.trimmed() + controlChar + // IntendedUser
            message->SenderUser->Username.trimmed() + controlChar +                 // SenderUser
            message->SenderUser->Alias.trimmed() + controlChar +                    // SenderAlias
            QString(message->SenderUser->AdminLevel + 0x30) + controlChar +        // AdminLevel
            (((int)message->MessageType)+0x30) + controlChar +                      // MessageType
            message->GroupName + controlChar +                                      // GroupName
            QString(getApiLevel() + 0x30) + controlChar +                      // ApiLevel
            message->Message.trimmed();                                             // Message
    if(message->CustomFields.count() > 0){                                          // Custom Fields
        for(int i = 0; i < message->CustomFields.count(); i++){
            messageData += (controlChar + message->CustomFields[i]);
        }
    }
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
             UdpMessage* newMessage = UdpMessage().parseMessage(QString().fromUtf8(datagram.data(),datagram.size()));
             if(newMessage->GroupName == "ALL_HOSTS"){
                emit OnMessageRecieved(newMessage);
             }else if(messageGroups.contains(newMessage->GroupName)){
                emit OnMessageRecieved(newMessage);
             }
    }
}

void BroadcastService::joinGroup(QString GroupName){
    if(!messageGroups.contains(GroupName)){
        messageGroups.append(GroupName);
        qDebug() << QString("Joined Group: " + GroupName);
    }
}

void BroadcastService::leaveGroup(QString GroupName){
    if(messageGroups.contains(GroupName)){
        messageGroups.removeAt(messageGroups.indexOf(GroupName));
        qDebug() << QString("Left Group: " + GroupName);
    }
}

int BroadcastService::getApiLevel(){
    return API_LEVEL;
}

