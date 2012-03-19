// Common_Help - Help strings
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
#include "Common/Common_Help.h"
//---------------------------------------------------------------------------

const char* Help_Summary_HTML() {return
"<h2>Information Summary</h2>"
"<h3>Frame Information</h3>"
"<ul>"
"<li>Frame: The number of the frame within the video. The first frame is zero.</li>"
"<li>Absolute time: Begins with 00:00:00.000. Represents the time elapsed from the start of the video</li>"
"<li>DV timecode: This is the timecode as documented within the referenced frame. This information is typically written by the camera.</li>"
"<li>Timecode info: This field contains 'Repeating' if the DV Timecode is the same as the previous frame or 'Non-sequential' if it doesn't follow the previous frame. The field is disabled when the timecode equals '00:00:00;00'.</li>"
"<li>Rec. date/time: This is the date and time as set on the original recording device. A DV camera will normally document this information in every DV frame written to tape.</li>"
"<li>Rec. date/time Info: Similar to 'Timecode info', this field states if the 'Rec. date/time' is 'Repeating' or 'Non-sequential' as related to the 'Rec. date/time' value of the previous frame.</li>"
"<li>Arb bits: Every block of video data contains an 'Arbitrary bit', a unit of data with a 4 bit value. The exact meaning of the Arbitrary bit is obscure, but if there is inconsistency in the pattern of the bits there may likely be an error or inconsistency in the image.</li>"
"<li>Arb bits info: Similar to 'Timecode info' this value shows when the 'Arbitrary bit' is 'Repeating' or 'Non-sequential' as related to the 'Arbitrary bit' of the previous frame.</li>"
"<li>Start: Contains an 'S' if the camera has noted that this frame is the first frame of a recording.</li>"
"<li>End: Contains an 'E' if the camera has noted that this frame is the last frame of a recording.</li>"
"</ul>"
"<h3>Error Detection</h3>"
"<ul>"
"<li>Video error concealment: This is glitchiness, blockiness, or pixelization within a frame caused by the deck covering video data that was not properly read from the tape.</li>"
"<li>Audio errors: If the DV deck fails to read audio data, it may export error codes that can be detected. They are played as dropouts.</li>"
"<li>Timecode inconsistency: DV contains many timecode values per frame (this helps enable the timecode to be viewable while the tape is shuttled). This field notes when the timecodes within a frame are inconsistent.</li>"
"<li>DIF incoherency: Notes structural problems with the frame such as unexpected, irregular information.</li>"
"<li>Arbitrary bit inconsistency: Notes when the Arbitrary bits within a frame are not consistent.</li>"
"<li>Stts fluctuation: Notes frames that are assigned a presentation time that is longer or shorter than the other frames (normally all DV frames are presented for same amount of time). Occasionally this is indicative of audio/video sync issues and may present a stutter during playback.</li>"
"</ul>"
;}

