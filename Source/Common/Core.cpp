// Main - Main functions
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
#include "Common/Core.h"
#include "ZenLib/ZtringListList.h"
#include "ZenLib/Ztring.h"
#include "ZenLib/File.h"
#include "ZenLib/Format/Http/Http_Utils.h"
#include "Common/Common_About.h"
#include <sstream>
#include <string>
#include <cstring>
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
using namespace ZenLib;
//---------------------------------------------------------------------------

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

void __stdcall Event_CallBackFunction(unsigned char* Data_Content, size_t Data_Size, void* UserHandler_Void)
{
    //Retrieving UserHandler
    Core*                               UserHandler=(Core*)UserHandler_Void;
    struct MediaInfo_Event_Generic*     Event_Generic=(struct MediaInfo_Event_Generic*) Data_Content;
    unsigned char                       ParserID;
    unsigned short                      EventID;
    unsigned char                       EventVersion;

    //Integrity test
    if (Data_Size<4)
        return; //There is a problem

    //Retrieving EventID
    ParserID    =(unsigned char) ((Event_Generic->EventCode&0xFF000000)>>24);
    EventID     =(unsigned short)((Event_Generic->EventCode&0x00FFFF00)>>8 );
    EventVersion=(unsigned char) ( Event_Generic->EventCode&0x000000FF     );
    switch (ParserID)
    {
        case MediaInfo_Parser_None :    
                switch (EventID)
                {    
                    case MediaInfo_Event_General_Start                                          : if (EventVersion==0 && Data_Size==sizeof(struct MediaInfo_Event_General_Start_0)) UserHandler->Analysis_NewFile(); break;
                    default                                                                     : ;
                }
                break;
        case MediaInfo_Parser_DvDif :    
                switch (EventID)
                {    
                    case MediaInfo_Event_DvDif_Analysis_Frame                                   : if (EventVersion==0 && Data_Size==sizeof(struct MediaInfo_Event_DvDif_Analysis_Frame_0)) UserHandler->Analysis_Frame_Add((MediaInfo_Event_DvDif_Analysis_Frame_0*)Event_Generic); break;
                    default                                                                     : ;
                }
                break;
        default : ; //ParserID is unknown
    }
}

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
Core::Core()
{
    MI=new MediaInfoNameSpace::MediaInfoList;
    MI->Option(_T("File_Event_CallBackFunction"), _T("CallBack=memory://")+Ztring::ToZtring((size_t)&Event_CallBackFunction)+_T(";UserHandler=memory://")+Ztring::ToZtring((size_t)this));
    MI->Option(_T("ParseSpeed"), _T("1.000"));
    MI->Option(_T("File_DvDif_Analysis"), _T("1"));
    Errors_Stats_WithHeader=false;
    Errors_Stats_WithFooter=false;
    Errors_Stats_XML=false;
    Errors_Stats_AppleXMLIFv3=false;
    Errors_Stats_AppleXMLIFv4=false;
    Errors_Stats_AppleXMLIFv5=false;
    Verbosity=0.5;
    WithThreads=false;
}

Core::~Core()
{
    delete MI;

    Analysis_Clear();
}

//---------------------------------------------------------------------------
void Core::Data_Prepare()
{
    //Inform
    Text=Ztring(MI->Inform((size_t)-1)).To_UTF8().c_str();
}

//---------------------------------------------------------------------------
void Core::Analysis_NewFile()
{
    Analysis.push_back(new std::vector<MediaInfo_Event_DvDif_Analysis_Frame_0>);
}

//---------------------------------------------------------------------------
void Core::Analysis_Clear()
{
    for (size_t File_Pos=0; File_Pos<Analysis.size(); File_Pos++)
    {
        for (size_t Pos=0; Pos<Analysis[File_Pos]->size(); Pos++)
            if (Analysis[File_Pos]->at(Pos).Errors)
                delete[] Analysis[File_Pos]->at(Pos).Errors; //Analysis[Pos].Errors=NULL;
        delete Analysis[File_Pos]; //Analysis[File_Pos]=NULL;
    }
    Analysis.clear();
}

//---------------------------------------------------------------------------
void Core::Analysis_Frame_Add(const MediaInfo_Event_DvDif_Analysis_Frame_0* FrameData)
{
    MediaInfo_Event_DvDif_Analysis_Frame_0 ToPush;
    std::memcpy(&ToPush, FrameData, sizeof(MediaInfo_Event_DvDif_Analysis_Frame_0));
    if (ToPush.Errors)
    {
        size_t SizeToCopy=std::strlen(FrameData->Errors)+1;
        ToPush.Errors=new char[SizeToCopy];
        std::memcpy(ToPush.Errors, FrameData->Errors, SizeToCopy);
    }
    Analysis[Analysis.size()-1]->push_back(ToPush);
}

//***************************************************************************
// Menu
//***************************************************************************

//---------------------------------------------------------------------------
size_t Core::Menu_File_Open_File (const MediaInfoNameSpace::String& FileName)
{
    Menu_File_Open_Files_Begin();
    return Menu_File_Open_Files_Continue(FileName);
}

//---------------------------------------------------------------------------
void Core::Menu_File_Open_Files_Begin ()
{
    Analysis_Clear();
    
    MI->Close();
    if (WithThreads)
        MI->Option(_T("Thread"), _T("1"));
}

//---------------------------------------------------------------------------
size_t Core::Menu_File_Open_Files_Continue (const MediaInfoNameSpace::String &FileName)
{
    size_t ToReturn=MI->Open(FileName);
    if (WithThreads)
        return 0;
    return ToReturn;
}

//---------------------------------------------------------------------------
void Core::Menu_File_Open_Directory (const MediaInfoNameSpace::String &DirectoryName)
{
    MI->Open(DirectoryName);
}

//---------------------------------------------------------------------------
float Core::Menu_File_Open_State ()
{
    return (((float)MI->State_Get())/10000);
}

//---------------------------------------------------------------------------
void Core::Menu_Verbosity_XX (const MediaInfoNameSpace::String &Value)
{
    Verbosity=Ztring(Value).To_float32();
}

//---------------------------------------------------------------------------
void Core::Menu_Verbosity_03 ()
{
    Verbosity=(float)0.3;
}

//---------------------------------------------------------------------------
void Core::Menu_Verbosity_05 ()
{
    Verbosity=(float)0.5;
}

//---------------------------------------------------------------------------
void Core::Menu_Verbosity_09 ()
{
    Verbosity=(float)0.9;
}

