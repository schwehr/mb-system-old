.TH mbset l "10 August 2001" "MB-System 5.0" "MB-System 5.0"
.SH NAME
\fBmbset\fP - Sets values in \fBmbprocess\fP parameter files.

.SH VERSION
Version 5.0

.SH SYNOPSIS
\fBmbset\fP \fB-I\fIinfile\fP 
[\fB-E -L\fP \fB-P\fIPARAMETER:value\fP -V -H\fP]

.SH DESCRIPTION
\fBmbset\fP is a utility for creating and 
modifying \fBmbprocess\fP parameter files.

The program \fBmbprocess\fP
can perform a variety of swath data processing functions in
a single step (producing a single output swath data file), 
including:
     - Merge edited navigation generated by \fBmbnavedit\fP.
     - Apply bathymetry edit flags from \fBmbedit\fP 
       and \fBmbclean\fP
     - Recalculate bathymetry from raw travel time and
       angle data by raytracing through water sound speed
       models from \fBmbvelocitytool\fP or \fBmbsvplist\fP.
     - Apply changes to roll bias, pitch bias, heading
       bias, and draft values.
     - Recalculate sidescan from raw backscatter samples
       (Simrad multibeam data only).
     - Apply tides to bathymetry.
     - Insert metadata.

The actions of \fBmbprocess\fP are controlled by text
parameter files. Each \fBmbprocess\fP parameter file
contains single line commands that set 
processing modes and parameters. The \fB-P\fP option of
\fBmbset\fP is used to modify a single \fBmbprocess\fP parameter
command. This option can be invoked as many times as desired
on the command line, allowing \fBmbset\fP to set multiple
\fBmbprocess\fP processing parameters and modes. 
If the swath data file
specified by the \fB-I\fP\fIinfile\fP option of 
\fBmbset\fP has an existing \fBmbprocess\fP parameter file,
then that parameter file will be read and the existing
parameter values will be modified. If no \fBmbprocess\fP 
parameter file exists, then \fBmbset\fP starts with
default processing parameters, modifies those, and then
generates a new parameter file.

