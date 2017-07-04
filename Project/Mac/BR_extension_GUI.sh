#! /bin/sh

# Because of the autotools bug
cd ZenLib/Project/GNU/Library
./autogen.sh
cd ../../../../MediaInfoLib/Project/GNU/Library
./autogen.sh
cd ../../../../AVPS_DV_Analyzer/Project/GNU/GUI
./autogen.sh
cd ../../../..

./GUI_Compile.sh
