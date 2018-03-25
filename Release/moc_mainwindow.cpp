/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../jlu-drcom-client-qt/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[18];
    char stringdata[370];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 22),
QT_MOC_LITERAL(2, 34, 0),
QT_MOC_LITERAL(3, 35, 20),
QT_MOC_LITERAL(4, 56, 23),
QT_MOC_LITERAL(5, 80, 31),
QT_MOC_LITERAL(6, 112, 27),
QT_MOC_LITERAL(7, 140, 22),
QT_MOC_LITERAL(8, 163, 33),
QT_MOC_LITERAL(9, 197, 6),
QT_MOC_LITERAL(10, 204, 14),
QT_MOC_LITERAL(11, 219, 10),
QT_MOC_LITERAL(12, 230, 24),
QT_MOC_LITERAL(13, 255, 4),
QT_MOC_LITERAL(14, 260, 26),
QT_MOC_LITERAL(15, 287, 27),
QT_MOC_LITERAL(16, 315, 24),
QT_MOC_LITERAL(17, 340, 28)
    },
    "MainWindow\0on_loginButton_clicked\0\0"
    "on_minButton_clicked\0on_actionExit_triggered\0"
    "on_actionLogin_Logout_triggered\0"
    "on_actionMinimize_triggered\0"
    "onActivitedSysTrayIcon\0"
    "QSystemTrayIcon::ActivationReason\0"
    "reason\0showMainAction\0exitAction\0"
    "on_checkBox_stateChanged\0arg1\0"
    "on_checkBox_2_stateChanged\0"
    "on_actionSettings_triggered\0"
    "on_actionAbout_triggered\0"
    "on_actionCheck_Log_triggered\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08,
       3,    0,   80,    2, 0x08,
       4,    0,   81,    2, 0x08,
       5,    0,   82,    2, 0x08,
       6,    0,   83,    2, 0x08,
       7,    1,   84,    2, 0x08,
      10,    0,   87,    2, 0x08,
      11,    0,   88,    2, 0x08,
      12,    1,   89,    2, 0x08,
      14,    1,   92,    2, 0x08,
      15,    0,   95,    2, 0x08,
      16,    0,   96,    2, 0x08,
      17,    0,   97,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int,   13,
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
        case 0: _t->on_loginButton_clicked(); break;
        case 1: _t->on_minButton_clicked(); break;
        case 2: _t->on_actionExit_triggered(); break;
        case 3: _t->on_actionLogin_Logout_triggered(); break;
        case 4: _t->on_actionMinimize_triggered(); break;
        case 5: _t->onActivitedSysTrayIcon((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 6: _t->showMainAction(); break;
        case 7: _t->exitAction(); break;
        case 8: _t->on_checkBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_checkBox_2_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_actionSettings_triggered(); break;
        case 11: _t->on_actionAbout_triggered(); break;
        case 12: _t->on_actionCheck_Log_triggered(); break;
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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
