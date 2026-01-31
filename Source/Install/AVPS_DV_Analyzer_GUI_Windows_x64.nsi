; Request application privileges for Windows Vista
RequestExecutionLevel admin

; Some defines
!define PRODUCT_NAME "DV Analyzer"
!define PRODUCT_NAME_EXE "${PRODUCT_NAME}.exe"
!define PRODUCT_PUBLISHER "AudioVisual Preservation Solutions"
!define PRODUCT_VERSION "1.4.2"
!define PRODUCT_VERSION4 "${PRODUCT_VERSION}.0"
!define PRODUCT_WEB_SITE "http://www.digitizationguidelines.gov"
!define COMPANY_REGISTRY "Software\AVPS"
!define PRODUCT_REGISTRY "Software\AVPS\DV Analyzer"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\${PRODUCT_NAME_EXE}"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

; Compression
SetCompressor /FINAL /SOLID lzma

; x64 stuff
!include "x64.nsh"

; Modern UI
!include "MUI2.nsh"
!define MUI_ABORTWARNING
!define MUI_ICON "..\..\Source\Resource\Image\AVPS\logo_sign_alpha_square.ico"

; Uninstaller signing
!ifdef EXPORT_UNINST
  !uninstfinalize 'copy /Y "%1" "../../Release/DVAnalyzer_GUI_${PRODUCT_VERSION}_Windows_x64-uninst.exe"'
!endif


; Language Selection Dialog Settings
!define MUI_LANGDLL_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_LANGDLL_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_LANGDLL_REGISTRY_VALUENAME "NSIS:Language"

; Installer pages
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!define MUI_WELCOMEFINISHPAGE_BITMAP "..\..\Source\Resource\Image\Windows_Finish.bmp"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

; Language files
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_RESERVEFILE_LANGDLL

; Info
VIProductVersion "${PRODUCT_VERSION4}"
VIAddVersionKey "ProductName" "${PRODUCT_NAME}"
VIAddVersionKey "Comments" "DV Analyzer"
VIAddVersionKey "CompanyName" "AVPS"
VIAddVersionKey "LegalTrademarks" "BSD license"
VIAddVersionKey "LegalCopyright" ""
VIAddVersionKey "FileDescription" "DV Analyzer"
VIAddVersionKey "FileVersion" "${PRODUCT_VERSION}"
BrandingText " "

; Modern UI end

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "..\..\Release\DVAnalyzer_GUI_${PRODUCT_VERSION}_Windows_x64.exe"
InstallDir "$PROGRAMFILES64\DV Analyzer"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails nevershow
ShowUnInstDetails nevershow

Function .onInit
  ${If} ${RunningX64}
    SetRegView 64
  ${Else}
    MessageBox MB_OK|MB_ICONSTOP 'You are trying to install the 64-bit version of ${PRODUCT_NAME} on 32-bit Windows.$\r$\nPlease download and use the 32-bit version instead.$\r$\nClick OK to quit Setup.'
    Quit
  ${EndIf}
FunctionEnd

Section "SectionPrincipale" SEC01
  SetOverwrite on

  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}.lnk" "$INSTDIR\${PRODUCT_NAME_EXE}" "" "" "" "" "" "${PRODUCT_NAME} ${PRODUCT_VERSION}"
  SetOutPath "$INSTDIR"
  File "/oname=\${PRODUCT_NAME_EXE}" "..\..\Project\QtCreator\x64\DV Analyzer.exe"
  File "/oname=History.txt" "..\..\History_GUI.txt"
  File "..\..\License.html"
  File  "/oname=ReadMe.txt""..\..\Release\ReadMe_GUI_Windows.txt"

  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"

  ; Delete files that might be present from older installation
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\App Paths\AVPS_DV_Analyzer.exe"
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\AVPS DV Analyzer"
  Delete "$PROGRAMFILES64\AVPS\DV Analyzer\AVPS DB Analyzer.url"
  Delete "$PROGRAMFILES64\AVPS\DV Analyzer\AVPS_DV_Analyzer.exe"
  Delete "$PROGRAMFILES64\AVPS\DV Analyzer\uninst.exe"
  Delete "$PROGRAMFILES64\AVPS\DV Analyzer\License.html"
  Delete "$PROGRAMFILES64\AVPS\DV Analyzer\History.txt"
  Delete "$PROGRAMFILES64\AVPS\DV Analyzer\ReadMe.txt"
  RMDir "$PROGRAMFILES64\AVPS\DV Analyzer"
  RMDir "$PROGRAMFILES74\AVPS" ; only if empty
  Delete "$SMPROGRAMS\DV Analyzer\DV Analyzer.lnk"
  Delete "$SMPROGRAMS\DV Analyzer\Uninstall.lnk"
  Delete "$SMPROGRAMS\DV Analyzer\Website.lnk"
  Delete "$SMPROGRAMS\DV Analyzer\History.lnk"
  RMDir  "$SMPROGRAMS\DV Analyzer"
SectionEnd

Section -Post
  !if /FileExists "..\..\Release\DVAnalyzer_GUI_${PRODUCT_VERSION}_Windows_x64-uninst.exe"
    File "/oname=$INSTDIR\uninst.exe" "..\..\Release\DVAnalyzer_GUI_${PRODUCT_VERSION}_Windows_x64-uninst.exe"
  !else
    WriteUninstaller "$INSTDIR\uninst.exe"
  !endif
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\${PRODUCT_NAME_EXE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\${PRODUCT_NAME_EXE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
SectionEnd


Section Uninstall
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\${PRODUCT_NAME_EXE}"
  Delete "$INSTDIR\History.txt"
  Delete "$INSTDIR\License.html"
  Delete "$INSTDIR\ReadMe.txt"
  Delete "$SMPROGRAMS\${PRODUCT_NAME}.lnk"
  RMDir "$INSTDIR"

  SetRegView 64
  DeleteRegKey HKLM "${PRODUCT_REGISTRY}"
  DeleteRegKey /ifempty HKLM "${COMPANY_REGISTRY}"
  DeleteRegKey HKCU "${PRODUCT_REGISTRY}"
  DeleteRegKey /ifempty HKCU "${COMPANY_REGISTRY}"
  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd
