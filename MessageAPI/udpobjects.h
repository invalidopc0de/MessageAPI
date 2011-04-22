#ifndef UDPOBJECTS_H
#define UDPOBJECTS_H

#include <QObject>

class  UdpUser : public QObject
{
    Q_OBJECT
public:
    QString Username;
    QString Alias;
    static const QString Anyone;
    static const QString Self;
    UdpUser();
    UdpUser(QString);
    UdpUser(QString, QString);
    QString getCurrentUser();
};

class UdpMessage : public QObject
{
    Q_OBJECT
public:
    enum udpMessageType {Unknown, WebsiteShare, Chat, Whois};
    UdpMessage() {}
    UdpMessage(QString, QString);
    UdpMessage(QString, QString, udpMessageType);
    UdpMessage(UdpUser&, QString, udpMessageType);
    udpMessageType messageTypeFromString(QString);
    virtual ~UdpMessage() {}
    UdpUser *IntendedUser;
    UdpUser *SenderUser;
    QString Message;
    udpMessageType MessageType;
    UdpMessage* parseMessage(QString);
    static const QChar controlChar;
private:
    void setupUser(QString, QString, udpMessageType);
};

#endif // UDPOBJECTS_H
