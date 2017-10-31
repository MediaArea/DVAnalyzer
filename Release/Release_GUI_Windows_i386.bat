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
del   ADVAnalyzer_GUI_Windows_i386.exe
del   DVAnalyzer_GUI_Windows_i386_WithoutInstaller.7z
rmdir DVAnalyzer_GUI_Windows_i386 /S /Q
mkdir DVAnalyzer_GUI_Windows_i386

@rem --- Copying : Exe ---
copy  ..\Project\MSVC2017\GUI\Win32\Release\AVPS_DV_Analyzer_GUI.exe DVAnalyzer_GUI_Windows_i386\DVAnalyzer.exe

@rem --- Copying : Plugins ---
xcopy ..\Source\Resource\Plugin\* DVAnalyzer_GUI_Windows_i386\Plugin\ /S

@rem --- Copying : Information files ---
copy ..\License.html DVAnalyzer_GUI_Windows_i386\
copy ..\History_GUI.txt DVAnalyzer_GUI_Windows_i386\History.txt
copy ReadMe_GUI_Windows.txt DVAnalyzer_GUI_Windows_i386\ReadMe.txt


rem --- Compressing Archive ---
cd DVAnalyzer_GUI_Windows_i386\
%BPATH%\Windows\7-Zip\7z a -r -t7z -mx9 ..\DVAnalyzer_GUI_Windows_i386_WithoutInstaller.7z *
cd ..

rem --- Installer ---
%BPATH%\Windows\NSIS\makensis ..\Source\Install\AVPS_DV_Analyzer_GUI_Windows_i386.nsi

rem --- Clean up ---
if "%1"=="SkipCleanUp" goto SkipCleanUp
rmdir DVAnalyzer_GUI_Windows_i386\ /S /Q
:SkipCleanUp
