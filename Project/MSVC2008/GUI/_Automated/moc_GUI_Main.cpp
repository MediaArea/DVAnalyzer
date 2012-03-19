/****************************************************************************
** Meta object code from reading C++ file 'GUI_Main.h'
**
** Created: Fri 30. Apr 02:04:31 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Source/GUI/Qt/GUI_Main.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GUI_Main.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GUI_Main[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      31,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      35,    9,    9,    9, 0x08,
      64,    9,    9,    9, 0x08,
      86,    9,    9,    9, 0x08,
     114,    9,    9,    9, 0x08,
     141,    9,    9,    9, 0x08,
     159,    9,    9,    9, 0x08,
     186,    9,    9,    9, 0x08,
     213,    9,    9,    9, 0x08,
     240,    9,    9,    9, 0x08,
     264,    9,    9,    9, 0x08,
     294,    9,    9,    9, 0x08,
     324,    9,    9,    9, 0x08,
     354,    9,    9,    9, 0x08,
     384,    9,    9,    9, 0x08,
     408,    9,    9,    9, 0x08,
     432,    9,    9,    9, 0x08,
     452,    9,    9,    9, 0x08,
     481,    9,    9,    9, 0x08,
     510,    9,    9,    9, 0x08,
     539,    9,    9,    9, 0x08,
     570,    9,    9,    9, 0x08,
     600,    9,    9,    9, 0x08,
     633,    9,    9,    9, 0x08,
     675,    9,    9,    9, 0x08,
     717,    9,    9,    9, 0x08,
     736,    9,    9,    9, 0x08,
     756,    9,    9,    9, 0x08,
     783,    9,    9,    9, 0x08,
     822,  816,    9,    9, 0x08,
     844,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GUI_Main[] = {
    "GUI_Main\0\0OnMenu_File_Open_Files()\0"
    "OnMenu_File_Open_Directory()\0"
    "OnMenu_View_Summary()\0OnMenu_View_ByFrame_Table()\0"
    "OnMenu_View_ByFrame_Text()\0OnMenu_View_XML()\0"
    "OnMenu_View_AppleXMLIFv3()\0"
    "OnMenu_View_AppleXMLIFv4()\0"
    "OnMenu_View_AppleXMLIFv5()\0"
    "OnMenu_View_MediaInfo()\0"
    "OnMenu_Options_Verbosity_03()\0"
    "OnMenu_Options_Verbosity_05()\0"
    "OnMenu_Options_Verbosity_09()\0"
    "OnMenu_Options_Verbosity_10()\0"
    "OnMenu_Export_Summary()\0OnMenu_Export_ByFrame()\0"
    "OnMenu_Export_XML()\0OnMenu_Export_AppleXMLIFv3()\0"
    "OnMenu_Export_AppleXMLIFv4()\0"
    "OnMenu_Export_AppleXMLIFv5()\0"
    "OnMenu_Export_MediaInfo_Text()\0"
    "OnMenu_Export_MediaInfo_XML()\0"
    "OnMenu_Options_ResetFieldSizes()\0"
    "OnMenu_Options_MediaInfo_InternalFields()\0"
    "OnMenu_Options_MediaInfo_RawFieldsNames()\0"
    "OnMenu_Help_Help()\0OnMenu_Help_About()\0"
    "OnMenu_Help_AVPS_Website()\0"
    "OnMenu_Help_DvAnalyzer_Website()\0Index\0"
    "OnCurrentChanged(int)\0OnOpen_Timer()\0"
};

const QMetaObject GUI_Main::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_GUI_Main,
      qt_meta_data_GUI_Main, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GUI_Main::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GUI_Main::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GUI_Main::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GUI_Main))
        return static_cast<void*>(const_cast< GUI_Main*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int GUI_Main::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnMenu_File_Open_Files(); break;
        case 1: OnMenu_File_Open_Directory(); break;
        case 2: OnMenu_View_Summary(); break;
        case 3: OnMenu_View_ByFrame_Table(); break;
        case 4: OnMenu_View_ByFrame_Text(); break;
        case 5: OnMenu_View_XML(); break;
        case 6: OnMenu_View_AppleXMLIFv3(); break;
        case 7: OnMenu_View_AppleXMLIFv4(); break;
        case 8: OnMenu_View_AppleXMLIFv5(); break;
        case 9: OnMenu_View_MediaInfo(); break;
        case 10: OnMenu_Options_Verbosity_03(); break;
        case 11: OnMenu_Options_Verbosity_05(); break;
        case 12: OnMenu_Options_Verbosity_09(); break;
        case 13: OnMenu_Options_Verbosity_10(); break;
        case 14: OnMenu_Export_Summary(); break;
        case 15: OnMenu_Export_ByFrame(); break;
        case 16: OnMenu_Export_XML(); break;
        case 17: OnMenu_Export_AppleXMLIFv3(); break;
        case 18: OnMenu_Export_AppleXMLIFv4(); break;
        case 19: OnMenu_Export_AppleXMLIFv5(); break;
        case 20: OnMenu_Export_MediaInfo_Text(); break;
        case 21: OnMenu_Export_MediaInfo_XML(); break;
        case 22: OnMenu_Options_ResetFieldSizes(); break;
        case 23: OnMenu_Options_MediaInfo_InternalFields(); break;
        case 24: OnMenu_Options_MediaInfo_RawFieldsNames(); break;
        case 25: OnMenu_Help_Help(); break;
        case 26: OnMenu_Help_About(); break;
        case 27: OnMenu_Help_AVPS_Website(); break;
        case 28: OnMenu_Help_DvAnalyzer_Website(); break;
        case 29: OnCurrentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: OnOpen_Timer(); break;
        default: ;
        }
        _id -= 31;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
