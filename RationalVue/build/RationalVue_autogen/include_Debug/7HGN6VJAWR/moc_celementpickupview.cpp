/****************************************************************************
** Meta object code from reading C++ file 'celementpickupview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gui/GraphiceZone/celementpickupview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'celementpickupview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CElementPickupView_t {
    QByteArrayData data[13];
    char stringdata0[168];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CElementPickupView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CElementPickupView_t qt_meta_stringdata_CElementPickupView = {
    {
QT_MOC_LITERAL(0, 0, 18), // "CElementPickupView"
QT_MOC_LITERAL(1, 19, 23), // "onScorllBarRangeChanged"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 3), // "min"
QT_MOC_LITERAL(4, 48, 3), // "max"
QT_MOC_LITERAL(5, 52, 6), // "zoomIn"
QT_MOC_LITERAL(6, 59, 7), // "zoomOut"
QT_MOC_LITERAL(7, 67, 16), // "showOriginalSize"
QT_MOC_LITERAL(8, 84, 15), // "showFitViewSize"
QT_MOC_LITERAL(9, 100, 17), // "rotate90Clockwise"
QT_MOC_LITERAL(10, 118, 21), // "rotate90AntiClockwise"
QT_MOC_LITERAL(11, 140, 9), // "rotate180"
QT_MOC_LITERAL(12, 150, 17) // "getViewEntireSize"

    },
    "CElementPickupView\0onScorllBarRangeChanged\0"
    "\0min\0max\0zoomIn\0zoomOut\0showOriginalSize\0"
    "showFitViewSize\0rotate90Clockwise\0"
    "rotate90AntiClockwise\0rotate180\0"
    "getViewEntireSize"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CElementPickupView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x08 /* Private */,
       5,    0,   64,    2, 0x0a /* Public */,
       6,    0,   65,    2, 0x0a /* Public */,
       7,    0,   66,    2, 0x0a /* Public */,
       8,    0,   67,    2, 0x0a /* Public */,
       9,    0,   68,    2, 0x0a /* Public */,
      10,    0,   69,    2, 0x0a /* Public */,
      11,    0,   70,    2, 0x0a /* Public */,
      12,    0,   71,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QSize,

       0        // eod
};

void CElementPickupView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CElementPickupView *_t = static_cast<CElementPickupView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onScorllBarRangeChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->zoomIn(); break;
        case 2: _t->zoomOut(); break;
        case 3: _t->showOriginalSize(); break;
        case 4: _t->showFitViewSize(); break;
        case 5: _t->rotate90Clockwise(); break;
        case 6: _t->rotate90AntiClockwise(); break;
        case 7: _t->rotate180(); break;
        case 8: { QSize _r = _t->getViewEntireSize();
            if (_a[0]) *reinterpret_cast< QSize*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject CElementPickupView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_CElementPickupView.data,
      qt_meta_data_CElementPickupView,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CElementPickupView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CElementPickupView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CElementPickupView.stringdata0))
        return static_cast<void*>(const_cast< CElementPickupView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int CElementPickupView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