The \fBmbprocess\fP commands modified by \fBmbset\fP are:

 GENERAL PARAMETERS:
   EXPLICIT
        causes mbprocess to set modes implicitely
        - e.g. the SVPFILE command will also set 
          raytracing on even if the RAYTRACE command 
          is not given [explicit mode commands required] 
   FORMAT constant
        sets format id [no default]
   INFILE filename
        sets input file path [no default]
   OUTFILE filename
        sets output file path [no default]

 NAVIGATION MERGING:
   NAVMODE boolean
        sets navigation merging [0]
          0: navigation merge off
          1: navigation merge on
   NAVFILE filename
        sets navigation file path [no default]
   NAVFORMAT constant
        sets navigation file format [9]
   NAVHEADING boolean
        sets heading to be merged from navigation file
        - note: heading merged from navigation before 
          heading correction applied
          0: heading not changed
          1: heading merged from navigation file
   NAVSPEED boolean
        sets speed to be merged from navigation file
          0: speed not changed
          1: speed merged from navigation file
   NAVDRAFT boolean
        sets draft to be merged from navigation file
        - note: draft merged from navigation before 
          draft correction applied
          0: draft not changed
          1: draft merged from navigation file
   NAVINTERP boolean
        sets navigation interpolation algorithm [0]
          0: linear interpolation (recommended)
          1: spline interpolation

 ADJUSTED NAVIGATION MERGING:
   NAVADJMODE boolean
        sets navigation merging from mbnavadjust [0]
        - longitude and latitude only
          0: adjusted navigation merge off
          1: adjusted navigation merge on
   NAVADJFILE filename
        sets adjusted navigation file path
        - this file supercedes navigation file for
          lon and lat only
        - uses mbnavadjust output
   NAVADJINTERP boolean
        sets adjusted navigation interpolation algorithm [0]
          0: linear interpolation (recommended)
          1: spline interpolation

 DATA CUTTING:
   DATACUTCLEAR
        removes all existing data cutting commands
   DATACUT kind mode min max
        adds new data cutting command, where:
          kind = 0 : cut applied to bathymetry data
          kind = 1 : cut applied to amplitude data
          kind = 2 : cut applied to sidescan data
          mode = 0 : min and max indicate start and end
                     beam/pixel numbers between which data
                     are flagged or zeroed
          mode = 1 : min and max indicate start and end
                     acrosstrack distance (m) between which
                     data are flagged or zeroed
   BATHCUTNUMBER min max
        adds new bathymetry data cutting command where
        min and max are the start and end beam numbers
        between which data are flagged (note that 
 	flagging bathymetry also flags amplitude data)
   BATHCUTDISTANCE min max
        adds new bathymetry data cutting command where
        min and max are the start and end acrosstrack
        distance (m) between which data are flagged 
 	(note that flagging bathymetry also flags  
 	amplitude data)
   BATHCUTSPEED min max
        adds new bathymetry data cutting command where
        all beams are flagged for pings with a ship
 	or vehicle speed less than min or greater than
 	max (note that flagging bathymetry also flags  
 	amplitude data)
   AMPCUTNUMBER min max
        adds new amplitude data cutting command where
        min and max are the start and end beam numbers
        between which amplitude data are zeroed (note
 	that zeroing amplitude data has no impact on
 	bathymetry data)
   AMPCUTDISTANCE min max
        adds new amplitude data cutting command where
        min and max are the start and end acrosstrack
        distance (m) between which amplitude data are 
 	zeroed (note that zeroing amplitude data has 
 	no impact on bathymetry data)
   AMPCUTSPEED min max
        adds new amplitude data cutting command where
        all amplitude values are zeroed for pings with 
 	a ship or vehicle speed less than min or greater 
 	than max (note that zeroing amplitude data has 
 	no impact on bathymetry data)
   SSCUTNUMBER min max
        adds new sidescan data cutting command where
        min and max are the start and end pixel numbers
        between which sidescan data are zeroed  (note 
 	that zeroing sidescan data has no impact on 
 	bathymetry data)
   SSCUTDISTANCE min max
        adds new sidescan data cutting command where
        min and max are the start and end acrosstrack
        distance (m) between which sidescan data are 
 	zeroed  (note that zeroing sidescan data has 
 	no impact on bathymetry data)
   SSCUTSPEED min max
        adds new sidescan data cutting command where
        all sidescan values are zeroed for pings with 
 	a ship or vehicle speed less than min or greater 
 	than max (note that zeroing sidescan data has 
 	no impact on bathymetry data)

 BATHYMETRY EDITING:
   EDITSAVEMODE boolean
        turns on reading edit save file (from mbedit) [0]
   EDITSAVEFILE filename
        sets edit save file path (from mbedit) [none]

 BATHYMETRY RECALCULATION:
   SVPMODE mode
        sets usage of a water sound speed model (sound
        velocity profile, or SVP) [0]
         0: bathymetry recalculation by raytracing off
         1: bathymetry recalculation by raytracing on
         2: translate depths from corrected to uncorrected
            or vice versa depending on SOUNDSPEEDREF
            command
   SVPFILE filename
        sets SVP file path [no default]
   SSVMODE boolean
        sets ssv mode [0]
         0: use ssv from file
         1: offset ssv from file (set by SSV)
         2: use constant ssv (set by SSV)
   SSV constant/offset
        sets ssv value or offset (m/s) [1500.0]
   TTMULTIPLY multiplier
        sets value multiplied by travel times [1.0]
   SOUNDSPEEDREF boolean
        determines the handling of the sound 
        speed reference for bathymetry [1]
	- note: if raytracing is turned off then
          this command implies correcting or
          uncorrecting using the SVP specified 
          with the SVPFILE command
         0: produce "uncorrected" bathymetry 
            referenced to a uniform 1500 m/s 
            water sound speed model.
         1: produce "corrected" bathymetry
            referenced to a realistic water 
            sound speed model.

 DRAFT CORRECTION:
   DRAFTMODE mode
        sets draft correction [0]
        - note: draft merged from navigation before 
          draft correction applied
          0: no draft correction
          1: draft correction by offset 
          2: draft correction by multiply
          3: draft correction by offset and multiply
          4: draft set to constant
   DRAFT constant
        sets draft value (m) [0.0]
   DRAFTOFFSET offset
        sets value added to draft (m) [0.0]
   DRAFTMULTIPLY multiplier
        sets value multiplied by draft [1.0]

 HEAVE CORRECTION:
   HEAVEMODE mode
        sets heave correction [0]
        - note: heave correction by offset and/or 
          multiplication is added to any lever
          heave correction, and then either used in 
          bathymetry recalculation or added to 
          existing bathymetry
          0: no heave correction
          1: heave correction by offset
          2: heave correction by multiply
          3: heave correction by offset and multiply
   HEAVEOFFSET offset
        sets value added to heave (m) 
   HEAVEMULTIPLY multiplier
        sets value multiplied by heave
	    
 LEVER CORRECTION:
   LEVERMODE mode
        sets heave correction by lever calculation [0]
        - note: lever heave correction is added to
          any heave correction by offset and/or 
          multiplication, and then either used in 
          bathymetry recalculation or added to 
          existing bathymetry
          0: no lever calculation
          1: heave correction by lever calculation 
   VRUOFFSETX constant
        sets athwartships offset of attitude sensor (m) 
        - note: positive to starboard 
   VRUOFFSETY constant
        sets fore-aft offset of attitude sensor (m) 
        - note: positive forward 
   VRUOFFSETZ constant
        sets vertical offset of attitude sensor (m) 
        - note: positive down
   SONAROFFSETX constant
        sets athwartships offset of sonar receive array (m) 
        - note: positive to starboard 
   SONAROFFSETY constant
        sets fore-aft offset of sonar receive array (m) 
        - note: positive forward 
   SONAROFFSETZ constant
        sets vertical offset of sonar receive array (m) 
        - note: positive down

 ROLL CORRECTION:
   ROLLBIASMODE mode
        sets roll correction [0]
          0: no roll correction
          1: roll correction by single roll bias
          2: roll correction by separate port and 
             starboard roll bias
   ROLLBIAS offset
        sets roll bias (degrees)
   ROLLBIASPORT offset
        sets port roll bias (degrees)
   ROLLBIASSTBD offset
        sets starboard roll bias (degrees)

 PITCH CORRECTION:
   PITCHBIASMODE mode
        sets pitch correction [0]
          0: no pitch correction
          1: pitch correction by pitch bias
   PITCHBIAS offset
        sets pitch bias (degrees)

 HEADING CORRECTION:
   HEADINGMODE mode
        sets heading correction [no heading correction]
        - note: heading merged from navigation before 
          heading correction applied
          0: no heading correction
          1: heading correction using course
             made good
          2: heading correction by offset
          3: heading correction using course 
             made good and offset
   HEADINGOFFSET offset
        sets value added to heading (degrees)

 SIDESCAN RECALCULATION:
   SSRECALCMODE  boolean
        sets recalculation of sidescan for 
        Simrad multibeam data
          0: sidescan recalculation off
          1: sidescan recalculation on
   SSPIXELSIZE constant
        sets recalculated sidescan pixel size (m) [0.0]
        - a zero value causes the pixel size to
          be recalculated for every data record
   SSSWATHWIDTH  constant
        sets sidescan swath width (degrees) [0.0]
        - a zero value causes the swath width
          to be recalculated for every data record
   SSINTERPOLATE  constant
        sets sidescan interpolation distance 
        (number of pixels)

 METADATA INSERTION:
   METAVESSEL string              
        sets mbinfo metadata string for vessel
   METAINSTITUTION string         
        sets mbinfo metadata string for vessel 
        operator institution or company
   METAPLATFORM string            
        sets mbinfo metadata string for sonar  
        platform (ship or vehicle)
   METASONAR string               
        sets mbinfo metadata string for sonar  
        model name
   METASONARVERSION string        
        sets mbinfo metadata string for sonar  
        version (usually software version)
   METACRUISEID string            
        sets mbinfo metadata string for institutional  
        cruise id
   METACRUISENAME string          
        sets mbinfo metadata string for descriptive  
        cruise name
   METAPI string                  
        sets mbinfo metadata string for principal  
        investigator
   METAPIINSTITUTION string       
        sets mbinfo metadata string for principal  
        investigator
   METACLIENT string              
        sets mbinfo metadata string fo data owner  
        (usually PI institution)
   METASVCORRECTED boolean        
        sets mbinfo metadata boolean for sound  
        velocity corrected depths
   METATIDECORRECTED boolean      
        sets mbinfo metadata boolean for tide  
        corrected bathymetry
   METABATHEDITMANUAL boolean     
        sets mbinfo metadata boolean for manually  
        edited bathymetry
   METABATHEDITAUTO boolean       
        sets mbinfo metadata boolean for automatically  
        edited bathymetry
   METAROLLBIAS constant           
        sets mbinfo metadata constant for roll bias  
        (degrees + to starboard)
   METAPITCHBIAS constant         
        sets mbinfo metadata constant for pitch bias  
        (degrees + forward)
   METAHEADINGBIAS constant        
        sets mbinfo metadata constant for heading bias
   METADRAFT constant             
        sets mbinfo metadata constant for vessel draft (m)

 PROCESSING KLUGES:
   KLUGE001
        processing kluge 001 (not yet defined)
        - occasionaly odd processing problems will
          occur that are specific to a particular
          survey or sonar version
        - mbprocess will allow one-time fixes to
          be defined as "kluges" that can be turned
          on through the parameter files.

