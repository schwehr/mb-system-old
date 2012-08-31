/*--------------------------------------------------------------------
 *    The MB-system:	mb_esf.c	4/10/2003
 *    $Id$
 *
 *    Copyright (c) 2003-2012 by
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
 * mb_esf.c includes the functions used to read, write, and use
 * edit save files.
 *
 * Author:	D. W. Caress
 * Date:	April 10, 2003
 *
 * $Log: mb_esf.c,v $
 * Revision 5.13  2008/07/10 06:43:40  caress
 * Preparing for 5.1.1beta20
 *
 * Revision 5.12  2007/07/03 17:33:07  caress
 * A couple of debug statements added.
 *
 * Revision 5.11  2007/06/18 01:19:48  caress
 * Changes as of 17 June 2007.
 *
 * Revision 5.10  2006/01/24 19:11:17  caress
 * Version 5.0.8 beta.
 *
 * Revision 5.9  2006/01/06 18:27:19  caress
 * Working towards 5.0.8
 *
 * Revision 5.8  2005/04/07 04:24:33  caress
 * 5.0.7 Release.
 *
 * Revision 5.7  2005/03/26 22:05:18  caress
 * Release 5.0.7.
 *
 * Revision 5.6  2004/12/02 06:33:30  caress
 * Fixes while supporting Reson 7k data.
 *
 * Revision 5.5  2004/04/27 01:46:12  caress
 * Various updates of April 26, 2004.
 *
 * Revision 5.4  2004/02/24 22:29:02  caress
 * Fixed errors in handling Simrad datagrams and edit save files on byteswapped machines (e.g. Intel or AMD processors).
 *
 * Revision 5.3  2003/07/30 16:19:20  caress
 * Changes during iSSP meeting July 2003.
 *
 * Revision 5.2  2003/07/27 21:58:57  caress
 * Added mb_mergesort function for 5.0.0
 *
 * Revision 5.1  2003/07/26 17:59:32  caress
 * Changed beamflag handling code.
 *
 * Revision 5.0  2003/04/16 16:45:50  caress
 * Initial Version.
 *
 *
 *
 */

/* standard include files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

/* mbio include files */
#include "../../include/mb_status.h"
#include "../../include/mb_define.h"
#include "../../include/mb_process.h"
#include "../../include/mb_swap.h"

/* local prototypes */
void mb_mergesort_setup(u_char *list1, u_char *list2, size_t n, size_t size, 
	int (*cmp) (void *, void *));
void mb_mergesort_insertionsort(u_char *a, size_t n, size_t size, 
	int (*cmp)(void *, void *));

static char rcs_id[]="$Id$";

/*--------------------------------------------------------------------*/
/* 	function mb_esf_check checks for an existing esf file. */
int mb_esf_check(int verbose, char *swathfile, char *esffile, 
		int *found, int *error)
{
  	char	*function_name = "mb_esf_check";
	int	status = MB_SUCCESS;
	int	mbp_edit_mode;
	char	mbp_editfile[MB_PATH_MAXLINE];
	

	/* print input debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> called\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Input arguments:\n");
		fprintf(stderr,"dbg2       verbose:     %d\n",verbose);
		fprintf(stderr,"dbg2       swathfile:   %s\n",swathfile);
		}

	/* check if edit save file is set in mbprocess parameter file
		or just lying around */
	status = mb_pr_get_edit(verbose, swathfile, 
			&mbp_edit_mode, mbp_editfile, error);
	if (mbp_edit_mode == MBP_EDIT_ON)
		{
		*found = MB_YES;
		strcpy(esffile, mbp_editfile);
		}
	else
		{
		*found = MB_NO;
		sprintf(esffile, "%s.esf", swathfile);
		}

	/* assume success */
	status = MB_SUCCESS;

	/* print output debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> completed\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Return value:\n");
		fprintf(stderr,"dbg2       esfile:      %s\n",esffile);
		fprintf(stderr,"dbg2       found:       %d\n",*found);
		fprintf(stderr,"dbg2       error:       %d\n",*error);
		fprintf(stderr,"dbg2  Return status:\n");
		fprintf(stderr,"dbg2       status:      %d\n",status);
		}

	/* return success */
	return(status);
}

