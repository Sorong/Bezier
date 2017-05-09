/****************************************************************************
** Meta object code from reading C++ file 'window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Bezier_t {
    QByteArrayData data[10];
    char stringdata0[98];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Bezier_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Bezier_t qt_meta_stringdata_Bezier = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Bezier"
QT_MOC_LITERAL(1, 7, 13), // "sliderToLabel"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 1), // "i"
QT_MOC_LITERAL(4, 24, 14), // "addCoordinates"
QT_MOC_LITERAL(5, 39, 13), // "keyPressEvent"
QT_MOC_LITERAL(6, 53, 10), // "QKeyEvent*"
QT_MOC_LITERAL(7, 64, 5), // "event"
QT_MOC_LITERAL(8, 70, 14), // "raiseElevation"
QT_MOC_LITERAL(9, 85, 12) // "getHodograph"

    },
    "Bezier\0sliderToLabel\0\0i\0addCoordinates\0"
    "keyPressEvent\0QKeyEvent*\0event\0"
    "raiseElevation\0getHodograph"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Bezier[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       4,    0,   42,    2, 0x0a /* Public */,
       5,    1,   43,    2, 0x0a /* Public */,
       8,    0,   46,    2, 0x0a /* Public */,
       9,    0,   47,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Bezier::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Bezier *_t = static_cast<Bezier *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sliderToLabel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->addCoordinates(); break;
        case 2: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 3: _t->raiseElevation(); break;
        case 4: _t->getHodograph(); break;
        default: ;
        }
    }
}

const QMetaObject Bezier::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Bezier.data,
      qt_meta_data_Bezier,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Bezier::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Bezier::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Bezier.stringdata0))
        return static_cast<void*>(const_cast< Bezier*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Bezier::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
