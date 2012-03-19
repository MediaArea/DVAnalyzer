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

//---------------------------------------------------------------------------
#include "GUI/Qt/GUI_Main.h"
#include "Common/Core.h"
#include <vector>
#include <algorithm>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include "GUI/Qt/GUI_Main_ByFrame_Table.h"
#include "GUI/Qt/GUI_Main_ByFrame_Text.h"
#include "GUI/Qt/GUI_Main_MediaInfo.h"
#include "GUI/Qt/GUI_Main_Summary.h"
#include "GUI/Qt/GUI_Main_XML.h"
#include "GUI/Qt/GUI_Main_AppleXMLIFv3.h"
#include "GUI/Qt/GUI_Main_AppleXMLIFv4.h"
#include "GUI/Qt/GUI_Main_AppleXMLIFv5.h"
#include <QtCore/QEvent>
#include <QtCore/QMimeData>
#include <QtCore/QUrl>
#include <QtGui/QApplication>
#include <QtGui/QDropEvent>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QDesktopWidget>
#include <QtGui/QTabWidget>
#include <QtGui/QProgressDialog>
#include <QtCore/QThread>
#include <QtCore/QTimer>
#include "ZenLib/Ztring.h"
using namespace std;
using namespace ZenLib;
//---------------------------------------------------------------------------

//***************************************************************************
// Menu actions
//***************************************************************************

class SleeperThread : public QThread
{
    public:
    static void msleep(unsigned long msecs)
    {
        QThread::msleep(msecs);
    }
};

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
// Constructor
GUI_Main::GUI_Main(Core* _C)
{
    //Internal
    C=_C;
    C->WithThreads=true;

    //Configure
    View_Current=View_Summary;
    MustCreate=true;

    //Menu and ToolBar
    Menu_Create();
    ToolBar_Create();

    //GUI
    View=NULL;
    //CenterOnScreen();
    setStatusBar(new QStatusBar());
    move(QApplication::desktop()->screenGeometry().width()/40, 40);
    resize(QApplication::desktop()->screenGeometry().width()-QApplication::desktop()->screenGeometry().width()/40*2, QApplication::desktop()->screenGeometry().height()/2);

    //Central
    Central=new QTabWidget(this);
    Central->addTab(new GUI_Main_Text_Summary      (C, this), tr("File Summary"));
    Central->addTab(new GUI_Main_ByFrame_Table     (C, this), tr("Frame Table"));
    Central->addTab(new GUI_Main_ByFrame_Text      (C, this), tr("Frame Text"));
    Central->addTab(new GUI_Main_XML               (C, this), tr("XML"));
    Central->addTab(new GUI_Main_AppleXMLIFv3      (C, this), tr("FCP v5"));
    Central->addTab(new GUI_Main_AppleXMLIFv4      (C, this), tr("FCP v6"));
    Central->addTab(new GUI_Main_AppleXMLIFv5      (C, this), tr("FCP v7"));
    Central->addTab(new GUI_Main_MediaInfo         (C, this), tr("MediaInfo"));
    setCentralWidget(Central);
    connect(Central, SIGNAL(currentChanged (int)), this, SLOT(OnCurrentChanged(int)));

    //Drag n drop
    setAcceptDrops(true);

    //Defaults
    Menu_View_Summary->setChecked(true);
    emit OnMenu_View_Summary();
    Menu_Options_Verbosity_05->setChecked(true);
    emit OnMenu_Options_Verbosity_05();

    //GUI
    setWindowTitle("DV Analyzer - AudioVisual Preservation Solutions, Inc.");
    setWindowIcon (QIcon(":/Image/AVPS/logo_sign_alpha_square.png"));

    //Timer
    ProgressDialog=NULL;
    Timer=NULL;
}

//---------------------------------------------------------------------------
GUI_Main::~GUI_Main()
{
    delete Timer; //Timer=NULL;
}

//***************************************************************************
// View_Refresh
//***************************************************************************