//---------------------------------------------------------------------------
void Core::Menu_Verbosity_10 ()
{
    Verbosity=(float)1.0;
}

//---------------------------------------------------------------------------
void Core::Menu_Option_Preferences_Option (const MediaInfoNameSpace::String& Param, const MediaInfoNameSpace::String& Value)
{
    MI->Option(Param, Value);
}

//***************************************************************************
// Helpers
//***************************************************************************

//---------------------------------------------------------------------------
string& Core::FileNames ()
{
    Text.clear();

    size_t Count=MI->Count_Get();
    for (size_t Pos=0; Pos<Count; Pos++)
    {
        Text+=Ztring(MI->Get(Pos, Stream_General, 0, _T("CompleteName"))).To_UTF8();
        
        Text+='\n';
    }

    return Text;
};

//---------------------------------------------------------------------------
string& Core::Summary ()
{
    Text.clear();
    
    size_t Count=MI->Count_Get();
    for (size_t Pos=0; Pos<Count; Pos++)
    {
        if (Errors_Stats_WithHeader)
        {
            Text+=NameVersion_Text();
            Text+="\n\n";
            Common_Header(Pos, Count);
        }

        if (MI->Get(Pos, Stream_General, 0, _T("Format"))!=_T("DV")
         && MI->Get(Pos, Stream_Video, 0, _T("Format"))!=_T("DV")
         && MI->Get(Pos, Stream_Audio, 0, _T("MuxingMode"))!=_T("DV")
         && MI->Get(Pos, Stream_Audio, 1, _T("MuxingMode"))!=_T("DV")
         && MI->Get(Pos, Stream_Audio, 2, _T("MuxingMode"))!=_T("DV")
         && MI->Get(Pos, Stream_Audio, 3, _T("MuxingMode"))!=_T("DV")
         && MI->Get(Pos, Stream_Audio, 4, _T("MuxingMode"))!=_T("DV"))
            Text+="This file does not appear to include a DV track.";
        else if (Verbosity>=(float)0.5)
            Text+=Ztring(MI->Get(Pos, Stream_Video, 0, _T("Errors_Stats_End_05"))).To_UTF8();
        else if (Verbosity>=(float)0.3)
            Text+=Ztring(MI->Get(Pos, Stream_Video, 0, _T("Errors_Stats_End_03"))).To_UTF8();
        
        Text+='\n';

        Common_Footer(Pos, Count);
    }

    Common();

    return Text;
}

