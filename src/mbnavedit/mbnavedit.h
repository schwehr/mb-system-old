/*--------------------------------------------------------------------
 *    The MB-system:	mbnavedit.h	6/24/95
 *    $Id$
 *
 *    Copyright (c) 1995-2012 by
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
 * MBNAVEDIT is an interactive navigation editor for swath sonar data.
 * It can work with any data format supported by the MBIO library.
 * This include file contains global control parameters shared with
 * the Motif interface code.
 *
 */

/*--------------------------------------------------------------------*/

#ifndef MB_YES
#include "mb_status.h"
#endif

#ifdef MBNAVEDIT_DECLARE_GLOBALS
#define EXTERNAL
#else
#define EXTERNAL extern
#endif

/* mbnavedit global control parameters */
EXTERNAL int	output_mode;
EXTERNAL int	run_mbprocess;
EXTERNAL int	gui_mode;
EXTERNAL int	data_show_max;
EXTERNAL int	data_show_size;
EXTERNAL int	data_step_max;
EXTERNAL int	data_step_size;
EXTERNAL int	mode_pick;
EXTERNAL int	mode_set_interval;
EXTERNAL int	plot_tint;
EXTERNAL int	plot_tint_org;
EXTERNAL int	plot_lon;
EXTERNAL int	plot_lon_org;
EXTERNAL int	plot_lon_dr;
EXTERNAL int	plot_lat;
EXTERNAL int	plot_lat_org;
EXTERNAL int	plot_lat_dr;
EXTERNAL int	plot_speed;
EXTERNAL int	plot_speed_org;
EXTERNAL int	plot_smg;
EXTERNAL int	plot_heading;
EXTERNAL int	plot_heading_org;
EXTERNAL int	plot_cmg;
EXTERNAL int	plot_draft;
EXTERNAL int	plot_draft_org;
EXTERNAL int	plot_draft_dr;
EXTERNAL int	plot_roll;
EXTERNAL int	plot_pitch;
EXTERNAL int	plot_heave;
EXTERNAL int	mean_time_window;
EXTERNAL int	drift_lon;
EXTERNAL int	drift_lat;
EXTERNAL int	timestamp_problem;
EXTERNAL int	use_ping_data;
EXTERNAL int	strip_comments;
EXTERNAL int	format;
EXTERNAL char	ifile[MB_PATH_MAXLINE];
EXTERNAL char	nfile[MB_PATH_MAXLINE];
EXTERNAL int	nfile_defined;
EXTERNAL int	model_mode;
EXTERNAL double	weight_speed;
EXTERNAL double	weight_acceleration;
EXTERNAL int	scrollcount;
EXTERNAL double	offset_lon;
EXTERNAL double	offset_lat;
EXTERNAL double	offset_lon_applied;
EXTERNAL double	offset_lat_applied;

/* mbnavedit plot size parameters */
EXTERNAL int	plot_width;
EXTERNAL int	plot_height;
EXTERNAL int	number_plots;
EXTERNAL int	window_width;
EXTERNAL int	window_height;

/* Mode value defines */
#define	PICK_MODE_PICK		0
#define	PICK_MODE_SELECT	1
#define	PICK_MODE_DESELECT	2
#define	PICK_MODE_SELECTALL	3
#define	PICK_MODE_DESELECTALL	4
#define	OUTPUT_MODE_OUTPUT	0
#define	OUTPUT_MODE_BROWSE	1
#define	PLOT_TINT	0
#define	PLOT_LONGITUDE	1
#define	PLOT_LATITUDE	2
#define	PLOT_SPEED	3
#define	PLOT_HEADING	4
#define	PLOT_DRAFT	5
#define	PLOT_ROLL	6
#define	PLOT_PITCH	7
#define	PLOT_HEAVE	8
#define	MODEL_MODE_OFF		0
#define	MODEL_MODE_MEAN		1
#define	MODEL_MODE_DR		2
#define	MODEL_MODE_INVERT	3
#define	NUM_FILES_MAX		1000

/*--------------------------------------------------------------------*/

