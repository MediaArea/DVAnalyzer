@rem echo off

rem --- Search binaries ---
set BPATH=
if exist "%~dp0\..\..\..\MediaArea-Utils-Binaries" set BPATH="%~dp0\..\..\..\MediaArea-Utils-Binaries"
if exist "%~dp0\..\..\MediaArea-Utils-Binaries" set BPATH="%~dp0\..\..\MediaArea-Utils-Binaries"
if "%BPATH%"=="" (
    echo "ERROR: binaries path not found"
    exit /b 1
)

@rem --- Clean up ---
del   AVPS_DV_Analyzer_CLI_Windows_x64.zip
rmdir AVPS_DV_Analyzer_CLI_Windows_x64 /S /Q
mkdir AVPS_DV_Analyzer_CLI_Windows_x64

rem --- Copying : Exe ---
xcopy ..\Project\MSVC2015\CLI\x64\Release\dvanalyzer.exe AVPS_DV_Analyzer_CLI_Windows_x64\ /S

rem --- Copying : Plugins ---
xcopy ..\Source\Resource\Plugin\Custom\* AVPS_DV_Analyzer_CLI_Windows_x64\Plugin\Custom\ /S

rem --- Copying : Information files ---
copy ..\License.html AVPS_DV_Analyzer_CLI_Windows_x64\
copy ..\History_CLI.txt AVPS_DV_Analyzer_CLI_Windows_x64\History.txt
copy Readme_CLI_Windows.txt AVPS_DV_Analyzer_CLI_Windows_x64\ReadMe.txt


rem --- Compressing Archive ---
cd AVPS_DV_Analyzer_CLI_Windows_x64\
%BPATH%\Windows\7-Zip\7z a -r -tzip ..\AVPS_DV_Analyzer_CLI_Windows_x64.zip *
cd ..

rem --- Clean up ---
if "%1"=="SkipCleanUp" goto SkipCleanUp
rmdir AVPS_DV_Analyzer_CLI_Windows_x64\ /S /Q
:SkipCleanUp
