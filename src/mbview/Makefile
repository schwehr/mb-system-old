#     Copyright (c) 2003-2011 by
#     David W. Caress (caress@mbari.org)
#     and Dale N. Chayes (dale@ldeo.columbia.edu)

BINDIR = ../../bin
LIBDIR = ../../lib
INCDIR = ../../include

GMTLIBDIR = /sw/lib
GMTINCDIR = /sw/include
NETCDFINCDIR = /sw/include
MOTIFINCDIR = /sw/include
MOTIFLIBS = -L/sw/lib -L/usr/X11R6/lib -lXm -lXt -lX11
OPENGLLIBS = -lGLU -lGL
CC = cc
CFLAGS = -O3 -funroll-loops -fexpensive-optimizations -I/usr/X11R6/include -Wall -Wimplicit -pedantic -W -Wstrict-prototypes -Wredundant-decls  -Wimplicit-int -Wimplicit-function-declaration -Wnested-externs -DBYTESWAPPED -I/usr/include/gmt
LFLAGS = -Wl -lm -lnetcdf -lgmt -lpsl
ARCHIVE = ar rcv

### set projlib - could be version supplied with MB-System or other installation
PROJLIB  = $(LIBDIR)/libmbproj.a

all: $(INCDIR)/mbview.h $(LIBDIR)/libmbview.a $(BINDIR)/mbgrdviz $(BINDIR)/mbeditviz

### make the library
$(LIBDIR)/libmbview.a:	MB3DView.o \
		MB3DSiteList.o\
		MB3DRouteList.o\
		MB3DNavList.o\
		mbview_callbacks.o\
		mbview_process.o \
		mbview_plot.o \
		mbview_primary.o \
		mbview_secondary.o \
		mbview_pick.o \
		mbview_profile.o \
		mbview_site.o \
		mbview_route.o\
		mbview_nav.o \
		mbview_vector.o \
		mb_glwdrawa.o \
		Mb3dsdg.o \
		mb3dsoundings_callbacks.o \
		MBpedit.o \
		mbpingedit_callbacks.o
	$(ARCHIVE) $(LIBDIR)/libmbview.a \
		MB3DView.o \
		MB3DSiteList.o\
		MB3DRouteList.o\
		MB3DNavList.o\
		mbview_callbacks.o \
		mbview_process.o \
		mbview_plot.o \
		mbview_primary.o \
		mbview_secondary.o \
		mbview_pick.o \
		mbview_profile.o \
		mbview_site.o \
		mbview_route.o\
		mbview_nav.o \
		mbview_vector.o \
		mb_glwdrawa.o \
		Mb3dsdg.o \
		mb3dsoundings_callbacks.o \
		MBpedit.o \
		mbpingedit_callbacks.o
	ranlib $(LIBDIR)/libmbview.a

### link the executables
$(BINDIR)/mbgrdviz: mbgrdviz_main.o \
		mbgrdviz_bxutils.o \
		mbgrdviz_callbacks.o \
		mbgrdviz_creation.o \
		$(LIBDIR)/libmbview.a \
		$(LIBDIR)/libmbio.a \
		$(LIBDIR)/libmbaux.a \
		$(PROJLIB) \
		$(LIBDIR)/libsapi.a \
		$(LIBDIR)/libmr1pr.a  \
		$(LIBDIR)/libmbps.a \
		$(LIBDIR)/libmbxgr.a
	$(CC) $(CFLAGS) mbgrdviz_main.o \
		mbgrdviz_bxutils.o \
		mbgrdviz_callbacks.o \
		mbgrdviz_creation.o \
		$(LIBDIR)/libmbview.a \
		$(LIBDIR)/libmbio.a \
		$(LIBDIR)/libmbaux.a \
		$(PROJLIB) \
		$(LIBDIR)/libsapi.a \
		$(LIBDIR)/libmr1pr.a  \
		$(LIBDIR)/libmbxgr.a \
		$(OPENGLLIBS) $(MOTIFLIBS) $(LFLAGS) -o $(BINDIR)/mbgrdviz
