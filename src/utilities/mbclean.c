/*--------------------------------------------------------------------
 *    The MB-system:	mbclean.c	3.00	2/26/93
 *    $Id: mbclean.c,v 3.1 1993-05-18 00:01:15 caress Exp $
 *
 *    Copyright (c) 1993 by 
 *    D. W. Caress (caress@lamont.ldgo.columbia.edu)
 *    and D. N. Chayes (dale@lamont.ldgo.columbia.edu)
 *    Lamont-Doherty Earth Observatory
 *    Palisades, NY  10964
 *
 *    See README file for copying and redistribution conditions.
 *--------------------------------------------------------------------*/
/*
 * MBCLEAN identifies and flags artifacts in multibeam bathymetry data
 * Bad beams  are  indentified  based  on  one simple criterion only: 
 * excessive bathymetric slopes.   The default input and output streams 
 * are stdin and stdout.
 *
 * Author:	D. W. Caress
 * Date:	February 26, 1993
 *
 * Acknowledgments:
 * This program is based to a large extent on the program mbcleanx
 * by Alberto Malinverno (formerly at L-DEO, now at Schlumberger),
 * which was in turn based on the original program mbclean (v. 1.0)
 * by David Caress.
 *
 * $Log: not supported by cvs2svn $
 * Revision 3.0  1993/05/04  22:21:32  dale
 * Initial version.
 *
 */

/* standard include files */
#include <stdio.h>
#include <math.h>
#include <strings.h>

/* mbio include files */
#include "../../include/mb_status.h"
#include "../../include/mb_format.h"

/* local defines */
#define DTR (M_PI/180.)
#define	MBCLEAN_FLAG_ONE	1
#define	MBCLEAN_FLAG_BOTH	2
#define	MBCLEAN_ZERO_ONE	3
#define	MBCLEAN_ZERO_BOTH	4

/* ping structure definition */
struct mbclean_ping_struct 
	{
	int	id;
	int	time_i[6];
	double	time_d;
	double	navlon;
	double	navlat;
	double	speed;
	double	heading;
	int	*bath;
	int	*bathdist;
	int	*back;
	int	*backdist;
	double	*bathx;
	double	*bathy;
	};

/* bad beam identifier structure definition */
struct bad_struct
	{
	int	flag;
	int	ping;
	int	beam;
	int	bath;
	};

/*--------------------------------------------------------------------*/