//---------------------------------------------------------------------------
void Core::Analysis_CreateText (string &Text, size_t File_Pos)
{
    float32 FrameRate=Ztring(MI->Get(File_Pos, Stream_Video, 0, _T("FrameRate_Original"))).To_float32();
    if (!FrameRate)
        FrameRate=Ztring(MI->Get(File_Pos, Stream_Video, 0, _T("FrameRate"))).To_float32();
    size_t A=Analysis[File_Pos]->size();
    for (size_t Frame=0; Frame<Analysis[File_Pos]->size(); Frame++)
    {
        if (float32_int32s(Verbosity*10)>=Analysis[File_Pos]->at(Frame).Verbosity)
        {
            Ztring Errors_Stats_Line;
            
            //Frame number
            Ztring Frame_Number_Padded=Ztring::ToZtring(Frame);
            if (Frame_Number_Padded.size()<8)
                Frame_Number_Padded.insert(Frame_Number_Padded.begin(), 8-Frame_Number_Padded.size(), _T(' '));
            Errors_Stats_Line+=Frame_Number_Padded;
            Errors_Stats_Line+=_T('\t');

            //Time Offset
            float64 Time_Offset=Frame*1000/(FrameRate?FrameRate:29.97); //Should never happen, but 29.97 if not available
            Errors_Stats_Line+=Ztring().Duration_From_Milliseconds((int64u)Time_Offset);
            Errors_Stats_Line+=_T('\t');

            //Timecode
            int32u TimeCode=(Analysis[File_Pos]->at(Frame).TimeCode&(0x7FFFF<<8))>>8;
            if (TimeCode!=0x7FFFF)
            {
                Errors_Stats_Line+=_T('0')+TimeCode/36000; TimeCode%=36000;
                Errors_Stats_Line+=_T('0')+TimeCode/ 3600; TimeCode%= 3600;
                Errors_Stats_Line+=_T(':');
                Errors_Stats_Line+=_T('0')+TimeCode/  600; TimeCode%=  600;
                Errors_Stats_Line+=_T('0')+TimeCode/   60; TimeCode%=   60;
                Errors_Stats_Line+=_T(':');
                Errors_Stats_Line+=_T('0')+TimeCode/   10; TimeCode%=  10;
                Errors_Stats_Line+=_T('0')+TimeCode;
                Errors_Stats_Line+=(Analysis[File_Pos]->at(Frame).TimeCode&0x00000080)?_T(';'):_T(':');
                Errors_Stats_Line+=_T('0')+(Analysis[File_Pos]->at(Frame).TimeCode&0x0000003F)/10;
                Errors_Stats_Line+=_T('0')+(Analysis[File_Pos]->at(Frame).TimeCode&0x0000003F)%10;
            }
            else
            {
                Errors_Stats_Line+=_T("XX:XX:XX:XX");
            }
            Errors_Stats_Line+=_T('\t');

            //Timecode order coherency
            if ((Analysis[File_Pos]->at(Frame).TimeCode&(1<<31)))
                Errors_Stats_Line+=_T('R');
            else if ((Analysis[File_Pos]->at(Frame).TimeCode&(1<<30)))
                Errors_Stats_Line+=_T('N');
            else
                Errors_Stats_Line+=_T(' ');
            Errors_Stats_Line+=_T('\t');

            //RecDate/RecTime
            int32u Years=(Analysis[File_Pos]->at(Frame).RecordedDateTime1&(0x7F<<17))>>17;
            if (Years!=0x7F)
            {
                int32u Months=(Analysis[File_Pos]->at(Frame).RecordedDateTime2&(0x0F<<12))>>12;
                int32u Days=(Analysis[File_Pos]->at(Frame).RecordedDateTime2&(0x1F<<8))>>8;
                Errors_Stats_Line+=Years<75?_T("20"):_T("19");
                Errors_Stats_Line+=_T('0')+Years  /10;
                Errors_Stats_Line+=_T('0')+Years  %10;
                Errors_Stats_Line+=_T('-');
                Errors_Stats_Line+=_T('0')+Months /10;
                Errors_Stats_Line+=_T('0')+Months %10;
                Errors_Stats_Line+=_T('-');
                Errors_Stats_Line+=_T('0')+Days   /10;
                Errors_Stats_Line+=_T('0')+Days   %10;
            }
            else
                Errors_Stats_Line+=_T("XXXX-XX-XX");
            Errors_Stats_Line+=_T(" ");
            int32u Seconds=Analysis[File_Pos]->at(Frame).RecordedDateTime1&0x1FFFF;
            if (Seconds!=0x1FFFF)
            {
                Errors_Stats_Line+=_T('0')+Seconds/36000; Seconds%=36000;
                Errors_Stats_Line+=_T('0')+Seconds/ 3600; Seconds%= 3600;
                Errors_Stats_Line+=_T(':');
                Errors_Stats_Line+=_T('0')+Seconds/  600; Seconds%=  600;
                Errors_Stats_Line+=_T('0')+Seconds/   60; Seconds%=   60;
                Errors_Stats_Line+=_T(':');
                Errors_Stats_Line+=_T('0')+Seconds/   10; Seconds%=  10;
                Errors_Stats_Line+=_T('0')+Seconds;
                int32u Frames=Analysis[File_Pos]->at(Frame).RecordedDateTime2&0x7F;
                if (Frames!=0x7F)
                {
                    int32u Milliseconds=float64_int32s(Frames*1000/(FrameRate?FrameRate:29.97)); //Should never happen, but 29.97 if not available
                    Errors_Stats_Line+=_T('.');
                    Errors_Stats_Line+=_T('0')+(MediaInfoLib::Char)(Milliseconds/100);
                    Errors_Stats_Line+=_T('0')+(MediaInfoLib::Char)((Milliseconds%100)/10);
                    Errors_Stats_Line+=_T('0')+(MediaInfoLib::Char)(Milliseconds%10);
                }
                else
                    Errors_Stats_Line+=_T("    ");
            }
            else
                Errors_Stats_Line+=_T("XX:XX:XX.XXX");
            Errors_Stats_Line+=_T('\t');

            //RecDate/RecTime coherency, Rec start/end
            if (Analysis[File_Pos]->at(Frame).RecordedDateTime1&(1<<30))
                Errors_Stats_Line+=_T('N');
            else
                Errors_Stats_Line+=_T(' ');
            Errors_Stats_Line+=_T('\t');

            //Speed_Arb_Current
            if (Analysis[File_Pos]->at(Frame).Arb&(1<<4))
                Errors_Stats_Line+=Ztring::ToZtring(Analysis[File_Pos]->at(Frame).Arb&0x0F, 16);
            else
                Errors_Stats_Line+=_T('X');
            Errors_Stats_Line+=_T('\t');

            //Speed_Arb_Current coherency
            if (Analysis[File_Pos]->at(Frame).Arb&(1<<7))
                Errors_Stats_Line+=_T('R');
            else if (Analysis[File_Pos]->at(Frame).Arb&(1<<6))
                Errors_Stats_Line+=_T('N');
            else
                Errors_Stats_Line+=_T(' ');
            Errors_Stats_Line+=_T('\t');

            //Start
            if (Analysis[File_Pos]->at(Frame).RecordedDateTime1&(1<<29))
                Errors_Stats_Line+=_T('S');
            else
                Errors_Stats_Line+=_T(' ');
            Errors_Stats_Line+=_T('\t');

            //End
            if (Analysis[File_Pos]->at(Frame).RecordedDateTime1&(1<<28))
                Errors_Stats_Line+=_T('E');
            else
                Errors_Stats_Line+=_T(' ');
            Errors_Stats_Line+=_T('\t');
            
            //Errors
            if (Analysis[File_Pos]->at(Frame).Errors)
            {
                Ztring Errors; Errors.From_Local(Analysis[File_Pos]->at(Frame).Errors);
                ZtringList Errors_List;
                Errors_List.Separator_Set(0, _T("\t"));
                Errors_List.Write(Errors);
                for (size_t List_Pos=0; List_Pos<10; List_Pos++)
                {
                    if (List_Pos<Errors_List.size() && !Errors_List[List_Pos].empty())
                        Errors_Stats_Line+=Ztring::ToZtring((List_Pos+1)%10);
                    else
                        Errors_Stats_Line+=_T(' ');
                    Errors_Stats_Line+=_T('\t');
                }
                Errors_Stats_Line+=Errors;
            }

            Errors_Stats_Line.TrimRight(_T('\t'));
            Errors_Stats_Line.TrimRight(_T(' '));
            Errors_Stats_Line.TrimRight(_T('\t'));
            Errors_Stats_Line.TrimRight(_T(' '));
            Errors_Stats_Line.TrimRight(_T('\t'));
            Errors_Stats_Line.TrimRight(_T(' '));
            Errors_Stats_Line.TrimRight(_T('\t'));
            Errors_Stats_Line.TrimRight(_T(' '));
            Errors_Stats_Line.TrimRight(_T('\t'));
            Errors_Stats_Line.TrimRight(_T(' '));
            Text+=Errors_Stats_Line.To_UTF8();
            Text+='\n';
        }
    }
}

//---------------------------------------------------------------------------
string& Core::ByFrame ()
{
    //From CLI
    if (Errors_Stats_XML)
        return XML();
    if (Errors_Stats_AppleXMLIFv3)
        return AppleXMLIF(3);
    if (Errors_Stats_AppleXMLIFv4)
        return AppleXMLIF(4);
    if (Errors_Stats_AppleXMLIFv5)
        return AppleXMLIF(5);
    
    Text.clear();
    
    size_t Count=MI->Count_Get();
    for (size_t Pos=0; Pos<Count; Pos++)
    {
        if (Errors_Stats_WithHeader)
        {
            Text+=NameVersion_Text();
            Text+=", verbosity is ";
            Text+=Ztring::ToZtring(Verbosity*10, 0).To_Local();
            Text+="\n\n";
            Common_Header(Pos, Count);
            Text+=Ztring(MI->Get(Pos, Stream_Video, 0, _T("Errors_Stats_Begin"))).To_Local(); Text+='\n';
        }
        
        Analysis_CreateText(Text, Pos);

        if (Errors_Stats_WithFooter)
        {
            Text+='\n';
            if (Verbosity>=(float)0.5)
                Text+=Ztring(MI->Get(Pos, Stream_Video, 0, _T("Errors_Stats_End_05"))).To_Local();
            else if (Verbosity>=(float)0.3)
                Text+=Ztring(MI->Get(Pos, Stream_Video, 0, _T("Errors_Stats_End_03"))).To_Local();
        }

        Common_Footer(Pos, Count);
    }

    Common();
    
    return Text;
}

