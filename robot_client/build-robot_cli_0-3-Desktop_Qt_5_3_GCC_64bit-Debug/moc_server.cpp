/****************************************************************************
** Meta object code from reading C++ file 'server.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../robot_cli_0.4/server.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'server.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Server_t {
    QByteArrayData data[17];
    char stringdata[244];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Server_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Server_t qt_meta_stringdata_Server = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 10),
QT_MOC_LITERAL(2, 18, 0),
QT_MOC_LITERAL(3, 19, 5),
QT_MOC_LITERAL(4, 25, 8),
QT_MOC_LITERAL(5, 34, 16),
QT_MOC_LITERAL(6, 51, 18),
QT_MOC_LITERAL(7, 70, 13),
QT_MOC_LITERAL(8, 84, 26),
QT_MOC_LITERAL(9, 111, 24),
QT_MOC_LITERAL(10, 136, 24),
QT_MOC_LITERAL(11, 161, 13),
QT_MOC_LITERAL(12, 175, 8),
QT_MOC_LITERAL(13, 184, 10),
QT_MOC_LITERAL(14, 195, 12),
QT_MOC_LITERAL(15, 208, 28),
QT_MOC_LITERAL(16, 237, 6)
    },
    "Server\0on_connect\0\0char*\0mess_con\0"
    "on_error_connect\0dataServerReceived\0"
    "dataReadyRead\0on_boutonConnexion_clicked\0"
    "on_boutonEnvoyer_clicked\0"
    "on_message_returnPressed\0donneesRecues\0"
    "connecte\0deconnecte\0erreurSocket\0"
    "QAbstractSocket::SocketError\0erreur"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Server[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       5,    0,   72,    2, 0x06 /* Public */,
       6,    0,   73,    2, 0x06 /* Public */,
       7,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    0,   79,    2, 0x08 /* Private */,
      13,    0,   80,    2, 0x08 /* Private */,
      14,    1,   81,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,   16,

       0        // eod
};

void Server::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Server *_t = static_cast<Server *>(_o);
        switch (_id) {
        case 0: _t->on_connect((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 1: _t->on_error_connect(); break;
        case 2: _t->dataServerReceived(); break;
        case 3: _t->dataReadyRead(); break;
        case 4: _t->on_boutonConnexion_clicked(); break;
        case 5: _t->on_boutonEnvoyer_clicked(); break;
        case 6: _t->on_message_returnPressed(); break;
        case 7: _t->donneesRecues(); break;
        case 8: _t->connecte(); break;
        case 9: _t->deconnecte(); break;
        case 10: _t->erreurSocket((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Server::*_t)(char * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Server::on_connect)) {
                *result = 0;
            }
        }
        {
            typedef void (Server::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Server::on_error_connect)) {
                *result = 1;
            }
        }
        {
            typedef void (Server::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Server::dataServerReceived)) {
                *result = 2;
            }
        }
        {
            typedef void (Server::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Server::dataReadyRead)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject Server::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Server.data,
      qt_meta_data_Server,  qt_static_metacall, 0, 0}
};


const QMetaObject *Server::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Server::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Server.stringdata))
        return static_cast<void*>(const_cast< Server*>(this));
    return QWidget::qt_metacast(_clname);
}

int Server::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Server::on_connect(char * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Server::on_error_connect()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Server::dataServerReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void Server::dataReadyRead()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
