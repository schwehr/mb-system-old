/*--------------------------------------------------------------------
 *    The MB-system:	mb_pslibface.c	5/15/94
 *    $Id$
 *
 *    Copyright (c) 1993-2012 by
 *    David W. Caress (caress@mbari.org)
 *      Monterey Bay Aquarium Research Institute
 *      Moss Landing, CA 95039
 *    and Dale N. Chayes (dale@ldeo.columbia.edu)
 *      Lamont-Doherty Earth Observatory
 *      Palisades, NY 10964
 *
 *    See README file for copying and redistribution conditions.
 *--------------------------------------------------------------------*/
/*
 * MB_PSLIBFACE is a set of functions which provide an interface
 * between the program MBCONTOUR and the PSLIB Postscript plotting
 * library from GMT.  This code is separated from MBCONTOUR so that
 * a similar set of interface functions for pen plotting can be linked
 * to the same source code.
 */

/* standard include files */
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

/* MBIO include files */
#include "../../include/mb_status.h"
#include "../../include/mb_define.h"
#include "../../include/mb_aux.h"

/* GMT include files */
#include "gmt.h"
#include "pslib.h"

/* global variables */
int	argc_save;
char	**argv_save;
double	inchtolon;
int	ncolor;
int	*red;
int	*green;
int	*blue;
int	rgb[3];