//---------------------------------------------------------------------------
string Core::ByFrame (size_t Pos)
{
    string Text; //Text.clear();
    
    Text=Ztring(MI->Get(Pos, Stream_Video, 0, _T("Errors_Stats_Begin"))).To_Local(); Text+='\n';
    for (size_t Text_Pos=0; Text_Pos<Text.size(); Text_Pos++)
        if (Text[Text_Pos]=='&')
            Text[Text_Pos]='\n';

    Analysis_CreateText(Text, Pos);
    
    return Text;
}

//---------------------------------------------------------------------------
string &Core::XML()
{
    Text.clear();

    //Header
    Text+="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    Text+="<dvanalyzer>\n";
    Text+="\t<configuration>\n";
    Text+="\t\t<company>"+Ztring().From_UTF8(NameVersion_Text()).SubString(_T(" by "), _T("")).To_Local()+"</company>\n";
    Text+="\t\t<version>"+Ztring().From_UTF8(NameVersion_Text()).SubString(_T("v."), _T(" by ")).To_Local()+"</version>\n";
    Text+="\t\t<verbosity>"+Ztring::ToZtring(Verbosity*10, 0).To_Local()+"</verbosity>\n";
    Text+="\t</configuration>\n";
    
    enum fields
    {
        frame,
        abs_time,
        dv_timecode,
        timecode_non_consecutive,
        recdate_rectime,
        recdate_rectime_non_consecutive,
        arb,
        arb_non_consecutive,
        flag_start,
        flag_end,
        error_1,
        error_2,
        error_3,
        error_4,
        error_5,
        error_6,
        error_7,
        error_8,
        error_9,
        error_0,
        error_1_more,
        error_2_more,
        error_3_more,
        error_4_more,
        error_5_more,
        error_6_more,
        error_7_more,
        error_8_more,
        error_9_more,
        error_0_more,
    };

    size_t Count=MI->Count_Get();
    for (size_t File_Pos=0; File_Pos<Count; File_Pos++)
    {
        //XML Header
        Text+="\t<file>\n";
        Text+="\t\t<filepath>"+Ztring(MI->Get(File_Pos, Stream_General, 0, _T("CompleteName"))).To_UTF8()+"</filepath>\n";
        
        //By Frame - Retrieving
        ZtringListList List;
        List.Separator_Set(0, _T("\n"));
        List.Separator_Set(1, _T("\t"));
        string List_Text; Analysis_CreateText(List_Text, File_Pos); List.Write(Ztring().From_Local(List_Text)); List_Text.clear();
        for (size_t Frame=0; Frame<List.size(); Frame++)
            for (size_t Field=0; Field<List[Frame].size(); Field++)
                List[Frame][Field].Trim();

        //By Frame - For each line
        if (!List.empty())
            Text+="\t\t<frames>\n";
        for (size_t Pos=0; Pos<List.size(); Pos++)
        {
            Text+="\t\t\t<frame";
            if (!List(Pos, error_1                          ).empty()
             || !List(Pos, error_2                          ).empty()
             || !List(Pos, error_3                          ).empty()
             || !List(Pos, error_4                          ).empty()
             || !List(Pos, error_5                          ).empty()
             || !List(Pos, error_6                          ).empty()
             || !List(Pos, error_7                          ).empty()
             || !List(Pos, error_8                          ).empty()
             || !List(Pos, error_9                          ).empty()
             || !List(Pos, error_0                          ).empty())
                Text+=" type=\"error\"";
            else
            if (!List(Pos, timecode_non_consecutive         ).empty()
             || !List(Pos, recdate_rectime_non_consecutive  ).empty()
             || !List(Pos, arb_non_consecutive              ).empty()
             || !List(Pos, error_1                          ).empty()
             || !List(Pos, error_2                          ).empty()
             || !List(Pos, error_3                          ).empty()
             || !List(Pos, error_4                          ).empty()
             || !List(Pos, error_5                          ).empty()
             || !List(Pos, error_6                          ).empty()
             || !List(Pos, error_7                          ).empty()
             || !List(Pos, error_8                          ).empty()
             || !List(Pos, error_9                          ).empty()
             || !List(Pos, error_0                          ).empty())
                Text+=" type=\"info\"";
            else
            if (Pos==0)
                Text+=" type=\"first\"";
            else
            if (Pos+1==List.size())
                Text+=" type=\"last\"";
            Text+=">\n";


            //General
            Text+="\t\t\t\t<frame>"+List(Pos, frame).TrimLeft().To_Local()+"</frame>\n";
            Text+="\t\t\t\t<abs_time>"+List(Pos, abs_time).To_Local()+"</abs_time>\n";
            Text+="\t\t\t\t<dv_timecode>"+List(Pos, dv_timecode).To_Local()+"</dv_timecode>\n";
            Text+="\t\t\t\t<recdate_rectime>"+List(Pos, recdate_rectime).TrimRight().To_Local()+"</recdate_rectime>\n";
            Text+="\t\t\t\t<arbitrary_bit>"+List(Pos, arb).TrimRight().To_Local()+"</arbitrary_bit>\n";
            
            //Flags
            if (!List(Pos, flag_start                        ).empty()
             || !List(Pos, flag_end                          ).empty())
            {
                Text+="\t\t\t\t<flags>\n";
                
                if (!List(Pos, flag_start).empty())
                    Text+="\t\t\t\t\t<flag>REC_START</flag>\n";
                if (!List(Pos, flag_end).empty())
                    Text+="\t\t\t\t\t<flag>REC_END</flag>\n";
                
                Text+="\t\t\t\t</flags>\n";
            }

            //Events
            if (!List(Pos, timecode_non_consecutive         ).empty()
             || !List(Pos, recdate_rectime_non_consecutive  ).empty()
             || !List(Pos, arb_non_consecutive              ).empty()
             || !List(Pos, error_1                          ).empty()
             || !List(Pos, error_2                          ).empty()
             || !List(Pos, error_3                          ).empty()
             || !List(Pos, error_4                          ).empty()
             || !List(Pos, error_5                          ).empty()
             || !List(Pos, error_6                          ).empty()
             || !List(Pos, error_7                          ).empty()
             || !List(Pos, error_8                          ).empty()
             || !List(Pos, error_9                          ).empty()
             || !List(Pos, error_0                          ).empty())
            {
                Text+="\t\t\t\t<events>\n";
                
                //Info
                if (List(Pos, timecode_non_consecutive)==_T("N"))
                    Text+="\t\t\t\t\t<event type=\"info\" event_id=\"NTC\">non-consecutive DV timecode</event>\n";
                if (List(Pos, timecode_non_consecutive)==_T("R"))
                    Text+="\t\t\t\t\t<event type=\"info\" event_id=\"RTC\">repeating DV timecode</event>\n";
                if (List(Pos, recdate_rectime_non_consecutive)==_T("N"))
                    Text+="\t\t\t\t\t<event type=\"info\" event_id=\"NRT\">non-consecutive recdate/rectime</event>\n";
                if (List(Pos, recdate_rectime_non_consecutive)==_T("R"))
                    Text+="\t\t\t\t\t<event type=\"info\" event_id=\"RRT\">repeating recdate/rectime</event>\n";
                if (List(Pos, arb_non_consecutive)==_T("N"))
                    Text+="\t\t\t\t\t<event type=\"info\" event_id=\"NAB\">non-consecutive arbitrary bit</event>\n";
                if (List(Pos, arb_non_consecutive)==_T("R"))
                    Text+="\t\t\t\t\t<event type=\"info\" event_id=\"RAB\">repeating arbitrary bit</event>\n";
                
                //Errors
                if (!List(Pos, error_1).empty())
                {
                    List(Pos, error_1_more).Trim();
                    while (List(Pos, error_1_more).FindAndReplace(_T("  "), _T(" "), 0, Ztring_Recursive));
                    while (List(Pos, error_1_more).FindAndReplace(_T("( "), _T("("), 0, Ztring_Recursive));
                    Text+="\t\t\t\t\t<event type=\"error\" event_id=\""+Ztring::ToZtring(error_1-error_1+1).To_Local()+"\" event_type=\"video error concealment\">"+List(Pos, error_1_more).To_Local()+"</event>\n";
                }
                if (!List(Pos, error_2).empty())
                {
                    List(Pos, error_2_more).Trim();
                    while (List(Pos, error_2_more).FindAndReplace(_T("  "), _T(" "), 0, Ztring_Recursive));
                    while (List(Pos, error_2_more).FindAndReplace(_T("( "), _T("("), 0, Ztring_Recursive));
                    Text+="\t\t\t\t\t<event type=\"error\" event_id=\""+Ztring::ToZtring(error_2-error_1+1).To_Local()+"\" event_type=\"audio error code\">"+List(Pos, error_2_more).To_Local()+"</event>\n";
                }
                if (!List(Pos, error_3).empty())
                    Text+="\t\t\t\t\t<event type=\"error\" event_id=\""+Ztring::ToZtring(error_3-error_1+1).To_Local()+"\" event_type=\"DV timecode incoherency\">"+List(Pos, error_3_more).To_Local()+"</event>\n";
                if (!List(Pos, error_4).empty())
                    Text+="\t\t\t\t\t<event type=\"error\" event_id=\""+Ztring::ToZtring(error_4-error_1+1).To_Local()+"\" event_type=\"DIF incoherency\">"+List(Pos, error_4_more).To_Local()+"</event>\n";
                if (!List(Pos, error_5).empty())
                    Text+="\t\t\t\t\t<event type=\"error\" event_id=\""+Ztring::ToZtring(error_5-error_1+1).To_Local()+"\" event_type=\"Arbitrary bit inconsistency\">"+List(Pos, error_5_more).To_Local()+"</event>\n";
                if (!List(Pos, error_6).empty())
                    Text+="\t\t\t\t\t<event type=\"error\" event_id=\""+Ztring::ToZtring(error_6-error_1+1).To_Local()+"\" event_type=\"Stts fluctuation\">"+List(Pos, error_6_more).To_Local()+"</event>\n";
                
                Text+="\t\t\t\t</events>\n";
            }
            Text+="\t\t\t</frame>\n";
        }
        if (!List.empty())
        {
            Text+="\t\t</frames>\n";

            //FrameCount
            if (!MI->Get(File_Pos, Stream_Video, 0, _T("FrameCount_Speed")).empty())
            {
                Text+="\t\t<frames_count>"+Ztring(MI->Get(File_Pos, Stream_Video, 0, _T("FrameCount_Speed"))).To_Local()+"</frames_count>\n";
                if (MI->Get(File_Pos, Stream_Video, 0, _T("Format"))==_T("DV") && MI->Get(File_Pos, Stream_Video, 0, _T("FrameCount_Speed"))!=MI->Get(File_Pos, Stream_Video, 0, _T("FrameCount")))
                {
                    Text+="\t\t<warnings>\n";
                    Text+="\t\t\t<warning code=\"1\">Warning, frame count is maybe incoherant (reported by MediaInfo: "+Ztring(MI->Get(File_Pos, Stream_Video, 0, _T("FrameCount"))).To_Local()+")</warning>\n";
                    Text+="\t\t</warnings>\n";
                }
            }
        }

        //Summary - Retrieving
        List.clear();
        if (Verbosity>=(float)0.5)
            List.Write(MI->Get(File_Pos, Stream_Video, 0, _T("Errors_Stats_End_05")));
        else if (Verbosity>=(float)0.3)
            List.Write(MI->Get(File_Pos, Stream_Video, 0, _T("Errors_Stats_End_03")));

        //Summary - For each line
        bool events_summary_open=false;
        for (size_t Pos=0; Pos<List.size(); Pos++)
        {
            if (List(Pos, 0).empty())
            {
                if (events_summary_open)
                {
                    Text+="\t\t</events_summary>\n";
                    events_summary_open=false;
                }
            }
            
            //error_1
            if (List(Pos, 0).find(_T("Frame count with video error concealment: "))==0)
            {
                if (!events_summary_open)
                {
                    Text+="\t\t<events_summary>\n";
                    events_summary_open=true;
                }
                Text+="\t\t\t<event type=\"error\" event_id=\"1\" event_type=\"video error concealment\">\n";
                Text+="\t\t\t\t<count>"+List(Pos+1, 0).SubString(_T(": "), _T(" errors")).TrimLeft().To_Local()+"</count>\n";
                Text+="\t\t\t\t<frames_count>"+List(Pos, 0).SubString(_T(": "), _T(" frames")).To_Local()+"</frames_count>\n";
                Pos++;
                Text+="\t\t\t</event>\n";
            }
            
            //error_2
            if (List(Pos, 0).find(_T("Frame count with CH1 audio error code: "))==0)
            {
                if (!events_summary_open)
                {
                    Text+="\t\t<events_summary>\n";
                    events_summary_open=true;
                }
                Text+="\t\t\t<event type=\"error\" event_id=\"2\" event_type=\"audio error code\" ch=\"1\" >\n";
                Text+="\t\t\t\t<count>"+List(Pos+1, 0).SubString(_T(": "), _T(" errors")).TrimLeft().To_Local()+"</count>\n";
                Text+="\t\t\t\t<frames_count>"+List(Pos, 0).SubString(_T(": "), _T(" frames")).To_Local()+"</frames_count>\n";
                Text+="\t\t\t\t<summary>"+List(Pos+1, 0).SubString(_T("("), _T(")")).To_Local()+"</summary>\n";
                Pos++;
                Text+="\t\t\t</event>\n";
            }
            if (List(Pos, 0).find(_T("Frame count with CH2 audio error code: "))==0)
            {
                if (!events_summary_open)
                {
                    Text+="\t\t<events_summary>\n";
                    events_summary_open=true;
                }
                Text+="\t\t\t<event type=\"error\" event_id=\"2\" event_type=\"audio error code\" ch=\"2\" >\n";
                Text+="\t\t\t\t<count>"+List(Pos+1, 0).SubString(_T(": "), _T(" errors")).TrimLeft().To_Local()+"</count>\n";
                Text+="\t\t\t\t<frames_count>"+List(Pos, 0).SubString(_T(": "), _T(" frames")).To_Local()+"</frames_count>\n";
                Text+="\t\t\t\t<summary>"+List(Pos+1, 0).SubString(_T("("), _T(")")).To_Local()+"</summary>\n";
                Pos++;
                Text+="\t\t\t</event>\n";
            }

            //error_3
            if (List(Pos, 0).find(_T("Frame count with DV timecode incoherency: "))==0)
            {
                if (!events_summary_open)
                {
                    Text+="\t\t<events_summary>\n";
                    events_summary_open=true;
                }
                Text+="\t\t\t<event type=\"error\" event_id=\"3\" event_type=\"DV timecode incoherency\">\n";
                Text+="\t\t\t\t<frames_count>"+List(Pos, 0).SubString(_T(": "), _T(" frames")).To_Local()+"</frames_count>\n";
                Text+="\t\t\t</event>\n";
            }

            //error_4
            if (List(Pos, 0).find(_T("Frame count with DIF incoherency: "))==0)
            {
                if (!events_summary_open)
                {
                    Text+="\t\t<events_summary>\n";
                    events_summary_open=true;
                }
                Text+="\t\t\t<event type=\"error\" event_id=\"4\" event_type=\"DIF incoherency\">\n";
                Text+="\t\t\t\t<frames_count>"+List(Pos, 0).SubString(_T(": "), _T(" frames")).To_Local()+"</frames_count>\n";
                Text+="\t\t\t</event>\n";
            }

            //error_5
            if (List(Pos, 0).find(_T("Frame count with Arbitrary bit inconsistency: "))==0)
            {
                if (!events_summary_open)
                {
                    Text+="\t\t<events_summary>\n";
                    events_summary_open=true;
                }
                Text+="\t\t\t<event type=\"error\" event_id=\"5\" event_type=\"Arbitrary bit inconsistency\">\n";
                Text+="\t\t\t\t<frames_count>"+List(Pos, 0).SubString(_T(": "), _T(" frames")).To_Local()+"</frames_count>\n";
                Text+="\t\t\t</event>\n";
            }

            //error_6
            if (List(Pos, 0).find(_T("Frame count with stts fluctuation: "))==0)
            {
                if (!events_summary_open)
                {
                    Text+="\t\t<events_summary>\n";
                    events_summary_open=true;
                }
                Text+="\t\t\t<event type=\"error\" event_id=\"6\" event_type=\"stts fluctuation\">\n";
                Text+="\t\t\t\t<frames_count>"+List(Pos, 0).SubString(_T(": "), _T(" frames")).To_Local()+"</frames_count>\n";
                Text+="\t\t\t</event>\n";
            }

            //Date
            if (List(Pos, 0).find(_T("Abs. Time"))==0)
            {
                Text+="\t\t<reverse_edl>\n";
                
                size_t PosLine=1;
                while (Pos+PosLine<List.size() && !List(Pos+PosLine, 0).empty())
                {
                    Text+="\t\t\t<edit>\n";
                    Text+="\t\t\t\t<frame_start>"+List(Pos+PosLine, 3).SubString(_T(""), _T(" -")).TrimLeft().To_Local()+"</frame_start>\n";
                    Text+="\t\t\t\t<frame_end>"+List(Pos+PosLine, 3).SubString(_T("- "), _T("")).TrimLeft().To_Local()+"</frame_end>\n";
                    Text+="\t\t\t\t<abstime_start>"+List(Pos+PosLine, 0).To_Local()+"</abstime_start>\n";
                    //Text+="\t\t\t\t<abstime_end>"+List(Pos+PosLine, 0).To_Local()+"</abstime_end>\n";
                    Text+="\t\t\t\t<timecode_start>"+List(Pos+PosLine, 1).SubString(_T(""), _T(" -")).To_Local()+"</timecode_start>\n";
                    Text+="\t\t\t\t<timecode_end>"+List(Pos+PosLine, 1).SubString(_T("- "), _T("")).To_Local()+"</timecode_end>\n";
                    Text+="\t\t\t\t<recdatetime_start>"+List(Pos+PosLine, 2).SubString(_T(""), _T(" -")).TrimRight().To_Local()+"</recdatetime_start>\n";
                    Text+="\t\t\t\t<recdatetime_end>"+List(Pos+PosLine, 2).SubString(_T("- "), _T("")).TrimRight().To_Local()+"</recdatetime_end>\n";
                    Text+="\t\t\t</edit>\n";

                    PosLine++;
                }

                Text+="\t\t</reverse_edl>\n";
            }
        }

        //XML Footer
        Text+="\t</file>\n";
    }
         
    //Footer
    Text+="</dvanalyzer>\n";

    return Text;
}

