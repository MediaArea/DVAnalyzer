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
del   AVPS_DV_Analyzer_GUI_Windows_x64.exe
del   AVPS_DV_Analyzer_GUI_Windows_x64_WithoutInstaller.7z
rmdir AVPS_DV_Analyzer_GUI_Windows_x64 /S /Q
mkdir AVPS_DV_Analyzer_GUI_Windows_x64

@rem --- Copying : Exe ---
copy  ..\Project\MSVC2015\GUI\x64\Release\AVPS_DV_Analyzer_GUI.exe AVPS_DV_Analyzer_GUI_Windows_x64\DV_Analyzer.exe

@rem --- Copying : Plugins ---
xcopy ..\Source\Resource\Plugin\* AVPS_DV_Analyzer_GUI_Windows_x64\Plugin\ /S

@rem --- Copying : Information files ---
copy ..\License.html AVPS_DV_Analyzer_GUI_Windows_x64\
copy ..\History_GUI.txt AVPS_DV_Analyzer_GUI_Windows_x64\History.txt
copy ReadMe_GUI_Windows.txt AVPS_DV_Analyzer_GUI_Windows_x64\ReadMe.txt


rem --- Compressing Archive ---
cd AVPS_DV_Analyzer_GUI_Windows_x64\
%BPATH%\Windows\7-Zip\7z a -r -t7z -mx9 ..\AVPS_DV_Analyzer_GUI_Windows_x64_WithoutInstaller.7z *
cd ..

rem --- Installer ---
%BPATH%\Windows\NSIS\makensis ..\Source\Install\AVPS_DV_Analyzer_GUI_Windows_x64.nsi

rem --- Clean up ---
if "%1"=="SkipCleanUp" goto SkipCleanUp
rmdir AVPS_DV_Analyzer_GUI_Windows_x64\ /S /Q
:SkipCleanUp
