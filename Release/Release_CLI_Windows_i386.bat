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
del   DVAnalyzer_CLI_Windows_i386.zip
rmdir DVAnalyzer_CLI_Windows_i386 /S /Q
mkdir DVAnalyzer_CLI_Windows_i386

rem --- Copying : Exe ---
xcopy ..\Project\MSVC2022\CLI\Win32\Release\dvanalyzer.exe DVAnalyzer_CLI_Windows_i386\ /S

rem --- Copying : Plugins ---
xcopy ..\Source\Resource\Plugin\Custom\* DVAnalyzer_CLI_Windows_i386\Plugin\Custom\ /S

rem --- Copying : Information files ---
copy ..\License.html DVAnalyzer_CLI_Windows_i386\
copy ..\History_CLI.txt DVAnalyzer_CLI_Windows_i386\History.txt
copy Readme_CLI_Windows.txt DVAnalyzer_CLI_Windows_i386\ReadMe.txt

rem --- Compressing Archive ---
cd DVAnalyzer_CLI_Windows_i386\
%BPATH%\Windows\7-Zip\7z a -r -tzip ..\DVAnalyzer_CLI_Windows_i386.zip *
cd ..


rem --- Clean up ---
if "%1"=="SkipCleanUp" goto SkipCleanUp
rmdir DVAnalyzer_CLI_Windows_i386\ /S /Q
:SkipCleanUp