//---------------------------------------------------------------------------
string &Core::AppleXMLIF(size_t Version)
{
    Text.clear();

    //Header
    Text+="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    Text+="<!DOCTYPE xmeml>\n";
    Text+="<!-- Generated by ";
    Text+=NameVersion_Text(); Text+=", verbosity is "+Ztring::ToZtring(Verbosity*10, 0).To_Local();
    Text+=" -->\n";
    Text+="<xmeml version=\""; Text+=Version==5?'5':'4'; Text+="\">\n";
	Text+="<importoptions>\n";
	Text+="	<createnewproject>TRUE</createnewproject>\n";
	Text+="	<defsequencepresetname>useFirstClipSettings</defsequencepresetname>\n";
	if (Version>=4)
        Text+="	<createfcpprojectatxmlfilepath>TRUE</createfcpprojectatxmlfilepath>\n";
	Text+="</importoptions>\n";
    
    enum fields
    {
        frame,
        abs_time,
        dv_timecode,
        timecode_non_consecutive,
        recdate_rectime,
        recdate_rectime_non_consecutive,
        arb,
        arb_non_consecutive,
        flag_start,
        flag_end,
        error_1,
        error_2,
        error_3,
        error_4,
        error_5,
        error_6,
        error_7,
        error_8,
        error_9,
        error_0,
        error_1_more,
        error_2_more,
        error_3_more,
        error_4_more,
        error_5_more,
        error_6_more,
        error_7_more,
        error_8_more,
        error_9_more,
        error_0_more,
    };

    size_t Count=MI->Count_Get();
    for (size_t File_Pos=0; File_Pos<Count; File_Pos++)
    {
        if (MI->Get(File_Pos, Stream_Video, 0, _T("Format"))==_T("DV"))
        {

        //XML Header
        Text+="\t<clip id=\""+Ztring(MI->Get(File_Pos, Stream_General, 0, _T("CompleteName"))).To_UTF8()+"\">\n";
        Text+="\t\t<name>"+Ztring(MI->Get(File_Pos, Stream_General, 0, _T("FileName"))).To_UTF8()+"</name>\n";
        Text+="\t\t<duration>"+Ztring(MI->Get(File_Pos, Stream_Video, 0, _T("FrameCount"))).To_Local()+"</duration>\n";
        Text+="\t\t<rate>\n";
        Text+="\t\t\t<ntsc>"; Text+=MI->Get(File_Pos, Stream_Video, 0, _T("Standard"))==_T("NTSC")?"TRUE":"FALSE"; Text+="</ntsc>\n";
        Text+="\t\t\t<timebase>"+Ztring::ToZtring(Ztring(MI->Get(File_Pos, Stream_Video, 0, MI->Get(File_Pos, Stream_Video, 0, _T("FrameRate_Original")).empty()?_T("FrameRate"):_T("FrameRate_Original"))).To_float32(), 0).To_Local()+"</timebase>\n";
        Text+="\t\t</rate>\n";
        Text+="\t\t<file id=\""+Ztring(MI->Get(File_Pos, Stream_General, 0, _T("CompleteName"))).To_Local()+" "+Ztring::ToZtring(File_Pos).To_Local()+"\">\n";
        Text+="\t\t\t<name>"+Ztring(MI->Get(File_Pos, Stream_General, 0, _T("FileName"))).To_UTF8()+"</name>\n";
        Text+="\t\t\t<pathurl>file://localhost";
        #ifdef __WINDOWS__
            Text+="/";
        #endif //__WINDOWS
            Text+=Format::Http::URL_Encoded_Encode(Ztring(MI->Get(File_Pos, Stream_General, 0, _T("CompleteName"))).To_UTF8())+"</pathurl>\n";
        Text+="\t\t</file>\n";
        
        //By Frame - Retrieving
        ZtringListList List;
        List.Separator_Set(0, _T("\n"));
        List.Separator_Set(1, _T("\t"));
        string List_Text; Analysis_CreateText(List_Text, File_Pos); List.Write(Ztring().From_Local(List_Text)); List_Text.clear();
        for (size_t Frame=0; Frame<List.size(); Frame++)
            for (size_t Field=0; Field<List[Frame].size(); Field++)
                List[Frame][Field].Trim();

        //By Frame - For each line
        string Name, Comment;
        bool Info=false, Error=false;
        for (size_t Pos=0; Pos<List.size(); Pos++)
        {
            //Setup
            Name.clear();
            Comment.clear();
            
            //Flags
            if (!List(Pos, flag_start).empty())
            {
                Name+=List(Pos, recdate_rectime).Trim().To_Local()+" - ";
                Comment+="REC_START - ";
                Info=true;
            }
            if (!List(Pos, flag_end).empty())
            {
                Name+=List(Pos, recdate_rectime).Trim().To_Local()+" - ";
                Comment+="REC_END - ";
                Info=true;
            }

            //Info
            if (List(Pos, timecode_non_consecutive)==_T("N")
             || List(Pos, timecode_non_consecutive)==_T("R"))
            {
                Name+=List(Pos, dv_timecode).To_Local()+" - ";
                if (List(Pos, timecode_non_consecutive)==_T("N"))
                    Comment+="non-consecutive DV timecode - ";
                if (List(Pos, timecode_non_consecutive)==_T("R"))
                    Comment+="repeating DV timecode - ";
                Info=true;
            }
            if (List(Pos, recdate_rectime_non_consecutive)==_T("N")
             || List(Pos, recdate_rectime_non_consecutive)==_T("R"))
            {
                Name+=List(Pos, recdate_rectime).TrimRight().To_Local()+" - ";
                if (List(Pos, recdate_rectime_non_consecutive)==_T("N"))
                    Comment+="non-consecutive recdate/rectime - ";
                if (List(Pos, recdate_rectime_non_consecutive)==_T("R"))
                    Comment+="repeating recdate/rectime - ";
                Info=true;
            }
            if (List(Pos, arb_non_consecutive)==_T("N")
             || List(Pos, arb_non_consecutive)==_T("R"))
            {
                Name+=List(Pos, arb).TrimRight().To_Local()+" - ";
                if (List(Pos, arb_non_consecutive)==_T("N"))
                    Comment+="non-consecutive arbitrary bit - ";
                if (List(Pos, arb_non_consecutive)==_T("R"))
                    Comment+="repeating arbitrary bit - ";
                Info=true;
            }
            
            //Errors
            if (!List(Pos, error_1).empty())
            {
                List(Pos, error_1_more).Trim();
                while (List(Pos, error_1_more).FindAndReplace(_T("  "), _T(" "), 0, Ztring_Recursive));
                while (List(Pos, error_1_more).FindAndReplace(_T("( "), _T("("), 0, Ztring_Recursive));
                Name+="video error concealment - ";
                Comment+=List(Pos, error_1_more).To_Local()+" - ";
                Error=true;
            }
            if (!List(Pos, error_2).empty())
            {
                List(Pos, error_2_more).Trim();
                while (List(Pos, error_2_more).FindAndReplace(_T("  "), _T(" "), 0, Ztring_Recursive));
                while (List(Pos, error_2_more).FindAndReplace(_T("( "), _T("("), 0, Ztring_Recursive));
                Name+="audio error code - ";
                Comment+=List(Pos, error_2_more).To_Local()+" - ";
                Error=true;
            }
            if (!List(Pos, error_3).empty())
            {
                Name+="DV timecode incoherency - ";
                Comment+=List(Pos, error_3_more).To_Local()+" - ";
                Error=true;
            }
            if (!List(Pos, error_4).empty())
            {
                Name+="DIF incoherency - ";
                Comment+=List(Pos, error_4_more).To_Local()+" - ";
                Error=true;
            }
            if (!List(Pos, error_5).empty())
            {
                Name+="Arbitrary bit inconsistency - ";
                Comment+=List(Pos, error_5_more).To_Local()+" - ";
                Error=true;
            }
            if (!List(Pos, error_6).empty())
            {
                Name+="Stts fluctuation - ";
                Comment+=List(Pos, error_6_more).To_Local()+" - ";
                Error=true;
            }
            
            if (!Name.empty())
            {
                Name.resize(Name.size()-3);
                Comment.resize(Comment.size()-3);
                Text+="\t\t<marker>\n";
                Text+="\t\t\t<name>"+Name+"</name>\n";
                Text+="\t\t\t<comment>"+Comment+"</comment>\n";
                Text+="\t\t\t<in>"+List(Pos, frame).TrimLeft().To_Local()+"</in>\n";
                Text+="\t\t\t<out>-1</out>\n";
                if (Version==5 && (Error || Info))
                {
                    Text+="\t\t\t<color>\n";
                    Text+="\t\t\t\t<alpha>0</alpha>\n";
                    if (Error && Info)
                        Text+="\t\t\t\t<red>127</red>\n";
                    else if (Error)
                        Text+="\t\t\t\t<red>255</red>\n";
                    else if (Info)
                        Text+="\t\t\t\t<red>0</red>\n";
                    Text+="\t\t\t\t<green>0</green>\n";
                    if (Error && Info)
                        Text+="\t\t\t\t<blue>127</blue>\n";
                    else if (Error)
                        Text+="\t\t\t\t<blue>0</blue>\n";
                    else if (Info)
                        Text+="\t\t\t\t<blue>255</blue>\n";
                    Text+="\t\t\t</color>\n";
                }
                Text+="\t\t</marker>\n";
            }
        }

        //XML Footer
        Text+="\t</clip>\n";

        }
    }
         
    //Footer
    Text+="</xmeml>\n";

    return Text;
}