/*--------------------------------------------------------------------------*/
/* 	function plot_init initializes the GMT plotting. */
int plot_init(	int	verbose,
		int	argc,
		char	**argv,
		double	*bounds_use,
		double	*scale,
		double	*inch2lon,
		int	*error)
{
	char	*function_name = "plot_init";
	int	status = MB_SUCCESS;
	int	errflg = 0;
	double	bounds[4];
	double	x1, y1, x2, y2, xx1, yy1, xx2, yy2;
	int	i;

	/* print input debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBBA function <%s> called\n",function_name);
		fprintf(stderr,"dbg2  Input arguments:\n");
		fprintf(stderr,"dbg2       verbose:          %d\n",verbose);
		fprintf(stderr,"dbg2       argc:             %d\n",argc);
		fprintf(stderr,"dbg2       argv:             %lu\n",(size_t)argv);
		fprintf(stderr,"dbg2       bounds_use[0]:    %f\n",bounds_use[0]);
		fprintf(stderr,"dbg2       bounds_use[1]:    %f\n",bounds_use[1]);
		fprintf(stderr,"dbg2       bounds_use[2]:    %f\n",bounds_use[2]);
		fprintf(stderr,"dbg2       bounds_use[3]:    %f\n",bounds_use[3]);
		fprintf(stderr,"dbg2       scale:            %f\n",*scale);
		}

	/* save argc and argv */
	argc_save = argc;
	argv_save = argv;

	/* deal with gmt options */
	GMT_begin (argc, argv);
	for (i = 1; i < argc; i++)
		{
		if (argv[i][0] == '-')
			{
			switch (argv[i][1])
				{
				/* Common parameters */

				case 'B':
				case 'J':
				case 'K':
				case 'O':
				case 'P':
				case 'R':
				case 'U':
				case 'V':
				case 'X':
				case 'x':
				case 'Y':
				case 'y':
				case 'c':
				case '\0':
					errflg += GMT_get_common_args (argv[i],
						&bounds[0], &bounds[1],
						&bounds[2], &bounds[3]);
					break;

				/* Supplemental parameters */

				case 'F':
					sscanf (&argv[i][2], "%d/%d/%d",
						&gmtdefs.basemap_frame_rgb[0],
						&gmtdefs.basemap_frame_rgb[1],
						&gmtdefs.basemap_frame_rgb[2]);
					break;
				}
			}
		}

	/* if error flagged then return */
	if (errflg)
		{
		status = MB_FAILURE;
		return(status);
		}

	/* set up map */
	GMT_map_setup(bounds[0],bounds[1],bounds[2],bounds[3]);

	/* initialize plotting */
	GMT_plotinit (argc, argv);

	/* copy bounds in correct order for use by this program */
	if (project_info.region == MB_YES)
		{
		bounds_use[0] = bounds[0];
		bounds_use[1] = bounds[1];
		bounds_use[2] = bounds[2];
		bounds_use[3] = bounds[3];
		}
	else
		{
		bounds_use[0] = bounds[0];
		bounds_use[1] = bounds[2];
		bounds_use[2] = bounds[1];
		bounds_use[3] = bounds[3];
		}

	/* set clip path */
	GMT_map_clip_on (GMT_no_rgb, 3);

	/* get inches to longitude scale */
	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 0.0;
	GMT_xy_to_geo(&xx1,&yy1,x1,y1);
	GMT_xy_to_geo(&xx2,&yy2,x2,y2);
	*inch2lon = xx2 - xx1;
	inchtolon = *inch2lon;

	/* set line width */
	ps_setline(0);

	/* print output debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> completed\n",function_name);
		fprintf(stderr,"dbg2  Return values:\n");
		fprintf(stderr,"dbg2       bounds[0]:  %f\n",bounds[0]);
		fprintf(stderr,"dbg2       bounds[1]:  %f\n",bounds[1]);
		fprintf(stderr,"dbg2       bounds[2]:  %f\n",bounds[2]);
		fprintf(stderr,"dbg2       bounds[3]:  %f\n",bounds[3]);
		fprintf(stderr,"dbg2       scale:      %f\n",*scale);
		fprintf(stderr,"dbg2       inchtolon:  %f\n",*inch2lon);
		fprintf(stderr,"dbg2       error:      %d\n",*error);
		fprintf(stderr,"dbg2  Return status:\n");
		fprintf(stderr,"dbg2       status:     %d\n",status);
		}

	return(status);
}
/*--------------------------------------------------------------------------*/
/* 	function plot_end ends the GMT plotting. */
int plot_end(int verbose, int *error)
{
	char	*function_name = "plot_end";
	int	status = MB_SUCCESS;

	/* print input debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBBA function <%s> called\n",function_name);
		fprintf(stderr,"dbg2  Input arguments:\n");
		fprintf(stderr,"dbg2       verbose:          %d\n",verbose);
		}

	/* turn off clipping */
	ps_clipoff();

	/* plot basemap if required */
	if (frame_info.plot)
		{
		ps_setpaint (gmtdefs.basemap_frame_rgb);
		GMT_map_basemap ();
		rgb[0] = 0;
		rgb[1] = 0;
		rgb[2] = 0;
		ps_setpaint (rgb);
		}

	/* end the plot */
	GMT_plotend ();

	/* print output debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> completed\n",function_name);
		fprintf(stderr,"dbg2  Return values:\n");
		fprintf(stderr,"dbg2       error:      %d\n",*error);
		fprintf(stderr,"dbg2  Return status:\n");
		fprintf(stderr,"dbg2       status:     %d\n",status);
		}

	return(status);
}
/*--------------------------------------------------------------------*/
int plot_exit(int argc, char **argv)
{
	int	status = MB_SUCCESS;

	GMT_end(argc, argv);

	return(status);
}

/*--------------------------------------------------------------------*/
void set_colors(int ncol, int *rd, int *gn, int *bl)
{
	ncolor = ncol;
	red = rd;
	green = gn;
	blue = bl;
	return;
}

/*--------------------------------------------------------------------*/
void plot(double x, double y, int ipen)
{
	double	xx, yy;
	GMT_geo_to_xy(x,y,&xx,&yy);
	ps_plot(xx,yy,ipen);
	return;
}
/*--------------------------------------------------------------------*/
void setline(int linewidth)
{
        ps_setline(linewidth);
        return;
}
/*--------------------------------------------------------------------*/
void newpen(int ipen)
{
	if (ipen > -1 && ipen < ncolor)
		{
		rgb[0] = red[ipen];
		rgb[1] = green[ipen];
		rgb[2] = blue[ipen];
		ps_setpaint(rgb);
		}
	return;
}
/*--------------------------------------------------------------------*/
void justify_string(double height, char *string, double *s)
{
	int	len;

	len = strlen(string);
	s[0] = 0.0;
	s[1] = 0.185*height*len;
	s[2] = 0.37*len*height;
	s[3] = 0.37*len*height;

	return;
}
/*--------------------------------------------------------------------*/
void plot_string(double x, double y, double hgt, double angle, char *label)
{
	double	point;
	double	height;
	double	xx, yy;

	height = hgt/inchtolon;
	point = height*72.;
	GMT_geo_to_xy(x,y,&xx,&yy);
	ps_text(xx,yy,point,label,angle,5,0);

	return;
}
/*--------------------------------------------------------------------*/
