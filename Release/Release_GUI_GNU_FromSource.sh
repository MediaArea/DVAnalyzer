#! /bin/sh

#-----------------------------------------------------------------------
# Clean up
test -e AVPS_DV_Analyzer_GUI_GNU_FromSource.tar     && rm    AVPS_DV_Analyzer_GUI_GNU_FromSource.tar
test -e AVPS_DV_Analyzer_GUI_GNU_FromSource.tar.bz2 && rm    AVPS_DV_Analyzer_GUI_GNU_FromSource.tar.bz2
test -d AVPS_DV_Analyzer_GUI_GNU_FromSource         && rm -r AVPS_DV_Analyzer_GUI_GNU_FromSource
mkdir AVPS_DV_Analyzer_GUI_GNU_FromSource


#-----------------------------------------------------------------------
# Preparing : Project
cd ../Project/GNU/GUI
chmod u+x autogen
./autogen
cd ../../../Release


#-----------------------------------------------------------------------
# Copying : Project
mkdir -p AVPS_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI
cp ../Project/GNU/GUI/aclocal.m4 AVPS_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/autogen AVPS_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/config.guess AVPS_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/config.sub AVPS_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/configure AVPS_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/configure.ac AVPS_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/depcomp AVPS_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/install-sh AVPS_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/ltmain.sh AVPS_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/Makefile.am AVPS_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/Makefile.in AVPS_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/missing AVPS_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/dvanalyzer-gui.desktop AVPS_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/dvanalyzer-gui.kde3.desktop AVPS_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/dvanalyzer-gui.kde4.desktop AVPS_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/

#-----------------------------------------------------------------------
# Copying : Source
mkdir -p AVPS_DV_Analyzer_GUI_GNU_FromSource/Source/Common
cp -r ../Source/Common/*.h AVPS_DV_Analyzer_GUI_GNU_FromSource/Source/Common/
cp -r ../Source/Common/*.cpp AVPS_DV_Analyzer_GUI_GNU_FromSource/Source/Common/
mkdir -p AVPS_DV_Analyzer_GUI_GNU_FromSource/Source/GUI/Qt
cp -r ../Source/GUI/Qt/*.h AVPS_DV_Analyzer_GUI_GNU_FromSource/Source/GUI/Qt/
cp -r ../Source/GUI/Qt/*.cpp AVPS_DV_Analyzer_GUI_GNU_FromSource/Source/GUI/Qt/
mkdir -p AVPS_DV_Analyzer_GUI_GNU_FromSource/Source/Resource/Image/Menu
cp -r ../Source/Resource/Image/Menu/*.png AVPS_DV_Analyzer_GUI_GNU_FromSource/Source/Resource/Image/Menu/
cp -r ../Source/Resource/Image/Menu/*.png AVPS_DV_Analyzer_GUI_GNU_FromSource/Source/Resource/Image/Menu/
mkdir -p AVPS_DV_Analyzer_GUI_GNU_FromSource/Source/Resource
cp -r ../Source/Resource/*.qrc AVPS_DV_Analyzer_GUI_GNU_FromSource/Source/Resource/
mkdir -p AVPS_DV_Analyzer_GUI_GNU_FromSource/Source/Resource/Image/AVPS
cp -r ../Source/Resource/Image/AVPS/*.png AVPS_DV_Analyzer_GUI_GNU_FromSource/Source/Resource/Image/AVPS/
cp -r ../Source/Resource/Image/AVPS/*.png AVPS_DV_Analyzer_GUI_GNU_FromSource/Source/Resource/Image/AVPS/

#-----------------------------------------------------------------------
# Copying : Release
mkdir -p AVPS_DV_Analyzer_GUI_GNU_FromSource/Release
cp Release_GUI_GNU.sub AVPS_DV_Analyzer_GUI_GNU_FromSource/Release/
cp *.sh AVPS_DV_Analyzer_GUI_GNU_FromSource/Release/
chmod u+x AVPS_DV_Analyzer_GUI_GNU_FromSource/Release/*.sh

#-----------------------------------------------------------------------
# Copying : Information
cp ../License.html AVPS_DV_Analyzer_GUI_GNU_FromSource/
cp ../History_GUI.txt AVPS_DV_Analyzer_GUI_GNU_FromSource/
dos2unix AVPS_DV_Analyzer_GUI_GNU_FromSource/History_GUI.txt
cp ReadMe_GUI_Linux.txt AVPS_DV_Analyzer_GUI_GNU_FromSource/Release/
cp ReadMe_GUI_Mac.txt AVPS_DV_Analyzer_GUI_GNU_FromSource/Release/


#-----------------------------------------------------------------------
# Preparing Archive : AVPS_DV_Analyzer
mv AVPS_DV_Analyzer_GUI_GNU_FromSource AVPS_DV_Analyzer
mkdir AVPS_DV_Analyzer_GUI_GNU_FromSource
mv AVPS_DV_Analyzer AVPS_DV_Analyzer_GUI_GNU_FromSource/

#-----------------------------------------------------------------------
# Preparing Archive : From MediaInfoLib
cd ../../MediaInfoLib/Release
. ./Release_Lib_GNU_FromSource.sh
tar xf MediaInfo_Lib_GNU_FromSource.tar.bz2
rm MediaInfo_Lib_GNU_FromSource.tar.bz2
cd ../../AVPS_DV_Analyzer/Release
mv ../../MediaInfoLib/Release/MediaInfo_Lib_GNU_FromSource AVPS_DV_Analyzer_GUI_GNU_FromSource/MediaInfoLib

#-----------------------------------------------------------------------
# Preparing Archive : From ZenLib
cd ../../ZenLib/Release
. ./Release_GNU_FromSource.sh
tar xf ZenLib_GNU_FromSource.tar.bz2
rm ZenLib_GNU_FromSource.tar.bz2
cd ../../AVPS_DV_Analyzer/Release
mv ../../ZenLib/Release/ZenLib_GNU_FromSource AVPS_DV_Analyzer_GUI_GNU_FromSource/ZenLib

#-----------------------------------------------------------------------
# Preparing Archive : From Shared
mkdir -p AVPS_DV_Analyzer_GUI_GNU_FromSource/Shared/Project/_Common
cp -r ../../Shared/Project/_Common/*.sh AVPS_DV_Analyzer_GUI_GNU_FromSource/Shared/Project/_Common
mkdir -p AVPS_DV_Analyzer_GUI_GNU_FromSource/Shared/Project/ZLib
cp -r ../../Shared/Project/ZLib/*.sh AVPS_DV_Analyzer_GUI_GNU_FromSource/Shared/Project/ZLib

#-----------------------------------------------------------------------
# Preparing Archive : Automation
cp ../Project/GNU/GUI/AddThisToRoot_GUI_compile.sh AVPS_DV_Analyzer_GUI_GNU_FromSource/GUI_Compile.sh
chmod u+x AVPS_DV_Analyzer_GUI_GNU_FromSource/GUI_Compile.sh


#-----------------------------------------------------------------------
# Compressing Archive
tar jchf AVPS_DV_Analyzer_GUI_GNU_FromSource.tar.bz2 AVPS_DV_Analyzer_GUI_GNU_FromSource/*

#-----------------------------------------------------------------------
# Clean up
rm -r AVPS_DV_Analyzer_GUI_GNU_FromSource
