/*--------------------------------------------------------------------
 *    The MB-system:	mbsys_elac.h	8/20/94
 *	$Id: mbsys_elac.h,v 4.0 1994-10-21 12:35:07 caress Exp $
 *
 *    Copyright (c) 1994 by 
 *    D. W. Caress (caress@lamont.ldgo.columbia.edu)
 *    and D. N. Chayes (dale@lamont.ldgo.columbia.edu)
 *    Lamont-Doherty Earth Observatory
 *    Palisades, NY  10964
 *
 *    See README file for copying and redistribution conditions.
 *--------------------------------------------------------------------*/
/*
 * mbsys_elac.h defines the data structures used by MBIO functions
 * to store data from Elac SeaBat 9001 multibeam sonar systems.
 * The data formats which are commonly used to store Elac 
 * data in files include
 *      MBF_CBAT9001 : MBIO ID 81
 *
 *
 * Author:	D. W. Caress (L-DEO)
 * Date:	August 20, 1994
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.1  1994/10/21  12:20:01  caress
 * Initial revision
 *
 *
 *
 */
/*
 * Notes on the MBSYS_ELAC data structure:
 *   1. Elac multibeam systems output binary data telegrams.
 *   2. Elac BottomChart sonar systems output both bathymetry
 *      and amplitude information for up to 56 beams per telegram.
 *   3. Each ping produces 8 beams.  A wide swath is constructed
 *      by successively pinging in different directions.
 *   4. Each telegram is preceded by a two byte start code and
 *      followed by a three byte end code consisting of 0x03
 *      followed by two bytes representing the checksum for
 *      the data bytes.  MB-System does not calculate checksums
 *      and puts 0's in the checksum bytes.
 *   5. The relevent telegram start codes, types, and sizes are:
 *         0x0250: Comment (Defined only for MB-System)   200 data bytes
 *         0x0251: Position                                36 data bytes
 *         0x0252: Parameter                               56 data bytes
 *         0x0253: Sound velocity profile                2016 data bytes
 *         0x0254: BottomChart 56 beam bathymetry         848 data bytes
 *         0x0255: BottomChart 40 beam bathymetry         608 data bytes
 *         0x0256: BottomChart 32 beam bathymetry         488 data bytes
 *   6. Elac systems record navigation fixes using the position 
 *      telegram; navigation is not always included in the per ping data.
 *      Since speed is not recorded, it is impossible to extrapolate
 *      position from the last navigation fix when processing the
 *      data serially, as MBIO does.  It may thus be necessary to extract
 *      the navigation from the position telegrams and remerge it with
 *      the ping telegrams using the program mbmerge.
 *
 */

/* sonar types */
#define	MBSYS_ELAC_UNKNOWN	0
#define	MBSYS_ELAC_BOTTOMCHART	1

/* maximum number of beams and pixels */
#define	MBSYS_ELAC_MAXBEAMS	56
#define	MBSYS_ELAC_COMMENT_LENGTH	200

/* telegram types */
#define	ELAC_NONE		0
#define	ELAC_COMMENT		0x0250
#define	ELAC_POS		0x0251
#define	ELAC_PARAMETER		0x0252
#define	ELAC_SVP		0x0253
#define	ELAC_BATH56		0x0254
#define	ELAC_BATH40		0x0255
#define	ELAC_BATH32		0x0256

/* telegram sizes */
#define	ELAC_COMMENT_SIZE	200
#define	ELAC_POS_SIZE		36
#define	ELAC_PARAMETER_SIZE	44
#define	ELAC_SVP_SIZE		2016
#define	ELAC_BATH56_SIZE	848
#define	ELAC_BATH40_SIZE	608
#define	ELAC_BATH32_SIZE	488

/* internal data structure */

struct mbsys_elac_profile_struct
	{
	int	year;
	int	month;
	int	day;
	int	hour;
	int	minute;
	int	second;
	int	hundredth_sec;
	int	thousandth_sec;
	int	latitude;		/* 180 deg = 2*pi*e9 */
	int	longitude;		/* 180 deg = 2*pi*e9 */
	int	roll;			/* 0.005 degrees */
	int	pitch;			/* 0.005 degrees */
	int	heading;		/* 0.01 degrees */
	int	heave;			/* 0.001 meters */
	short bath[8];		/* depths:  0.01 meters */	
	short int bath_acrosstrack[8];
				/* acrosstrack distances: 0.01 meters */
	short int bath_alongtrack[8];
				/* alongtrack distances: 0.01 meters */
	short int tt[8];	/* travel times:         0.05 msec */
	short int angle[8];	/* 0.005 degrees */
	short int quality[8];	/* 0 (bad) to 3 (good) */
	short int amp[8];	/* ??? */

	};

struct mbsys_elac_struct
	{
	/* type of data record */
	int	kind;			/* Data vs Comment */

	/* type of sonar */
	int	sonar;			/* Type of Elac sonar */

	/* parameter info (parameter telegrams) */
	int	par_year;
	int	par_month;
	int	par_day;
	int	par_hour;
	int	par_minute;
	int	par_second;
	int	par_hundredth_sec;
	int	par_thousandth_sec;
	short	roll_offset;	/* roll offset (degrees) */
	short	pitch_offset;	/* pitch offset (degrees) */
	short	heading_offset;	/* heading offset (degrees) */
	short	time_delay;	/* positioning system delay (sec) */
	short	transducer_port_height;
	short	transducer_starboard_height;
	short	transducer_port_depth;
	short	transducer_starboard_depth;
	short	transducer_port_x;
	short	transducer_starboard_x;
	short	transducer_port_y;
	short	transducer_starboard_y;
	short	transducer_port_error;
	short	transducer_starboard_error;
	short	antenna_height;
	short	antenna_x;
	short	antenna_y;
	short	vru_height;
	short	vru_x;
	short	vru_y;
	short	heave_offset;
	short	line_number;
	short	start_or_stop;
	short	transducer_serial_number;

	/* comment */
	char	comment[MBSYS_ELAC_COMMENT_LENGTH];

	/* position (position telegrams) */
	int	pos_year;
	int	pos_month;
	int	pos_day;
	int	pos_hour;
	int	pos_minute;
	int	pos_second;
	int	pos_hundredth_sec;
	int	pos_thousandth_sec;
	int	pos_latitude;		/* 180 deg = 2e9 */
	int	pos_longitude;		/* 180 deg = 2e9 */
	unsigned long	utm_northing;
	unsigned long	utm_easting;
	int	utm_zone_lon;		/* 180 deg = 2e9 */
	char	utm_zone;
	char	hemisphere;
	char	ellipsoid;
	char	pos_spare;
	int	semi_major_axis;
	int	other_quality;

	/* sound velocity profile */
	int	svp_year;
	int	svp_month;
	int	svp_day;
	int	svp_hour;
	int	svp_minute;
	int	svp_second;
	int	svp_hundredth_sec;
	int	svp_thousandth_sec;
	int	svp_latitude;		/* 180 deg = 2e9 */
	int	svp_longitude;		/* 180 deg = 2e9 */
	int	svp_num;
	int	svp_depth[500]; /* 0.1 meters */
	int	svp_vel[500];	/* 0.1 meters/sec */

	/* bathymetry */
	int	ping_num;
	int	sound_vel;
	int	mode;
	int	pulse_length;
	int	source_power;
	int	receiver_gain;
	int	profile_num;	/* number of profiles stored */
	int	beams_bath;	/* number of beams stored */
	struct mbsys_elac_profile_struct profile[7];
	};