const char* Help_Summary_Text() {return
"Information Summary\n"
"Frame Information\n"
"\n"
"Frame: The number of the frame within the video. The first frame is zero.\n"
"Absolute time: Begins with 00:00:00.000. Represents the time elapsed from the start of the video\n"
"DV timecode: This is the timecode as documented within the referenced frame. This information is typically written by the camera.\n"
"Timecode info: This field contains 'Repeating' if the DV Timecode is the same as the previous frame or 'Non-sequential' if it doesn't follow the previous frame. The field is disabled when the timecode equals '00:00:00;00'.\n"
"Rec. date/time: This is the date and time as set on the original recording device. A DV camera will normally document this information in every DV frame written to tape.\n"
"Rec. date/time Info: Similar to 'Timecode info', this field states if the 'Rec. date/time' is 'Repeating' or 'Non-sequential' as related to the 'Rec. date/time' value of the previous frame.\n"
"Arb bits: Every block of video data contains an 'Arbitrary bit', a unit of data with a 4 bit value. The exact meaning of the Arbitrary bit is obscure, but if there is inconsistency in the pattern of the bits there may likely be an error or inconsistency in the image.\n"
"Arb bits info: Similar to 'Timecode info' this value shows when the 'Arbitrary bit' is 'Repeating' or 'Non-sequential' as related to the 'Arbitrary bit' of the previous frame.\n"
"Start: Contains an 'S' if the camera has noted that this frame is the first frame of a recording.\n"
"End: Contains an 'E' if the camera has noted that this frame is the last frame of a recording.\n"
"\n"
"Error Detection\n"
"\n"
"Video error concealment: This is glitchiness, blockiness, or pixelization within a frame caused by the deck covering video data that was not properly read from the tape.\n"
"Audio errors: If the DV deck fails to read audio data, it may export error codes that can be detected. They are played as dropouts.\n"
"Timecode inconsistency: DV contains many timecode values per frame (this helps enable the timecode to be viewable while the tape is shuttled). This field notes when the timecodes within a frame are inconsistent.\n"
"DIF incoherency: Notes structural problems with the frame such as unexpected, irregular information.\n"
"Arbitrary bit inconsistency: Notes when the Arbitrary bits within a frame are not consistent.\n"
"Stts fluctuation: Notes frames that are assigned a presentation time that is longer or shorter than the other frames (normally all DV frames are presented for same amount of time). Occasionally this is indicative of audio/video sync issues and may present a stutter during playback.\n"
;}

