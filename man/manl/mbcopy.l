.TH MBCOPY 1 "22 February 1994"
.SH NAME
\fBmbcopy\fP - Copy multibeam bathymetry data files.

.SH VERSION
Version 4.00

.SH SYNOPSIS
\fBmbcopy\fP [\fB-F\fIinformat/outformat \fB-R\fIwest/east/south/north \fB-P\fIpings 
\fB-S\fIspeed \fB-L\fIlonflip \fB-B\fIyr/mo/da/hr/mn/sc \fB-E\fIyr/mo/da/hr/mn/sc 
\fB-I\fIinfilename \fB-O\fIoutfilename \fB-C\fIcommentfile\fP \fB-N \fB-V -H\fP]

.SH DESCRIPTION
\fBMBCOPY\fP is an utility for copying multibeam data files which
may be used to change formats, average pings, or window
in time and space. \fBMBCOPY\fP can be used as a filter from
stdin to stdout, or it may do i/o to and from files.

.SH AUTHORSHIP
David W. Caress (caress@lamont.ldeo.columbia.edu)
.br
Dale N. Chayes (dale@lamont.ldeo.columbia.edu)
.br
Lamont-Doherty Earth Observatory
.br
Palisades, NY 10964

.SH OPTIONS
.TP
.B \fB-B\fIyr/mo/da/hr/mn/sc\fP
Sets the starting time for data allowed in the input data; pings
with times before the starting time will be ignored. 
Default: \fIyr/mo/da/hr/mn/sc\fP = 1962/2/21/10/30/0.
.TP
.B \fB-C\fIcommentfile\fP
Text file containing comments which are inserted into the
beginning of the output data stream.  This option is typically
used to insert a data pedigree statement at the beginning of
data processing.
.TP
.B \fB-E\fIyr/mo/da/hr/mn/sc\fP
Sets the ending time for data allowed in the input data; pings
with times after the ending time will be ignored. 
Default: \fIyr/mo/da/hr/mn/sc\fP = 2062/2/21/10/30/0.
.TP
.B \fB-F\fIinformat/outformat\fP
Sets the format for the input and output multibeam data using 
\fBMBIO\fP integer format identifiers. 
This program uses the \fBMBIO\fP library and will read or write any multibeam
format supported by \fBMBIO\fP. A list of the multibeam data formats
currently supported by \fBMBIO\fP and their identifier values
is given in the \fBMBIO\fP manual page. When the \fIinformat\fP and
\fIoutformat\fP values are both associated with the same multibeam
sonar system (e.g. the Atlas Hydrosweep DS system), then the complete
data stream contained in the input file can be copied to the output
file.  If the two formats are associated with two different multibeam
systems, then only the time stamp, navigation, and beam values will
be copied.  The use of ping averaging also causes a partial data stream
to be passed, even when compatible or identical input and output formats
are specified (see the \fB-P\fP option).
Default: \fIinformat\fP = 11; \fIoutformat\fP = 11.
.TP
.B \fB-H\fP
This "help" flag cause the program to print out a description
of its operation and then exit immediately.
.TP
.B \fB-I\fIinfilename\fP
Data file from which the input data will be read. If
no input file is specified, the input will be read
from stdin. Default: \fIinfilename\fP = stdin.
.TP
.B \fB-L\fIlonflip\fP
Sets the range of the longitude values returned.
If \fIlonflip\fP=-1 then the longitude values will be in
the range from -360 to 0 degrees. If \fIlonflip\fP=0 
then the longitude values will be in
the range from -180 to 180 degrees. If \fIlonflip\fP=1 
then the longitude values will be in
the range from 0 to 360 degrees.
Default: \fIlonflip\fP = 0.
.TP
.B \fB-N\fP
Normally, \fBMBCOPY\fP generates a set of comment records at
the beginning of the output stream which record when, how,
and by whom \fBMBCOPY\fP was run.  If the
\fB-N\fP flag is given, these comments are not included in 
the output stream, and, in addition, any preexisting comment records
in the input data stream are not passed to the output data stream.
However, the \fB-N\fP option does not affect the insertion of
comments from a text file if specified using the \fB-C\fP option.
.TP
.B \fB-O\fIoutfilename\fP
Data file to which the output data will be written. If
no output file is specified, the output will be written to
stdout. Default: \fIoutfilename\fP = stdout.
.TP
.B \fB-P\fIpings\fP
Sets the ping averaging of the input data. If \fIpings\fP = 1, then
no ping averaging is performed. If \fIpings\fP > 0, then
that number of input pings will be averaged to produce one output
ping.  If \fIpings\fP = 0, then the ping averaging will automatically
be done so that the along-track ping spacing is equal to the across-track
beam spacing. If ping averaging is used (\fIpings\fP != 1), then
only a partial data stream can be copied (see the \fB-F\fP option).
Default: \fIpings\fP = 1 (no ping averaging).
.TP
.B \fB-R\fIwest/east/south/north\fP
Sets the longitude and latitude bounds within which multibeam 
data will be read. Only the data which lies within these bounds will
be copied. 
Default: \fIwest\fP=-360, east\fI=360\fP, \fIsouth\fP=-90, \fInorth\fP=90.
.TP
.B \fB-S\fIspeed\fP
Sets the minimum speed in km/hr (5.5 kts ~ 10 km/hr) allowed in 
the input data; pings associated with a smaller ship speed will not be
copied. Default: \fIspeed\fP = 0.
.TP
.B \fB-T\fItimegap\fP
Sets the maximum time gap in minutes between adjacent pings allowed before
the data is considered to have a gap. Default: \fItimegap\fP = 1.
.TP
.B \fB-V\fP
Normally, \fBMBCOPY\fP works "silently" without outputting
anything to the stderr stream.  If the
\fB-V\fP flag is given, then \fBMBCOPY\fP works in a "verbose" mode and
outputs the program version being used, all error status messages, 
and the number of records input and output.

.SH EXAMPLES
Suppose one wishes to copy a raw Hydrosweep file (format 21) called hs_raw into a
L-DEO binary Hydrosweep file (format 24) called hs_binary while windowing the data
into a region between 145W and 140W longitude and between 10S and 5S
longitude. The following will suffice:
 	mbcopy -P1 -F21/24 -R-145/-140/-10/-5 -Ihs_raw -Ohs_binary

Suppose one has a program called thrash_prog which requires Hydrosweep
data to be input in the URI format (format 23) to stdin, but the existing
data is in a raw Hydrosweep file (format 21).  The following will work:
 	mbcopy -P1 -F21/23 | thrash_prog

where a pipe (|) has been used to direct the stdout stream from \fBMBCOPY\fP
to the stdin stream of thrash_prog.
.SH BUGS
Certainly.