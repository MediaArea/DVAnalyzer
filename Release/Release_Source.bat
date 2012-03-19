@echo off

rem --- Clean up ---
del AVPS_DV_Analyzer_.tar.bz2
del AVPS_DV_Analyzer_Source.tar
del AVPS_DV_Analyzer_-1.tar.gz 
del AVPS_DV_Analyzer__AllInclusive.7z
rmdir AVPS_DV_Analyzer_Source /S /Q
rmdir MediaInfoLib /S /Q
rmdir ZenLib /S /Q
rmdir zlib /S /Q
mkdir AVPS_DV_Analyzer_Source


@rem --- Copying : Sources ---
xcopy ..\Source\*.cpp AVPS_DV_Analyzer_Source\Source\ /S
xcopy ..\Source\*.h AVPS_DV_Analyzer_Source\Source\ /S
xcopy ..\Source\*.dfm AVPS_DV_Analyzer_Source\Source\ /S
xcopy ..\Source\*.xml AVPS_DV_Analyzer_Source\Source\ /S
xcopy ..\Source\*.rc AVPS_DV_Analyzer_Source\Source\ /S
xcopy ..\Source\*.txt AVPS_DV_Analyzer_Source\Source\ /S
xcopy ..\Source\*.csv AVPS_DV_Analyzer_Source\Source\ /S
xcopy ..\Source\*.ico AVPS_DV_Analyzer_Source\Source\ /S
xcopy ..\Source\*.nsi AVPS_DV_Analyzer_Source\Source\ /S
xcopy ..\Source\*.sh  AVPS_DV_Analyzer_Source\Source\ /S
xcopy ..\Source\*.png AVPS_DV_Analyzer_Source\Source\ /S
xcopy ..\Source\*.qrc AVPS_DV_Analyzer_Source\Source\ /S
xcopy ..\Source\*.bat AVPS_DV_Analyzer_Source\Source\ /S

@rem --- Copying : Projects ---
xcopy ..\Project\*.bpg AVPS_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.bpf AVPS_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.bpr AVPS_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.cpp AVPS_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.c AVPS_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.h AVPS_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.bdsgroup AVPS_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.bdsproj AVPS_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.dev AVPS_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.sln AVPS_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.vc AVPS_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.vcproj AVPS_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.ico AVPS_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.workspace AVPS_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.cbp AVPS_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.def AVPS_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.idl AVPS_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.rgs AVPS_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.bat AVPS_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\BCB\AVPS_DV_Analyzer*.res AVPS_DV_Analyzer_Source\Project\BCB /S
xcopy ..\Project\MSVC2010\*.rc AVPS_DV_Analyzer_Source\Project\MSVC2010\ /S
xcopy ..\Project\GNU\* AVPS_DV_Analyzer_Source\Project\GNU\ /S

@rem --- Copying : Release ---
xcopy *.txt AVPS_DV_Analyzer_Source\Release\
xcopy *.bat AVPS_DV_Analyzer_Source\Release\
xcopy *.sh  AVPS_DV_Analyzer_Source\Release\
xcopy *.sub AVPS_DV_Analyzer_Source\Release\
xcopy BCB\*.txt AVPS_DV_Analyzer_Source\Release\BCB\ /S
xcopy MSVC2010\*.txt AVPS_DV_Analyzer_Source\Release\MSVC2010\ /S
xcopy GCC_MinGW32\*.txt AVPS_DV_Analyzer_Source\Release\GCC_MinGW32\ /S
xcopy GCC_Linux_i386\*.txt AVPS_DV_Analyzer_Source\Release\GCC_Linux_i386\ /S
xcopy Make_GCC.sh AVPS_DV_Analyzer_Source\Release\

@rem --- Copying : debian ---
xcopy ..\debian\* AVPS_DV_Analyzer_Source\debian\ /S

rem --- Copying : Information files ---
xcopy ..\*.txt AVPS_DV_Analyzer_Source\
xcopy ..\*.html AVPS_DV_Analyzer_Source\

rem --- Copying : Contrib files ---
xcopy ..\Contrib\*.doc AVPS_DV_Analyzer_Source\Contrib\ /S

rem --- Copying : Website files ---
xcopy ..\Website\*.* AVPS_DV_Analyzer_Source\Website\ /S

rem --- Copying : CVS files ---
xcopy ..\*.cvsignore AVPS_DV_Analyzer_Source\

rem --- Copying : MediaInfoLib files ---
cd ..\..\MediaInfoLib\Release
call Release_Source.bat SkipCleanUp SkipCompression
cd ..\..\AVPS_DV_Analyzer\Release
move ..\..\MediaInfoLib\Release\MediaInfo_Lib_Source .\MediaInfoLib

rem --- Copying : ZenLib files ---
cd ..\..\ZenLib\Release
call Release_Source.bat SkipCleanUp SkipCompression
cd ..\..\AVPS_DV_Analyzer\Release
move ..\..\ZenLib\Release\ZenLib_Source .\ZenLib

rem --- Copying : zlib files ---
xcopy ..\..\Shared\Source\zlib .\zlib\ /S
xcopy ..\..\Shared\Project\zlib\Template .\zlib\ /S


rem --- Compressing Archive ---
if "%2"=="SkipCompression" goto SkipCompression
move AVPS_DV_Analyzer_Source AVPS_DV_Analyzer
..\..\Shared\Binary\Windows_i386\7-zip\7z a -r -ttar -mx9 dvanalyzer.tar AVPS_DV_Analyzer\*
..\..\Shared\Binary\Windows_i386\7-zip\7z a -r -tbzip2 -mx9 dvanalyzer_.tar.bz2 dvanalyzer.tar
..\..\Shared\Binary\Windows_i386\7-zip\7z a -r -tgzip -mx9 dvanalyzer_-1.tar.gz dvanalyzer.tar
del dvanalyzer.tar
..\..\Shared\Binary\Windows_i386\7-zip\7z a -r -t7z -mx9 AVPS_DV_Analyzer__AllInclusive.7z AVPS_DV_Analyzer\* MediaInfoLib\* ZenLib\* zlib\*
move AVPS_DV_Analyzer AVPS_DV_Analyzer_Source
:SkipCompression

rem --- Clean up ---
if "%1"=="SkipCleanUp" goto SkipCleanUp
rmdir AVPS_DV_Analyzer_Source /S /Q
:SkipCleanUp
rmdir MediaInfoLib /S /Q
rmdir ZenLib /S /Q
rmdir zlib /S /Q