The file naming convention for parameter files, processing
files (e.g. bathymery edit, navigation, and svp files) and output
swath data files follows some simple rules based on suffixes
and the data format id. \fBMB-System\fP data formats are specified
using two-digit or three-digit numbers (see the \fBMBIO\fP manual page).
If an input swath data file is named "root.mbXX", where XX is the format
id, then the default processed output file will be "rootp.mbXX".
The "p" inserted before the ".mbXX" suffix indicates the output
file has been created by \fBmbprocess\fP.
If the input file does not follow the *.mbXX naming convention,
then the output filename will just consist of the input name
with "p.mbXX" added as a suffix. 

The default names for processing
files depends on their source and use. Typical examples include:

Bathymetry edit save file generated by \fBmbedit\fP and 
\fBmbclean\fP have an ".esf" suffix.
 	inputname.esf 

Water sound velocity profile (SVP) files generated 
by \fBmbvelocitytool\fP use a ".svp" suffix by default.
 	inputname.svp

Water sound velocity profile (SVP) files generated 
by \fBmbsvplist\fP also use the ".svp" suffix. 
However, multiple SVP files may be
extracted from each input swath file, so the files are
numbered. Here, "YYY" is the SVP number, incrementing from
"001":
 	inputname_YYY.svp

Edited navigation files generated by \fBmbnavedit\fP have 
an ".nve" suffix:
 	inputname.nve