/*--------------------------------------------------------------------*/
/* 	function mb_esf_load starts handling an edit save file for
		the specified swath file.
		The load flag indicates whether an existing esf file 
			should be loaded. 
		The output flag indicates whether an output
			esf file should be opened, 
			overwriting any existing esf file. Any
			existing esf file will be backed up first. 
		If both load and output are MB_NO, nothing will be
		done. */
int mb_esf_load(int verbose, char *swathfile,
		int load, int output,
		char *esffile, 
		struct mb_esf_struct *esf,
		int *error)
{
  	char	*function_name = "mb_esf_load";
	int	status = MB_SUCCESS;
	int	found;
	int	i;

	/* print input debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> called\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Input arguments:\n");
		fprintf(stderr,"dbg2       verbose:     %d\n",verbose);
		fprintf(stderr,"dbg2       swathfile:   %s\n",swathfile);
		fprintf(stderr,"dbg2       load:        %d\n",load);
		fprintf(stderr,"dbg2       output:      %d\n",output);
		}
		
	/* initialize the esf structure */
	esf->nedit = 0;
	esf->esffile[0] = '\0';
	esf->esstream[0] = '\0';
	esf->edit = NULL;
	esf->esffp = NULL;
	esf->essfp = NULL;
	esf->byteswapped = mb_swap_check();

	/* get name of existing or new esffile, then load old edits
		and/or open new esf file */
	status = mb_esf_check(verbose, swathfile, esffile, &found, error);
	if ((load == MB_YES && found == MB_YES) || output != MBP_ESF_NOWRITE)
		{
		status = mb_esf_open(verbose, esffile, 
				load, output, esf, error);
		}

	/* print output debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> completed\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Return value:\n");
		fprintf(stderr,"dbg2       esfile:      %s\n",esffile);
		fprintf(stderr,"dbg2       nedit:       %d\n",esf->nedit);
		for (i=0;i<esf->nedit;i++)
			fprintf(stderr,"dbg2       edit event:  %d %.6f %5d %3d %3d\n",
				i,esf->edit[i].time_d,esf->edit[i].beam,
				esf->edit[i].action,esf->edit[i].use);
		fprintf(stderr,"dbg2       esf->esffp:  %lu\n",(size_t)esf->esffp);
		fprintf(stderr,"dbg2       error:       %d\n",*error);
		fprintf(stderr,"dbg2  Return status:\n");
		fprintf(stderr,"dbg2       status:      %d\n",status);
		}

	/* return success */
	return(status);
}

/*--------------------------------------------------------------------*/
/* 	function mb_esf_open starts handling of an edit save file.
		The load flag indicates whether an existing esf file 
			should be loaded. 
		The output flag indicates whether to open an output
			edit save file and edit save stream. If 
			the output flag is MBP_ESF_WRITE a new 
			esf file is created. If the output flag is
			MBP_ESF_APPEND then edit events are appended
			to any existing esf file. Any
			existing esf file will be backed up first. */
