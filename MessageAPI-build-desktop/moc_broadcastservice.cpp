/****************************************************************************
** Meta object code from reading C++ file 'broadcastservice.h'
**
** Created: Fri Apr 22 11:12:46 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MessageAPI/broadcastservice.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'broadcastservice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BroadcastService[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,
      41,   17,   17,   17, 0x05,
      72,   17,   17,   17, 0x05,
      88,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     107,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BroadcastService[] = {
    "BroadcastService\0\0OnServiceStarted(bool)\0"
    "OnMessageRecieved(UdpMessage*)\0"
    "OnMessageFail()\0OnMessageSuccess()\0"
    "processPendingDatagrams()\0"
};

const QMetaObject BroadcastService::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_BroadcastService,
      qt_meta_data_BroadcastService, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BroadcastService::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BroadcastService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BroadcastService::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BroadcastService))
        return static_cast<void*>(const_cast< BroadcastService*>(this));
    return QObject::qt_metacast(_clname);
}

int BroadcastService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnServiceStarted((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: OnMessageRecieved((*reinterpret_cast< UdpMessage*(*)>(_a[1]))); break;
        case 2: OnMessageFail(); break;
        case 3: OnMessageSuccess(); break;
        case 4: processPendingDatagrams(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void BroadcastService::OnServiceStarted(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BroadcastService::OnMessageRecieved(UdpMessage * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void BroadcastService::OnMessageFail()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void BroadcastService::OnMessageSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
