/****************************************************************************
** Meta object code from reading C++ file 'udpclient.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../udpclient.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'udpclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSUdpClientENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSUdpClientENDCLASS = QtMocHelpers::stringData(
    "UdpClient",
    "messageReceived",
    "",
    "message",
    "msgLogin",
    "msgDelivery",
    "msgPickup",
    "msgRegister",
    "processPendingDatagrams",
    "sendMessage",
    "host",
    "port",
    "bindSocket"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSUdpClientENDCLASS_t {
    uint offsetsAndSizes[26];
    char stringdata0[10];
    char stringdata1[16];
    char stringdata2[1];
    char stringdata3[8];
    char stringdata4[9];
    char stringdata5[12];
    char stringdata6[10];
    char stringdata7[12];
    char stringdata8[24];
    char stringdata9[12];
    char stringdata10[5];
    char stringdata11[5];
    char stringdata12[11];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSUdpClientENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSUdpClientENDCLASS_t qt_meta_stringdata_CLASSUdpClientENDCLASS = {
    {
        QT_MOC_LITERAL(0, 9),  // "UdpClient"
        QT_MOC_LITERAL(10, 15),  // "messageReceived"
        QT_MOC_LITERAL(26, 0),  // ""
        QT_MOC_LITERAL(27, 7),  // "message"
        QT_MOC_LITERAL(35, 8),  // "msgLogin"
        QT_MOC_LITERAL(44, 11),  // "msgDelivery"
        QT_MOC_LITERAL(56, 9),  // "msgPickup"
        QT_MOC_LITERAL(66, 11),  // "msgRegister"
        QT_MOC_LITERAL(78, 23),  // "processPendingDatagrams"
        QT_MOC_LITERAL(102, 11),  // "sendMessage"
        QT_MOC_LITERAL(114, 4),  // "host"
        QT_MOC_LITERAL(119, 4),  // "port"
        QT_MOC_LITERAL(124, 10)   // "bindSocket"
    },
    "UdpClient",
    "messageReceived",
    "",
    "message",
    "msgLogin",
    "msgDelivery",
    "msgPickup",
    "msgRegister",
    "processPendingDatagrams",
    "sendMessage",
    "host",
    "port",
    "bindSocket"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSUdpClientENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   62,    2, 0x06,    1 /* Public */,
       4,    1,   65,    2, 0x06,    3 /* Public */,
       5,    1,   68,    2, 0x06,    5 /* Public */,
       6,    1,   71,    2, 0x06,    7 /* Public */,
       7,    1,   74,    2, 0x06,    9 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    0,   77,    2, 0x08,   11 /* Private */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       9,    3,   78,    2, 0x02,   12 /* Public */,
      12,    1,   85,    2, 0x02,   16 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::UShort,    3,   10,   11,
    QMetaType::Void, QMetaType::UShort,   11,

       0        // eod
};

Q_CONSTINIT const QMetaObject UdpClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSUdpClientENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSUdpClientENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSUdpClientENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<UdpClient, std::true_type>,
        // method 'messageReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'msgLogin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'msgDelivery'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'msgPickup'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'msgRegister'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'processPendingDatagrams'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint16, std::false_type>,
        // method 'bindSocket'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint16, std::false_type>
    >,
    nullptr
} };

void UdpClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UdpClient *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->messageReceived((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->msgLogin((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->msgDelivery((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->msgPickup((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->msgRegister((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->processPendingDatagrams(); break;
        case 6: _t->sendMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<quint16>>(_a[3]))); break;
        case 7: _t->bindSocket((*reinterpret_cast< std::add_pointer_t<quint16>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (UdpClient::*)(const QString & );
            if (_t _q_method = &UdpClient::messageReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (UdpClient::*)(const QString & );
            if (_t _q_method = &UdpClient::msgLogin; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (UdpClient::*)(const QString & );
            if (_t _q_method = &UdpClient::msgDelivery; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (UdpClient::*)(const QString & );
            if (_t _q_method = &UdpClient::msgPickup; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (UdpClient::*)(const QString & );
            if (_t _q_method = &UdpClient::msgRegister; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject *UdpClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UdpClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSUdpClientENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int UdpClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void UdpClient::messageReceived(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UdpClient::msgLogin(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UdpClient::msgDelivery(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void UdpClient::msgPickup(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void UdpClient::msgRegister(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
