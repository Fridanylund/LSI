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
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LSIProjectGUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LSIProjectGUI_t {
    QByteArrayData data[18];
    char stringdata0[262];
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
QT_MOC_LITERAL(6, 114, 24), // "on_listROI_selectedItems"
QT_MOC_LITERAL(7, 139, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(8, 156, 4), // "item"
QT_MOC_LITERAL(9, 161, 15), // "mousePressEvent"
QT_MOC_LITERAL(10, 177, 12), // "QMouseEvent*"
QT_MOC_LITERAL(11, 190, 5), // "event"
QT_MOC_LITERAL(12, 196, 14), // "mouseMoveEvent"
QT_MOC_LITERAL(13, 211, 17), // "mouseReleaseEvent"
QT_MOC_LITERAL(14, 229, 6), // "update"
QT_MOC_LITERAL(15, 236, 8), // "makePlot"
QT_MOC_LITERAL(16, 245, 14), // "QVector<qreal>"
QT_MOC_LITERAL(17, 260, 1) // "a"

    },
    "LSIProjectGUI\0on_startButton_clicked\0"
    "\0on_stopButton_clicked\0"
    "on_createROIButton_clicked\0"
    "on_removeROIButton_clicked\0"
    "on_listROI_selectedItems\0QListWidgetItem*\0"
    "item\0mousePressEvent\0QMouseEvent*\0"
    "event\0mouseMoveEvent\0mouseReleaseEvent\0"
    "update\0makePlot\0QVector<qreal>\0a"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LSIProjectGUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    0,   65,    2, 0x0a /* Public */,
       4,    0,   66,    2, 0x0a /* Public */,
       5,    0,   67,    2, 0x0a /* Public */,
       6,    1,   68,    2, 0x0a /* Public */,
       9,    1,   71,    2, 0x0a /* Public */,
      12,    1,   74,    2, 0x0a /* Public */,
      13,    1,   77,    2, 0x0a /* Public */,
      14,    0,   80,    2, 0x0a /* Public */,
      15,    1,   81,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,

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
        case 4: _t->on_listROI_selectedItems((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 5: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 6: _t->mouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 7: _t->mouseReleaseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 8: _t->update(); break;
        case 9: _t->makePlot((*reinterpret_cast< QVector<qreal>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<qreal> >(); break;
            }
            break;
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