int mb_esf_open(int verbose, char *esffile, 
		int load, int output,
		struct mb_esf_struct *esf,
		int *error)
{
  	char	*function_name = "mb_esf_open";
	int	status = MB_SUCCESS;
	char	command[MB_PATH_MAXLINE];
	FILE	*esffp;
	struct stat file_status;
	int	fstat;
	char	fmode[16];
	int	i;

	/* print input debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> called\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Input arguments:\n");
		fprintf(stderr,"dbg2       verbose:     %d\n",verbose);
		fprintf(stderr,"dbg2       esffile:     %s\n",esffile);
		fprintf(stderr,"dbg2       load:        %d\n",load);
		fprintf(stderr,"dbg2       output:      %d\n",output);
		fprintf(stderr,"dbg2       esf:         %lu\n",(size_t)esf);
		fprintf(stderr,"dbg2       error:       %lu\n",(size_t)error);
		}
		
	/* initialize the esf structure */
	esf->nedit = 0;
	strcpy(esf->esffile, esffile);
	sprintf(esf->esstream, "%s.stream", esffile);
	esf->edit = NULL;
	esf->esffp = NULL;
	esf->essfp = NULL;
	esf->byteswapped = mb_swap_check();
	
	/* load edits from existing esf file if requested */
	if (load == MB_YES)
		{

		/* check that esf file exists */
		fstat = stat(esffile, &file_status);
		if (fstat == 0
		    && (file_status.st_mode & S_IFMT) != S_IFDIR)
		    {
		    /* save filename in structure */
		    strcpy(esf->esffile, esffile);

		    /* get number of old edits */
		    esf->nedit = file_status.st_size
				/ (sizeof(double) + 2 * sizeof(int));

		    /* allocate arrays for old edits */
		    if (esf->nedit > 0)
			{
			status = mb_mallocd(verbose, __FILE__, __LINE__, esf->nedit * sizeof(struct mb_edit_struct), (void **)&(esf->edit), error);
			if (status == MB_SUCCESS)
			memset(esf->edit, 0, esf->nedit * sizeof(struct mb_edit_struct));

			/* if error initializing memory then quit */
			if (status != MB_SUCCESS)
			    {
			    *error = MB_ERROR_MEMORY_FAIL;
			    fprintf(stderr, "\nUnable to allocate memory for %d edit events\n",
				esf->nedit);
			    esf->nedit = 0;
			    return(status);
			    }	
			}	

		    /* open and read the old edit file */
		    if (status == MB_SUCCESS
	    		&& esf->nedit > 0
			&& (esffp = fopen(esffile,"rw")) == NULL)
			{
			fprintf(stderr, "\nnedit:%d\n",
			    esf->nedit);
			esf->nedit = 0;
			*error = MB_ERROR_OPEN_FAIL;
			fprintf(stderr, "\nUnable to open edit save file %s\n",
			    esffile);
			}
		    else if (status == MB_SUCCESS
	    		&& esf->nedit > 0)
			{
			/* reset message */
			if (verbose > 0)
				fprintf(stderr, "Reading %d old edits...\n", esf->nedit);

			*error = MB_ERROR_NO_ERROR;
			for (i=0;i<esf->nedit && *error == MB_ERROR_NO_ERROR;i++)
			    {
			    if (fread(&(esf->edit[i].time_d), sizeof(double), 1, esffp) != 1
				|| fread(&(esf->edit[i].beam), sizeof(int), 1, esffp) != 1
				|| fread(&(esf->edit[i].action), sizeof(int), 1, esffp) != 1)
				{
				status = MB_FAILURE;
				*error = MB_ERROR_EOF;
				}
			    else if (esf->byteswapped == MB_YES)
				{
				mb_swap_double(&(esf->edit[i].time_d));
				esf->edit[i].beam = mb_swap_int(esf->edit[i].beam);
				esf->edit[i].action = mb_swap_int(esf->edit[i].action);
				}
/*fprintf(stderr,"EDITS READ: i:%d edit: %f %d %d  use:%d\n",
i,esf->edit[i].time_d,esf->edit[i].beam,
esf->edit[i].action,esf->edit[i].use);*/
			    }
			    
			/* close the file */
			fclose(esffp);

			/* reset message */
			if (verbose > 0)
				fprintf(stderr, "Sorting %d old edits...\n", esf->nedit);
				
			/* first round all timestamps to the nearest 0.1 millisecond to avoid
				comparison errors during sorting */
			/* for (i=0;i<esf->nedit;i++)
			    {
			    esf->edit[i].time_d = 0.0001 * floor(10000.0 * esf->edit[i].time_d + 0.5);
			    } */
			
			/* now sort the edits */
			mb_mergesort((char *)esf->edit, esf->nedit, 
					sizeof(struct mb_edit_struct), mb_edit_compare);
/* for (i=0;i<esf->nedit;i++)
fprintf(stderr,"EDITS SORTED: i:%d edit: %f %d %d  use:%d\n",
i,esf->edit[i].time_d,esf->edit[i].beam,
esf->edit[i].action,esf->edit[i].use); */
			}
		    }
	    	}
		
	if (status == MB_SUCCESS
		&& output != MBP_ESF_NOWRITE)
	    	{
		/* check if esf file exists */
		fstat = stat(esffile, &file_status);
		if (fstat == 0
		    && (file_status.st_mode & S_IFMT) != S_IFDIR)
		    {
		    /* copy old edit save file to tmp file */
		    if (load == MB_YES)
	    		{
			sprintf(command, "cp %s %s.tmp\n", 
				esffile, esffile);
	    		system(command);
			}
		    }
		
		/* open the edit save file */
		if (output == MBP_ESF_WRITE)
			strcpy(fmode,"wb");
		else if (output == MBP_ESF_APPEND)
			strcpy(fmode,"ab");
		if ((esf->esffp = fopen(esf->esffile,fmode)) == NULL)
		    {
		    status = MB_FAILURE;
		    *error = MB_ERROR_OPEN_FAIL;
		    }
/*else
fprintf(stderr,"esffile %s opened with mode %s\n",esf->esffile,fmode);*/
		
		/* open the edit save stream file */
		if ((esf->essfp = fopen(esf->esstream,fmode)) == NULL)
		    {
		    status = MB_FAILURE;
		    *error = MB_ERROR_OPEN_FAIL;
		    }
/*else
fprintf(stderr,"esstream %s opened with mode %s\n",esf->esstream,fmode);*/
		}

	/* print output debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> completed\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Return value:\n");
		fprintf(stderr,"dbg2       nedit:       %d\n",esf->nedit);
		for (i=0;i<esf->nedit;i++)
			fprintf(stderr,"dbg2       edit event:  %d %.6f %5d %3d %3d\n",
				i,esf->edit[i].time_d,esf->edit[i].beam,
				esf->edit[i].action,esf->edit[i].use);
		fprintf(stderr,"dbg2       esf->esffile:  %s\n",esf->esffile);
		fprintf(stderr,"dbg2       esf->esstream: %s\n",esf->esstream);
		fprintf(stderr,"dbg2       esf->esffp:    %lu\n",(size_t)esf->esffp);
		fprintf(stderr,"dbg2       esf->essfp:    %lu\n",(size_t)esf->essfp);
		fprintf(stderr,"dbg2       error:         %d\n",*error);
		fprintf(stderr,"dbg2  Return status:\n");
		fprintf(stderr,"dbg2       status:       %d\n",status);
		}

	/* return success */
	return(status);
}

