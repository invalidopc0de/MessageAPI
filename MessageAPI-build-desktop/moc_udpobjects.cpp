/****************************************************************************
** Meta object code from reading C++ file 'udpobjects.h'
**
** Created: Fri Apr 22 11:12:45 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MessageAPI/udpobjects.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'udpobjects.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UdpUser[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_UdpUser[] = {
    "UdpUser\0"
};

const QMetaObject UdpUser::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UdpUser,
      qt_meta_data_UdpUser, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UdpUser::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UdpUser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UdpUser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UdpUser))
        return static_cast<void*>(const_cast< UdpUser*>(this));
    return QObject::qt_metacast(_clname);
}

int UdpUser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_UdpMessage[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_UdpMessage[] = {
    "UdpMessage\0"
};

const QMetaObject UdpMessage::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UdpMessage,
      qt_meta_data_UdpMessage, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UdpMessage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UdpMessage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UdpMessage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UdpMessage))
        return static_cast<void*>(const_cast< UdpMessage*>(this));
    return QObject::qt_metacast(_clname);
}

int UdpMessage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
