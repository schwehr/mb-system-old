/*--------------------------------------------------------------------
 *    The MB-system:	mbformat.c	3.00	1/22/93
 *    $Id: mbformat.c,v 3.0 1993-05-04 22:38:45 dale Exp $
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
 * MBFORMAT provides a description of the multibeam data format
 * associated with a particular MBIO format identifier.  If
 * no format is specified, MBFORMAT will list descriptions of all
 * the currently supported formats.
 *
 * Author:	D. W. Caress
 * Date:	January 22, 1993
 *
 * $Log: not supported by cvs2svn $
 */

/* standard include files */
#include <stdio.h>
#include <math.h>
#include <strings.h>

/* mbio include files */
#include "../../include/mb_format.h"
#include "../../include/mb_status.h"

/*--------------------------------------------------------------------*/

main (argc, argv)
int argc;
char **argv; 
{
	/* id variables */
	static char rcs_id[] = "$Id: mbformat.c,v 3.0 1993-05-04 22:38:45 dale Exp $";
	static char program_name[] = "MBFORMAT";
	static char help_message[] = "MBFORMAT is an utility which identifies the multibeam data formats \nassociated with MBIO format id's.  If no format id is specified, \nMBFORMAT lists all of the currently supported formats.";
	static char usage_message[] = "mbformat [-Fformat -V -H]";

	/* parsing variables */
	extern char *optarg;
	extern int optkind;
	int	errflg = 0;
	int	c;
	int	status;
	int	help;
	int	verbose;
	int	format;
	char	*message;
	int	i;

	help = 0;
	verbose = 0;
	format = 0;

	/* process argument list */
	while ((c = getopt(argc, argv, "VvHhF:f:")) != -1)
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
			break;
		case '?':
			errflg++;
		}

	/* if error flagged then print it and exit */
	if (errflg)
		{
		fprintf(stderr,"usage: %s\n", usage_message);
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
		fprintf(stderr,"dbg2       verbose: %d\n",verbose);
		fprintf(stderr,"dbg2       help:    %d\n",help);
		fprintf(stderr,"dbg2       format:  %d\n",format);
		}

	/* if help desired then print it and exit */
	if (help)
		{
		fprintf(stderr,"\n%s\n",help_message);
		fprintf(stderr,"\nusage: %s\n", usage_message);
		exit(MB_SUCCESS);
		}

	/* print out the info */
	if (format != 0)
		{
		status = mb_format_inf(verbose,format,&message);
		printf("\nMBIO data format id: %d\n",format);
		printf("%s",message);
		}
	else
		for (i=1;i<=MB_FORMATS;i++)
			{
			status = mb_format_inf(verbose,i,&message);
			printf("\nMBIO Data Format ID:  %d\n",i);
			printf("%s",message);
			}

	/* print output debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  Program <%s> completed\n",
			program_name);
		fprintf(stderr,"dbg2  Ending status:\n");
		fprintf(stderr,"dbg2       status:  %d\n",status);
		}

	/* end it all */
	exit(status);
}