//---------------------------------------------------------------------------
string& Core::MediaInfo_Text ()
{
    Text=Ztring(MI->Inform()).To_UTF8();

    //Adapting
    size_t Begin=Text.find("Errors_Stats_Begin");
    size_t End=Text.find("\r\n\r\n", Begin);
    if (Begin!=std::string::npos && End!=std::string::npos)
            Text.erase(Begin, End-Begin);

    return Text;
}

//---------------------------------------------------------------------------
string& Core::MediaInfo_HTML ()
{
    MI->Option(_T("Inform"), _T("HTML"));
    Text=Ztring(MI->Inform()).To_UTF8();
    MI->Option(_T("Inform"), _T(""));

    //Adapting
    size_t Begin=Text.find("  <tr>"+Ztring(EOL).To_Local()+"    <td><i>Errors_Stats_Begin :</i></td>");
    size_t End=Text.find("</table>", Begin);
    if (Begin!=std::string::npos && End!=std::string::npos)
            Text.erase(Begin, End-Begin);

    return Text;
}

//---------------------------------------------------------------------------
string& Core::MediaInfo_XML ()
{
    MI->Option(_T("Inform"), _T("XML"));
    Text=Ztring(MI->Inform()).To_UTF8();
    MI->Option(_T("Inform"), _T(""));

    //Adapting
    size_t Begin=Text.find("<Errors_Stats_Begin>");
    size_t End=Text.find("</track>", Begin);
    if (Begin!=std::string::npos && End!=std::string::npos)
            Text.erase(Begin, End-Begin);

    return Text;
}