//---------------------------------------------------------------------------
void GUI_Main::View_Refresh(view View_New)
{
    if (View_New!=View_None)
    {
        Central->setCurrentIndex(View_New);
        View=Central->currentWidget();
        View_Current=View_New;
    }

    /*
    if (View_New!=View_None)
    {
        View_Current=View_New;
        MustCreate=true;
    }
        
    if (MustCreate)
    {
        delete View;
        switch (View_Current)
        {
            case View_Summary       : View=new GUI_Main_Text_Summary    (C, this); MustCreate=false; break;
            case View_ByFrame_Table : View=new GUI_Main_ByFrame_Table   (C, this); MustCreate=false; break;
            case View_ByFrame_Text  : View=new GUI_Main_ByFrame_Text    (C, this); MustCreate=false; break;
            case View_XML           : View=new GUI_Main_XML             (C, this); MustCreate=false; break;
            case View_MediaInfo     : View=new GUI_Main_MediaInfo       (C, this); MustCreate=false; break;
            default                 : View=NULL;
        }

        setCentralWidget(View);
    }*/

    QEvent event(QEvent::User);
    QApplication::sendEvent(View, &event);
}

void GUI_Main::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}
 
void GUI_Main::dropEvent(QDropEvent *event)
{
    C->Menu_File_Open_Files_Begin();

    const QMimeData* Data=event->mimeData ();
    if (event->mimeData()->hasUrls())
    {
        foreach (QUrl url, event->mimeData()->urls())
        {
            Ztring FileName; FileName.From_UTF8(url.toLocalFile().toUtf8().data());
            #ifdef __WINDOWS__
                FileName.FindAndReplace(Ztring("/"), Ztring("\\"), 0, Ztring_Recursive);
            #endif //__WINDOWS__
            C->Menu_File_Open_Files_Continue(FileName);

        }

        Open_Timer_Init();
    }
}

void GUI_Main::OnOpen_Timer ()
{
    if (ProgressDialog==NULL)
        return;    
        
    float Result=C->Menu_File_Open_State();
    ProgressDialog->setValue((int)(Result*100));

    if (Result==1.0 || ProgressDialog->wasCanceled())
    {
        ProgressDialog->hide();
        Timer->stop();

        delete ProgressDialog; ProgressDialog=NULL;
        delete Timer; Timer=NULL;

        //Showing
        View_Refresh();
    }
}     
     
void GUI_Main::OnCurrentChanged (int Index)
{
    //Showing
    switch (Index)
    {
        case 0  : Menu_View_Summary->setChecked(true); OnMenu_View_Summary(); break;
        case 1  : Menu_View_ByFrame_Table->setChecked(true); OnMenu_View_ByFrame_Table(); break;
        case 2  : Menu_View_ByFrame_Text->setChecked(true); OnMenu_View_ByFrame_Text(); break;
        case 3  : Menu_View_XML->setChecked(true); OnMenu_View_XML(); break;
        case 4  : Menu_View_AppleXMLIFv3->setChecked(true); OnMenu_View_AppleXMLIFv3(); break;
        case 5  : Menu_View_AppleXMLIFv4->setChecked(true); OnMenu_View_AppleXMLIFv4(); break;
        case 6  : Menu_View_AppleXMLIFv5->setChecked(true); OnMenu_View_AppleXMLIFv5(); break;
        case 7  : Menu_View_MediaInfo->setChecked(true); OnMenu_View_MediaInfo(); break;
        default : ;
    }

    //Options
    switch (Index)
    {
        case 1                              : Menu_Options_ResetFieldSizes->setVisible(true); break;
        default                             : Menu_Options_ResetFieldSizes->setVisible(false);
    }

}

void GUI_Main::Open_Timer_Init ()
{
    if (!C->WithThreads)
    {
        //Showing
        View_Refresh();

        return;
    }
        
    ProgressDialog=new QProgressDialog("Opening files...", "Abort Opening", 0, 100, this);
    ProgressDialog->setWindowModality(Qt::WindowModal);
    ProgressDialog->setMinimumDuration(0);
    ProgressDialog->setWindowTitle("DV Analyzer");

    if (Timer==NULL)
    {
        Timer=new QTimer();
        connect(Timer, SIGNAL(timeout()), this, SLOT(OnOpen_Timer()));
        Timer->start(100);
    }
}     
     
