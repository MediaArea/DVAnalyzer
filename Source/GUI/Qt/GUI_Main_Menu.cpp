// GUI_Main_Menu - WxWidgets GUI for MediaInfo, Menu
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

//---------------------------------------------------------------------------
//#include "GUI/WxWidgets/GUI_About.h"
#include "GUI/Qt/GUI_Main.h"
#include "Common/Core.h"
#include <QtGui/QMenuBar>
#include <QtGui/QToolBar>
#include <QtGui/QFileDialog>
#include <QtGui/QDesktopServices>
#include <QtGui/QApplication>
#include <QtCore/QUrl>
#include <QtCore/QEvent>
#include "GUI/Qt/GUI_About.h"
#include "ZenLib/ZtringList.h"
#include "ZenLib/File.h"
#include "GUI/Qt/GUI_Help.h"
using namespace ZenLib;
//---------------------------------------------------------------------------

//***************************************************************************
// Events
//***************************************************************************

//***************************************************************************
// Menu creation
//***************************************************************************

//---------------------------------------------------------------------------
void GUI_Main::Menu_Create()
{
    //File
    Menu_File_Open_Files = new QAction(QIcon(":/Image/Menu/File_Open_File.png"), tr("Open file(s)..."), this);
    Menu_File_Open_Files->setShortcut(tr("Ctrl+F"));
    Menu_File_Open_Files->setStatusTip(tr("Open file(s)"));
    connect(Menu_File_Open_Files, SIGNAL(triggered()), this, SLOT(OnMenu_File_Open_Files()));

    Menu_File_Open_Directory = new QAction(QIcon(":/Image/Menu/File_Open_Directory.png"), tr("Open Directory..."), this);
    Menu_File_Open_Directory->setShortcut(tr("Ctrl+D"));
    Menu_File_Open_Directory->setStatusTip(tr("Open directory"));
    connect(Menu_File_Open_Directory, SIGNAL(triggered()), this, SLOT(OnMenu_File_Open_Directory()));

    Menu_File_Quit = new QAction(tr("Q&uit"), this);
    Menu_File_Quit->setShortcut(tr("Ctrl+Q"));
    Menu_File_Quit->setStatusTip(tr("Quit the application"));
    connect(Menu_File_Quit, SIGNAL(triggered()), this, SLOT(close()));

    Menu_File = menuBar()->addMenu(tr("&File"));
    Menu_File->addAction(Menu_File_Open_Files);
    Menu_File->addAction(Menu_File_Open_Directory);
    Menu_File->addSeparator();
    Menu_File->addAction(Menu_File_Quit);

    //View
    Menu_View_Summary = new QAction(tr("DV analysis summary"), this);
    Menu_View_Summary->setShortcut(tr(""));
    Menu_View_Summary->setCheckable(true);
    Menu_View_Summary->setStatusTip(tr(""));
    connect(Menu_View_Summary, SIGNAL(triggered()), this, SLOT(OnMenu_View_Summary()));

    Menu_View_ByFrame_Table = new QAction(tr("DV analysis by frame (Table)"), this);
    Menu_View_ByFrame_Table->setShortcut(tr(""));
    Menu_View_ByFrame_Table->setCheckable(true);
    Menu_View_ByFrame_Table->setStatusTip(tr(""));
    connect(Menu_View_ByFrame_Table, SIGNAL(triggered()), this, SLOT(OnMenu_View_ByFrame_Table()));

    Menu_View_ByFrame_Text = new QAction(tr("DV analysis by frame (Text)"), this);
    Menu_View_ByFrame_Text->setShortcut(tr(""));
    Menu_View_ByFrame_Text->setCheckable(true);
    Menu_View_ByFrame_Text->setStatusTip(tr(""));
    connect(Menu_View_ByFrame_Text, SIGNAL(triggered()), this, SLOT(OnMenu_View_ByFrame_Text()));

    Menu_View_XML = new QAction(tr("XML output"), this);
    Menu_View_XML->setShortcut(tr(""));
    Menu_View_XML->setCheckable(true);
    Menu_View_XML->setStatusTip(tr(""));
    connect(Menu_View_XML, SIGNAL(triggered()), this, SLOT(OnMenu_View_XML()));

    Menu_View_AppleXMLIFv3 = new QAction(tr("Apple XML Interchange Format, version 3 (for Final Cut 5 or higher) output"), this);
    Menu_View_AppleXMLIFv3->setShortcut(tr(""));
    Menu_View_AppleXMLIFv3->setCheckable(true);
    Menu_View_AppleXMLIFv3->setStatusTip(tr(""));
    connect(Menu_View_AppleXMLIFv3, SIGNAL(triggered()), this, SLOT(OnMenu_View_AppleXMLIFv3()));

    Menu_View_AppleXMLIFv4 = new QAction(tr("Apple XML Interchange Format, version 4 (for Final Cut 6 or higher) output"), this);
    Menu_View_AppleXMLIFv4->setShortcut(tr(""));
    Menu_View_AppleXMLIFv4->setCheckable(true);
    Menu_View_AppleXMLIFv4->setStatusTip(tr(""));
    connect(Menu_View_AppleXMLIFv4, SIGNAL(triggered()), this, SLOT(OnMenu_View_AppleXMLIFv4()));

    Menu_View_AppleXMLIFv5 = new QAction(tr("Apple XML Interchange Format, version 5 (for Final Cut 7 or higher) output"), this);
    Menu_View_AppleXMLIFv5->setShortcut(tr(""));
    Menu_View_AppleXMLIFv5->setCheckable(true);
    Menu_View_AppleXMLIFv5->setStatusTip(tr(""));
    connect(Menu_View_AppleXMLIFv5, SIGNAL(triggered()), this, SLOT(OnMenu_View_AppleXMLIFv5()));

    Menu_View_MediaInfo = new QAction(tr("Technical metadata (MediaInfo)"), this);
    Menu_View_MediaInfo->setShortcut(tr(""));
    Menu_View_MediaInfo->setCheckable(true);
    Menu_View_MediaInfo->setStatusTip(tr(""));
    connect(Menu_View_MediaInfo, SIGNAL(triggered()), this, SLOT(OnMenu_View_MediaInfo()));

    Menu_View_Group = new QActionGroup(this);
    Menu_View_Group->addAction(Menu_View_Summary);
    Menu_View_Group->addAction(Menu_View_ByFrame_Table);
    Menu_View_Group->addAction(Menu_View_ByFrame_Text);
    Menu_View_Group->addAction(Menu_View_XML);
    Menu_View_Group->addAction(Menu_View_AppleXMLIFv3);
    Menu_View_Group->addAction(Menu_View_AppleXMLIFv4);
    Menu_View_Group->addAction(Menu_View_AppleXMLIFv5);
    Menu_View_Group->addAction(Menu_View_MediaInfo);
    Menu_View = menuBar()->addMenu(tr("&View"));
    Menu_View->addAction(Menu_View_Summary);
    Menu_View->addAction(Menu_View_ByFrame_Table);
    Menu_View->addAction(Menu_View_ByFrame_Text);
    Menu_View->addAction(Menu_View_XML);
    Menu_View->addAction(Menu_View_AppleXMLIFv3);
    Menu_View->addAction(Menu_View_AppleXMLIFv4);
    Menu_View->addAction(Menu_View_AppleXMLIFv5);
    Menu_View->addAction(Menu_View_MediaInfo);
    Menu_View_Group = new QActionGroup(this);

    //Menu Export
    Menu_Export_Summary = new QAction(tr("DV analysis summary..."), this);
    Menu_Export_Summary->setStatusTip(tr(""));
    connect(Menu_Export_Summary, SIGNAL(triggered()), this, SLOT(OnMenu_Export_Summary()));

    Menu_Export_ByFrame = new QAction(tr("DV analysis by frame..."), this);
    Menu_Export_ByFrame->setStatusTip(tr(""));
    connect(Menu_Export_ByFrame, SIGNAL(triggered()), this, SLOT(OnMenu_Export_ByFrame()));

    Menu_Export_XML = new QAction(tr("XML output..."), this);
    Menu_Export_XML->setStatusTip(tr(""));
    connect(Menu_Export_XML, SIGNAL(triggered()), this, SLOT(OnMenu_Export_XML()));

    Menu_Export_AppleXMLIFv3 = new QAction(tr("Apple XML Interchange Format, version 3 (for Final Cut 5 or higher)..."), this);
    Menu_Export_AppleXMLIFv3->setStatusTip(tr(""));
    connect(Menu_Export_AppleXMLIFv3, SIGNAL(triggered()), this, SLOT(OnMenu_Export_AppleXMLIFv3()));

    Menu_Export_AppleXMLIFv4 = new QAction(tr("Apple XML Interchange Format, version 4 (for Final Cut 6 or higher)..."), this);
    Menu_Export_AppleXMLIFv4->setStatusTip(tr(""));
    connect(Menu_Export_AppleXMLIFv4, SIGNAL(triggered()), this, SLOT(OnMenu_Export_AppleXMLIFv4()));

    Menu_Export_AppleXMLIFv5 = new QAction(tr("Apple XML Interchange Format, version 5 (for Final Cut 7 or higher)..."), this);
    Menu_Export_AppleXMLIFv5->setStatusTip(tr(""));
    connect(Menu_Export_AppleXMLIFv5, SIGNAL(triggered()), this, SLOT(OnMenu_Export_AppleXMLIFv5()));

    Menu_Export_MediaInfo_Text = new QAction(tr("Technical metadata (MediaInfo) (Text)..."), this);
    Menu_Export_MediaInfo_Text->setStatusTip(tr(""));
    connect(Menu_Export_MediaInfo_Text, SIGNAL(triggered()), this, SLOT(OnMenu_Export_MediaInfo_Text()));

    Menu_Export_MediaInfo_XML = new QAction(tr("Technical metadata (MediaInfo) (XML)..."), this);
    Menu_Export_MediaInfo_XML->setStatusTip(tr(""));
    connect(Menu_Export_MediaInfo_XML, SIGNAL(triggered()), this, SLOT(OnMenu_Export_MediaInfo_XML()));

    Menu_Export = menuBar()->addMenu(tr("&Export"));
    Menu_Export->addAction(Menu_Export_Summary);
    Menu_Export->addAction(Menu_Export_ByFrame);
    Menu_Export->addAction(Menu_Export_XML);
    Menu_Export->addAction(Menu_Export_AppleXMLIFv3);
    Menu_Export->addAction(Menu_Export_AppleXMLIFv4);
    Menu_Export->addAction(Menu_Export_AppleXMLIFv5);
    Menu_Export->addAction(Menu_Export_MediaInfo_Text);
    Menu_Export->addAction(Menu_Export_MediaInfo_XML);

    //Options
    Menu_Options_Verbosity_03 = new QAction(tr("Errors only"), this);
    Menu_Options_Verbosity_03->setShortcut(tr(""));
    Menu_Options_Verbosity_03->setCheckable(true);
    Menu_Options_Verbosity_03->setStatusTip(tr("DV analysis by frame, Errors only"));
    connect(Menu_Options_Verbosity_03, SIGNAL(triggered()), this, SLOT(OnMenu_Options_Verbosity_03()));

    Menu_Options_Verbosity_05 = new QAction(tr("Errors and information"), this);
    Menu_Options_Verbosity_05->setShortcut(tr(""));
    Menu_Options_Verbosity_05->setCheckable(true);
    Menu_Options_Verbosity_05->setStatusTip(tr("DV analysis by frame, Errors and information"));
    connect(Menu_Options_Verbosity_05, SIGNAL(triggered()), this, SLOT(OnMenu_Options_Verbosity_05()));

    Menu_Options_Verbosity_09 = new QAction(tr("Errors and information (including arbitrary bit)"), this);
    Menu_Options_Verbosity_09->setShortcut(tr(""));
    Menu_Options_Verbosity_09->setCheckable(true);
    Menu_Options_Verbosity_09->setStatusTip(tr("DV analysis by frame, Errors and information (including arbitrary bit)"));
    connect(Menu_Options_Verbosity_09, SIGNAL(triggered()), this, SLOT(OnMenu_Options_Verbosity_09()));

    Menu_Options_Verbosity_10 = new QAction(tr("All frames"), this);
    Menu_Options_Verbosity_10->setShortcut(tr(""));
    Menu_Options_Verbosity_10->setCheckable(true);
    Menu_Options_Verbosity_10->setStatusTip(tr("DV analysis by frame, All"));
    connect(Menu_Options_Verbosity_10, SIGNAL(triggered()), this, SLOT(OnMenu_Options_Verbosity_10()));

    Menu_Options_Verbosity_Group = new QActionGroup(this);
    Menu_Options_Verbosity_Group->addAction(Menu_Options_Verbosity_03);
    Menu_Options_Verbosity_Group->addAction(Menu_Options_Verbosity_05);
    Menu_Options_Verbosity_Group->addAction(Menu_Options_Verbosity_09);
    Menu_Options_Verbosity_Group->addAction(Menu_Options_Verbosity_10);

    Menu_Options_MediaInfo_InternalFields = new QAction(tr("Internal fields"), this);
    Menu_Options_MediaInfo_InternalFields->setShortcut(tr(""));
    Menu_Options_MediaInfo_InternalFields->setCheckable(true);
    Menu_Options_MediaInfo_InternalFields->setStatusTip(tr(""));
    connect(Menu_Options_MediaInfo_InternalFields, SIGNAL(triggered()), this, SLOT(OnMenu_Options_MediaInfo_InternalFields()));

    Menu_Options_MediaInfo_RawFieldsNames = new QAction(tr("Raw field names"), this);
    Menu_Options_MediaInfo_RawFieldsNames->setShortcut(tr(""));
    Menu_Options_MediaInfo_RawFieldsNames->setCheckable(true);
    Menu_Options_MediaInfo_RawFieldsNames->setStatusTip(tr(""));
    connect(Menu_Options_MediaInfo_RawFieldsNames, SIGNAL(triggered()), this, SLOT(OnMenu_Options_MediaInfo_RawFieldsNames()));
    //Menu_Options_MediaInfo_RawFieldsNames->setChecked(true); OnMenu_Options_MediaInfo_RawFieldsNames();

    Menu_Options_ResetFieldSizes = new QAction(tr("Reset field sizes"), this);
    Menu_Options_ResetFieldSizes->setStatusTip(tr(""));
    connect(Menu_Options_ResetFieldSizes, SIGNAL(triggered()), this, SLOT(OnMenu_Options_ResetFieldSizes()));
    Menu_Options_ResetFieldSizes->setVisible(false);

    Menu_Options=menuBar()->addMenu(tr("&Options"));
    Menu_Options_Verbosity=Menu_Options->addMenu(tr("&Verbosity (frame reporting)"));
    Menu_Options_Verbosity->addAction(Menu_Options_Verbosity_03);
    Menu_Options_Verbosity->addAction(Menu_Options_Verbosity_05);
    Menu_Options_Verbosity->addAction(Menu_Options_Verbosity_09);
    Menu_Options_Verbosity->addAction(Menu_Options_Verbosity_10);
    Menu_Options_MediaInfo=Menu_Options->addMenu(tr("&Technical Metadata (MediaInfo)"));
    Menu_Options_MediaInfo->addAction(Menu_Options_MediaInfo_InternalFields);
    Menu_Options_MediaInfo->addAction(Menu_Options_MediaInfo_RawFieldsNames);
    Menu_Options->addAction(Menu_Options_ResetFieldSizes);

    //Menu Help
    Menu_Help_Help = new QAction(tr("Help"), this);
    Menu_Help_Help->setShortcut(tr(""));
    Menu_Help_Help->setStatusTip(tr(""));
    connect(Menu_Help_Help, SIGNAL(triggered()), this, SLOT(OnMenu_Help_Help()));

    Menu_Help_About = new QAction(QIcon(":/Image/Menu/Help_About.png"), tr("About..."), this);
    Menu_Help_About->setShortcut(tr(""));
    Menu_Help_About->setStatusTip(tr(""));
    connect(Menu_Help_About, SIGNAL(triggered()), this, SLOT(OnMenu_Help_About()));

    Menu_Help_AVPS_Website = new QAction(QIcon(":/Image/AVPS/logo_sign_alpha.png"), tr("AVPS website"), this);
    Menu_Help_AVPS_Website->setShortcut(tr(""));
    Menu_Help_AVPS_Website->setStatusTip(tr(""));
    connect(Menu_Help_AVPS_Website, SIGNAL(triggered()), this, SLOT(OnMenu_Help_AVPS_Website()));

    Menu_Help_DvAnalyzer_Website = new QAction(QIcon(":/Image/AVPS/logo_sign_alpha.png"), tr("AVPS DV Analyzer website"), this);
    Menu_Help_DvAnalyzer_Website->setShortcut(tr(""));
    Menu_Help_DvAnalyzer_Website->setStatusTip(tr(""));
    connect(Menu_Help_DvAnalyzer_Website, SIGNAL(triggered()), this, SLOT(OnMenu_Help_DvAnalyzer_Website()));

    Menu_Help = menuBar()->addMenu(tr("&Help"));
    Menu_Help->addAction(Menu_Help_Help);
    Menu_Help->addSeparator();
    Menu_Help->addAction(Menu_Help_About);
    Menu_Help->addAction(Menu_Help_AVPS_Website);
    Menu_Help->addAction(Menu_Help_DvAnalyzer_Website);
}