main (argc, argv)
int argc;
char **argv; 
{
	static char rcs_id[] = "$Id: mbclean.c,v 3.1 1993-05-18 00:01:15 caress Exp $";
	static char program_name[] = "MBCLEAN";
	static char help_message[] =  "MBCLEAN identifies and flags artifacts in multibeam bathymetry data\nBad beams  are  indentified  based  on  one simple criterion only: \nexcessive bathymetric slopes.   The default input and output streams \nare stdin and stdout.";
	static char usage_message[] = "mbclean [-Fformat -Llonflip -Mmode -Cslope -Ddistance -Xzap_beams \n\t-N -V -H -Iinfile -Ooutfile]";
	extern char *optarg;
	extern int optkind;
	int	errflg = 0;
	int	c;
	int	help = 0;
	int	flag = 0;

	/* MBIO status variables */
	int	status;
	int	verbose = 0;
	int	error = MB_ERROR_NO_ERROR;
	char	*message;

	/* MBIO read control parameters */
	int	format;
	int	pings;
	int	lonflip;
	double	bounds[4];
	int	btime_i[6];
	int	etime_i[6];
	double	btime_d;
	double	etime_d;
	double	speedmin;
	double	timegap;
	int	beams_bath;
	int	beams_back;
	char	ifile[128];
	char	*imbio_ptr;

	/* MBIO write control parameters */
	char	ofile[128];
	char	*ombio_ptr;

	/* MBIO buffer structure pointer */
	char	*buff_ptr;
	int	nbuff;
	int	nwant = 500;
	int	nload;
	int	nhold = 50;
	int	ndump;
	int	done;
	int	finished;

	/* mbio read and write values */
	char	*store_ptr;
	int	kind;
	struct mbclean_ping_struct ping[3];
	struct bad_struct bad[2];
	int	find_bad;
	int	ndata = 0;
	int	nbad = 0;
	int	nflag = 0;
	int	nzero = 0;
	char	comment[256];
	double	slopemax = 1.0;
	double	distancemin = 10.;
	int	mode = MBCLEAN_FLAG_ONE;
	int	zap_beams = 0;

	/* slope processing variables */
	double	mtodeglon;
	double	mtodeglat;
	double	headingx;
	double	headingy;
	double	*bathx1;
	double	*bathy1;
	double	*bathx2;
	double	*bathy2;
	double	*bathx3;
	double	*bathy3;
	int	nlist;
	int	*list;
	int	median;
	double	dd;
	double	slope;

	/* time, user, host variables */
	long int	right_now;
	char	date[25], user[128], host[128];

	/* processing variables */
	int	start;

	int	i, j, k, l, m, p, b;

	/* get current default values */
	status = mb_defaults(verbose,&format,&pings,&lonflip,bounds,
		btime_i,etime_i,&speedmin,&timegap);

	/* reset all defaults but the format and lonflip */
	pings = 1;
	bounds[0] = -360.;
	bounds[1] = 360.;
	bounds[2] = -90.;
	bounds[3] = 90.;
	btime_i[0] = 1962;
	btime_i[1] = 2;
	btime_i[2] = 21;
	btime_i[3] = 10;
	btime_i[4] = 30;
	btime_i[5] = 0;
	etime_i[0] = 2062;
	etime_i[1] = 2;
	etime_i[2] = 21;
	etime_i[3] = 10;
	etime_i[4] = 30;
	etime_i[5] = 0;
	speedmin = 0.0;
	timegap = 1000000000.0;

	/* set default input and output */
	strcpy (ifile, "stdin");
	strcpy (ofile, "stdout");

	/* process argument list */
	while ((c = getopt(argc, argv, "VvHhF:f:L:l:I:i:O:o:C:c:D:d:M:m:X:x:")) != -1)
	  switch (c) 
		{
		case 'H':
		case 'h':
			help++;
			break;
		case 'V':
		case 'v':
			verbose++;
			break;
		case 'F':
		case 'f':
			sscanf (optarg,"%d", &format);
			flag++;
			break;
		case 'L':
		case 'l':
			sscanf (optarg,"%d", &lonflip);
			flag++;
			break;
		case 'I':
		case 'i':
			sscanf (optarg,"%s", ifile);
			flag++;
			break;
		case 'O':
		case 'o':
			sscanf (optarg,"%s", ofile);
			flag++;
			break;
		case 'C':
		case 'c':
			sscanf (optarg,"%lf", &slopemax);
			flag++;
			break;
		case 'D':
		case 'd':
			sscanf (optarg,"%lf", &distancemin);
			flag++;
			break;
		case 'M':
		case 'm':
			sscanf (optarg,"%d", &mode);
			flag++;
			break;
		case 'X':
		case 'x':
			sscanf (optarg,"%d", &zap_beams);
			flag++;
			break;
		case '?':
			errflg++;
		}

	/* if error flagged then print it and exit */
	if (errflg)
		{
		fprintf(stderr,"usage: %s\n", usage_message);
		fprintf(stderr,"\nProgram <%s> Terminated\n",
			program_name);
		exit(MB_FAILURE);
		}

	/* print starting message */
	if (verbose == 1)
		{
		fprintf(stderr,"\nProgram %s\n",program_name);
		fprintf(stderr,"Version %s\n",rcs_id);
		fprintf(stderr,"MB-system Version %s\n",MB_VERSION);
		}

	/* print starting debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  Program <%s>\n",program_name);
		fprintf(stderr,"dbg2  Version %s\n",rcs_id);
		fprintf(stderr,"dbg2  MB-system Version %s\n",MB_VERSION);
		fprintf(stderr,"dbg2  Control Parameters:\n");
		fprintf(stderr,"dbg2       verbose:        %d\n",verbose);
		fprintf(stderr,"dbg2       help:           %d\n",help);
		fprintf(stderr,"dbg2       pings:          %d\n",pings);
		fprintf(stderr,"dbg2       lonflip:        %d\n",lonflip);
		fprintf(stderr,"dbg2       bounds[0]:      %f\n",bounds[0]);
		fprintf(stderr,"dbg2       bounds[1]:      %f\n",bounds[1]);
		fprintf(stderr,"dbg2       bounds[2]:      %f\n",bounds[2]);
		fprintf(stderr,"dbg2       bounds[3]:      %f\n",bounds[3]);
		fprintf(stderr,"dbg2       btime_i[0]:     %d\n",btime_i[0]);
		fprintf(stderr,"dbg2       btime_i[1]:     %d\n",btime_i[1]);
		fprintf(stderr,"dbg2       btime_i[2]:     %d\n",btime_i[2]);
		fprintf(stderr,"dbg2       btime_i[3]:     %d\n",btime_i[3]);
		fprintf(stderr,"dbg2       btime_i[4]:     %d\n",btime_i[4]);
		fprintf(stderr,"dbg2       btime_i[5]:     %d\n",btime_i[5]);
		fprintf(stderr,"dbg2       etime_i[0]:     %d\n",etime_i[0]);
		fprintf(stderr,"dbg2       etime_i[1]:     %d\n",etime_i[1]);
		fprintf(stderr,"dbg2       etime_i[2]:     %d\n",etime_i[2]);
		fprintf(stderr,"dbg2       etime_i[3]:     %d\n",etime_i[3]);
		fprintf(stderr,"dbg2       etime_i[4]:     %d\n",etime_i[4]);
		fprintf(stderr,"dbg2       etime_i[5]:     %d\n",etime_i[5]);
		fprintf(stderr,"dbg2       speedmin:       %f\n",speedmin);
		fprintf(stderr,"dbg2       timegap:        %f\n",timegap);
		fprintf(stderr,"dbg2       data format:    %d\n",format);
		fprintf(stderr,"dbg2       input file:     %s\n",ifile);
		fprintf(stderr,"dbg2       output file:    %s\n",ofile);
		fprintf(stderr,"dbg2       mode:           %d\n",mode);
		fprintf(stderr,"dbg2       maximum slope:  %f\n",slopemax);
		fprintf(stderr,"dbg2       minimum dist:   %f\n",distancemin);
		fprintf(stderr,"dbg2       zap_beams:      %d\n",zap_beams);
		}

	/* if help desired then print it and exit */
	if (help)
		{
		fprintf(stderr,"\n%s\n",help_message);
		fprintf(stderr,"\nusage: %s\n", usage_message);
		exit(MB_ERROR_NO_ERROR);
		}

	/* check that clean mode is allowed 
		for the specified data format */
	if (mb_flag_table[format] == MB_NO && mode <= 2)
		{
		fprintf(stderr,"\nMBIO format %d does not allow flagging of bad data \nas negative numbers (specified by cleaning mode %d).\n",format,mode);
		fprintf(stderr,"\nCopy the data to another format or set the cleaning mode to zero \nbad data values (-M3 or -M4).\n");
		fprintf(stderr,"\nProgram <%s> Terminated\n",
			program_name);
		exit(error);
		}

	/* initialize reading the input multibeam file */
	if ((status = mb_read_init(
		verbose,ifile,format,pings,lonflip,bounds,
		btime_i,etime_i,speedmin,timegap,
		&imbio_ptr,&btime_d,&etime_d,
		&beams_bath,&beams_back,&error)) != MB_SUCCESS)
		{
		mb_error(verbose,error,&message);
		fprintf(stderr,"\nMBIO Error returned from function <mb_read_init>:\n%s\n",message);
		fprintf(stderr,"\nMultibeam File <%s> not initialized for reading\n",ifile);
		fprintf(stderr,"\nProgram <%s> Terminated\n",
			program_name);
		exit(error);
		}

	/* initialize writing the output multibeam file */
	if ((status = mb_write_init(
		verbose,ofile,format,&ombio_ptr,
		&beams_bath,&beams_back,&error)) != MB_SUCCESS)
		{
		mb_error(verbose,error,&message);
		fprintf(stderr,"\nMBIO Error returned from function <mb_write_init>:\n%s\n",message);
		fprintf(stderr,"\nMultibeam File <%s> not initialized for writing\n",ofile);
		fprintf(stderr,"\nProgram <%s> Terminated\n",
			program_name);
		exit(error);
		}

	/* allocate memory for data arrays */
	status = mb_malloc(verbose,beams_bath*sizeof(int),&ping[0].bath,&error);
	status = mb_malloc(verbose,beams_bath*sizeof(int),&ping[0].bathdist,&error);
	status = mb_malloc(verbose,beams_back*sizeof(int),&ping[0].back,&error);
	status = mb_malloc(verbose,beams_back*sizeof(int),&ping[0].backdist,&error);
	status = mb_malloc(verbose,beams_bath*sizeof(double),&ping[0].bathx,&error);
	status = mb_malloc(verbose,beams_bath*sizeof(double),&ping[0].bathy,&error);
	status = mb_malloc(verbose,beams_bath*sizeof(int),&ping[1].bath,&error);
	status = mb_malloc(verbose,beams_bath*sizeof(int),&ping[1].bathdist,&error);
	status = mb_malloc(verbose,beams_back*sizeof(int),&ping[1].back,&error);
	status = mb_malloc(verbose,beams_back*sizeof(int),&ping[1].backdist,&error);
	status = mb_malloc(verbose,beams_bath*sizeof(double),&ping[1].bathx,&error);
	status = mb_malloc(verbose,beams_bath*sizeof(double),&ping[1].bathy,&error);
	status = mb_malloc(verbose,beams_bath*sizeof(int),&ping[2].bath,&error);
	status = mb_malloc(verbose,beams_bath*sizeof(int),&ping[2].bathdist,&error);
	status = mb_malloc(verbose,beams_back*sizeof(int),&ping[2].back,&error);
	status = mb_malloc(verbose,beams_back*sizeof(int),&ping[2].backdist,&error);
	status = mb_malloc(verbose,beams_bath*sizeof(double),&ping[2].bathx,&error);
	status = mb_malloc(verbose,beams_bath*sizeof(double),&ping[2].bathy,&error);
	status = mb_malloc(verbose,3*beams_bath*sizeof(int),&list,&error);

	/* if error initializing memory then quit */
	if (error != MB_ERROR_NO_ERROR)
		{
		mb_error(verbose,error,message);
		fprintf(stderr,"\nMBIO Error allocating data arrays:\n%s\n",message);
		fprintf(stderr,"\nProgram <%s> Terminated\n",
			program_name);
		exit(error);
		}

	/* write comments to beginning of output file */
	kind = MB_DATA_COMMENT;
	strncpy(comment,"\0",256);
	sprintf(comment,"This bathymetry data automatically edited by program %s version %s",
		program_name,rcs_id);
	status = mb_put(verbose,ombio_ptr,kind,
			ping[0].time_i,ping[0].time_d,
			ping[0].navlon,ping[0].navlat,
			ping[0].speed,ping[0].heading,
			beams_bath,ping[0].bath,ping[0].bathdist,
			beams_back,ping[0].back,ping[0].backdist,
			comment,&error);
	strncpy(comment,"\0",256);
	sprintf(comment,"MB-system Version %s",MB_VERSION);
	status = mb_put(verbose,ombio_ptr,kind,
			ping[0].time_i,ping[0].time_d,
			ping[0].navlon,ping[0].navlat,
			ping[0].speed,ping[0].heading,
			beams_bath,ping[0].bath,ping[0].bathdist,
			beams_back,ping[0].back,ping[0].backdist,
			comment,&error);
	right_now = time((long *)0);
	strncpy(date,"\0",25);
	right_now = time((long *)0);
	strncpy(date,ctime(&right_now),24);
	strcpy(user,getenv("USER"));
	gethostname(host,128);
	strncpy(comment,"\0",256);
	sprintf(comment,"Run by user <%s> on cpu <%s> at <%s>",
		user,host,date);
	status = mb_put(verbose,ombio_ptr,kind,
			ping[0].time_i,ping[0].time_d,
			ping[0].navlon,ping[0].navlat,
			ping[0].speed,ping[0].heading,
			beams_bath,ping[0].bath,ping[0].bathdist,
			beams_back,ping[0].back,ping[0].backdist,
			comment,&error);
	strncpy(comment,"\0",256);
	sprintf(comment,"Control Parameters:");
	status = mb_put(verbose,ombio_ptr,kind,
			ping[0].time_i,ping[0].time_d,
			ping[0].navlon,ping[0].navlat,
			ping[0].speed,ping[0].heading,
			beams_bath,ping[0].bath,ping[0].bathdist,
			beams_back,ping[0].back,ping[0].backdist,
			comment,&error);
	strncpy(comment,"\0",256);
	sprintf(comment,"  MBIO data format:   %d",format);
	status = mb_put(verbose,ombio_ptr,kind,
			ping[0].time_i,ping[0].time_d,
			ping[0].navlon,ping[0].navlat,
			ping[0].speed,ping[0].heading,
			beams_bath,ping[0].bath,ping[0].bathdist,
			beams_back,ping[0].back,ping[0].backdist,
			comment,&error);
	strncpy(comment,"\0",256);
	sprintf(comment,"  Input file:         %s",ifile);
	status = mb_put(verbose,ombio_ptr,kind,
			ping[0].time_i,ping[0].time_d,
			ping[0].navlon,ping[0].navlat,
			ping[0].speed,ping[0].heading,
			beams_bath,ping[0].bath,ping[0].bathdist,
			beams_back,ping[0].back,ping[0].backdist,
			comment,&error);
	strncpy(comment,"\0",256);
	sprintf(comment,"  Output file:        %s",ofile);
	status = mb_put(verbose,ombio_ptr,kind,
			ping[0].time_i,ping[0].time_d,
			ping[0].navlon,ping[0].navlat,
			ping[0].speed,ping[0].heading,
			beams_bath,ping[0].bath,ping[0].bathdist,
			beams_back,ping[0].back,ping[0].backdist,
			comment,&error);
	strncpy(comment,"\0",256);
	sprintf(comment,"  Longitude flip:     %d",lonflip);
	status = mb_put(verbose,ombio_ptr,kind,
			ping[0].time_i,ping[0].time_d,
			ping[0].navlon,ping[0].navlat,
			ping[0].speed,ping[0].heading,
			beams_bath,ping[0].bath,ping[0].bathdist,
			beams_back,ping[0].back,ping[0].backdist,
			comment,&error);
	strncpy(comment,"\0",256);
	sprintf(comment,"  Cleaning mode:      %d",mode);
	if (mode == MBCLEAN_FLAG_ONE)
		strcat(comment," (flag one beam of each outlier slope)");
	if (mode == MBCLEAN_FLAG_BOTH)
		strcat(comment," (flag both beams of each outlier slope)");
	if (mode == MBCLEAN_ZERO_ONE)
		strcat(comment," (zero one beam of each outlier slope)");
	if (mode == MBCLEAN_ZERO_BOTH)
		strcat(comment," (zero both beams of each outlier slope)");
	status = mb_put(verbose,ombio_ptr,kind,
			ping[0].time_i,ping[0].time_d,
			ping[0].navlon,ping[0].navlat,
			ping[0].speed,ping[0].heading,
			beams_bath,ping[0].bath,ping[0].bathdist,
			beams_back,ping[0].back,ping[0].backdist,
			comment,&error);
	strncpy(comment,"\0",256);
	sprintf(comment,"  Maximum slope:      %f",slopemax);
	status = mb_put(verbose,ombio_ptr,kind,
			ping[0].time_i,ping[0].time_d,
			ping[0].navlon,ping[0].navlat,
			ping[0].speed,ping[0].heading,
			beams_bath,ping[0].bath,ping[0].bathdist,
			beams_back,ping[0].back,ping[0].backdist,
			comment,&error);
	strncpy(comment,"\0",256);
	sprintf(comment,"  Minimum distance:   %f",distancemin);
	status = mb_put(verbose,ombio_ptr,kind,
			ping[0].time_i,ping[0].time_d,
			ping[0].navlon,ping[0].navlat,
			ping[0].speed,ping[0].heading,
			beams_bath,ping[0].bath,ping[0].bathdist,
			beams_back,ping[0].back,ping[0].backdist,
			comment,&error);
	strncpy(comment,"\0",256);
	sprintf(comment,"  Outer beams zapped: %d",zap_beams);
	status = mb_put(verbose,ombio_ptr,kind,
			ping[0].time_i,ping[0].time_d,
			ping[0].navlon,ping[0].navlat,
			ping[0].speed,ping[0].heading,
			beams_bath,ping[0].bath,ping[0].bathdist,
			beams_back,ping[0].back,ping[0].backdist,
			comment,&error);
	strncpy(comment,"\0",256);
	sprintf(comment," ");
	status = mb_put(verbose,ombio_ptr,kind,
			ping[0].time_i,ping[0].time_d,
			ping[0].navlon,ping[0].navlat,
			ping[0].speed,ping[0].heading,
			beams_bath,ping[0].bath,ping[0].bathdist,
			beams_back,ping[0].back,ping[0].backdist,
			comment,&error);

	/* initialize the buffer */
	status = mb_buffer_init(verbose,&buff_ptr,&error);

	/* read and write */
	done = MB_NO;
	start = 0;
	ping[0].id = -1;
	ping[1].id = -1;
	ping[2].id = -1;
	if (verbose == 1) fprintf(stderr,"\n");
	while (!done)
		{
		/* load some data into the buffer */
		error = MB_ERROR_NO_ERROR;
		status = mb_buffer_load(verbose,buff_ptr,imbio_ptr,nwant,
				&nload,&nbuff,&error);

		/* give the statistics */
		if (verbose > 1) fprintf(stderr,"\n");
		if (verbose >= 1)
			{
			fprintf(stderr,"%d records loaded into buffer\n\n",nload);
			}

		/* check for done */
		if (nload <= 0)
			{
			done = MB_YES;
			nhold = 0;
			}

		/* find first data */
		if (ping[1].id < 0)
			{
			status = mb_buffer_get_next_data(verbose,
				buff_ptr,imbio_ptr,start,&ping[1].id,
				ping[1].time_i,&ping[1].time_d,
				&ping[1].navlon,&ping[1].navlat,
				&ping[1].speed,&ping[1].heading,
				&beams_bath,ping[1].bath,ping[1].bathdist,
				&beams_back,ping[1].back,ping[1].backdist,
				&error);
			if (status = MB_SUCCESS)
				ndata++;
			}

		/* find next data */
		finished = MB_NO;
		while (finished == MB_NO)
			{
			find_bad = MB_NO;
			status = mb_buffer_get_next_data(verbose,
				buff_ptr,imbio_ptr,ping[1].id+1,&ping[2].id,
				ping[2].time_i,&ping[2].time_d,
				&ping[2].navlon,&ping[2].navlat,
				&ping[2].speed,&ping[2].heading,
				&beams_bath,ping[2].bath,ping[2].bathdist,
				&beams_back,ping[2].back,ping[2].backdist,
				&error);
			if (status == MB_SUCCESS)
				ndata++;

			if (verbose >= 2)
				{
				fprintf(stderr,"\ndbg2  current data status:\n");
				fprintf(stderr,"dbg2    last:     %d\n",ping[0].id);
				fprintf(stderr,"dbg2    current:  %d\n",ping[1].id);
				fprintf(stderr,"dbg2    next:     %d\n",ping[2].id);
				}

			/* zap outer beams if requested */
			if (zap_beams > 0 && ping[1].id >= 0)
				{
				for (i=0;i<zap_beams;i++)
					{
					if (ping[1].bath[i] > 0)
					{
					find_bad = MB_YES;
					if (mode <= 2)
						{
						ping[1].bath[i] = -ping[1].bath[i];
						nflag++;
						}
					else
						{
						ping[1].bath[i] = 0;
						nzero++;
						}
					}
					j = beams_bath - i - 1;
					if (ping[1].bath[j] > 0)
					{
					find_bad = MB_YES;
					if (mode <= 2)
						{
						ping[1].bath[j] = -ping[1].bath[j];
						nflag++;
						}
					else
						{
						ping[1].bath[j] = 0;
						nzero++;
						}
					}
					}
				}

			/* get locations of data points in local coordinates */
			if (ping[1].id >= 0)
				mb_coor_scale(verbose,ping[1].navlat,
					&mtodeglon,&mtodeglat);
			for (j=0;j<3;j++)
			{
			if (ping[j].id >= 0)
				{
				headingx = sin(ping[j].heading*DTR);
				headingy = cos(ping[j].heading*DTR);
				for (i=0;i<beams_bath;i++)
					{
					ping[j].bathx[i] = (ping[j].navlon 
						- ping[1].navlon)/mtodeglon 
						+ headingy*ping[j].bathdist[i];
					ping[j].bathy[i] = (ping[j].navlat 
						- ping[1].navlat)/mtodeglat 
						- headingx*ping[j].bathdist[i];
					}
				}
			}
			if (verbose >= 2)
				{
				fprintf(stderr,"\ndbg2  center beam locations:\n");
				for (j=0;j<3;j++)
				{
				if (ping[j].id >= 0)
					{
					fprintf(stderr,"dbg2    ping[%d] x:    %f\n",
						j,ping[j].bathx[beams_bath/2]);
					fprintf(stderr,"dbg2    ping[%d] y:    %f\n",
						j,ping[j].bathy[beams_bath/2]);
					}
				}
				}

			/* find the median depth in current ping */
			nlist = 0;
			for (j=0;j<3;j++)
			{
			if (ping[j].id >= 0)
				for (i=0;i<beams_bath;i++)
					{
					if (ping[j].bath[i] > 0)
						{
						list[nlist] = ping[j].bath[i];
						nlist++;
						}
					}
			}
			sort(nlist,list);
			median = list[nlist/2];
			if (verbose >= 2)
				{
				fprintf(stderr,"\ndbg2  depth statistics:\n");
				fprintf(stderr,"dbg2    number:        %d\n",nlist);
				fprintf(stderr,"dbg2    minimum depth: %d\n",list[0]);
				fprintf(stderr,"dbg2    median depth:  %d\n",median);
				fprintf(stderr,"dbg2    maximum depth: %d\n",
					list[nlist-1]);
				}

			/* loop over each of the points in the current ping */
			if (ping[1].id >= 0)
			{
			for (i=0;i<beams_bath;i++)
			if (ping[1].bath[i] > 0)
			{
			for (j=0;j<3;j++)
				{
				if (ping[j].id >= 0)
				{
				for (k=0;k<beams_bath;k++)
				if (ping[j].bath[k] > 0 
					&& ping[1].bath[i] > 0)
					{
					dd = sqrt((ping[j].bathx[k] 
						- ping[1].bathx[i])
						*(ping[j].bathx[k] 
						- ping[1].bathx[i])
						+ (ping[j].bathy[k] 
						- ping[1].bathy[i])
						*(ping[j].bathy[k] 
						- ping[1].bathy[i]));
					if (dd > 0.0)
						slope = fabs(
						(ping[j].bath[k] 
						- ping[1].bath[i])/dd);
					else
						slope = 0.0;
					if (slope > slopemax 
						&& dd > distancemin)
						{
						find_bad = MB_YES;
						if (mode == MBCLEAN_FLAG_BOTH)
							{
							bad[0].flag = MB_YES;
							bad[0].ping = j;
							bad[0].beam = k;
							bad[0].bath = 
								ping[j].bath[k];
							bad[1].flag = MB_YES;
							bad[1].ping = 1;
							bad[1].beam = i;
							bad[1].bath = 
								ping[1].bath[i];
							ping[j].bath[k] = 
								-ping[j].bath[k];
							ping[1].bath[i] = 
								-ping[1].bath[i];
							nbad++;
							nflag = nflag + 2;
							if (verbose >= 1)
							fprintf(stderr,"%4d %2d %2d %2.2d:%2.2d:%2.2d  %4d %6.2f %5d %5d\n",
							ping[j].time_i[0],
							ping[j].time_i[1],
							ping[j].time_i[2],
							ping[j].time_i[3],
							ping[j].time_i[4],
							ping[j].time_i[5],
							k,slope,
							ping[j].bath[k],median);
							}
						else if (mode == MBCLEAN_FLAG_ONE)
							{
							if (fabs((double)ping[j].bath[k]-median) 
							> fabs((double)ping[1].bath[i]-median))
								{
								bad[0].flag = MB_YES;
								bad[0].ping = j;
								bad[0].beam = k;
								bad[0].bath = ping[j].bath[k];
								bad[1].flag = MB_NO;
								ping[j].bath[k] = -ping[j].bath[k];
								}
							else
								{
								bad[0].flag = MB_YES;
								bad[0].ping = 1;
								bad[0].beam = i;
								bad[0].bath = ping[1].bath[i];
								bad[1].flag = MB_NO;
								ping[1].bath[i] = -ping[1].bath[i];
								}
							nbad++;
							nflag++;
							}
						else if (mode == MBCLEAN_ZERO_BOTH)
							{
							bad[0].flag = MB_YES;
							bad[0].ping = j;
							bad[0].beam = k;
							bad[0].bath = ping[j].bath[k];
							bad[1].flag = MB_YES;
							bad[1].ping = 1;
							bad[1].beam = i;
							bad[1].bath = ping[1].bath[i];
							ping[j].bath[k] = 0;
							ping[1].bath[i] = 0;
							nbad++;
							nzero = nzero + 2;
							}
						else if (mode == MBCLEAN_ZERO_ONE)
							{
							if (fabs((double)ping[j].bath[k]-median) 
							> fabs((double)ping[1].bath[i]-median))
								{
								bad[0].flag = MB_YES;
								bad[0].ping = j;
								bad[0].beam = k;
								bad[0].bath = ping[j].bath[k];
								bad[1].flag = MB_NO;
								ping[j].bath[k] = 0;
								}
							else
								{
								bad[0].flag = MB_YES;
								bad[0].ping = 1;
								bad[0].beam = i;
								bad[0].bath = ping[1].bath[i];
								bad[1].flag = MB_NO;

								ping[1].bath[i] = 0;
								}
							nbad++;
							nzero++;
							}
						}
					if (verbose >= 1 && slope > slopemax 
						&& dd > distancemin
						&& bad[0].flag == MB_YES)
						{
						p = bad[0].ping;
						b = bad[0].beam;
						if (verbose >= 2)
							fprintf(stderr,"\n");
						fprintf(stderr,"%4d %2d %2d %2.2d:%2.2d:%2.2d  %4d %6.2f %8.2f %5d %5d\n",
						ping[p].time_i[0],
						ping[p].time_i[1],
						ping[p].time_i[2],
						ping[p].time_i[3],
						ping[p].time_i[4],
						ping[p].time_i[5],
						b,slope,dd,bad[0].bath,median);
						}
					if (verbose >= 1 && slope > slopemax
						&& dd > distancemin
						&& bad[1].flag == MB_YES)
						{
						p = bad[1].ping;
						b = bad[1].beam;
						if (verbose >= 2)
							fprintf(stderr,"\n");
						fprintf(stderr,"%4d %2d %2d %2.2d:%2.2d:%2.2d  %4d %6.2f %8.2f %5d %5d\n",
						ping[p].time_i[0],
						ping[p].time_i[1],
						ping[p].time_i[2],
						ping[p].time_i[3],
						ping[p].time_i[4],
						ping[p].time_i[5],
						b,slope,dd,bad[1].bath,median);
						}
					}
					
				}
				}
			}
			}

			/* if a bad ping was found reset pings in buffer */
			if (find_bad == MB_YES)
			for (j=0;j<3;j++)
				status = mb_buffer_insert(verbose,
					buff_ptr,imbio_ptr,ping[j].id,
					ping[j].time_i,ping[j].time_d,
					ping[j].navlon,ping[j].navlat,
					ping[j].speed,ping[j].heading,
					beams_bath,ping[j].bath,ping[j].bathdist,
					beams_back,ping[j].back,ping[j].backdist,
					comment,&error);

			/* reset counters and data */
			if (status == MB_SUCCESS)
				{
				for (j=0;j<2;j++)
					{
					ping[j].id = ping[j+1].id;
					for (i=0;i<6;i++)
						ping[j].time_i[i] = 
							ping[j+1].time_i[i];
					ping[j].time_d = ping[j+1].time_d;
					ping[j].navlon = ping[j+1].navlon;
					ping[j].navlat = ping[j+1].navlat;
					ping[j].speed = ping[j+1].speed;
					ping[j].heading = ping[j+1].heading;
					for (i=0;i<beams_bath;i++)
						{
						ping[j].bath[i] = 
							ping[j+1].bath[i];
						ping[j].bathdist[i] = 
							ping[j+1].bathdist[i];
						}
					for (i=0;i<beams_back;i++)
						{
						ping[j].back[i] = 
							ping[j+1].back[i];
						ping[j].backdist[i] = 
							ping[j+1].backdist[i];
						}
					}
				}
			else
				finished = MB_YES;
			}

		/* dump data from the buffer */
		ndump = 0;
		if (nbuff > 0)
			{
			status = mb_buffer_dump(verbose,buff_ptr,ombio_ptr,
				nhold,&ndump,&nbuff,&error);
			ping[1].id = ping[1].id - ndump;
			ping[0].id = ping[0].id - ndump;
			}

		/* give the statistics */
		if (verbose >= 1)
			{
			fprintf(stderr,"\n%d records dumped from buffer\n",ndump);
			}
		}

	/* close the files */
	status = mb_buffer_close(verbose,buff_ptr,&error);
	status = mb_close(verbose,imbio_ptr,&error);
	status = mb_close(verbose,ombio_ptr,&error);

	/* free the memory */
	for (j=0;j<3;j++)
		{
		mb_free(verbose,ping[j].bath,&error); 
		mb_free(verbose,ping[j].bathdist,&error); 
		mb_free(verbose,ping[j].back,&error); 
		mb_free(verbose,ping[j].backdist,&error); 
		mb_free(verbose,ping[j].bathx,&error); 
		mb_free(verbose,ping[j].bathy,&error); 
		}
	mb_free(verbose,list,&error); 

	/* check memory */
	if (verbose >= 4)
		status = mb_memory_list(verbose,&error);

	/* give the statistics */
	if (verbose >= 1)
		{
		fprintf(stderr,"\n%d bathymetry data records processed\n",ndata);
		fprintf(stderr,"%d excessive slopes identified\n",nbad);
		fprintf(stderr,"%d beams flagged\n",nflag);
		fprintf(stderr,"%d beams zeroed\n",nzero);
		}

	/* end it all */
	exit(status);
}
/*--------------------------------------------------------------------*/
/* 	function sort sorts the data.  
 *	Uses the shell method from Numerical Recipes.
 */
#define ALN2I 1.442695022
#define TINY 1.0e-5
int sort(n,r)
int	n;
int *r;
{
	int	status = MB_SUCCESS;
	int	nn, m, j, i, lognb2;
	int	tr;

	if (n <= 0) 
		{
		status = MB_FAILURE;
		return(status);
		}

	lognb2 = (log((double) n)*ALN2I + TINY);
	m = n;
	for (nn=1;nn<=lognb2;nn++)
		{
		m >>= 1;
		for (j=m+1;j<=n;j++)
			{
			i = j - m;
			tr = r[j];
			while (i >= 1 && r[i] > tr)
				{
				r[i+m] = r[i];
				i -= m;
				}
			r[i+m] = tr;
			}
		}

	return(status);
}
/*--------------------------------------------------------------------*/