/* function prototypes */
void do_mbnavedit_init(int argc, char **argv);
void  do_parse_datalist( char *file, int form);
void do_editlistselection( Widget w, XtPointer client_data, XtPointer call_data);
void do_filelist_remove( Widget w, XtPointer client_data, XtPointer call_data);
void do_load_specific_file(int i_file);
void do_set_controls();
void do_nextbuffer( Widget w, XtPointer client_data, XtPointer call_data);
void do_done( Widget w, XtPointer client_data, XtPointer call_data);
void do_start( Widget w, XtPointer client_data, XtPointer call_data);
void do_end( Widget w, XtPointer client_data, XtPointer call_data);
void do_forward( Widget w, XtPointer client_data, XtPointer call_data);
void do_reverse( Widget w, XtPointer client_data, XtPointer call_data);
void do_timespan( Widget w, XtPointer client_data, XtPointer call_data);
void do_timestep( Widget w, XtPointer client_data, XtPointer call_data);
void do_expose( Widget w, XtPointer client_data, XtPointer call_data);
void do_event( Widget w, XtPointer client_data, XtPointer call_data);
void do_resize( Widget w, XtPointer client_data, XEvent *event, Boolean *unused);
void do_toggle_time( Widget w, XtPointer client_data, XtPointer call_data);
void do_toggle_lon( Widget w, XtPointer client_data, XtPointer call_data);
void do_toggle_lat( Widget w, XtPointer client_data, XtPointer call_data);
void do_toggle_heading( Widget w, XtPointer client_data, XtPointer call_data);
void do_toggle_speed( Widget w, XtPointer client_data, XtPointer call_data);
void do_toggle_sonardepth( Widget w, XtPointer client_data, XtPointer call_data);
void do_toggle_org_time( Widget w, XtPointer client_data, XtPointer call_data);
void do_toggle_org_lon( Widget w, XtPointer client_data, XtPointer call_data);
void do_toggle_org_lat( Widget w, XtPointer client_data, XtPointer call_data);
void do_toggle_org_speed( Widget w, XtPointer client_data, XtPointer call_data);
void do_toggle_dr_lat( Widget w, XtPointer client_data, XtPointer call_data);
void do_toggle_dr_lon( Widget w, XtPointer client_data, XtPointer call_data);
void do_flag( Widget w, XtPointer client_data, XtPointer call_data);
void do_unflag( Widget w, XtPointer client_data, XtPointer call_data);
void do_modeling_apply( Widget w, XtPointer client_data, XtPointer call_data);
void do_model_mode( Widget w, XtPointer client_data, XtPointer call_data);
void do_timeinterpolation_apply( Widget w, XtPointer client_data, XtPointer call_data);
void do_deletebadtimetag_apply( Widget w, XtPointer client_data, XtPointer call_data);
void do_meantimewindow( Widget w, XtPointer client_data, XtPointer call_data);
void do_driftlon( Widget w, XtPointer client_data, XtPointer call_data);
void do_driftlat( Widget w, XtPointer client_data, XtPointer call_data);
void do_offset_apply( Widget w, XtPointer client_data, XtPointer call_data);
void do_toggle_show_smg( Widget w, XtPointer client_data, XtPointer call_data);
void do_toggle_org_heading( Widget w, XtPointer client_data, XtPointer call_data);
void do_toggle_org_sonardepth( Widget w, XtPointer client_data, XtPointer call_data);
void do_toggle_show_cmg( Widget w, XtPointer client_data, XtPointer call_data);
void do_button_use_dr( Widget w, XtPointer client_data, XtPointer call_data);
void do_button_use_smg( Widget w, XtPointer client_data, XtPointer call_data);
void do_button_use_cmg( Widget w, XtPointer client_data, XtPointer call_data);
void do_toggle_output_on( Widget w, XtPointer client_data, XtPointer call_data);
void do_toggle_output_off( Widget w, XtPointer client_data, XtPointer call_data);
void do_fileselection_cancel( Widget w, XtPointer client_data, XtPointer call_data);
void do_filebutton_on();
void do_filebutton_off();
void do_fileselection_ok( Widget w, XtPointer client_data, XtPointer call_data);
void do_checkuseprevious();
void do_useprevious_yes( Widget w, XtPointer client_data, XtPointer call_data);
void do_useprevious_no( Widget w, XtPointer client_data, XtPointer call_data);
void do_load(int useprevious);
void do_fileselection_filter( Widget w, XtPointer client_data, XtPointer call_data);
void do_fileselection_list( Widget w, XtPointer client_data, XtPointer call_data);
void do_fileselection_nomatch( Widget w, XtPointer client_data, XtPointer call_data);
void do_toggle_pick( Widget w, XtPointer client_data, XtPointer call_data);
void do_toggle_select( Widget w, XtPointer client_data, XtPointer call_data);
void do_toggle_deselect( Widget w, XtPointer client_data, XtPointer call_data);
void do_toggle_selectall( Widget w, XtPointer client_data, XtPointer call_data);
void do_toggle_deselectall( Widget w, XtPointer client_data, XtPointer call_data);
void do_quit( Widget w, XtPointer client_data, XtPointer call_data);
void do_interpolation( Widget w, XtPointer client_data, XtPointer call_data);
void do_interpolationrepeats( Widget w, XtPointer client_data, XtPointer call_data);
void do_scroll( Widget w, XtPointer client_data, XtPointer call_data);
void do_revert( Widget w, XtPointer client_data, XtPointer call_data);
void do_showall( Widget w, XtPointer client_data, XtPointer call_data);
void do_set_interval( Widget w, XtPointer client_data, XtPointer call_data);
int do_unset_interval();
void do_toggle_vru( Widget w, XtPointer client_data, XtPointer call_data);
void mbnavedit_bell(int length);
void mbnavedit_get_position(int *win_x, int *win_y, unsigned int *mask_return);
void mbnavedit_pickcursor();
void mbnavedit_selectcursor();
void mbnavedit_deselectcursor();
void mbnavedit_selectallcursor();
void mbnavedit_deselectallcursor();
void mbnavedit_setintervalcursor();
int do_wait_until_viewed(XtAppContext app);
int do_mbnavedit_settimer();
int do_mbnavedit_workfunction(XtPointer client_data);
int do_message_on(char *message);
int do_message_off();
int do_error_dialog(char *s1, char *s2, char *s3);
void set_label_string(Widget w, String str);
void set_label_multiline_string(Widget w, String str);
void get_text_string(Widget w, String str);