Adjusted navigation files generated by \fBmbnavadjust\fP
have an ".naY" suffix, where "Y" is a number between 0-9.
The \fBmbnavadjust\fP package may be used multiple times
for a survey; the adjustments are numbered sequentially from
"0":
 	inputname.naY

.SH AUTHORSHIP
David W. Caress (caress@mbari.org)
.br
  Monterey Bay Aquarium Research Institute
.br
Dale N. Chayes (dale@ldeo.columbia.edu)
.br
  Lamont-Doherty Earth Observatory

.SH OPTIONS
.TP
.B \-E
.br
This option causes \fBmbset\fP to require all
processing modes to be explicitly set by \fB-P\fP
calls. Normally, \fBmbset\fP will implicitly set
some modes based on the parameters applied. For example,
if a user applies \fB-P\fP\fISVPFILE:best.svp\fP, \fBmbset\fP
would normally set the bathymetry recalculation mode
on so that the SVP file specified actually gets used.
.TP
.B \-I
\fIinfile\fP
.br
This option sets the swath data file whose
\fBmprocess\fP parameter file is created or
modified by\fBmbset\fP. If 
.TP
.B \-L
.br
This option causes \fBmbset\fP to look for any edit save
files, navigation files, and SVP files with expected names
and set the \fBmbprocess\fP parameters so that these files
are used. If multiple navigation files are available
(reflecting use of \fBmbnavedit\fP and one or more
uses of \fBmbnavadjust\fP), then the latest (highest numbered)
\fBmbnavadjust\fP solution is used.
.TP
.B \-H
This "help" flag causes the program to print out a description
of its operation and then exit immediately.
.TP
.B \-V
Normally, \fBmbset\fP works "silently" without outputting
anything to the stderr stream.  If the
\fB-V\fP flag is given, then \fBmbset\fP works in a "verbose" mode and
outputs the program version being used and lists the processing
parameters output to the \fBmbprocess\fP parameter file.