$(BINDIR)/mbeditviz: mbeditviz_main.o \
		mbeditviz_bxutils.o \
		mbeditviz_callbacks.o \
		mbeditviz_prog.o \
		mbeditviz_creation.o \
		$(LIBDIR)/libmbview.a \
		$(LIBDIR)/libmbio.a \
		$(LIBDIR)/libmbaux.a \
		$(PROJLIB) \
		$(LIBDIR)/libsapi.a \
		$(LIBDIR)/libmr1pr.a  \
		$(LIBDIR)/libmbps.a \
		$(LIBDIR)/libmbxgr.a
	$(CC) $(CFLAGS) mbeditviz_main.o \
		mbeditviz_bxutils.o \
		mbeditviz_callbacks.o \
		mbeditviz_prog.o \
		mbeditviz_creation.o \
		$(LIBDIR)/libmbview.a \
		$(LIBDIR)/libmbio.a \
		$(LIBDIR)/libmbaux.a \
		$(PROJLIB) \
		$(LIBDIR)/libsapi.a \
		$(LIBDIR)/libmr1pr.a  \
		$(LIBDIR)/libmbxgr.a \
		$(OPENGLLIBS) $(MOTIFLIBS) $(LFLAGS) -o $(BINDIR)/mbeditviz

### compile the source files
MB3DView.o: MB3DView.c MB3DView.h mbview.h mbviewprivate.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c MB3DView.c
MB3DSiteList.o: MB3DSiteList.c MB3DSiteList.h mbview.h mbviewprivate.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c MB3DSiteList.c
MB3DRouteList.o: MB3DRouteList.c MB3DRouteList.h mbview.h mbviewprivate.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c MB3DRouteList.c
MB3DNavList.o: MB3DNavList.c MB3DNavList.h mbview.h mbviewprivate.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c MB3DNavList.c
mbview_callbacks.o: mbview_callbacks.c mbview.h mbviewprivate.h
	$(CC) $(CFLAGS) -DMBVIEW_LIBRARY -I$(INCDIR) -I$(MOTIFINCDIR) -c mbview_callbacks.c
mbview_process.o: mbview_process.c mbview.h mbviewprivate.h
	$(CC) $(CFLAGS) -DMBVIEW_LIBRARY -I$(INCDIR) -I$(MOTIFINCDIR) -c mbview_process.c
mbview_plot.o: mbview_plot.c mbview.h mbviewprivate.h
	$(CC) $(CFLAGS) -DMBVIEW_LIBRARY -I$(INCDIR) -I$(MOTIFINCDIR) -c mbview_plot.c
mbview_primary.o: mbview_primary.c mbview.h mbviewprivate.h
	$(CC) $(CFLAGS) -DMBVIEW_LIBRARY -I$(INCDIR) -I$(MOTIFINCDIR) -c mbview_primary.c
mbview_secondary.o: mbview_secondary.c mbview.h mbviewprivate.h
	$(CC) $(CFLAGS) -DMBVIEW_LIBRARY -I$(INCDIR) -I$(MOTIFINCDIR) -c mbview_secondary.c
mbview_pick.o: mbview_pick.c mbview.h mbviewprivate.h
	$(CC) $(CFLAGS) -DMBVIEW_LIBRARY -I$(INCDIR) -I$(MOTIFINCDIR) -c mbview_pick.c
mbview_profile.o: mbview_profile.c mbview.h mbviewprivate.h
	$(CC) $(CFLAGS) -DMBVIEW_LIBRARY -I$(INCDIR) -I$(MOTIFINCDIR) -c mbview_profile.c
mbview_site.o: mbview_site.c mbview.h mbviewprivate.h
	$(CC) $(CFLAGS) -DMBVIEW_LIBRARY -I$(INCDIR) -I$(MOTIFINCDIR) -c mbview_site.c
