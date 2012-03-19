@rem echo off

@rem --- Clean up ---
del   AVPS_DV_Analyzer_CLI_Windows_i386.zip
rmdir AVPS_DV_Analyzer_CLI_Windows_i386 /S /Q
mkdir AVPS_DV_Analyzer_CLI_Windows_i386

rem --- Copying : Exe ---
xcopy ..\Project\MSVC2010\CLI\Win32\Release\dvanalyzer.exe AVPS_DV_Analyzer_CLI_Windows_i386\ /S

rem --- Copying : Plugins ---
xcopy ..\Source\Resource\Plugin\Custom\* AVPS_DV_Analyzer_CLI_Windows_i386\Plugin\Custom\ /S

rem --- Copying : Information files ---
copy ..\License.html AVPS_DV_Analyzer_CLI_Windows_i386\
copy ..\History_CLI.txt AVPS_DV_Analyzer_CLI_Windows_i386\History.txt
copy Readme_CLI_Windows.txt AVPS_DV_Analyzer_CLI_Windows_i386\ReadMe.txt

rem --- Compressing Archive ---
cd AVPS_DV_Analyzer_CLI_Windows_i386\
..\..\..\Shared\Binary\Windows_i386\7-Zip\7z a -r -tzip ..\AVPS_DV_Analyzer_CLI_Windows_i386.zip *
cd ..


rem --- Clean up ---
if "%1"=="SkipCleanUp" goto SkipCleanUp
rmdir AVPS_DV_Analyzer_CLI_Windows_i386\ /S /Q
:SkipCleanUp