.SH EXAMPLES
Suppose the user has a Simrad EM300 data file called
"mbari_1998_526_msn.mb57" that requires processing.

Editing the bathymetry data in this file with mbedit will generate
an edit save file "mbari_1998_526_msn.mb57.esf" and
an mbprocess parameter file "mbari_1998_526_msn.mb57.par".
The contents of the parameter file are:

 ## MB-System processing parameter file
 ## Written by mb_pr_writepar version $Id: mbset.l,v 5.5 2001-08-10 22:42:50 dcaress Exp $
 ## MB-system Version 5.0.0
 ## Generated by user <caress> on cpu <menard> at <Tue Jan 16 13:23:06 2001>
 ## 
 ##
 ## Forces explicit reading of parameter modes.
 EXPLICIT 
 ##
 ## General Parameters:
 FORMAT 57
 INFILE /u/caress/dev/test/mbari_1998_526_msn.mb57
 OUTFILE /u/caress/dev/test/mbari_1998_526_msnp.mb57
 ## 
 ## Navigation Merging:
 NAVMODE 0
 NAVFILE /u/caress/dev/test/mbari_1998_526_msn.mb57.nve
 NAVFORMAT 0
 NAVHEADING 0
 NAVSPEED 0
 NAVDRAFT 0
 NAVINTERP 0
 ## 
 ## Adjusted Navigation Merging:
 NAVADJMODE 0
 NAVADJFILE 
 NAVADJINTERP 0
 ## 
 ## Bathymetry Flagging:
 EDITSAVEMODE 1
 EDITSAVEFILE /u/caress/dev/test/mbari_1998_526_msn.mb57.esf
 ## 
 ## Bathymetry Recalculation:
 RAYTRACE 0
 SVPFILE 
 SSVMODE 0
 SSV 0.000000
 TTMULTIPLY 1.000000
 CORRECTED 1
 ## 
 ## Draft Correction:
 DRAFTMODE 0
 DRAFT 0.000000
 DRAFTOFFSET 0.000000
 DRAFTMULTIPLY 1.000000
 ## 
 ## Heave Correction:
 HEAVEMODE 0.000000
 HEAVEOFFSET 0.000000
 HEAVEMULTIPLY 1.000000
 ## 
 ## Roll Correction:
 ROLLBIASMODE 0
 ROLLBIAS 0.000000
 ROLLBIASPORT 0.000000
 ROLLBIASSTBD 0.000000
 ## 
 ## Pitch Correction:
 PITCHBIASMODE 0
 PITCHBIAS 0.000000
 ## 
 ## Heading Correction:
 HEADINGMODE 0
 HEADINGOFFSET 0.000000
 ## 
 ## Sidescan Recalculation:
 SSRECALCMODE 0
 SSPIXELSIZE 0.000000
 SSSWATHWIDTH 0.000000
 SSINTERPOLATE 0.000000

Editing the navigation with mbnavedit will generate
a navigation file named "mbari_1998_526_msn.mb57.nve"
and will modify the parameter file. The changed lines
in "mbari_1998_526_msn.mb57.par" are:

 ## Navigation Merging:
 NAVMODE 1
 NAVFILE /u/caress/dev/test/mbari_1998_526_msn.mb57.nve
 NAVFORMAT 9
 NAVHEADING 1
 NAVSPEED 1
 NAVDRAFT 1
 NAVINTERP 0

