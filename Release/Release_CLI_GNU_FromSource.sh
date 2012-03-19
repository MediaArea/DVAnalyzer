#! /bin/sh

#-----------------------------------------------------------------------
# Clean up
test -e AVPS_DV_Analyzer_CLI_GNU_FromSource.tar     && rm    AVPS_DV_Analyzer_CLI_GNU_FromSource.tar
test -e AVPS_DV_Analyzer_CLI_GNU_FromSource.tar.bz2 && rm    AVPS_DV_Analyzer_CLI_GNU_FromSource.tar.bz2
test -d AVPS_DV_Analyzer_CLI_GNU_FromSource         && rm -r AVPS_DV_Analyzer_CLI_GNU_FromSource
mkdir AVPS_DV_Analyzer_CLI_GNU_FromSource


#-----------------------------------------------------------------------
# Preparing : Project
cd ../Project/GNU/CLI
chmod u+x autogen
./autogen
cd ../../../Release


#-----------------------------------------------------------------------
# Copying : Project
mkdir -p AVPS_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI
cp ../Project/GNU/CLI/aclocal.m4 AVPS_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/autogen AVPS_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/config.guess AVPS_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/config.sub AVPS_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/configure AVPS_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/configure.ac AVPS_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/depcomp AVPS_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/install-sh AVPS_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/ltmain.sh AVPS_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/Makefile.am AVPS_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/Makefile.in AVPS_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/missing AVPS_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI/

#-----------------------------------------------------------------------
# Copying : Source
mkdir -p AVPS_DV_Analyzer_CLI_GNU_FromSource/Source/Common
cp -r ../Source/Common/*.h AVPS_DV_Analyzer_CLI_GNU_FromSource/Source/Common/
cp -r ../Source/Common/*.cpp AVPS_DV_Analyzer_CLI_GNU_FromSource/Source/Common/
mkdir -p AVPS_DV_Analyzer_CLI_GNU_FromSource/Source/CLI
cp -r ../Source/CLI/*.h AVPS_DV_Analyzer_CLI_GNU_FromSource/Source/CLI/
cp -r ../Source/CLI/*.cpp AVPS_DV_Analyzer_CLI_GNU_FromSource/Source/CLI/

#-----------------------------------------------------------------------
# Copying : Release
mkdir -p AVPS_DV_Analyzer_CLI_GNU_FromSource/Release
cp Release_CLI_GNU.sub AVPS_DV_Analyzer_CLI_GNU_FromSource/Release/
cp *.sh AVPS_DV_Analyzer_CLI_GNU_FromSource/Release/
chmod u+x AVPS_DV_Analyzer_CLI_GNU_FromSource/Release/*.sh

#-----------------------------------------------------------------------
# Copying : Information
cp ../License.html AVPS_DV_Analyzer_CLI_GNU_FromSource/
cp ../History_CLI.txt AVPS_DV_Analyzer_CLI_GNU_FromSource/
dos2unix AVPS_DV_Analyzer_CLI_GNU_FromSource/History_CLI.txt
cp ReadMe_CLI_Linux.txt AVPS_DV_Analyzer_CLI_GNU_FromSource/Release/
cp ReadMe_CLI_Mac.txt AVPS_DV_Analyzer_CLI_GNU_FromSource/Release/


#-----------------------------------------------------------------------
# Preparing Archive : AVPS_DV_Analyzer
mv AVPS_DV_Analyzer_CLI_GNU_FromSource AVPS_DV_Analyzer
mkdir AVPS_DV_Analyzer_CLI_GNU_FromSource
mv AVPS_DV_Analyzer AVPS_DV_Analyzer_CLI_GNU_FromSource/

#-----------------------------------------------------------------------
# Preparing Archive : From MediaInfoLib
cd ../../MediaInfoLib/Release
. ./Release_Lib_GNU_FromSource.sh
tar xf MediaInfo_Lib_GNU_FromSource.tar.bz2
rm MediaInfo_Lib_GNU_FromSource.tar.bz2
cd ../../AVPS_DV_Analyzer/Release
mv ../../MediaInfoLib/Release/MediaInfo_Lib_GNU_FromSource AVPS_DV_Analyzer_CLI_GNU_FromSource/MediaInfoLib

#-----------------------------------------------------------------------
# Preparing Archive : From ZenLib
cd ../../ZenLib/Release
. ./Release_GNU_FromSource.sh
tar xf ZenLib_GNU_FromSource.tar.bz2
rm ZenLib_GNU_FromSource.tar.bz2
cd ../../AVPS_DV_Analyzer/Release
mv ../../ZenLib/Release/ZenLib_GNU_FromSource AVPS_DV_Analyzer_CLI_GNU_FromSource/ZenLib

#-----------------------------------------------------------------------
# Preparing Archive : From Shared
mkdir -p AVPS_DV_Analyzer_CLI_GNU_FromSource/Shared/Project/_Common
cp -r ../../Shared/Project/_Common/*.sh AVPS_DV_Analyzer_CLI_GNU_FromSource/Shared/Project/_Common
mkdir -p AVPS_DV_Analyzer_CLI_GNU_FromSource/Shared/Project/ZLib
cp -r ../../Shared/Project/ZLib/*.sh AVPS_DV_Analyzer_CLI_GNU_FromSource/Shared/Project/ZLib
mkdir -p AVPS_DV_Analyzer_CLI_GNU_FromSource/Shared/Project/ZLib/Template/projects/GNU
cp -r ../../Shared/Project/ZLib/Template/projects/GNU/* AVPS_DV_Analyzer_CLI_GNU_FromSource/Shared/Project/ZLib/Template/projects/GNU

#-----------------------------------------------------------------------
# Preparing Archive : Automation
cp ../Project/GNU/CLI/AddThisToRoot_CLI_compile.sh AVPS_DV_Analyzer_CLI_GNU_FromSource/CLI_Compile.sh
chmod u+x AVPS_DV_Analyzer_CLI_GNU_FromSource/CLI_Compile.sh


#-----------------------------------------------------------------------
# Compressing Archive
tar jchf AVPS_DV_Analyzer_CLI_GNU_FromSource.tar.bz2 AVPS_DV_Analyzer_CLI_GNU_FromSource/*

#-----------------------------------------------------------------------
# Clean up
rm -r AVPS_DV_Analyzer_CLI_GNU_FromSource
