// CLI_Help - Help for DV Analyzer
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
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "CLI/CLI_Help.h"
#include "Common/Common_Help.h"
#include <sstream>
//---------------------------------------------------------------------------

//***************************************************************************
//
//***************************************************************************

//---------------------------------------------------------------------------
std::string Help()
{
    std::ostringstream ToDisplay;

    ToDisplay<<"Usage: \"dvanalyzer [-Options...] FileName1 [Filename2...]\""<<std::endl;
    ToDisplay<<""<<std::endl;
    ToDisplay<<"Options:"<<std::endl;
    ToDisplay<<"--Help, -h         Display this help and exit"<<std::endl;
    ToDisplay<<"--Version          Display AVPS DV Analyzer version and exit"<<std::endl;
    ToDisplay<<""<<std::endl;
    ToDisplay<<"--Header           With a header (file name, column names...)"<<std::endl;
    ToDisplay<<"--Footer           With a footer (global stats)"<<std::endl;
    ToDisplay<<"--XML              XML form"<<std::endl;
    ToDisplay<<"--AppleXMLIFv3     Apple XML Interchange Format, version 3 (for Final Cut 5 or higher)"<<std::endl;
    ToDisplay<<"--AppleXMLIFv4     Apple XML Interchange Format, version 4 (for Final Cut 6 or higher)"<<std::endl;
    ToDisplay<<"--AppleXMLIFv5     Apple XML Interchange Format, version 5 (for Final Cut 7 or higher)"<<std::endl;
    ToDisplay<<""<<std::endl;
    ToDisplay<<"--Verbosity=x      Set the verbosity of the output"<<std::endl;
    ToDisplay<<""<<std::endl;
    ToDisplay<<"--Help-Summary     Display more info about the output format (short)"<<std::endl;
    ToDisplay<<"--Help-Detail      Display more info about the output format (long)"<<std::endl;
    ToDisplay<<"--Help-Verbosity   Display more info about the verbosity option"<<std::endl;
    ToDisplay<<"--LogFile=...      Save the output in the specified file"<<std::endl;

    return ToDisplay.str();
}

//---------------------------------------------------------------------------
std::string Help_Nothing()
{
    std::ostringstream ToDisplay;

    ToDisplay<<"Usage: \"dvanalyzer [-Options...] FileName1 [Filename2...]\""<<std::endl;
    ToDisplay<<"\"dvanalyzer --Help\" for displaying more information"<<std::endl;

    return ToDisplay.str();
}

//---------------------------------------------------------------------------
std::string Help_Summary()
{
    return Help_Summary_Text();
}

//---------------------------------------------------------------------------
std::string Help_Details()
{
    return Help_Details_Text();
}

//---------------------------------------------------------------------------
std::string Help_Verbosity()
{
    std::ostringstream ToDisplay;

    ToDisplay<<"0-2                : No info"<<std::endl;
    ToDisplay<<"3-4                : Errors only"<<std::endl;
    ToDisplay<<"5-8                : Errors and info"<<std::endl;
    ToDisplay<<"9                  : Errors and info (including arbitrary bit)"<<std::endl;
    ToDisplay<<"10                 : All"<<std::endl;

    return ToDisplay.str();
}

