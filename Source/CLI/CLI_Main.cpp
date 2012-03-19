// MediaArea_DV_Analyzer_CLI - A Command Line Interface for DV analyzing
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
#include <iostream>
#include <vector>
#include <algorithm>
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "CLI/CommandLine_Parser.h"
#include "CLI/CLI_Help.h"
#include "CLI/IO.h"
#include "Common/Core.h"
using namespace std;
using namespace MediaInfoNameSpace;
//---------------------------------------------------------------------------

//***************************************************************************
// Main
//***************************************************************************

int main(int argc, char* argv_ansi[])
{
    //Localisation
    setlocale(LC_ALL, """""");

    //Configure MediaInfo core
    Core C;

    //Retrieve command line (mainly for Unicode) and parse it
    GETCOMMANDLINE();
    vector<String> List;
    for (int Pos=1; Pos<argc; Pos++)
    {
        //First part of argument (before "=") should be case insensitive
        String Argument(argv[Pos]);
        size_t Egal_Pos=Argument.find(_T('='));
        if (Egal_Pos==string::npos)
            Egal_Pos=Argument.size();
        transform(Argument.begin(), Argument.begin()+Egal_Pos, Argument.begin(), (int(*)(int))tolower); //(int(*)(int)) is a patch for unix
        int Return=Parse (C, Argument);
        if (Return>=0)
            return Return; //no more tasks to do
        if (Return==-1)
            List.push_back(argv[Pos]); //Append the filename to the list of filenames to parse
    }

    //If no filenames (and no options)
    if (List.empty())
    {
        std::cout<<Help_Nothing();
        return 0;
    }

    //Parse files
    C.Menu_File_Open_Files_Begin();
    size_t Files_Count=0;
    for (size_t Pos=0; Pos<List.size(); Pos++)
        Files_Count+=C.Menu_File_Open_Files_Continue(List[Pos]);

    //Output
    STRINGOUT(C.ByFrame());

    //Output, in a file if needed
    LogFile_Action(C.ByFrame());
    
    return Files_Count?0:1;
}
//---------------------------------------------------------------------------

