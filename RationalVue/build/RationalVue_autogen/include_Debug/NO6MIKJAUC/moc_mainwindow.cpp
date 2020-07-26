/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gui/MainWindow/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[327];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 13), // "switchLanToEn"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 6), // "string"
QT_MOC_LITERAL(4, 33, 3), // "lan"
QT_MOC_LITERAL(5, 37, 13), // "switchLanToCh"
QT_MOC_LITERAL(6, 51, 21), // "onShowContextCategory"
QT_MOC_LITERAL(7, 73, 2), // "on"
QT_MOC_LITERAL(8, 76, 10), // "onWpsStyle"
QT_MOC_LITERAL(9, 87, 30), // "onMenuButtonPopupCheckableTest"
QT_MOC_LITERAL(10, 118, 1), // "b"
QT_MOC_LITERAL(11, 120, 27), // "onInstantPopupCheckableTest"
QT_MOC_LITERAL(12, 148, 27), // "onDelayedPopupCheckableTest"
QT_MOC_LITERAL(13, 176, 35), // "onMenuButtonPopupCheckabletri..."
QT_MOC_LITERAL(14, 212, 32), // "onInstantPopupCheckabletriggered"
QT_MOC_LITERAL(15, 245, 32), // "onDelayedPopupCheckabletriggered"
QT_MOC_LITERAL(16, 278, 16), // "selectLanguageEn"
QT_MOC_LITERAL(17, 295, 16), // "selectLanguageCh"
QT_MOC_LITERAL(18, 312, 14) // "switchLanguage"

    },
    "MainWindow\0switchLanToEn\0\0string\0lan\0"
    "switchLanToCh\0onShowContextCategory\0"
    "on\0onWpsStyle\0onMenuButtonPopupCheckableTest\0"
    "b\0onInstantPopupCheckableTest\0"
    "onDelayedPopupCheckableTest\0"
    "onMenuButtonPopupCheckabletriggered\0"
    "onInstantPopupCheckabletriggered\0"
    "onDelayedPopupCheckabletriggered\0"
    "selectLanguageEn\0selectLanguageCh\0"
    "switchLanguage"
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
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       5,    1,   82,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   85,    2, 0x08 /* Private */,
       8,    1,   88,    2, 0x08 /* Private */,
       9,    1,   91,    2, 0x08 /* Private */,
      11,    1,   94,    2, 0x08 /* Private */,
      12,    1,   97,    2, 0x08 /* Private */,
      13,    1,  100,    2, 0x08 /* Private */,
      14,    1,  103,    2, 0x08 /* Private */,
      15,    1,  106,    2, 0x08 /* Private */,
      16,    0,  109,    2, 0x08 /* Private */,
      17,    0,  110,    2, 0x08 /* Private */,
      18,    1,  111,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->switchLanToEn((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 1: _t->switchLanToCh((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 2: _t->onShowContextCategory((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->onWpsStyle((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->onMenuButtonPopupCheckableTest((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->onInstantPopupCheckableTest((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->onDelayedPopupCheckableTest((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->onMenuButtonPopupCheckabletriggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->onInstantPopupCheckabletriggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->onDelayedPopupCheckabletriggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->selectLanguageEn(); break;
        case 11: _t->selectLanguageCh(); break;
        case 12: _t->switchLanguage((*reinterpret_cast< string(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(string );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::switchLanToEn)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(string );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::switchLanToCh)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &SARibbonMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "CCommonData"))
        return static_cast< CCommonData*>(const_cast< MainWindow*>(this));
    return SARibbonMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SARibbonMainWindow::qt_metacall(_c, _id, _a);
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
void MainWindow::switchLanToEn(string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::switchLanToCh(string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
