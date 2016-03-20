/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../robot_cli_0.4/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[25];
    char stringdata[362];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 7),
QT_MOC_LITERAL(2, 19, 0),
QT_MOC_LITERAL(3, 20, 15),
QT_MOC_LITERAL(4, 36, 15),
QT_MOC_LITERAL(5, 52, 5),
QT_MOC_LITERAL(6, 58, 4),
QT_MOC_LITERAL(7, 63, 24),
QT_MOC_LITERAL(8, 88, 14),
QT_MOC_LITERAL(9, 103, 15),
QT_MOC_LITERAL(10, 119, 9),
QT_MOC_LITERAL(11, 129, 4),
QT_MOC_LITERAL(12, 134, 8),
QT_MOC_LITERAL(13, 143, 19),
QT_MOC_LITERAL(14, 163, 19),
QT_MOC_LITERAL(15, 183, 19),
QT_MOC_LITERAL(16, 203, 19),
QT_MOC_LITERAL(17, 223, 19),
QT_MOC_LITERAL(18, 243, 19),
QT_MOC_LITERAL(19, 263, 19),
QT_MOC_LITERAL(20, 283, 15),
QT_MOC_LITERAL(21, 299, 15),
QT_MOC_LITERAL(22, 315, 15),
QT_MOC_LITERAL(23, 331, 15),
QT_MOC_LITERAL(24, 347, 14)
    },
    "MainWindow\0aPropos\0\0status_en_cours\0"
    "status_connecte\0char*\0toto\0"
    "status_erreur_connection\0openSerialPort\0"
    "closeSerialPort\0writeData\0data\0readData\0"
    "buttonTerminalText1\0buttonTerminalText2\0"
    "buttonTerminalText3\0buttonTerminalText4\0"
    "buttonTerminalText5\0buttonTerminalText6\0"
    "buttonTerminalText7\0buttonTerminal1\0"
    "buttonTerminal2\0buttonTerminal3\0"
    "buttonTerminal4\0buttonStartMPU"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  114,    2, 0x0a /* Public */,
       3,    0,  115,    2, 0x0a /* Public */,
       4,    1,  116,    2, 0x0a /* Public */,
       7,    0,  119,    2, 0x0a /* Public */,
       8,    0,  120,    2, 0x0a /* Public */,
       9,    0,  121,    2, 0x0a /* Public */,
      10,    1,  122,    2, 0x08 /* Private */,
      12,    0,  125,    2, 0x08 /* Private */,
      13,    0,  126,    2, 0x08 /* Private */,
      14,    0,  127,    2, 0x08 /* Private */,
      15,    0,  128,    2, 0x08 /* Private */,
      16,    0,  129,    2, 0x08 /* Private */,
      17,    0,  130,    2, 0x08 /* Private */,
      18,    0,  131,    2, 0x08 /* Private */,
      19,    0,  132,    2, 0x08 /* Private */,
      20,    0,  133,    2, 0x08 /* Private */,
      21,    0,  134,    2, 0x08 /* Private */,
      22,    0,  135,    2, 0x08 /* Private */,
      23,    0,  136,    2, 0x08 /* Private */,
      24,    0,  137,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->aPropos(); break;
        case 1: _t->status_en_cours(); break;
        case 2: _t->status_connecte((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 3: _t->status_erreur_connection(); break;
        case 4: _t->openSerialPort(); break;
        case 5: _t->closeSerialPort(); break;
        case 6: _t->writeData((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 7: _t->readData(); break;
        case 8: _t->buttonTerminalText1(); break;
        case 9: _t->buttonTerminalText2(); break;
        case 10: _t->buttonTerminalText3(); break;
        case 11: _t->buttonTerminalText4(); break;
        case 12: _t->buttonTerminalText5(); break;
        case 13: _t->buttonTerminalText6(); break;
        case 14: _t->buttonTerminalText7(); break;
        case 15: _t->buttonTerminal1(); break;
        case 16: _t->buttonTerminal2(); break;
        case 17: _t->buttonTerminal3(); break;
        case 18: _t->buttonTerminal4(); break;
        case 19: _t->buttonStartMPU(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