/*--------------------------------------------------------------------*/
/* 	function mb_esf_apply applies saved edits to the beamflags
	in a ping. If an output esf file is open the applied edits
	are saved to that file. */
int mb_esf_apply(int verbose, struct mb_esf_struct *esf,
		double time_d, int pingmultiplicity, int nbath, char *beamflag, 
		int *error)
{
  	char	*function_name = "mb_esf_apply";
	int	status = MB_SUCCESS;
	int	firstedit, lastedit;
	int	apply, action;
	int	beamoffset;
	char	beamflagorg;
	int	ibeam;
	int	i, j;

	/* print input debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> called\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Input arguments:\n");
		fprintf(stderr,"dbg2       verbose:          %d\n",verbose);
		fprintf(stderr,"dbg2       nedit:            %d\n",esf->nedit);
		for (i=0;i<esf->nedit;i++)
			fprintf(stderr,"dbg2       edit event: %d %.6f %5d %3d %3d\n",
				i,esf->edit[i].time_d,esf->edit[i].beam,
				esf->edit[i].action,esf->edit[i].use);
		fprintf(stderr,"dbg2       time_d:           %f\n",time_d);
		fprintf(stderr,"dbg2       pingmultiplicity: %d\n",pingmultiplicity);
		fprintf(stderr,"dbg2       nbath:            %d\n",nbath);
		for (i=0;i<nbath;i++)
			fprintf(stderr,"dbg2       beamflag:    %d %d\n",i,beamflag[i]);
		}
		
	/* if ping has the same time stamp as previous pings, pingmultiplicity will be
		> 0 and the edit beam values will be augmented by 
		MB_ESF_MULTIPLICITY_FACTOR * pingmultiplicity */
	beamoffset = MB_ESF_MULTIPLICITY_FACTOR * pingmultiplicity;

	/* find first and last edits for this ping */
	firstedit = 0;
	lastedit = firstedit - 1;
	for (j = firstedit; j < esf->nedit && time_d >= (esf->edit[j].time_d - MB_ESF_MAXTIMEDIFF); j++)
		{
		if (fabs(esf->edit[j].time_d - time_d) < MB_ESF_MAXTIMEDIFF)
		    {
		    if (lastedit < firstedit)
			firstedit = j;
		    lastedit = j;
		    }
		}
/*fprintf(stderr,"firstedit:%d lastedit:%d\n",firstedit,lastedit);*/
			
	/* apply edits */
	if (lastedit >= firstedit)
		{
		/* check for edits with bad beam numbers */
		for (j=firstedit;j<=lastedit;j++)
		    {
		    if (esf->edit[j].beam < 0 
		    	|| (esf->edit[j].beam % MB_ESF_MULTIPLICITY_FACTOR) >= nbath)
		    	esf->edit[j].use += 10000;
		    }
		    
		/* loop over all beams */
		for (i=0;i<nbath;i++)
		    {
		    /* apply beam offset for cases of multiple pings */
		    ibeam = i + beamoffset;
		    
		    /* loop over all edits for this ping */
		    apply = MB_NO;
		    beamflagorg = beamflag[i];
		    for (j=firstedit;j<=lastedit;j++)
			{
			/* apply the edits for this beam in the
			   order they were created so that the last
			   edit event is applied last - only the 
			   last event will be output to a new
			   esf file - the overridden edit events
			   may already be indicated by a use value
			   of 100 or more. */
			if (esf->edit[j].beam == ibeam
			    && esf->edit[j].use < 100)
			    {
			    /* apply edit */
			    if (esf->edit[j].action == MBP_EDIT_FLAG
				&& beamflag[i] != MB_FLAG_NULL)
				{
/*fprintf(stderr,"edit:%d beam:%d MBP_EDIT_FLAG  flag:%d ",j,i,beamflag[i]);*/
				beamflag[i] 
				    = MB_FLAG_FLAG + MB_FLAG_MANUAL;
				esf->edit[j].use++;
				apply = MB_YES;
				action = esf->edit[j].action;
/*fprintf(stderr," %d\n",beamflag[i]);*/
				}
			    else if (esf->edit[j].action == MBP_EDIT_FILTER
				&& beamflag[i] != MB_FLAG_NULL)
				{
/*fprintf(stderr,"edit:%d beam:%d MBP_EDIT_FILTER\n",j,i);*/
				beamflag[i] 
				    = MB_FLAG_FLAG + MB_FLAG_FILTER;
				esf->edit[j].use++;
				apply = MB_YES;
				action = esf->edit[j].action;
				}
			    else if (esf->edit[j].action == MBP_EDIT_UNFLAG
				&& beamflag[i] != MB_FLAG_NULL)
				{
/*fprintf(stderr,"edit:%d beam:%d MBP_EDIT_UNFLAG\n",j,i);*/
				beamflag[i] = MB_FLAG_NONE;
				esf->edit[j].use++;
				apply = MB_YES;
				action = esf->edit[j].action;
				}
			    else if (esf->edit[j].action == MBP_EDIT_ZERO)
				{
/*fprintf(stderr,"edit:%d beam:%d MBP_EDIT_ZERO\n",j,i);*/
				beamflag[i] = MB_FLAG_NULL;
				esf->edit[j].use++;
				apply = MB_YES;
				action = esf->edit[j].action;
				}
			    else
				{
/*fprintf(stderr,"edit:%d beam:%d NOT USED\n",j,i);*/
				esf->edit[j].use += 1000;
/*fprintf(stderr,"Dup Edit[%d]?: ping:%f beam:%d flag:%d action:%d\n",
j, time_d, i, beamflag[i], esf->edit[j].action);*/
				}
			    }
			}
		    if (apply == MB_YES 
		    	&& esf->essfp != NULL
			&& beamflag[i] != beamflagorg)
		    	mb_ess_save(verbose, esf, time_d, ibeam, action, error);
		    }
		}

	/* print output debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> completed\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Return value:\n");
		fprintf(stderr,"dbg2       time_d:           %f\n",time_d);
		fprintf(stderr,"dbg2       pingmultiplicity: %d\n",pingmultiplicity);
		fprintf(stderr,"dbg2       nbath:            %d\n",nbath);
		for (i=0;i<nbath;i++)
			fprintf(stderr,"dbg2       beamflag:    %d %d %d\n",i,ibeam,beamflag[i]);
		fprintf(stderr,"dbg2       error:  %d\n",*error);
		fprintf(stderr,"dbg2  Return status:\n");
		fprintf(stderr,"dbg2       status:  %d\n",status);
		}

	/* return success */
	return(status);
}


