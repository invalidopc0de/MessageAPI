#ifndef UDPOBJECTS_H
#define UDPOBJECTS_H

#include <QObject>

class  UdpUser : public QObject
{
    Q_OBJECT
public:
    //! Username
    /*!
      The network-friendly username of the User
      */
    QString Username;

    //! Alias
    /*!
      The alias of the User
      */
    QString Alias;

    //! Admin Level
    /*!
      The Admin Privilege Level of the User
      */
    int AdminLevel;

    //! Anyone Username
    /*!
      A special username which when specified sends a message everyone who is listening
      */
    static const QString Anyone;

    //! Self Username
    /*!
      A special username which when specified sends a message only to the user who sent it.
      */
    static const QString Self;

    //! UdpUser Constructor
    /*!
      Creates an empty UdpUser
      */
    UdpUser();

    //! UdpUser Constructor
    /*!
      Creates a UdpUser with a specified username
      \param name the username to create the UdpUser with
      */
    UdpUser(QString);

    //! UdpUser Constructor
    /*!
      Creates a UdpUser which a specified username and alias
      \param name the username to create the UdpUser with
      \param alias the alias to create the UdpUser with
      */
    UdpUser(QString, QString);

    //! Get the Current User
    /*!
      Gets the network-friendly username of the current logged in user.
      \return the username of the current user
      */
    QString getCurrentUser();
};

class UdpMessage : public QObject
{
    Q_OBJECT
public:
    //! Message Type
    /*!
      This enum is used to specify what the type of the UdpMessage is.
      */
    enum UdpMessageType {Unknown, /*!< Message Type Unknown */
                         WebsiteShare, /*!< Message Type WebsiteShare */
                         Chat, /*!< Message Type Chat */
                         System, /*!< Message Type System */
                         Error, /*!< Message Type Error */
                         Whois, /*!< Message Type Whois */
                         Custom /*!< Message Type Custom */
                        };
    UdpMessage() {}
    //! UdpMessage Constructor
    /*!
      Creates a new UdpMessage.
      \param user the username of the recipient user
      \param message the message to send
      */
    UdpMessage(QString, QString);
    //! UdpMessage Constructor
    /*!
      Creates a new UdpMessage.
      \param user the username of the recipient user
      \param message the message to send
      \param type the type of the message
      */
    UdpMessage(QString, QString, UdpMessageType);
    //! UdpMessage Constructor
    /*!
      Creates a new UdpMessage.
      \param user a UdpUser specifying the recipent of the message
      \param message the message to send
      \param type the type of the message
      */
    UdpMessage(UdpUser&, QString, UdpMessageType);
    //! Find UdpMessageType from QString
    /*!
      This is used to find a UdpMessage::UdpMessageType from a given string
      \param type the string from which the UdpMessage::UdpMessageType is found
      \return a UdpMessage::UdpMessageType from the string. Returns type "Unknown" if the string doesn't match any known types
      */
    UdpMessageType messageTypeFromString(QString);
    virtual ~UdpMessage() {}

    //! Intended User
    /*!
      Specifies the intended recipent of the message
      */
    UdpUser *IntendedUser;

    //! Sender User
    /*!
      Specifies the user who send the message
      */
    UdpUser *SenderUser;

    //! Message Data
    /*!
      The actually string data contained in the message
      */
    QString Message;

    //! Message Type
    /*!
      Specifies what type the message is.
      */
    UdpMessageType MessageType;

    //! Group Name
    /*!
      The group to which the message is addressed to.
      */
    QString GroupName;

    //! Api Level
    /*!
      The API Level of the client which created the message
      */
    int ApiLevel;

    //! Custom Fields
    /*!
      Fields which can be attached to the message which are not part of the MessageAPI Protocol
      */
    QList<QString> CustomFields;

    //! Parse Message from QString
    /*!
      Takes a Message in string from (such as from a network stream) and parses it into a UdpMessage
      \param message the string to parse
      \return the UdpMessage that was parsed from the string
      */
    UdpMessage* parseMessage(QString);

    //! Control Char
    /*!
      The control char is used to separate the individual elements when the UdpMessage is in string form
      */
    static const QChar controlChar;
private:
    void setupUser(QString, QString, UdpMessageType);
};

#endif // UDPOBJECTS_H