mbview_route.o: mbview_route.c mbview.h mbviewprivate.h
	$(CC) $(CFLAGS) -DMBVIEW_LIBRARY -I$(INCDIR) -I$(MOTIFINCDIR) -c mbview_route.c
mbview_nav.o: mbview_nav.c mbview.h mbviewprivate.h
	$(CC) $(CFLAGS) -DMBVIEW_LIBRARY -I$(INCDIR) -I$(MOTIFINCDIR) -c mbview_nav.c
mbview_vector.o: mbview_vector.c mbview.h mbviewprivate.h
	$(CC) $(CFLAGS) -DMBVIEW_LIBRARY -I$(INCDIR) -I$(MOTIFINCDIR) -c mbview_vector.c
mb_glwdrawa.o: mb_glwdrawa.c mb_glwdrawa.h mb_glwdrawap.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c mb_glwdrawa.c
mbgrdviz_bxutils.o: mbgrdviz_bxutils.c
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c mbgrdviz_bxutils.c
mbgrdviz_creation.o: mbgrdviz_creation.c mbgrdviz_creation.h 
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c mbgrdviz_creation.c
mbgrdviz_main.o: mbgrdviz_main.c mbview.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c mbgrdviz_main.c
mbgrdviz_callbacks.o: mbgrdviz_callbacks.c mbview.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -I$(NETCDFINCDIR) -I$(GMTINCDIR) -c mbgrdviz_callbacks.c
Mb3dsdg.o: Mb3dsdg.c Mb3dsdg.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -I$(NETCDFINCDIR) -I$(GMTINCDIR) -c Mb3dsdg.c
mb3dsoundings_callbacks.o: mb3dsoundings_callbacks.c Mb3dsdg.h mb3dsoundingsprivate.h 
	$(CC) $(CFLAGS) -DMBVIEW_LIBRARY -I$(INCDIR) -I$(MOTIFINCDIR) -I$(NETCDFINCDIR) -I$(GMTINCDIR) -c mb3dsoundings_callbacks.c
MBpedit.o: MBpedit.c MBpedit.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -I$(NETCDFINCDIR) -I$(GMTINCDIR) -c MBpedit.c
mbpingedit_callbacks.o: mbpingedit_callbacks.c Mb3dsdg.h mbpingeditprivate.h 
	$(CC) $(CFLAGS) -DMBVIEW_LIBRARY -I$(INCDIR) -I$(MOTIFINCDIR) -I$(NETCDFINCDIR) -I$(GMTINCDIR) -c mbpingedit_callbacks.c
mbeditviz_bxutils.o: mbeditviz_bxutils.c
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c mbeditviz_bxutils.c
mbeditviz_creation.o: mbeditviz_creation.c mbeditviz_creation.h 
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c mbeditviz_creation.c
mbeditviz_main.o: mbeditviz_main.c mbeditviz.h $(INCDIR)/mbview.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c mbeditviz_main.c
mbeditviz_callbacks.o: mbeditviz_callbacks.c mbeditviz.h $(INCDIR)/mbview.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -I$(NETCDFINCDIR) -I$(GMTINCDIR) -c mbeditviz_callbacks.c
mbeditviz_prog.o: mbeditviz_prog.c mbeditviz.h $(INCDIR)/mbview.h
	$(CC) $(CFLAGS)  -DMBEDITVIZ_DECLARE_GLOBALS -I$(INCDIR) -I$(MOTIFINCDIR) -I$(NETCDFINCDIR) -I$(GMTINCDIR) -c mbeditviz_prog.c

## copy the include files to the include file directory
$(INCDIR)/mbview.h:	mbview.h
	cp mbview.h $(INCDIR)/mbview.h
	chmod 664 $(INCDIR)/mbview.h

### copy the man page to the man page directory

clean: 
	rm -f *.o

