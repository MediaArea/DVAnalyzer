#! /bin/sh

#############################################################################
# Configure
Home=`pwd`
MediaInfoLib_Options="--enable-static --disable-shared"
ZenLib_Options="--enable-static --disable-shared"

if [ "$(uname -s)" = "Darwin" ] ; then
    MediaInfoLib_Options="$MediaInfoLib_Options --with-macosx-version-min=10.10"
    ZenLib_Options="$ZenLib_Options --with-macosx-version-min=10.10"
fi

#############################################################################
# Setup for parallel builds
Zen_Make()
{
 if test -e /proc/stat; then
  numprocs=`egrep -c ^cpu[0-9]+ /proc/stat || :`
  if [ "$numprocs" = "0" ]; then
   numprocs=1
  fi
  make -s -j$numprocs
 else
  make
 fi
}

#############################################################################
# ZenLib
if test -e ZenLib/Project/GNU/Library/configure; then
 cd ZenLib/Project/GNU/Library/
 test -e Makefile && rm Makefile
 chmod u+x configure
 ./configure $ZenLib_Options $*
 if test -e Makefile; then
  make clean
  Zen_Make
  if test -e libzen.la; then
   echo ZenLib compiled
  else
   echo Problem while compiling ZenLib
   exit
  fi
 else
  echo Problem while configuring ZenLib
  exit
 fi
else
 echo ZenLib directory is not found
 exit
fi
cd $Home

#############################################################################
# MediaInfoLib
if test -e MediaInfoLib/Project/GNU/Library/configure; then
 cd MediaInfoLib/Project/GNU/Library/
 test -e Makefile && rm Makefile
 chmod u+x configure
 ./configure $MediaInfoLib_Options $*
 if test -e Makefile; then
  make clean
  Zen_Make
  if test -e libmediainfo.la; then
   echo MediaInfoLib compiled
  else
   echo Problem while compiling MediaInfoLib
   exit
  fi
 else
  echo Problem while configuring MediaInfoLib
  exit
 fi
else
 echo MediaInfoLib directory is not found
 exit
fi
cd $Home

#############################################################################
# DVAnalyzer
if test -e DVAnalyzer/Project/QtCreator/dvanalyzer-gui.pro; then
 cd DVAnalyzer/Project/QtCreator
 test -e Makefile && rm Makefile
 chmod u+x prepare
 ./prepare STATIC_LIBS=1
 if test -e Makefile; then
  make clean
  Zen_Make
  if test -e dvanalyzer-gui  || test -e "DV Analyzer.app"; then
   echo DVAnalyzer compiled
  else
   echo Problem while compiling DVAnalyzer
   exit
  fi
 else
  echo Problem while configuring DVAnalyzer
  exit
 fi
else
 echo DVAnalyzer directory is not found
 exit
fi
cd $Home

#############################################################################
# Going home
cd $Home
echo "DVAnalyzer executable is in DVAnalyzer/Project/QtCreator"
