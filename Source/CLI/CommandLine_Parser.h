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
#ifndef CommandLine_ParserH
#define CommandLine_ParserH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "Common/Core.h"
#include "ZenLib/Ztring.h"
//---------------------------------------------------------------------------

//***************************************************************************
//
//***************************************************************************

int Parse(Core &C, MediaInfoNameSpace::String &Argument);


//---------------------------------------------------------------------------
#define CL_METHOD(_NAME) \
    int CL_##_NAME(Core &C, const MediaInfoNameSpace::String &Argument)

#define CL_OPTION(_NAME) \
    int CL_##_NAME(Core &C, const MediaInfoNameSpace::String &Argument)

CL_OPTION(Help);
CL_OPTION(Help_xxx);
CL_OPTION(Help_Summary);
CL_OPTION(Help_Details);
CL_OPTION(Help_Verbosity);
CL_OPTION(Header);
CL_OPTION(Footer);
CL_OPTION(Xml);
CL_OPTION(AppleXMLIFv3);
CL_OPTION(AppleXMLIFv4);
CL_OPTION(AppleXMLIFv5);
CL_OPTION(Verbosity);
CL_OPTION(LogFile);
CL_OPTION(Version);
CL_OPTION(Default);

//***************************************************************************
// Options which need actions
//***************************************************************************

void LogFile_Action(const string &Inform);

#endif
