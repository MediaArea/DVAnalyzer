// GUI_About - Qt GUI for DV Analyzer
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
#include "GUI/Qt/GUI_About.h"
#include "Common/Core.h"
#include <QtGui/QTextEdit>
#include <QtGui/QTextBrowser>
#include <QtGui/QGridLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QAbstractTextDocumentLayout>
#include <QtGui/QScrollBar>
#include <QtGui/QImage>
#include <QtGui/QLabel>
#include <QtGui/QDialogButtonBox>
#include "Common/Common_About.h"
//---------------------------------------------------------------------------

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
// Constructor
GUI_About::GUI_About(QWidget * parent)
: QDialog(parent)
{
    #ifdef __WINDOWS__
        resize(620, 440);
    #else
        resize(780, 540);
    #endif
    setWindowFlags(windowFlags()&(0xFFFFFFFF-Qt::WindowContextHelpButtonHint));
    setWindowTitle("About DV Analyzer");

    Close=new QPushButton("&Close");
    Close->setDefault(true);
    QDialogButtonBox* Dialog=new QDialogButtonBox();
    Dialog->addButton(Close, QDialogButtonBox::AcceptRole);
    connect(Dialog, SIGNAL(accepted()), this, SLOT(close()));

    QGridLayout* L=new QGridLayout();
    QVBoxLayout* L00=new QVBoxLayout();
    Button_Description=new QPushButton("&Description", this);
    Button_TechnicalSynopsis=new QPushButton("&Technical Synopsis", this);
    Button_AuthorLicense=new QPushButton("&Author and License", this);
    L00->addWidget(Button_Description);
    L00->addWidget(Button_TechnicalSynopsis);
    L00->addWidget(Button_AuthorLicense);
    QPixmap* A=new QPixmap(QPixmap(":/Image/AVPS/logo_avps_alpha.png").scaledToWidth(160));
    QLabel* B=new QLabel();
    B->setPixmap(*A);
    L00->addWidget(B);
    Button_Description->setChecked(true);
    L->addLayout(L00, 0, 0, 3, 1);
    NameVersion=new QTextBrowser();
    NameVersion->setReadOnly(true);
    NameVersion->setOpenExternalLinks(true);
    NameVersion->setHtml(NameVersion_HTML());
    L->addWidget(NameVersion, 0, 1, 1, 2);
    Text=new QTextBrowser();
    Text->setReadOnly(true);
    Text->setOpenExternalLinks(true);
    Text->setHtml(Description_HTML());
    L->addWidget(Text, 1, 1, 1, 2);
    Websites=new QTextBrowser();
    Websites->setReadOnly(true);
    Websites->setOpenExternalLinks(true);
    Websites->setHtml(Websites_HTML());
    L->addWidget(Websites, 2, 1);
    L->addWidget(Close, 2, 2);

    connect(Button_Description, SIGNAL(clicked()), this, SLOT(OnDescription()));
    connect(Button_TechnicalSynopsis, SIGNAL(clicked()), this, SLOT(OnTechnicalSynopsis()));
    connect(Button_AuthorLicense, SIGNAL(clicked()), this, SLOT(OnAuthorLicense()));
    setLayout(L);

    OnDescription();
}

//---------------------------------------------------------------------------
GUI_About::~GUI_About()
{
}

//***************************************************************************
// Actions
//***************************************************************************

//---------------------------------------------------------------------------
void GUI_About::OnDescription()
{
    Text->clear();
    Text->setHtml(Description_HTML());
    Button_Description->setEnabled(false);
    Button_TechnicalSynopsis->setEnabled(true);
    Button_AuthorLicense->setEnabled(true);
}

//---------------------------------------------------------------------------
void GUI_About::OnTechnicalSynopsis()
{
    Text->clear();
    Text->setHtml(TechnicalSynopsis_HTML());
    Button_Description->setEnabled(true);
    Button_TechnicalSynopsis->setEnabled(false);
    Button_AuthorLicense->setEnabled(true);
}

//---------------------------------------------------------------------------
void GUI_About::OnAuthorLicense()
{
    Text->clear();
    Text->setHtml(AuthorLicense_HTML());
    Button_Description->setEnabled(true);
    Button_TechnicalSynopsis->setEnabled(true);
    Button_AuthorLicense->setEnabled(false);
}

void GUI_About::showEvent(QShowEvent* event)
{
    NameVersion->setBackgroundRole(QPalette::Window);
    resizeEvent(NULL);
}

void GUI_About::resizeEvent(QResizeEvent* event)
{
    NameVersion->setMaximumHeight((int)NameVersion->document()->documentLayout()->documentSize().height()+6);
    Websites->setMaximumHeight((int)Websites->document()->documentLayout()->documentSize().height()+6);
}