/*--------------------------------------------------------------------*/
/* 	function mb_esf_save saves one edit event to an esf file. */
int mb_esf_save(int verbose, struct mb_esf_struct *esf, 
		double time_d, int beam, int action, int *error)
{
  	char	*function_name = "mb_esf_save";
	int	status = MB_SUCCESS;

	/* print input debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> called\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Input arguments:\n");
		fprintf(stderr,"dbg2       verbose:          %d\n",verbose);
		fprintf(stderr,"dbg2       esf->nedit:       %d\n",esf->nedit);
		fprintf(stderr,"dbg2       esf->edit:        %lu\n",(size_t)esf->edit);
		fprintf(stderr,"dbg2       esf->esffp:       %lu\n",(size_t)esf->esffp);
		fprintf(stderr,"dbg2       time_d:           %f\n",time_d);
		fprintf(stderr,"dbg2       beam:             %d\n",beam);
		fprintf(stderr,"dbg2       action:           %d\n",action);
		}

	/* write out the edit */
	if (esf->esffp != NULL)
	    {		
/*fprintf(stderr,"OUTPUT EDIT: %f %d %d\n",time_d,beam,action);*/
	    if (esf->byteswapped == MB_YES)
	    	{
	   	mb_swap_double(&time_d);
	    	beam = mb_swap_int(beam);
	    	action = mb_swap_int(action);
		}
	    if (fwrite(&time_d, sizeof(double), 1, esf->esffp) != 1)
		{
		status = MB_FAILURE;
		*error = MB_ERROR_WRITE_FAIL;
		}
	    if (status == MB_SUCCESS
		&& fwrite(&beam, sizeof(int), 1, esf->esffp) != 1)
		{
		status = MB_FAILURE;
		*error = MB_ERROR_WRITE_FAIL;
		}
	    if (status == MB_SUCCESS
		&& fwrite(&action, sizeof(int), 1, esf->esffp) != 1)
		{
		status = MB_FAILURE;
		*error = MB_ERROR_WRITE_FAIL;
		}
	    }

	/* print output debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> completed\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Return value:\n");
		fprintf(stderr,"dbg2       esf->nedit:       %d\n",esf->nedit);
		fprintf(stderr,"dbg2       esf->edit:        %lu\n",(size_t)esf->edit);
		fprintf(stderr,"dbg2       esf->esffp:       %lu\n",(size_t)esf->esffp);
		fprintf(stderr,"dbg2       error:            %d\n",*error);
		fprintf(stderr,"dbg2  Return status:\n");
		fprintf(stderr,"dbg2       status:           %d\n",status);
		}

	/* return success */
	return(status);
}


