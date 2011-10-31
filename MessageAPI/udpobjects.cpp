#include "messageapi.h"
#include "QtNetwork/QtNetwork"
#include "QDebug"
#include "stdio.h"

const QString UdpUser::Anyone = QString("ANY");
const QString UdpUser::Self = QString("SELF");
const QChar UdpMessage::controlChar = QChar(65533);

UdpUser::UdpUser()
{
    Username = "";
    Alias = "";
    AdminLevel = 0;
}

UdpUser::UdpUser(QString name)
{
    Username = name;
    Alias = "";
    AdminLevel = 0;
}

UdpUser::UdpUser(QString name, QString alias)
{
    Username = name;
    Alias = alias;
    AdminLevel = 0;
}

UdpMessage::UdpMessage(QString user, QString message, QString groupname = "ALL_HOSTS"){
    setupUser(user, message, this->Unknown, groupname);
}

UdpMessage::UdpMessage(QString user, QString message, UdpMessageType type, QString groupname = "ALL_HOSTS"){
    setupUser(user, message, type, groupname);
}

UdpMessage::UdpMessage(UdpUser& user, QString message, UdpMessageType type, QString groupname = "ALL_HOSTS")
{
    IntendedUser = &user;
    Message = message;
    MessageType = type;
    GroupName = groupname;
}

void UdpMessage::setupUser(QString user, QString userMessage, UdpMessageType type, QString groupname = "ALL_HOSTS")
{
    IntendedUser = new UdpUser(user);
    Message = userMessage;
    MessageType = type;
    GroupName = groupname;
}

UdpMessage::UdpMessageType UdpMessage::messageTypeFromString(QString type)
{
    if(type == "1")
            return this->WebsiteShare;
    else if(type == "2")
            return this->Chat;
    else if(type == "3")
            return this->System;
    else if(type == "4")
            return this->Error;
    else if(type == "5")
            return this->Whois;
    else
            return this->Unknown;
}

UdpMessage* UdpMessage::parseMessage(QString message){
    message = message.trimmed();
    qDebug() << message;
    //    int username = 0;
    //    int sendername = 0;
    //    int alias = 0;
    //    bool foundUsername = false;
    //    bool foundSenderName = false;
    //    bool foundAliasName = false;

    //    QChar x;
    //    for(int i = 0; i<message.length(); i++)
    //    {
    //        x = message.at(i);
    //        if (x == controlChar)
    //        {
    //            if (foundUsername == false)
    //            {
    //                foundUsername = true;
    //            } else if (foundSenderName == false)
    //            {
    //                foundSenderName = true;
    //            } else if (foundAliasName == false)
    //            {
    //                foundAliasName = true;
    //            }
    //            else
    //            {
    //                break;
    //            }
    //        }
    //        else
    //        {
    //            if(foundUsername == false) {
    //                username += 1;
    //            }
    //            else if (foundSenderName == false)
    //            {
    //                sendername += 1;
    //            } else if (foundAliasName == false)
    //            {
    //                alias += 1;
    //            }
    //        }
    //    }
    //    UdpMessage *newMessage = new UdpMessage();
    //    newMessage->IntendedUser = new UdpUser(message.mid(0, username));
    //    newMessage->SenderUser = new UdpUser(message.mid(username + 1, sendername), message.mid(username + sendername + 2, alias));
    //    newMessage->MessageType = newMessage->messageTypeFromString(message.mid((username + sendername + alias) + 3, 1));
    //    newMessage->Message = message.mid((username + sendername + alias) + 5, (message.length() - ((username + sendername + alias) + 5)));
    QList<QString> fields;
    QString buffer;
    for(int c = 0; c < message.length(); c++){
        if(message[c] == UdpMessage().controlChar){
            fields.append(buffer);
            buffer = "";
        } else {
            buffer.append(message[c]);
        }
    }
    fields.append(buffer);

    UdpMessage *newMessage = new UdpMessage();
    newMessage->IntendedUser = new UdpUser(fields[0]);
    newMessage->SenderUser = new UdpUser(fields[1], fields[2]);
    newMessage->SenderUser->AdminLevel = fields[3].toInt();
    newMessage->MessageType = newMessage->messageTypeFromString(fields[4]);
    newMessage->GroupName = fields[5];
    newMessage->ApiLevel = fields[6].toInt();
    newMessage->Message = fields[7];
    if(fields.count() > 8){
        for(int i = 8; i < fields.count(); i++){
            newMessage->CustomFields.append(fields[i]);
        }
    }

    buffer = "";
    qDebug() << fields.count();
    for(int i = 0; i < fields.count(); i++){
        buffer += QString(fields[i]) + ":";
    }
    //qDebug() << QString(newMessage->IntendedUser->Username + ":" + newMessage->SenderUser->Username +":" + newMessage->SenderUser->Alias + ":" + (((int)newMessage->MessageType)+0x30) + ":" + newMessage->Message);
    //qDebug() << (int) newMessage->MessageType;
    qDebug() << buffer;
    return newMessage;
}

QString UdpUser::getCurrentUser(){
    QString currentUser;
#ifdef Q_WS_X11 //Linux
    currentUser = QHostInfo().localHostName().toUpper() + "\\";
    currentUser += QString(getenv("USER"));
    qDebug() << currentUser;
#endif
#ifdef Q_WS_QWS //Embedded Linux
    currentUser = QHostInfo().localHostName().toUpper() + "\\";
    currentUser += QString(getenv("USER"));
#endif
#ifdef Q_WS_MAC // Mac
    currentUser = QHostInfo().localHostName().toUpper() + "\\";
    currentUser += QString(getenv("USER"));
#endif
#ifdef Q_WS_WIN //Windows
    currentUser = QString(getenv("USERNAME"));
#endif
    return currentUser;
}
