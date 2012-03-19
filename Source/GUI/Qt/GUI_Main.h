// GUI_Main - WxWidgets GUI for MediaInfo
// Copyright (C) 2009-2009 AudioVisual Preservation Solutions, dv@avpreserve.com
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// WxWidgets GUI for MediaInfo
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifndef GUI_MainH
#define GUI_MainH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QAction>
#include <QtGui/QActionGroup>
#include <QtGui/QToolBar>
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifdef MEDIAINFO_DLL
    #include "MediaInfoDLL/MediaInfoDLL.h"
    #define MediaInfoNameSpace MediaInfoDLL
#elif defined MEDIAINFO_STATIC
    #include "MediaInfoDLL/MediaInfoDLL_Static.h"
    #define MediaInfoNameSpace MediaInfoDLL
#else
    #include "MediaInfo/MediaInfoList.h"
    #define MediaInfoNameSpace MediaInfoLib
#endif
using namespace MediaInfoNameSpace;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
class Core;
class FileDrop;
class QWidget;
class QDropEvent;
class QDragEnterEvent;
class QTabWidget;
class QProgressDialog;
class QTimer;
//---------------------------------------------------------------------------

//***************************************************************************
// GUI_Main
//***************************************************************************

class GUI_Main : public QMainWindow
{
     Q_OBJECT

public:
    GUI_Main (Core* _C);
    ~GUI_Main ();

 private:
    //Menu - List
    void Menu_Create();
    QTabWidget*     Central;
    QMenu*          Menu_File;
    QAction*        Menu_File_Open_Files;
    QAction*        Menu_File_Open_Directory;
    QAction*        Menu_File_Quit;
    QMenu*          Menu_View;
    QAction*        Menu_View_Summary;
    QAction*        Menu_View_ByFrame_Table;
    QAction*        Menu_View_ByFrame_Text;
    QAction*        Menu_View_XML;
    QAction*        Menu_View_AppleXMLIFv3;
    QAction*        Menu_View_AppleXMLIFv4;
    QAction*        Menu_View_AppleXMLIFv5;
    QAction*        Menu_View_MediaInfo;
    QActionGroup*   Menu_View_Group;
    QActionGroup*   Menu_Options_Verbosity_Group;
    QMenu*          Menu_Export;
    QAction*        Menu_Export_Summary;
    QAction*        Menu_Export_ByFrame;
    QAction*        Menu_Export_XML;
    QAction*        Menu_Export_AppleXMLIFv3;
    QAction*        Menu_Export_AppleXMLIFv4;
    QAction*        Menu_Export_AppleXMLIFv5;
    QAction*        Menu_Export_MediaInfo_Text;
    QAction*        Menu_Export_MediaInfo_XML;
    QMenu*          Menu_Options;
    QMenu*          Menu_Options_Verbosity;
    QAction*        Menu_Options_Verbosity_03;
    QAction*        Menu_Options_Verbosity_05;
    QAction*        Menu_Options_Verbosity_09;
    QAction*        Menu_Options_Verbosity_10;
    QMenu*          Menu_Options_MediaInfo;
    QAction*        Menu_Options_MediaInfo_InternalFields;
    QAction*        Menu_Options_MediaInfo_RawFieldsNames;
    QAction*        Menu_Options_ResetFieldSizes;
    QMenu*          Menu_Help;
    QAction*        Menu_Help_Help;
    QAction*        Menu_Help_About;
    QAction*        Menu_Help_AVPS_Website;
    QAction*        Menu_Help_DvAnalyzer_Website;

 private slots:
    //Menu - Actions
    void OnMenu_File_Open_Files                 ();
    void OnMenu_File_Open_Directory             ();
    void OnMenu_View_Summary                    ();
    void OnMenu_View_ByFrame_Table              ();
    void OnMenu_View_ByFrame_Text               ();
    void OnMenu_View_XML                        ();
    void OnMenu_View_AppleXMLIFv3               ();
    void OnMenu_View_AppleXMLIFv4               ();
    void OnMenu_View_AppleXMLIFv5               ();
    void OnMenu_View_MediaInfo                  ();
    void OnMenu_Options_Verbosity_03            ();
    void OnMenu_Options_Verbosity_05            ();
    void OnMenu_Options_Verbosity_09            ();
    void OnMenu_Options_Verbosity_10            ();
    void OnMenu_Export_Summary                  ();
    void OnMenu_Export_ByFrame                  ();
    void OnMenu_Export_XML                      ();
    void OnMenu_Export_AppleXMLIFv3             ();
    void OnMenu_Export_AppleXMLIFv4             ();
    void OnMenu_Export_AppleXMLIFv5             ();
    void OnMenu_Export_MediaInfo_Text           ();
    void OnMenu_Export_MediaInfo_XML            ();
    void OnMenu_Options_ResetFieldSizes         ();
    void OnMenu_Options_MediaInfo_InternalFields();
    void OnMenu_Options_MediaInfo_RawFieldsNames();
    void OnMenu_Help_Help                       ();
    void OnMenu_Help_About                      ();
    void OnMenu_Help_AVPS_Website               ();
    void OnMenu_Help_DvAnalyzer_Website         ();
    void OnCurrentChanged                       (int Index);
    void OnOpen_Timer                           ();

private:
    //ToolBar - List
    QToolBar*  ToolBar;

    //ToolBar - Actions
    void ToolBar_Create();

private:
    //Non-GUI Elements
    Core* C;

    //GUI
    QWidget* View;
    enum view
    {
        View_Summary,
        View_ByFrame_Table,
        View_ByFrame_Text,
        View_XML,
        View_AppleXMLIFv3,
        View_AppleXMLIFv4,
        View_AppleXMLIFv5,
        View_MediaInfo,
        View_None,
    };
    view View_Current;
    bool MustCreate;

    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    QProgressDialog* ProgressDialog;
    QTimer* Timer;

    //Helpers
    void View_Refresh(view View_New=View_None);
    void Open_Timer_Init ();

};

#endif
