/****************************************************************************
** Meta object code from reading C++ file 'bezierscreen.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../bezierscreen.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bezierscreen.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BezierScreen_t {
    QByteArrayData data[7];
    char stringdata0[73];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BezierScreen_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BezierScreen_t qt_meta_stringdata_BezierScreen = {
    {
QT_MOC_LITERAL(0, 0, 12), // "BezierScreen"
QT_MOC_LITERAL(1, 13, 4), // "setT"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 1), // "t"
QT_MOC_LITERAL(4, 21, 14), // "raiseElevation"
QT_MOC_LITERAL(5, 36, 17), // "toggleSublineMode"
QT_MOC_LITERAL(6, 54, 18) // "calculateHodograph"

    },
    "BezierScreen\0setT\0\0t\0raiseElevation\0"
    "toggleSublineMode\0calculateHodograph"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BezierScreen[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       4,    0,   37,    2, 0x0a /* Public */,
       5,    0,   38,    2, 0x0a /* Public */,
       6,    0,   39,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BezierScreen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BezierScreen *_t = static_cast<BezierScreen *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setT((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->raiseElevation(); break;
        case 2: _t->toggleSublineMode(); break;
        case 3: _t->calculateHodograph(); break;
        default: ;
        }
    }
}

const QMetaObject BezierScreen::staticMetaObject = {
    { &QOpenGLWidget::staticMetaObject, qt_meta_stringdata_BezierScreen.data,
      qt_meta_data_BezierScreen,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BezierScreen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BezierScreen::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BezierScreen.stringdata0))
        return static_cast<void*>(const_cast< BezierScreen*>(this));
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(const_cast< BezierScreen*>(this));
    return QOpenGLWidget::qt_metacast(_clname);
}

int BezierScreen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
