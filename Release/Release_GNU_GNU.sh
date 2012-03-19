#! /bin/sh

#-----------------------------------------------------------------------
# Clean up
rm    AVPS_DV_Analyzer_GUI_GNU.tar
rm    AVPS_DV_Analyzer_GUI_GNU.tar.bz2
rm -r AVPS_DV_Analyzer_GUI_GNU
mkdir AVPS_DV_Analyzer_GUI_GNU

#-----------------------------------------------------------------------
# Copying : Exe
cp ../Project/GNU/GUI/MediaInfo AVPS_DV_Analyzer_GUI_GNU/MediaInfo

#-----------------------------------------------------------------------
# Copying : Information file
cp ../License.html AVPS_DV_Analyzer_GUI_GNU/
cp ../History_GUI.txt AVPS_DV_Analyzer_GUI_GNU/History.txt
cp ReadMe_GUI_Linux.txt AVPS_DV_Analyzer_GUI_GNU/ReadMe.txt

#-----------------------------------------------------------------------
# Compressing Archive
tar jcf AVPS_DV_Analyzer_GUI_GNU.tar.bz2 AVPS_DV_Analyzer_GUI_GNU
rm AVPS_DV_Analyzer_GUI_GNU.tar

#-----------------------------------------------------------------------
# Clean up
#if "%1"=="SkipCleanUp" goto SkipCleanUp
rm -r AVPS_DV_Analyzer_GUI_GNU
#:SkipCleanUp