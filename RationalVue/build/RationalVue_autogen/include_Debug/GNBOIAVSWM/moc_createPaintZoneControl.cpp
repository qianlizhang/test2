/****************************************************************************
** Meta object code from reading C++ file 'createPaintZoneControl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gui/PaintZone/createPaintZoneControl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'createPaintZoneControl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CCreatePaintZoneControl_t {
    QByteArrayData data[16];
    char stringdata0[337];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CCreatePaintZoneControl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CCreatePaintZoneControl_t qt_meta_stringdata_CCreatePaintZoneControl = {
    {
QT_MOC_LITERAL(0, 0, 23), // "CCreatePaintZoneControl"
QT_MOC_LITERAL(1, 24, 15), // "sendRectClicked"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 6), // "string"
QT_MOC_LITERAL(4, 48, 21), // "on_toolButton_clicked"
QT_MOC_LITERAL(5, 70, 23), // "on_toolButton_2_clicked"
QT_MOC_LITERAL(6, 94, 23), // "on_toolButton_3_clicked"
QT_MOC_LITERAL(7, 118, 23), // "on_toolButton_4_clicked"
QT_MOC_LITERAL(8, 142, 23), // "on_toolButton_5_clicked"
QT_MOC_LITERAL(9, 166, 23), // "on_toolButton_6_clicked"
QT_MOC_LITERAL(10, 190, 23), // "on_toolButton_7_clicked"
QT_MOC_LITERAL(11, 214, 23), // "on_toolButton_8_clicked"
QT_MOC_LITERAL(12, 238, 23), // "on_toolButton_9_clicked"
QT_MOC_LITERAL(13, 262, 24), // "on_toolButton_10_clicked"
QT_MOC_LITERAL(14, 287, 24), // "on_toolButton_16_clicked"
QT_MOC_LITERAL(15, 312, 24) // "on_toolButton_18_clicked"

    },
    "CCreatePaintZoneControl\0sendRectClicked\0"
    "\0string\0on_toolButton_clicked\0"
    "on_toolButton_2_clicked\0on_toolButton_3_clicked\0"
    "on_toolButton_4_clicked\0on_toolButton_5_clicked\0"
    "on_toolButton_6_clicked\0on_toolButton_7_clicked\0"
    "on_toolButton_8_clicked\0on_toolButton_9_clicked\0"
    "on_toolButton_10_clicked\0"
    "on_toolButton_16_clicked\0"
    "on_toolButton_18_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CCreatePaintZoneControl[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   82,    2, 0x0a /* Public */,
       5,    0,   83,    2, 0x0a /* Public */,
       6,    0,   84,    2, 0x0a /* Public */,
       7,    0,   85,    2, 0x0a /* Public */,
       8,    0,   86,    2, 0x0a /* Public */,
       9,    0,   87,    2, 0x0a /* Public */,
      10,    0,   88,    2, 0x0a /* Public */,
      11,    0,   89,    2, 0x0a /* Public */,
      12,    0,   90,    2, 0x0a /* Public */,
      13,    0,   91,    2, 0x0a /* Public */,
      14,    0,   92,    2, 0x0a /* Public */,
      15,    0,   93,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
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

void CCreatePaintZoneControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CCreatePaintZoneControl *_t = static_cast<CCreatePaintZoneControl *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendRectClicked((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 1: _t->on_toolButton_clicked(); break;
        case 2: _t->on_toolButton_2_clicked(); break;
        case 3: _t->on_toolButton_3_clicked(); break;
        case 4: _t->on_toolButton_4_clicked(); break;
        case 5: _t->on_toolButton_5_clicked(); break;
        case 6: _t->on_toolButton_6_clicked(); break;
        case 7: _t->on_toolButton_7_clicked(); break;
        case 8: _t->on_toolButton_8_clicked(); break;
        case 9: _t->on_toolButton_9_clicked(); break;
        case 10: _t->on_toolButton_10_clicked(); break;
        case 11: _t->on_toolButton_16_clicked(); break;
        case 12: _t->on_toolButton_18_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CCreatePaintZoneControl::*_t)(string );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CCreatePaintZoneControl::sendRectClicked)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject CCreatePaintZoneControl::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CCreatePaintZoneControl.data,
      qt_meta_data_CCreatePaintZoneControl,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CCreatePaintZoneControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CCreatePaintZoneControl::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CCreatePaintZoneControl.stringdata0))
        return static_cast<void*>(const_cast< CCreatePaintZoneControl*>(this));
    if (!strcmp(_clname, "CCommonData"))
        return static_cast< CCommonData*>(const_cast< CCreatePaintZoneControl*>(this));
    return QWidget::qt_metacast(_clname);
}

int CCreatePaintZoneControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void CCreatePaintZoneControl::sendRectClicked(string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
