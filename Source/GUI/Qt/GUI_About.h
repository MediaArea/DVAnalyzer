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
#ifndef GUI_AboutH
#define GUI_AboutH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include <QtGui/QDialog>
class QTextBrowser;
//---------------------------------------------------------------------------

//***************************************************************************
// GUI_Main
//***************************************************************************

class GUI_About : public QDialog
{
     Q_OBJECT

public:
    GUI_About (QWidget * parent);
    ~GUI_About ();

private slots:
    //Menu - Actions
    void OnDescription                  ();
    void OnTechnicalSynopsis            ();
    void OnAuthorLicense                ();

private:
    //GUI
    QTextBrowser* NameVersion;
    QTextBrowser* Text;
    QTextBrowser* Websites;
    QPushButton*  Button_Description;
    QPushButton*  Button_TechnicalSynopsis;
    QPushButton*  Button_AuthorLicense;
    QPushButton*  Close;

    void showEvent(QShowEvent* event);
    void resizeEvent(QResizeEvent* event);
};

#endif
