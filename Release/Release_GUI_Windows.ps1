##  Copyright (c) MediaArea.net SARL. All Rights Reserved.
##
##  Use of this source code is governed by a BSD-style license that can
##  be found in the License.html file in the root of the source tree.
##

Param([parameter(Mandatory=$true)][String]$arch)

$ErrorActionPreference = "Stop"

#-----------------------------------------------------------------------
# Setup
$release_directory = $PSScriptRoot
$version = (Get-Content "${release_directory}\..\Project\version.txt" -Raw).Trim()
$arch_alt="${arch}"
if ("${arch}" -eq "Win32" ) {
    $arch_alt="i386"
}

#-----------------------------------------------------------------------
# Cleanup
$artifact = "${release_directory}\DVAnalyzer_GUI_${version}_Windows_${arch_alt}"
if (Test-Path "${artifact}") {
    Remove-Item -Force -Recurse "${artifact}"
}

$artifact = "${release_directory}\DVAnalyzer_GUI_${version}_Windows_${arch_alt}_WithoutInstaller.7z"
if (Test-Path "${artifact}") {
    Remove-Item -Force "${artifact}"
}

$artifact = "${release_directory}\DVAnalyzer_GUI_${version}_Windows_${arch_alt}.exe"
if (Test-Path "${artifact}") {
    Remove-Item -Force "${artifact}"
}

#-----------------------------------------------------------------------
# Package GUI
Push-Location "${release_directory}"
    New-Item -Force -ItemType Directory -Path "DVAnalyzer_GUI_${version}_Windows_${arch_alt}"
    Push-Location "DVAnalyzer_GUI_${version}_Windows_${arch_alt}"
        ### Copying: Exe ###
        Copy-Item -Force "..\..\Project\QtCreator\${arch}\DV Analyzer.exe" DVAnalyzer.exe
        ### Copying: Information files ###
        Copy-Item -Force "..\..\License.html" .
        Copy-Item -Force "..\..\History_GUI.txt" "History.txt"
        Copy-Item -Force "..\Readme_GUI_Windows.txt" "ReadMe.txt"
        ### Archive
        7za.exe a -r -t7z -mx9 "..\DVAnalyzer_GUI_${version}_Windows_${arch_alt}_WithoutInstaller.7z" *
    Pop-Location
Pop-Location

#-----------------------------------------------------------------------
# Package installer
Push-Location "${release_directory}"
    makensis.exe "..\Source\Install\AVPS_DV_Analyzer_GUI_Windows_${arch_alt}.nsi"
Pop-Location
