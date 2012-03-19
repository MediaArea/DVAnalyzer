/****************************************************************************
** Meta object code from reading C++ file 'GUI_Main_ByFrame_Table.h'
**
** Created: Sun 18. Mar 15:52:03 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Source/GUI/Qt/GUI_Main_ByFrame_Table.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GUI_Main_ByFrame_Table.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GUI_Main_ByFrame_Table[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      28,   24,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GUI_Main_ByFrame_Table[] = {
    "GUI_Main_ByFrame_Table\0\0Pos\0"
    "Files_Changed(int)\0"
};

void GUI_Main_ByFrame_Table::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GUI_Main_ByFrame_Table *_t = static_cast<GUI_Main_ByFrame_Table *>(_o);
        switch (_id) {
        case 0: _t->Files_Changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GUI_Main_ByFrame_Table::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GUI_Main_ByFrame_Table::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GUI_Main_ByFrame_Table,
      qt_meta_data_GUI_Main_ByFrame_Table, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GUI_Main_ByFrame_Table::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GUI_Main_ByFrame_Table::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GUI_Main_ByFrame_Table::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GUI_Main_ByFrame_Table))
        return static_cast<void*>(const_cast< GUI_Main_ByFrame_Table*>(this));
    return QWidget::qt_metacast(_clname);
}

int GUI_Main_ByFrame_Table::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
