/****************************************************************************
** Meta object code from reading C++ file 'LSIProjectGUI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LSIProjectGUI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LSIProjectGUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LSIProjectGUI_t {
    QByteArrayData data[10];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LSIProjectGUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LSIProjectGUI_t qt_meta_stringdata_LSIProjectGUI = {
    {
QT_MOC_LITERAL(0, 0, 13), // "LSIProjectGUI"
QT_MOC_LITERAL(1, 14, 22), // "on_startButton_clicked"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 21), // "on_stopButton_clicked"
QT_MOC_LITERAL(4, 60, 26), // "on_createROIButton_clicked"
QT_MOC_LITERAL(5, 87, 26), // "on_removeROIButton_clicked"
QT_MOC_LITERAL(6, 114, 25), // "on_settingsButton_clicked"
QT_MOC_LITERAL(7, 140, 15), // "mousePressEvent"
QT_MOC_LITERAL(8, 156, 12), // "QMouseEvent*"
QT_MOC_LITERAL(9, 169, 2) // "ev"

    },
    "LSIProjectGUI\0on_startButton_clicked\0"
    "\0on_stopButton_clicked\0"
    "on_createROIButton_clicked\0"
    "on_removeROIButton_clicked\0"
    "on_settingsButton_clicked\0mousePressEvent\0"
    "QMouseEvent*\0ev"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LSIProjectGUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    1,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void LSIProjectGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LSIProjectGUI *_t = static_cast<LSIProjectGUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_startButton_clicked(); break;
        case 1: _t->on_stopButton_clicked(); break;
        case 2: _t->on_createROIButton_clicked(); break;
        case 3: _t->on_removeROIButton_clicked(); break;
        case 4: _t->on_settingsButton_clicked(); break;
        case 5: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject LSIProjectGUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_LSIProjectGUI.data,
      qt_meta_data_LSIProjectGUI,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LSIProjectGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LSIProjectGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LSIProjectGUI.stringdata0))
        return static_cast<void*>(const_cast< LSIProjectGUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int LSIProjectGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
