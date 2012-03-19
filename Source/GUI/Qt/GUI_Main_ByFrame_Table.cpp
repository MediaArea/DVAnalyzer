// GUI_Main_ByFrame_Table - 
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
#include "GUI/Qt/GUI_Main_ByFrame_Table.h"
#include "Common/Core.h"
#include "ZenLib/ZtringListList.h"
#include "ZenLib/Ztring.h"
#include <QtCore/QEvent>
#include <QtGui/QVBoxLayout>
#include <QtGui/QTableWidget>
#include <QtGui/QComboBox>
using namespace ZenLib;
using namespace std;
//---------------------------------------------------------------------------

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
GUI_Main_ByFrame_Table::GUI_Main_ByFrame_Table(Core* _C, QWidget* parent)
: QWidget(parent)
{
    //Internal
    C=_C;

    QVBoxLayout* L=new QVBoxLayout();
    Files=new QComboBox(this);
    Table=new QTableWidget(this);
    L->addWidget(Files);
    L->addWidget(Table);

    #if (QT_VERSION >= 0x040300)
        L->setContentsMargins(0, 0, 0, 0);
    #endif

    setLayout(L);
    setGeometry (0, 0, frameGeometry().width(), frameGeometry().height());

    connect(Files, SIGNAL(currentIndexChanged(int)), this, SLOT(Files_Changed(int)));

}

//***************************************************************************
// Actions
//***************************************************************************

//---------------------------------------------------------------------------
bool GUI_Main_ByFrame_Table::event (QEvent *Event) 
{
    if (Event->type()==QEvent::User)
    {
        //Showing
        Files->clear();
        string &FileNames=C->FileNames();
        size_t Begin=0;
        size_t End=FileNames.find('\n', 0);
        do
        {
            if (End!=string::npos)
                Files->addItem(QString().fromUtf8(FileNames.substr(Begin, End-Begin).c_str()));
            else if (!FileNames.empty())
                Files->addItem(QString().fromUtf8(FileNames.substr(Begin, string::npos).c_str()));
            Begin=End+1;
            End=FileNames.find('\n', Begin);
        }
        while (End!=string::npos);

        Event->accept();
        return true;

        Files_Changed(0);
    }

    if (Event->type()==(QEvent::Type)(QEvent::User+1))
    {
        Table->resizeColumnsToContents();
        Table->resizeRowsToContents();

        Event->accept();
        return true;
    }

    return QWidget::event(Event);
}

//---------------------------------------------------------------------------
void GUI_Main_ByFrame_Table::Files_Changed (int Pos) 
{
    Table->clear();

    if (Pos==-1)
    {
        Table->setRowCount(0);
        Table->setColumnCount(0);
        return;
    }

    ZtringListList List;
    List.Separator_Set(0, "\n");
    List.Separator_Set(1, "\t");
    List.Write(Ztring().From_Local(C->ByFrame((size_t)Pos)));
    if (!List.empty() && !List[0].empty())
    {
        Table->setRowCount(List.size()-1);
        Table->setColumnCount(List[0].size()-1-10-4);

        for (size_t Data_Pos=1; Data_Pos<List[0].size()-4; Data_Pos++)
        {
            Ztring &Value=List[0][Data_Pos];
            
            //Adaptation
            switch (Data_Pos)
            {
                case  0 : Value=_T("Frame #"); break;
                case  1 : Value=_T("Absolute time"); break;
                case  2 : Value=_T("DV timecode"); break;
                case  3 : Value=_T("DV timecode info"); break;
                case  4 : Value=_T("Rec. date/time"); break;
                case  5 : Value=_T("Rec. date/time info"); break;
                case  6 : Value=_T("Arb bits"); break;
                case  7 : Value=_T("Arb bits info"); break;
                case  8 : Value=_T("Start"); break;
                case  9 : Value=_T("End"); break;
                case 20 : Value=_T("Video error concealment"); break;
                case 21 : Value=_T("Audio errors"); break;
                case 22 : Value=_T("DV timecode incoherency"); break;
                case 23 : Value=_T("DIF incoherency"); break;
                case 24 : Value=_T("Arbitrary bit inconsistency"); break;
                case 25 : Value=_T("Stts fluctuation"); break;
                case 26 : Value.clear(); break;
                case 27 : Value.clear(); break;
                case 28 : Value.clear(); break;
                case 29 : Value.clear(); break;
                default : ;
            }
            
            Table->setHorizontalHeaderItem(Data_Pos>9?(Data_Pos-1-10):(Data_Pos-1), new QTableWidgetItem(QString().fromUtf8(Value.To_Local().c_str())));
            
            if (Data_Pos==9)
                Data_Pos=19;
        }
        for (size_t File_Pos=1; File_Pos<List.size(); File_Pos++)
        {
            Table->setVerticalHeaderItem(File_Pos-1, new QTableWidgetItem(QString().fromUtf8(ZenLib::Ztring(List[File_Pos][0]).To_Local().c_str())));
            for (size_t Data_Pos=1; Data_Pos<List[0].size()-4; Data_Pos++)
            {
                QTableWidgetItem* Item;
                if (Data_Pos<List[File_Pos].size())
                {
                    Ztring &Value=List[File_Pos][Data_Pos];
                    Value.Trim();
                    while (Value.FindAndReplace(_T("  "), _T(" "), 0, Ztring_Recursive));
                    while (Value.FindAndReplace(_T("( "), _T("("), 0, Ztring_Recursive));

                    switch (Data_Pos)
                    {
                        case  3 :   //Timecode Info
                        case  5 :   //Rec. Date / Time Info"
                        case  7 :   //Arb bits Info"
                                    if (Value==_T("R"))
                                        Value=_T("Repeated");
                                    if (Value==_T("N"))
                                        Value=_T("Not Sequential");
                                    break;
                        default : ;
                    }
                    
                    Item=new QTableWidgetItem(QString().fromUtf8(Value.To_Local().c_str()));
                }
                else
                    Item=new QTableWidgetItem(QString());
                Item->setFlags(Item->flags()&((Qt::ItemFlags)-1-Qt::ItemIsEnabled));
                Table->setItem(File_Pos-1, Data_Pos>9?(Data_Pos-1-10):(Data_Pos-1), Item);

                if (Data_Pos==9)
                    Data_Pos=19;
            }
        }
    }
    else
    {
        Table->setRowCount(1);
        Table->setColumnCount(1);
        Table->setHorizontalHeaderItem(0, new QTableWidgetItem(QString()));
        Table->setVerticalHeaderItem(0, new QTableWidgetItem(QString()));
        Table->setItem(0, 0, new QTableWidgetItem(QString("This file does not appear to include a DV track.")));
    }

    Table->resizeColumnsToContents ();
    Table->resizeRowsToContents();
    Table->resizeColumnsToContents ();
    Table->resizeRowsToContents();
}