//***************************************************************************
// Menu actions
//***************************************************************************

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_File_Open_Files()
{
    //User interaction
    QStringList FileNamesQ = QFileDialog::getOpenFileNames(this, "", "", "");
    if (FileNamesQ.empty())
        return;

    ZenLib::ZtringList FileNames;
    for (int Pos=0; Pos<FileNamesQ.size(); Pos++)
        FileNames.push_back(ZenLib::Ztring().From_UTF8(FileNamesQ[Pos].toUtf8().data()));

    //Configuring
    C->Menu_File_Open_Files_Begin();
    for (size_t Pos=0; Pos<FileNames.size(); Pos++)
    {
        #ifdef __WINDOWS__
            FileNames[Pos].FindAndReplace(Ztring("/"), Ztring("\\"), 0, Ztring_Recursive);
        #endif //__WINDOWS__
        C->Menu_File_Open_Files_Continue(FileNames[Pos]);
    }

    //Showing
    Open_Timer_Init();
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_File_Open_Directory()
{
    //User interaction
    QString FileNamesQ = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    if (FileNamesQ.isEmpty())
        return;

    //Configuring
    C->Menu_File_Open_Files_Begin();
    Ztring FileName; FileName.From_UTF8(FileNamesQ.toUtf8().data());
    #ifdef __WINDOWS__
        FileName.FindAndReplace(Ztring("/"), Ztring("\\"), 0, Ztring_Recursive);
    #endif //__WINDOWS__
    C->Menu_File_Open_Files_Continue(FileName);

    //Showing
    Open_Timer_Init();
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_View_Summary()
{
    //Configuring
    C->Errors_Stats_WithHeader=true;
    C->Errors_Stats_WithFooter=false;

    //Showing
    View_Refresh(View_Summary);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_View_ByFrame_Table()
{
    //Configuring
    C->Errors_Stats_WithHeader=false;
    C->Errors_Stats_WithFooter=false;

    //Showing
    View_Refresh(View_ByFrame_Table);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_View_ByFrame_Text()
{
    //Configuring
    C->Errors_Stats_WithHeader=true;
    C->Errors_Stats_WithFooter=false;

    //Showing
    View_Refresh(View_ByFrame_Text);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_View_MediaInfo()
{
    //Showing
    View_Refresh(View_MediaInfo);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_View_XML()
{
    //Showing
    View_Refresh(View_XML);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_View_AppleXMLIFv3()
{
    //Showing
    View_Refresh(View_AppleXMLIFv3);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_View_AppleXMLIFv4()
{
    //Showing
    View_Refresh(View_AppleXMLIFv4);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_View_AppleXMLIFv5()
{
    //Showing
    View_Refresh(View_AppleXMLIFv5);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Options_Verbosity_03()
{
    //Configuring
    C->Menu_Verbosity_03();

    //Showing
    if (View_Current==View_Summary || View_Current==View_ByFrame_Table || View_Current==View_ByFrame_Text || View_Current==View_XML)
        View_Refresh();
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Options_Verbosity_05()
{
    //Configuring
    C->Menu_Verbosity_05();

    //Showing
    if (View_Current==View_Summary || View_Current==View_ByFrame_Table || View_Current==View_ByFrame_Text || View_Current==View_XML)
        View_Refresh();
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Options_Verbosity_09()
{
    //Configuring
    C->Menu_Verbosity_09();

    //Showing
    if (View_Current==View_Summary || View_Current==View_ByFrame_Table || View_Current==View_ByFrame_Text || View_Current==View_XML)
        View_Refresh();
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Options_Verbosity_10()
{
    //Configuring
    C->Menu_Verbosity_10();

    //Showing
    if (View_Current==View_Summary || View_Current==View_ByFrame_Table || View_Current==View_ByFrame_Text || View_Current==View_XML)
        View_Refresh();
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Export_Summary()
{
    //User interaction
    QString FileNamesQ = QFileDialog::getSaveFileName(  this,
                                                        tr("Save Summary..."),
                                                        tr(""),
                                                        tr("Text file (*.txt)"));
    if (FileNamesQ.isEmpty())
        return;

    //Configuring
    ZenLib::Ztring FileName; FileName.From_UTF8(FileNamesQ.toUtf8().data());
    #if defined(_MACOSX)
        FileName+=_T(".txt");
    #endif
    File F; F.Create(FileName);
    
    //Running
    Ztring ToWrite; ToWrite.From_UTF8(C->Summary());
    ToWrite.FindAndReplace(_T("\n"), EOL, 0, Ztring_Recursive);
    F.Write(ToWrite);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Export_ByFrame()
{
    //User interaction
    QString FileNamesQ = QFileDialog::getSaveFileName(  this,
                                                        tr("Save By Frame..."),
                                                        tr(""),
                                                        tr("Text file (*.txt)"));
    if (FileNamesQ.isEmpty())
        return;

    //Configuring
    ZenLib::Ztring FileName; FileName.From_UTF8(FileNamesQ.toUtf8().data());
    #if defined(_MACOSX)
        FileName+=_T(".txt");
    #endif
    File F; F.Create(FileName);
    
    //Running
    Ztring ToWrite; ToWrite.From_UTF8(C->ByFrame());
    ToWrite.FindAndReplace(_T("\n"), EOL, 0, Ztring_Recursive);
    F.Write(ToWrite);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Export_XML()
{
    //User interaction
    QString FileNamesQ = QFileDialog::getSaveFileName(  this,
                                                        tr("Save XML..."),
                                                        tr(""),
                                                        tr("XML file (*.xml)"));
    if (FileNamesQ.isEmpty())
        return;

    //Configuring
    ZenLib::Ztring FileName; FileName.From_UTF8(FileNamesQ.toUtf8().data());
    #if defined(_MACOSX)
        FileName+=_T(".xml");
    #endif
    File F; F.Create(FileName);
    
    //Running
    Ztring ToWrite; ToWrite.From_UTF8(C->XML());
    ToWrite.FindAndReplace(_T("\n"), EOL, 0, Ztring_Recursive);
    F.Write(ToWrite);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Export_AppleXMLIFv3()
{
    //User interaction
    QString FileNamesQ = QFileDialog::getSaveFileName(  this,
                                                        tr("Save Apple XML Interchange Format, version 3 (for Final Cut 5 or higher)..."),
                                                        tr(""),
                                                        tr("XML file (*.xml)"));
    if (FileNamesQ.isEmpty())
        return;

    //Configuring
    ZenLib::Ztring FileName; FileName.From_UTF8(FileNamesQ.toUtf8().data());
    #if defined(_MACOSX)
        FileName+=_T(".xml");
    #endif
    File F; F.Create(FileName);
    
    //Running
    Ztring ToWrite; ToWrite.From_UTF8(C->AppleXMLIF(3));
    ToWrite.FindAndReplace(_T("\n"), EOL, 0, Ztring_Recursive);
    F.Write(ToWrite);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Export_AppleXMLIFv4()
{
    //User interaction
    QString FileNamesQ = QFileDialog::getSaveFileName(  this,
                                                        tr("Save Apple XML Interchange Format, version 4 (for Final Cut 6 or higher)..."),
                                                        tr(""),
                                                        tr("XML file (*.xml)"));
    if (FileNamesQ.isEmpty())
        return;

    //Configuring
    ZenLib::Ztring FileName; FileName.From_UTF8(FileNamesQ.toUtf8().data());
    #if defined(_MACOSX)
        FileName+=_T(".xml");
    #endif
    File F; F.Create(FileName);
    
    //Running
    Ztring ToWrite; ToWrite.From_UTF8(C->AppleXMLIF(4));
    ToWrite.FindAndReplace(_T("\n"), EOL, 0, Ztring_Recursive);
    F.Write(ToWrite);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Export_AppleXMLIFv5()
{
    //User interaction
    QString FileNamesQ = QFileDialog::getSaveFileName(  this,
                                                        tr("Save Apple XML Interchange Format, version 5 (for Final Cut 7 or higher)..."),
                                                        tr(""),
                                                        tr("XML file (*.xml)"));
    if (FileNamesQ.isEmpty())
        return;

    //Configuring
    ZenLib::Ztring FileName; FileName.From_UTF8(FileNamesQ.toUtf8().data());
    #if defined(_MACOSX)
        FileName+=_T(".xml");
    #endif
    File F; F.Create(FileName);
    
    //Running
    Ztring ToWrite; ToWrite.From_UTF8(C->AppleXMLIF(5));
    ToWrite.FindAndReplace(_T("\n"), EOL, 0, Ztring_Recursive);
    F.Write(ToWrite);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Export_MediaInfo_Text()
{
    //User interaction
    QString FileNamesQ = QFileDialog::getSaveFileName(  this,
                                                        tr("Save Technical metadata..."),
                                                        tr(""),
                                                        tr("Text file (*.txt)"));
    if (FileNamesQ.isEmpty())
        return;

    //Configuring
    ZenLib::Ztring FileName; FileName.From_UTF8(FileNamesQ.toUtf8().data());
    #if defined(_MACOSX)
        FileName+=_T(".txt");
    #endif
    File F; F.Create(FileName);
    
    //Running
    C->Menu_Option_Preferences_Option(_T("Language"), _T("raw"));
    Ztring ToWrite; ToWrite.From_UTF8(C->MediaInfo_Text());
    C->Menu_Option_Preferences_Option(_T("Language"), Menu_Options_MediaInfo_RawFieldsNames->isChecked()?_T("raw"):_T(""));
    F.Write(ToWrite);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Export_MediaInfo_XML()
{
    //User interaction
    QString FileNamesQ = QFileDialog::getSaveFileName(  this,
                                                        tr("Save Technical metadata..."),
                                                        tr(""),
                                                        tr("XML file (*.xml)"));
    if (FileNamesQ.isEmpty())
        return;

    //Configuring
    ZenLib::Ztring FileName; FileName.From_UTF8(FileNamesQ.toUtf8().data());
    #if defined(_MACOSX)
        FileName+=_T(".xml");
    #endif
    File F; F.Create(FileName);
    
    //Running
    C->Menu_Option_Preferences_Option(_T("Language"), _T("raw"));
    Ztring ToWrite; ToWrite.From_UTF8(C->MediaInfo_XML());
    C->Menu_Option_Preferences_Option(_T("Language"), Menu_Options_MediaInfo_RawFieldsNames->isChecked()?_T("raw"):_T(""));
    F.Write(ToWrite);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Options_ResetFieldSizes()
{
    QEvent event((QEvent::Type)(QEvent::User+1));
    QApplication::sendEvent(View, &event);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Options_MediaInfo_InternalFields()
{
    //Configuring
    C->Menu_Option_Preferences_Option(_T("Complete"), Menu_Options_MediaInfo_InternalFields->isChecked()?_T("1"):_T("0"));

    //Showing
    if (View_Current==View_MediaInfo)
        View_Refresh();
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Options_MediaInfo_RawFieldsNames()
{
    //Configuring
    C->Menu_Option_Preferences_Option(_T("Language"), Menu_Options_MediaInfo_RawFieldsNames->isChecked()?_T("raw"):_T(""));

    //Showing
    if (View_Current==View_MediaInfo)
        View_Refresh();
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Help_Help()
{
    //Showing
    GUI_Help* Frame=new GUI_Help(this);
    Frame->show();
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Help_About()
{
    //Showing
    GUI_About *About = new GUI_About(this);
    About->exec();
    delete About;
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Help_AVPS_Website()
{
    //Showing
    QDesktopServices::openUrl(QUrl("http://www.avpreserve.com/", QUrl::TolerantMode));
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Help_DvAnalyzer_Website()
{
    //Showing
    QDesktopServices::openUrl(QUrl("http://www.avpreserve.com/dvanalyzer/", QUrl::TolerantMode));
}

//***************************************************************************
// ToolBar creation
//***************************************************************************

//---------------------------------------------------------------------------
void GUI_Main::ToolBar_Create()
{
    ToolBar=new QToolBar(tr("ToolBar"));
    ToolBar->setIconSize(QSize(32, 32));
        
    ToolBar->addAction(Menu_File_Open_Files);
    ToolBar->addAction(Menu_File_Open_Directory);
    ToolBar->addSeparator();
    ToolBar->addAction(Menu_Help_About);
    ToolBar->addAction(Menu_Help_DvAnalyzer_Website);

    #ifndef __APPLE__
        addToolBar(Qt::LeftToolBarArea, ToolBar);
    #else //__APPLE__
        addToolBar(ToolBar);
    #endif //__APPLE__
}
