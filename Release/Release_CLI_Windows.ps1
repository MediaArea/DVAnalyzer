##  Copyright (c) MediaArea.net SARL. All Rights Reserved.
##
##  Use of this source code is governed by a BSD-style license that can
##  be found in the License.html file in the root of the source tree.
##

Param([parameter(Mandatory=$true)][String]$arch)

$ErrorActionPreference = "Stop"

#-----------------------------------------------------------------------
# Setup
$release_directory = Split-Path -Parent $MyInvocation.MyCommand.Path
$version = (Get-Content "${release_directory}\..\Project\version.txt" -Raw).Trim()
$arch_alt="${arch}"
if ("${arch}" -eq "Win32" ) {
    $arch_alt="i386"
}

#-----------------------------------------------------------------------
# Cleanup
$artifact = "${release_directory}\DVAnalyzer_CLI_${version}_Windows_${arch_alt}"
if (Test-Path "${artifact}") {
    Remove-Item -Force -Recurse "${artifact}"
}

$artifact = "${release_directory}\DVAnalyzer_CLI_${version}_Windows_${arch_alt}.zip"
if (Test-Path "${artifact}") {
    Remove-Item -Force "${artifact}"
}

#-----------------------------------------------------------------------
# Package CLI
Push-Location "${release_directory}"
    New-Item -Force -ItemType Directory -Path "DVAnalyzer_CLI_${version}_Windows_${arch_alt}"
    Push-Location "DVAnalyzer_CLI_${version}_Windows_${arch_alt}"
        ### Copying: Exe ###
        Copy-Item -Force "..\..\Project\MSVC2022\CLI\${arch}\Release\dvanalyzer.exe" .
        ### Copying: Information files ###
        Copy-Item -Force "..\..\License.html" .
        Copy-Item -Force "..\..\History_CLI.txt" "History.txt"
        Copy-Item -Force "..\Readme_CLI_Windows.txt" "ReadMe.txt"
        ### Archive
        7za.exe a -r -tzip -mx9 "..\DVAnalyzer_CLI_${version}_Windows_${arch_alt}.zip" *
        7za.exe a -r -tzip -mx9 "..\DVAnalyzer_CLI_${version}_Windows_${arch_alt}_DebugInfo.zip" "..\..\Project\MSVC2022\CLI\${arch}\Release\AVPS_DV_Analyzer_CLI.pdb"
    Pop-Location
Pop-Location