//---------------------------------------------------------------------------
void Core::Common_Header (size_t Pos, size_t)
{
    Text+=Ztring(MI->Get(Pos, Stream_General, 0, _T("CompleteName"))).To_Local()+'\n';
    Text+='\n';
}

//---------------------------------------------------------------------------
void Core::Common_Footer (size_t Pos, size_t Count)
{
    if (MI->Get(Pos, Stream_Video, 0, _T("Format"))==_T("DV") && !MI->Get(Pos, Stream_Video, 0, _T("FrameCount")).empty() && MI->Get(Pos, Stream_Video, 0, _T("FrameCount"))!=MI->Get(Pos, Stream_Video, 0, _T("FrameCount_Speed")))
    {
        Text+='\n';
        Text+="Warning, frame count is maybe incoherant (reported by MediaInfo: ";
        Text+=Ztring(MI->Get(Pos, Stream_Video, 0, _T("FrameCount"))).To_Local();
        Text+=")\n";
    }
    if (MI->Get(Pos, Stream_General, 0, _T("Format"))!=_T("DV"))
    {
        //Searching the count of DV audio and of container
        size_t Count=MI->Count_Get(Pos, Stream_Audio);
        size_t DV_Count=0;
        size_t Container_Count=0;
        for (size_t Audio_Pos=0; Audio_Pos<Count; Audio_Pos++)
        {
            if (MI->Get(Pos, Stream_Audio, Audio_Pos, _T("MuxingMode"))==_T("DV"))
                DV_Count++;
            else
                Container_Count++;
        }
        
        if (Container_Count<DV_Count)
        {
            //Text+='\n');
            //Text+="Warning, the DV track audio configuration doesn't match the container (")+Ztring::ToZtring(DV_Count)+_T(" DV audio tracks, ")+Ztring::ToZtring(Container_Count)+_T(" container audio tracks)\n");
        }
    }
    if (Pos+1<Count)
    {
        Text+='\n';
        Text+="***************************************************************************\n";
        Text+='\n';
    }
}

//---------------------------------------------------------------------------
void Core::Common ()
{
    for (size_t Pos=0; Pos<Text.size(); Pos++)
        if (Text[Pos]=='&')
            Text[Pos]='\n';
}
