@echo off

rem --- Clean up ---
del AVPS_DV_Analyzer_CLI_GNU_Prepare.7z
rmdir AVPS_DV_Analyzer_CLI_GNU_Prepare /S /Q
mkdir AVPS_DV_Analyzer_CLI_GNU_Prepare


rem --- Copying : Sources ---
xcopy ..\Source\Common\*.cpp AVPS_DV_Analyzer_CLI_GNU_Prepare\Source\Common\ /S
xcopy ..\Source\Common\*.h AVPS_DV_Analyzer_CLI_GNU_Prepare\Source\Common\ /S
xcopy ..\Source\CLI\*.cpp AVPS_DV_Analyzer_CLI_GNU_Prepare\Source\CLI\ /S
xcopy ..\Source\CLI\*.h AVPS_DV_Analyzer_CLI_GNU_Prepare\Source\CLI\ /S

rem --- Copying : Projects ---
xcopy ..\Project\GNU\CLI\autogen AVPS_DV_Analyzer_CLI_GNU_Prepare\Project\GNU\CLI\ /S
xcopy ..\Project\GNU\CLI\configure.ac AVPS_DV_Analyzer_CLI_GNU_Prepare\Project\GNU\CLI\ /S
xcopy ..\Project\GNU\CLI\Makefile.am AVPS_DV_Analyzer_CLI_GNU_Prepare\Project\GNU\CLI\ /S
xcopy ..\Project\GNU\CLI\AddThisToRoot_CLI_compile.sh AVPS_DV_Analyzer_CLI_GNU_Prepare\Project\GNU\CLI\ /S

rem --- Copying : Release ---
xcopy Release_CLI_GNU.sub AVPS_DV_Analyzer_CLI_GNU_Prepare\Release\
xcopy Release_CLI_*.sh AVPS_DV_Analyzer_CLI_GNU_Prepare\Release\

rem --- Copying : Information files ---
copy ..\History_CLI.txt AVPS_DV_Analyzer_CLI_GNU_Prepare\
copy ..\License.html AVPS_DV_Analyzer_CLI_GNU_Prepare\
copy ReadMe_CLI_Linux.txt AVPS_DV_Analyzer_CLI_GNU_Prepare\Release\
copy ReadMe_CLI_Mac.txt AVPS_DV_Analyzer_CLI_GNU_Prepare\Release\


rem --- Preparing Archive : AVPS_DV_Analyzer ---
move AVPS_DV_Analyzer_CLI_GNU_Prepare AVPS_DV_Analyzer
mkdir AVPS_DV_Analyzer_CLI_GNU_Prepare
move AVPS_DV_Analyzer AVPS_DV_Analyzer_CLI_GNU_Prepare

rem --- Preparing Archive : MediaInfoLib ---
cd ..\..\MediaInfoLib\Release
call Release_Lib_GNU_Prepare.bat SkipCleanUp SkipCompression
cd ..\..\AVPS_DV_Analyzer\Release
move ..\..\MediaInfoLib\Release\MediaInfo_Lib_GNU_Prepare AVPS_DV_Analyzer_CLI_GNU_Prepare\MediaInfoLib

rem --- Preparing Archive : ZenLib ---
cd ..\..\ZenLib\Release
call Release_GNU_Prepare.bat SkipCleanUp SkipCompression
cd ..\..\AVPS_DV_Analyzer\Release
move ..\..\ZenLib\Release\ZenLib_GNU_Prepare AVPS_DV_Analyzer_CLI_GNU_Prepare\ZenLib

rem --- Shared ---
mkdir AVPS_DV_Analyzer_CLI_GNU_Prepare\Shared
xcopy ..\..\Shared\Project\_Common\* AVPS_DV_Analyzer_CLI_GNU_Prepare\Shared\Project\_Common\ /S
xcopy ..\..\Shared\Project\ZLib\*.sh AVPS_DV_Analyzer_CLI_GNU_Prepare\Shared\Project\ZLib\ /S
xcopy ..\..\Shared\Project\ZLib\Template\projects\GNU\* AVPS_DV_Analyzer_CLI_GNU_Prepare\Shared\Project\ZLib\Template\projects\GNU\ /S


rem --- Compressing Archive ---
if "%2"=="SkipCompression" goto SkipCompression
..\..\Shared\Binary\Windows_i386\7-Zip\7z a -r -t7z -mx9 AVPS_DV_Analyzer_CLI_GNU_Prepare.7z AVPS_DV_Analyzer_CLI_GNU_Prepare\*
:SkipCompression

rem --- Clean up ---
if "%1"=="SkipCleanUp" goto SkipCleanUp
rmdir AVPS_DV_Analyzer_CLI_GNU_Prepare /S /Q
:SkipCleanUp
