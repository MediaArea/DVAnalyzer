// Core - Main functions
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
// Core functions
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifndef CoreH
#define CoreH
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
#include <vector>
#include "MediaInfo/MediaInfo_Events.h"
using namespace MediaInfoNameSpace;
using namespace std;
//---------------------------------------------------------------------------

//***************************************************************************
// Class Core
//***************************************************************************

class Core
{
public:
    //Constructor/Destructor
    Core();
    ~Core();

    //Menu
    size_t                      Menu_File_Open_File             (const MediaInfoNameSpace::String &FileName);
    void                        Menu_File_Open_Files_Begin      ();
    size_t                      Menu_File_Open_Files_Continue   (const MediaInfoNameSpace::String &FileName);
    void                        Menu_File_Open_Directory        (const MediaInfoNameSpace::String &DirectoryName);
    float                       Menu_File_Open_State            ();
    void                        Menu_Verbosity_XX               (const MediaInfoNameSpace::String &Value);
    void                        Menu_Verbosity_03               ();
    void                        Menu_Verbosity_05               ();
    void                        Menu_Verbosity_09               ();
    void                        Menu_Verbosity_10               ();
    void                        Menu_Option_Preferences_Option  (const MediaInfoNameSpace::String &Param, const MediaInfoNameSpace::String &Value);

    //Datas
    string &FileNames();
    string &Summary();
    string &ByFrame();
    string  ByFrame(size_t Pos);
    string &XML();
    string &AppleXMLIF(size_t Version=5);
    string &MediaInfo_Text();
    string &MediaInfo_HTML();
    string &MediaInfo_XML();
    bool Errors_Stats_WithHeader;
    bool Errors_Stats_WithFooter;
    bool Errors_Stats_XML;
    bool Errors_Stats_AppleXMLIFv3;
    bool Errors_Stats_AppleXMLIFv4;
    bool Errors_Stats_AppleXMLIFv5;
    bool WithThreads;

    //Temp
    void    Data_Prepare();
    string &Text_Get() {return Text;};
    void* GUI_Main_Handler;
    void Analysis_NewFile();
    void Analysis_Clear();
    void Analysis_Frame_Add(const MediaInfo_Event_DvDif_Analysis_Frame_0* FrameData);

protected:
    MediaInfoNameSpace::MediaInfoList* MI;
    string  Text;
    float Verbosity;

    //Internal
    void Common_Header(size_t Pos, size_t Count);
    void Common_Footer(size_t Pos, size_t Count);
    void Common();
    std::vector<std::vector<MediaInfo_Event_DvDif_Analysis_Frame_0>*> Analysis;
    void Analysis_CreateText(string &Text, size_t File_Pos);
};

#endif