At this point, running \fBmbprocess\fP on 
"mbari_1998_526_msn.mb57" will apply the bathymetry
flags from \fBmbedit\fP and merge the navigation from
\fBmbnavedit\fP, but will not modify the data in any
other way.

If the user wants to recalculate the bathymetry using
an SVP file "goodmodel.svp" and a roll bias correction
of +0.5 degrees, the following will suffice:

 	mbset -I mbari_1998_526_msn.mb57 \
 		-PSVPFILE:goodmodel.svp \
 		-PROLLBIAS:0.5 \
 		-PDRAFT:1.95 \
 		-V
 
The changed lines in "mbari_1998_526_msn.mb57.par" are:

 ##
 ## Bathymetry Recalculation:
 RAYTRACE 1
 SVPFILE goodmodel.svp
 ##
 ## Draft Correction:
 DRAFTMODE 4
 DRAFT 1.950000
 ##
 ## Roll Correction:
 ROLLBIASMODE 1
 ROLLBIAS 0.500000

To process the data, run mbprocess:

 	mbprocess -Imbari_1998_526_msn.mb57 -V

The output to the terminal is:
 
 Program mbprocess
 Version $Id: mbset.l,v 5.5 2001-08-10 22:42:50 dcaress Exp $
 MB-System Version 5.0.alpha01
 
 Program <mbprocess>
 Version $Id: mbset.l,v 5.5 2001-08-10 22:42:50 dcaress Exp $
 MB-system Version 5.0.alpha01
 
 Input and Output Files:
   Format:                        57
   Input file:                    mbari_1998_526_msn.mb57
   Output file:                   /u/caress/dev/test/mbari_1998_526_msnp.mb57
 
 Navigation Merging:
   Navigation merged from navigation file.
   Heading merged from navigation file.
   Speed merged from navigation file.
   Draft merged from navigation file.
   Navigation file:               /u/caress/dev/test/mbari_1998_526_msn.mb57.nve
   Navigation algorithm:          linear interpolation
 
 Adjusted Navigation Merging:
   Navigation not merged from adjusted navigation file.
   Adjusted navigation file:      
   Adjusted navigation algorithm: linear interpolation
 
 Bathymetry Editing:
   Bathymetry edits applied from file.
   Bathymetry edit file:          mbari_1998_526_msn.mb57.esf
 
 Bathymetry Recalculation:
   Bathymetry recalculated by raytracing.
   SVP file:                      goodmodel.svp
   SSV not modified.
   SSV offset/constant:           0.000000 m/s
   Travel time multiplier:        1.000000 m
   Bathymetry reference:          CORRECTED
 
 Draft Correction:
   Draft constant:                1.950000 m
   Draft offset:                  0.000000 m
   Draft multiplier:              1.000000 m
 
 Heave Correction:
   Heave not modified.
   Heave offset:                  0.000000 m
   Heave multiplier:              1.000000 m
 
 Roll Correction:
   Roll offset by bias.
   Roll bias:                     0.500000 deg
   Port roll bias:                0.000000 deg
   Starboard roll bias:           0.000000 deg
 
 Pitch Correction:
   Pitch not modified.
   Pitch bias:                    0.000000 deg
 
 Heading Correction:
   Heading not modified.
   Heading offset:                0.000000 deg
 
 Sidescan Recalculation:
   Sidescan not recalculated.
   Sidescan pixel size:           0.000000
   Sidescan swath width:          0.000000
   Sidescan interpolation:        0
 
 1264 navigation records read
 Nav start time: 1998 05 02 01:29:27.722000
 Nav end time:   1998 05 02 01:50:30.743000
 
 369 bathymetry edits read
 
 279 input data records
 1264 input nav records
 47 input comment records
 1551 input other records
 279 output data records
 1264 output nav records
 127 output comment records
 1551 output other records

.SH SEE ALSO
\fBmbsystem\fP(l), \fBmbprocess\fP(l), 
\fBmbedit\fP(l), \fBmbnavedit\fP(l), \fBmbvelocitytool\fP(l)

.SH BUGS
Oh yeah...