/*--------------------------------------------------------------------*/
/* 	function mb_ess_save saves one edit event to an edit save stream file. */
int mb_ess_save(int verbose, struct mb_esf_struct *esf, 
		double time_d, int beam, int action, int *error)
{
  	char	*function_name = "mb_ess_save";
	int	status = MB_SUCCESS;

	/* print input debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> called\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Input arguments:\n");
		fprintf(stderr,"dbg2       verbose:          %d\n",verbose);
		fprintf(stderr,"dbg2       esf->nedit:       %d\n",esf->nedit);
		fprintf(stderr,"dbg2       esf->edit:        %lu\n",(size_t)esf->edit);
		fprintf(stderr,"dbg2       esf->essfp:       %lu\n",(size_t)esf->essfp);
		fprintf(stderr,"dbg2       time_d:           %f\n",time_d);
		fprintf(stderr,"dbg2       beam:             %d\n",beam);
		fprintf(stderr,"dbg2       action:           %d\n",action);
		}

	/* write out the edit */
	if (esf->essfp != NULL)
	    {		
/*fprintf(stderr,"OUTPUT EDIT: %f %d %d\n",time_d,beam,action);*/
	    if (esf->byteswapped == MB_YES)
	    	{
	        mb_swap_double(&time_d);
	        beam = mb_swap_int(beam);
	        action = mb_swap_int(action);
		}
	    if (fwrite(&time_d, sizeof(double), 1, esf->essfp) != 1)
		{
		status = MB_FAILURE;
		*error = MB_ERROR_WRITE_FAIL;
		}
	    if (status == MB_SUCCESS
		&& fwrite(&beam, sizeof(int), 1, esf->essfp) != 1)
		{
		status = MB_FAILURE;
		*error = MB_ERROR_WRITE_FAIL;
		}
	    if (status == MB_SUCCESS
		&& fwrite(&action, sizeof(int), 1, esf->essfp) != 1)
		{
		status = MB_FAILURE;
		*error = MB_ERROR_WRITE_FAIL;
		}
	    }

	/* print output debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> completed\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Return value:\n");
		fprintf(stderr,"dbg2       esf->nedit:       %d\n",esf->nedit);
		fprintf(stderr,"dbg2       esf->edit:        %lu\n",(size_t)esf->edit);
		fprintf(stderr,"dbg2       esf->essfp:       %lu\n",(size_t)esf->essfp);
		fprintf(stderr,"dbg2       error:            %d\n",*error);
		fprintf(stderr,"dbg2  Return status:\n");
		fprintf(stderr,"dbg2       status:           %d\n",status);
		}

	/* return success */
	return(status);
}

