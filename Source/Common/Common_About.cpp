// Common_About - About strings
// Copyright (C) 2009-2009 AudioVisual Preservation Solutions, dv@avpreserve.com
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#include "Common/Common_About.h"
//---------------------------------------------------------------------------

//***************************************************************************
// NameVersion
//***************************************************************************

//---------------------------------------------------------------------------
const char* NameVersion_HTML() {return
"DV Analyzer v.1.4.2 by <a href=\"http://avpreserve.com/dvanalyzer/\">AudioVisual Preservation Solutions, Inc.</a>"
;}

//---------------------------------------------------------------------------
const char* NameVersion_Text() {return
"DV Analyzer v.1.4.2 by AudioVisual Preservation Solutions, Inc. http://www.avpreserve.com"
;}

//***************************************************************************
// NameVersion
//***************************************************************************

//---------------------------------------------------------------------------
const char* Description_HTML() {return
"<h3>DESCRIPTION</h3>"
"DV Analyzer provides two primary services simultaneously:"
""
"<h4>Error Detection and Quality Control</h4>"
""
"The reformatting of DV tapes (such as miniDV, DVCam, and DVCPro) to DV file-based formats is a point when the introduction of permanent errors is of particularly high risk. Most capture tools for DV only report errors if they are significant, such as a lost frame, whereas other documented errors are not reviewed. DVanalyzer provides a way to analyze and report audio, video, subcode, and structural errors within a DV file. This enables automated quality control and the ability to verify the accuracy and integrity of the reformatting process on a frame-by-frame basis."
""
""
"<h4>Temporal Metadata Reporting</h4>"
""
"The DV format is rich with temporal metadata. Every frame may contain time code, recording date and time information, recording markers, and more. DVanalyzer reports this information which can be used in a variety of meaningful ways when working with and preserving DV content.  This is particularly useful in documenting source material of edited DV content."
;}

//---------------------------------------------------------------------------
const char* Description_Text() {return
"DESCRIPTION\n"
"\n"
"DVanalyzer provides two primary services simultaneously:\n"
"\n"
"Error Detection and Quality Control\n"
"\n"
"The reformatting of DV tapes (such as miniDV, DVCam, and DVCPro) to DV file-based formats is a point when the introduction of permanent errors is of particularly high risk. Most capture tools for DV only report errors if they are significant, such as a lost frame, whereas other documented errors are not reviewed. DVanalyzer provides a way to analyze and report audio, video, subcode, and structural errors within a DV file. This enables automated quality control and the ability to verify the accuracy and integrity of the reformatting process on a frame-by-frame basis.\n"
"\n"
"\n"
"Temporal Metadata Reporting\n"
"\n"
"The DV format is rich with temporal metadata. Every frame may contain time code, recording date and time information, recording markers, and more. DVanalyzer reports this information which can be used in a variety of meaningful ways when working with and preserving DV content.  This is particularly useful in documenting source material of edited DV content.\n"
"\n"
;}

//***************************************************************************
// TechnicalSynopsis
//***************************************************************************

//---------------------------------------------------------------------------
const char* TechnicalSynopsis_HTML() {return
"<h3>TECHNICAL SYNOPSIS</h3>"
""
"DV Analyzer is a technical quality control and reporting tool that examines DV streams in order to report errors in the tape-to-file transfer process, such as video error concealment information, invalid audio samples, timecode inconsistency, inconsistent use of arbitrary bits in video DIF blocks, and DIF structural problems.<br />"
"<br />"
"DV Analyzer also reports on patterns within DV streams such as changes in DV time code, changes in recording date and time markers, first and last frame markers within individual recordings, and more.<br />"
;}

//---------------------------------------------------------------------------
const char* TechnicalSynopsis_Text() {return
"TECHNICAL SYNOPSIS\n"
"\n"
"DV Analyzer is a technical quality control and reporting tool that examines DV streams in order to report errors in the tape-to-file transfer process, such as video error concealment information, invalid audio samples, timecode inconsistency, inconsistent use of arbitrary bits in video DIF blocks, and DIF structural problems.\n"
"\n"
"DV Analyzer also reports on patterns within DV streams such as changes in DV time code, changes in recording date and time markers, first and last frame markers within individual recordings, and more.\n"
"\n"
;}

//***************************************************************************
// AuthorLicense
//***************************************************************************

//---------------------------------------------------------------------------
const char* AuthorLicense_HTML() {return
"<h3>AUTHOR and LICENSE</h3>"
""
"DV Analyzer was developed by AudioVisual Preservation Solutions, Inc. (AVPS).<br />"
"Copyright (C) 2009 AudioVisual Preservation Solutions, Inc. All rights reserved.<br />"
"<br />"
"Please report bugs and suggestions to <a href=\"mailto:dv@avpreserve.com\">dv@avpreserve.com</a><br />"
"<br />"
"This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.<br />"
"<br />"
"This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.<br />"
"<br />"
"You should have received a copy of the GNU General Public License along with this program. If not, see <a href=\"http://www.gnu.org/licenses/\">http://www.gnu.org/licenses/</a>."
"<br />"
"<h4>Special Thanks</h4>"
""
"Special thanks to Jerome Martinez of MediaArea.net for his work on this project and for the creation and ongoing upkeep of MediaInfo. Jerome's excellent work can be found at <a href=\"http://mediainfo.sourceforge.net\">http://mediainfo.sourceforge.net</a>"
;}

//---------------------------------------------------------------------------
const char* AuthorLicense_Text() {return
"AUTHOR and LICENSE\n"
"\n"
"DV Analyzer was developed by AudioVisual Preservation Solutions, Inc. (AVPS).\n"
"Copyright (C) 2009 AudioVisual Preservation Solutions, Inc. All rights reserved.\n"
"\n"
"Please report bugs and suggestions to <dv@avpreserve.com>\n"
"\n"
"This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.\n"
"\n"
"This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.\n"
"\n"
"You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.\n"
"\n"
"Special Thanks\n"
"\n"
"Special thanks to Jerome Martinez of MediaArea.net for his work on this project and for the creation and ongoing upkeep of MediaInfo. Jerome's excellent work can be found at http://mediainfo.sourceforge.net"
"\n"
;}

//***************************************************************************
// Websites
//***************************************************************************

//---------------------------------------------------------------------------
const char* Websites_HTML() {return
"Developed by <a href=\"http://avpreserve.com/dvanalyzer\">AVPS</a> with support from <a href=\"http://mediainfo.sourceforge.net\">MediaArea.net</a>"
;}

//---------------------------------------------------------------------------
const char* Websites_Text() {return
"Developed by AVPS http://avpreserve.com/dvanalyzer\n"
"with support from MediaArea.net http://mediainfo.sourceforge.net"
"\n"
;}