const char* Help_Details_HTML() {return
"<h2>Information Detail</h2>"
"<h3>Frame Information</h3>"
"<h4>Frame</h4>"
"The number of the frame within the video. The first frame is zero."
"<h4>Absolute time</h4>"
"Begins with 00:00:00.000. Represents the time from the start of the video."
"<h4>DV timecode</h4>"
"This is the timecode as documented within the referenced frame. This information is typically written by the camera. Often this information will survive from the ingest of the source tape, through an edit, and to a final output. However, if the content is recompressed through rendering or a transcoding, this information is easily lost."
"<h4>Timecode info</h4>"
"This field contains 'Repeating' if the DV Timecode is the same as the previous frame or 'Non-sequential' if it doesn't follow the previous frame. The field is disabled when the timecode equals '00:00:00.000'. Timecode Info is more likely to be maintained in DV that has been ingested directly from an unedited DV tape than from an edited video."
"<h4>Rec. date/time</h4>"
"This is the date and time as set on the original recording device. A DV camera will normally document this information in every DV frame written to tape."
"<h4>Rec. date/time Info</h4>"
"Similar to 'Timecode Info', this field states if the 'Rec. date/time' is 'Repeating' or 'Non-sequential' as related to the 'Rec. date/time' value of the previous frame. A Non-Sequential value occurs when the recording is stopped and restarted, thus Non-Sequential recording date/time can be used to identify separate shots within an ingested DV tape."
"<h4>Arb bits</h4>"
"Every block of video data contains an 'Arbitrary bit', a unit of data with a 4 bit value. The exact meaning of the Arbitrary bit is obscure, but if there is inconsistency in the pattern of the bits there is likely an error or inconsistency in the image. An NTSC DV25 file will have 1,350 expressions of Arbitrary bit, PAL DV25 will have 1,620. Arbitrary bit codes for the frame are typically expressed as a hexadecimal character. Arbitrary bit values typically follow a repeating sequential pattern of 0,1,2,3,4,5,6,7,8,9,0,A,B (both in NTSC and PAL). An inconsistency is expressed by a value duplicated within the sequence (ex. 0, 1, 2, 2, 3...)."
"<h4>Arb bits info</h4>"
"Similar to 'Timecode Info' this value shows when the 'Arbitrary bit' is 'Repeating' or 'Non-sequential' as related to the 'Arbitrary bit' of the previous frame. A Non-Sequential Arbitrary bit value may indicate a missing frame, an edit, or an error."
"<h4>Start</h4>"
"Contains an 'S' if the camera has noted that this frame is the first frame of a recording."
"<h4>End</h4>"
"Contains an 'E' if the camera has noted that this frame is the last frame of a recording."
""
"<h3>Error Detection</h3>"
"<h4>Video error concealment</h4>"
"DV tapes contain parity data to enable the deck to determine if data was read correctly. When video data can not be read correctly, the deck may conceal the missing information using a number of strategies. The type of concealment is documented in the output DV stream as a STA value ('STAtus of compressed macro block'). The STA values are noted by DV Analyzer as a hexadecimal character:"
"<ul>"
"<li>STA = 'A': This block of video data is replaced by the corresponding video data of the previous frame (very common).</li>"
"<li>STA = 'C': This block of video data is replaced by the corresponding video data of the next frame.</li>"
"<li>STA = 'E': Unspecified concealment.</li>"
"<li>STA = 'F': Error. Typically represented as grey blocks on the frame.</li>"
"</ul>"
"There can be up to 1,350 STA errors per NTSC frame (1,620 in PAL). If an NTSC frame notes '1,350 STA errors', then the entire frame failed to read correctly. The higher the total number of STA errors per frame, the more noticeable the concealment may be. In many case, video error concealment may not be easily detected by visual inspection."
"<h4>Audio errors</h4>"
"If the DV deck fails to read audio data, it may export error codes to the output stream that can be detected. They are played as dropouts because there is no process for audio error concealment. Since audio data are shuffled when written to tape the audio errors will often to spread across the duration of a frame of video.<br></br>Each frame of NTSC DV contains 90 blocks of audio data (108 in PAL). In NTSC it takes 10 passes of the deck's head across the tape to read the data for an entire frame (12 in PAL). Each head pass reads one DIF sequence (Dseq). Often when audio fails to be read properly, it fails for the entire pass.<br></br>DV Analyzer will provide the total number of audio block read errors (1 to 90 or 108) and detail how many occurred within each head pass (DIF sequence). If the audio errors mostly occur on all odd numbered DIF sequences only or all even numbered DIF sequences only then the deck (or the original recording device) may have one dirty or damaged head."
"<h4>Timecode inconsistency</h4>"
"DV contains many timecode values per frame (this helps enable the timecode to be viewable while the tape is shuttled). This field notes when the timecodes within a frame are inconsistent. This error does not affect video or audio quality but may be indictative of other problems."
"<h4>DIF incoherency</h4>"
"Notes structural problems with the frame such as unexpected, irregular information.<br></br>DIF incoherency means that the frame may be failing to follow basic structural expectations of DV which can cause unpredictable behaviors during playback or when encoding with various hardware and software applications."
"<h4>Arbitrary bit inconsistency</h4>"
"Notes when the Arbitrary bits within a frame are not consistent. The information that makes up the bit is 'arbitrary', but the pattern it follows within the file is not. As such, inconsistencies in the pattern can indicate issues with the frame, such as when data from two different frames is mixed into a single frame (from recording over recordings or glitchy playout)."
"<h4>Stts fluctuation</h4>"
"Notes frames that are assigned a presentation time that is longer or shorter than the other frames (normally all DV frames are presented for same amount of time). Occasionally this is indicative of audio/video sync issues and may present a stutter during playback."
;}

