// GUI_Main_ByFrame_Table - 
// Copyright (C) 2009-2009 AudioVisual Preservation Solutions, dv@avpreserve.com
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifndef GUI_Main_ByFrame_TableH
#define GUI_Main_ByFrame_TableH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
class Core;
#include <QtGui/QWidget>
class QEvent;
class QTableWidget;
class QComboBox;
//---------------------------------------------------------------------------

//***************************************************************************
// GUI_Main_ByFrame_Table
//***************************************************************************

class GUI_Main_ByFrame_Table : public QWidget 
{
    Q_OBJECT

public:
    //Constructor/Destructor
    GUI_Main_ByFrame_Table(Core* C, QWidget* parent);

    //Events
    bool event (QEvent *Event);

private slots:
    void Files_Changed                  (int Pos); 

private:
    //GUI
    QTableWidget   *Table;
    QComboBox      *Files;
    
    //Internal
    Core* C;
};

#endif
