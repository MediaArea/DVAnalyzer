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
del   DVAnalyzer_GUI_Windows_x64.exe
del   DVAnalyzer_GUI_Windows_x64_WithoutInstaller.7z
rmdir DVAnalyzer_GUI_Windows_x64 /S /Q
mkdir DVAnalyzer_GUI_Windows_x64

@rem --- Copying : Exe ---
copy  ..\Project\MSVC2017\GUI\x64\Release\AVPS_DV_Analyzer_GUI.exe DVAnalyzer_GUI_Windows_x64\DVAnalyzer.exe

@rem --- Copying : Plugins ---
xcopy ..\Source\Resource\Plugin\* DVAnalyzer_GUI_Windows_x64\Plugin\ /S

@rem --- Copying : Information files ---
copy ..\License.html DVAnalyzer_GUI_Windows_x64\
copy ..\History_GUI.txt DVAnalyzer_GUI_Windows_x64\History.txt
copy ReadMe_GUI_Windows.txt DVAnalyzer_GUI_Windows_x64\ReadMe.txt


rem --- Compressing Archive ---
cd DVAnalyzer_GUI_Windows_x64\
%BPATH%\Windows\7-Zip\7z a -r -t7z -mx9 ..\DVAnalyzer_GUI_Windows_x64_WithoutInstaller.7z *
cd ..

rem --- Installer ---
pushd %BPATH%\Windows\NSIS
makensis.exe "%~dp0\..\Source\Install\AVPS_DV_Analyzer_GUI_Windows_x64.nsi"
popd

rem --- Clean up ---
if "%1"=="SkipCleanUp" goto SkipCleanUp
rmdir DVAnalyzer_GUI_Windows_x64\ /S /Q
:SkipCleanUp