int mbnavedit_init_globals();
int mbnavedit_init(int argc, char **argv, int *startup_file);
int mbnavedit_set_graphics(void *xgid, int ncol, unsigned int *pixels);
int mbnavedit_action_open(int useprevious);
int mbnavedit_open_file(int useprevious);
int mbnavedit_close_file();
int mbnavedit_dump_data(int hold);
int mbnavedit_load_data();
int mbnavedit_clear_screen();
int mbnavedit_action_next_buffer(int *quit);
int mbnavedit_action_offset();
int mbnavedit_action_close();
int mbnavedit_action_done(int *quit);
int mbnavedit_action_quit();
int mbnavedit_action_step(int step);
int mbnavedit_action_start();
int mbnavedit_action_end();
int mbnavedit_action_mouse_pick(int xx, int yy);
int mbnavedit_action_mouse_select(int xx, int yy);
int mbnavedit_action_mouse_deselect(int xx, int yy);
int mbnavedit_action_mouse_selectall(int xx, int yy);
int mbnavedit_action_mouse_deselectall(int xx, int yy);
int mbnavedit_action_deselect_all(int type);
int mbnavedit_action_set_interval(int xx, int yy, int which);
int mbnavedit_action_use_dr();
int mbnavedit_action_use_smg();
int mbnavedit_action_use_cmg();
int mbnavedit_action_interpolate();
int mbnavedit_action_interpolaterepeats();
int mbnavedit_action_revert();
int mbnavedit_action_flag();
int mbnavedit_action_unflag();
int mbnavedit_action_fixtime();
int mbnavedit_action_deletebadtime();
int mbnavedit_action_showall();
int mbnavedit_get_smgcmg(int i);
int mbnavedit_get_model();
int mbnavedit_get_gaussianmean();
int mbnavedit_get_dr();
int mbnavedit_get_inversion();
int mbnavedit_plot_all();
int mbnavedit_plot_tint(int iplot);
int mbnavedit_plot_lon(int iplot);
int mbnavedit_plot_lat(int iplot);
int mbnavedit_plot_speed(int iplot);
int mbnavedit_plot_heading(int iplot);
int mbnavedit_plot_draft(int iplot);
int mbnavedit_plot_roll(int iplot);
int mbnavedit_plot_pitch(int iplot);
int mbnavedit_plot_heave(int iplot);
int mbnavedit_plot_tint_value(int iplot, int iping);
int mbnavedit_plot_lon_value(int iplot, int iping);
int mbnavedit_plot_lat_value(int iplot, int iping);
int mbnavedit_plot_speed_value(int iplot, int iping);
int mbnavedit_plot_heading_value(int iplot, int iping);
int mbnavedit_plot_draft_value(int iplot, int iping);

XtPointer BX_CONVERT(Widget, char *, char *, int, Boolean *);

/*--------------------------------------------------------------------*/