const char* Help_Details_Text() {return
"Information Details\n"
"Frame Information\n"
"Frame\n"
"The number of the frame within the video. The first frame is zero.\n"
"Absolute time\n"
"Begins with 00:00:00.000. Represents the time from the start of the video.\n"
"DV timecode\n"
"This is the timecode as documented within the referenced frame. This information is typically written by the camera. Often this information will survive from the ingest of the source tape, through an edit, and to a final output. However, if the content is recompressed through rendering or a transcoding, this information is easily lost.\n"
"Timecode info\n"
"This field contains 'Repeating' if the DV Timecode is the same as the previous frame or 'Non-sequential' if it doesn't follow the previous frame. The field is disabled when the timecode equals '00:00:00.000'. Timecode Info is more likely to be maintained in DV that has been ingested directly from an unedited DV tape than from an edited video.\n"
"Rec. date/time\n"
"This is the date and time as set on the original recording device. A DV camera will normally document this information in every DV frame written to tape.\n"
"Rec. date/time Info\n"
"Similar to 'Timecode Info', this field states if the 'Rec. date/time' is 'Repeating' or 'Non-sequential' as related to the 'Rec. date/time' value of the previous frame. A Non-Sequential value occurs when the recording is stopped and restarted, thus Non-Sequential recording date/time can be used to identify separate shots within an ingested DV tape.\n"
"Arb bits\n"
"Every block of video data contains an 'Arbitrary bit', a unit of data with a 4 bit value. The exact meaning of the Arbitrary bit is obscure, but if there is inconsistency in the pattern of the bits there is likely an error or inconsistency in the image. An NTSC DV25 file will have 1,350 expressions of Arbitrary bit, PAL DV25 will have 1,620. Arbitrary bit codes for the frame are typically expressed as a hexadecimal character. Arbitrary bit values typically follow a repeating sequential pattern of 0,1,2,3,4,5,6,7,8,9,0,A,B (both in NTSC and PAL). An inconsistency is expressed by a value duplicated within the sequence (ex. 0, 1, 2, 2, 3...).\n"
"Arb bits info\n"
"Similar to 'Timecode Info' this value shows when the 'Arbitrary bit' is 'Repeating' or 'Non-sequential' as related to the 'Arbitrary bit' of the previous frame. A Non-Sequential Arbitrary bit value may indicate a missing frame, an edit, or an error.\n"
"Start\n"
"Contains an 'S' if the camera has noted that this frame is the first frame of a recording.\n"
"End\n"
"Contains an 'E' if the camera has noted that this frame is the last frame of a recording.\n"
"\n"
"Error Detection\n"
"Video error concealment\n"
"DV tapes contain parity data to enable the deck to determine if data was read correctly. When video data can not be read correctly, the deck may conceal the missing information using a number of strategies. The type of concealment is documented in the output DV stream as a STA value ('STAtus of compressed macro block'). The STA values are noted by DV Analyzer as a hexadecimal character:\n"
"\n"
"STA = 'A': This block of video data is replaced by the corresponding video data of the previous frame (very common).\n"
"STA = 'C': This block of video data is replaced by the corresponding video data of the next frame.\n"
"STA = 'E': Unspecified concealment.\n"
"STA = 'F': Error. Typically represented as grey blocks on the frame.\n"
"\n"
"There can be up to 1,350 STA errors per NTSC frame (1,620 in PAL). If an NTSC frame notes '1,350 STA errors', then the entire frame failed to read correctly. The higher the total number of STA errors per frame, the more noticeable the concealment may be. In many case, video error concealment may not be easily detected by visual inspection.\n"
"Audio errors\n"
"If the DV deck fails to read audio data, it may export error codes to the output stream that can be detected. They are played as dropouts because there is no process for audio error concealment. Since audio data are shuffled when written to tape the audio errors will often to spread across the duration of a frame of video.DV Analyzer will provide the total number of audio block read errors (1 to 90 or 108) and detail how many occurred within each head pass (DIF sequence). If the audio errors mostly occur on all odd numbered DIF sequences only or all even numbered DIF sequences only then the deck (or the original recording device) may have one dirty or damaged head.\n"
"Timecode inconsistency\n"
"DV contains many timecode values per frame (this helps enable the timecode to be viewable while the tape is shuttled). This field notes when the timecodes within a frame are inconsistent. This error does not affect video or audio quality but may be indictative of other problems.\n"
"DIF incoherency\n"
"Notes structural problems with the frame such as unexpected, irregular information.DIF incoherency means that the frame may be failing to follow basic structural expectations of DV which can cause unpredictable behaviors during playback or when encoding with various hardware and software applications.\n"
"Arbitrary bit inconsistency\n"
"Notes when the Arbitrary bits within a frame are not consistent. The information that makes up the bit is 'arbitrary', but the pattern it follows within the file is not. As such, inconsistencies in the pattern can indicate issues with the frame, such as when data from two different frames is mixed into a single frame (from recording over recordings or glitchy playout).\n"
"Stts fluctuation\n"
"Notes frames that are assigned a presentation time that is longer or shorter than the other frames (normally all DV frames are presented for same amount of time). Occasionally this is indicative of audio/video sync issues and may present a stutter during playback."
;}