/*--------------------------------------------------------------------*/
/* 	function mb_esf_close deallocates memory in the esf structure. */
int mb_esf_close(int verbose, struct mb_esf_struct *esf, int *error)
{
  	char	*function_name = "mb_esf_close";
	int	status = MB_SUCCESS;

	/* print input debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> called\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Input arguments:\n");
		fprintf(stderr,"dbg2       verbose:          %d\n",verbose);
		fprintf(stderr,"dbg2       esf->nedit:       %d\n",esf->nedit);
		fprintf(stderr,"dbg2       esf->edit:        %lu\n",(size_t)esf->edit);
		fprintf(stderr,"dbg2       esf->esffp:       %lu\n",(size_t)esf->esffp);
		}

	/* deallocate the arrays */
	if (esf->nedit != 0)
		{
		if (esf->edit != NULL)
			status = mb_freed(verbose,__FILE__, __LINE__,(void **)&(esf->edit), error);
		}
	esf->nedit = 0;

	/* close the esf file */
	if (esf->esffp != NULL)
		{
		fclose(esf->esffp);
		esf->esffp = NULL;
		}

	/* close the esf stream file */
	if (esf->essfp != NULL)
		{
		fclose(esf->essfp);
		esf->essfp = NULL;
		}

	/* print output debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> completed\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Return value:\n");
		fprintf(stderr,"dbg2       esf->nedit:       %d\n",esf->nedit);
		fprintf(stderr,"dbg2       esf->edit:        %lu\n",(size_t)esf->edit);
		fprintf(stderr,"dbg2       esf->esffp:       %lu\n",(size_t)esf->esffp);
		fprintf(stderr,"dbg2       esf->essfp:       %lu\n",(size_t)esf->essfp);
		fprintf(stderr,"dbg2       error:            %d\n",*error);
		fprintf(stderr,"dbg2  Return status:\n");
		fprintf(stderr,"dbg2       status:           %d\n",status);
		}

	/* return success */
	return(status);
}

/*--------------------------------------------------------------------*/
/* The following code has been modified from code obtained from
	http://www.gnu-darwin.org/sources/4Darwin-x86/src/lib/libc/stdlib/merge.c
   on July 27, 2003 by David W. Caress.
 */

#error "Code removed because it is GPL incompatible."

int mb_mergesort(void *base, size_t nmemb,register size_t size,
	int (*cmp) (void *, void *))
{
#error "Code not GPL compatible"
}

void mb_mergesort_setup(u_char *list1, u_char *list2, size_t n, size_t size,
	int (*cmp) (void *, void *))
{
#error "Code not GPL compatible"
}

void mb_mergesort_insertionsort(u_char *a, size_t n, size_t size,
	int (*cmp)(void *, void *))
{
#error "Code not GPL compatible"
}
