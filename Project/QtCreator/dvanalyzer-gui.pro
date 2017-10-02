QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32|macx {
TARGET = "DV Analyzer"
} else {
TARGET = "dvanalyzer-gui"
}

win32 {
    RC_FILE = dvanalyzer-gui.rc
    contains(QT_ARCH, i386): DESTDIR = Win32
    contains(QT_ARCH, x86_64): DESTDIR = x64
}

macx {
    LIBS += -framework CoreFoundation -framework ApplicationServices
    QMAKE_INFO_PLIST = ../Mac/Info.plist
    ICON = ../Mac/Logo.icns

    contains(MACSTORE, yes|1) {
        QMAKE_CFLAGS += -gdwarf-2
        QMAKE_CXXFLAGS += -gdwarf-2
        QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.7
    }
}

unix {
    CONFIG += link_pkgconfig
    isEmpty(BINDIR): BINDIR = /usr/bin
    target.path = $$BINDIR
    INSTALLS += target
}

TEMPLATE = app

CONFIG += qt release
CONFIG += no_keywords

DEFINES          +=  _UNICODE

!defined(packagesExist, test) {
    defineTest(packagesExist) {
        system(pkg-config $$ARGS): return(true)
        return(false)
    }
}

unix:exists(../../../MediaInfoLib/Project/GNU/Library/libmediainfo-config) {
    INCLUDEPATH      += ../../../MediaInfoLib/Source
    contains(STATIC_LIBS, yes|1) {
        LIBS             += $$system(../../../MediaInfoLib/Project/GNU/Library/libmediainfo-config LIBS_Static)
        message("custom libmediainfo: yes (static)")
    } else {
        LIBS             += $$system(../../../MediaInfoLib/Project/GNU/Library/libmediainfo-config LIBS)
        message("custom libmediainfo: yes (shared)")
    }
} else:unix {
    !packagesExist(libmediainfo) {
        error("libmediainfo not found on system")
    }
    LIBS += $$system(pkg-config --libs libmediainfo)
}

unix:exists(../../../ZenLib/Project/GNU/Library/libzen-config) {
    INCLUDEPATH      += ../../../ZenLib/Source
    contains(STATIC_LIBS, yes|1) {
        LIBS             += $$system(../../../ZenLib/Project/GNU/Library/libzen-config LIBS_Static)
        message("custom libzen       : yes (static)")
    } else {
        LIBS             += $$system(../../../ZenLib/Project/GNU/Library/libzen-config LIBS)
        message("custom libzen       : yes (shared)")
    }
} else:unix {
    PKGCONFIG        += libzen
    message("libzen      : system")
}

SOURCES += \
        ../../Source/Common/Common_About.cpp \
        ../../Source/Common/Common_Help.cpp \
        ../../Source/Common/Core.cpp \
        ../../Source/GUI/Qt/App.cpp \
        ../../Source/GUI/Qt/GUI_About.cpp \
        ../../Source/GUI/Qt/GUI_Help.cpp \
        ../../Source/GUI/Qt/GUI_Main.cpp \
        ../../Source/GUI/Qt/GUI_Main_ByFrame_Table.cpp \
        ../../Source/GUI/Qt/GUI_Main_ByFrame_Text.cpp \
        ../../Source/GUI/Qt/GUI_Main_AppleXMLIFv3.cpp \
        ../../Source/GUI/Qt/GUI_Main_AppleXMLIFv4.cpp \
        ../../Source/GUI/Qt/GUI_Main_AppleXMLIFv5.cpp \
        ../../Source/GUI/Qt/GUI_Main_MediaInfo.cpp \
        ../../Source/GUI/Qt/GUI_Main_Menu.cpp \
        ../../Source/GUI/Qt/GUI_Main_Summary.cpp \
        ../../Source/GUI/Qt/GUI_Main_XML.cpp

HEADERS += \
        ../../Source/Common/Common_About.h \
        ../../Source/Common/Common_Help.h \
        ../../Source/Common/Core.h \
        ../../Source/GUI/Qt/App.h \
        ../../Source/GUI/Qt/GUI_About.h \
        ../../Source/GUI/Qt/GUI_Help.h \
        ../../Source/GUI/Qt/GUI_Main.h\
        ../../Source/GUI/Qt/GUI_Main_ByFrame_Table.h \
        ../../Source/GUI/Qt/GUI_Main_ByFrame_Text.h \
        ../../Source/GUI/Qt/GUI_Main_AppleXMLIFv3.h \
        ../../Source/GUI/Qt/GUI_Main_AppleXMLIFv4.h \
        ../../Source/GUI/Qt/GUI_Main_AppleXMLIFv5.h \
        ../../Source/GUI/Qt/GUI_Main_MediaInfo.h \
        ../../Source/GUI/Qt/GUI_Main_Summary.h \
        ../../Source/GUI/Qt/GUI_Main_XML.h

RESOURCES += ../../Source/Resource/GUI_Main.qrc

INCLUDEPATH += ../../Source ../../Source/GUI/Qt
