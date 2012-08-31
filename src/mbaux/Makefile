#     Copyright (c) 2000-2009 by David W. Caress and Dale N. Chayes

BINDIR = ../../bin
LIBDIR = ../../lib
INCDIR = ../../include

GMTINCDIR = /sw/include
NETCDFINCDIR = /sw/include
# 
# Compilers 
CC = cc
#
# Compile and load flags:
CFLAGS = -O3 -funroll-loops -fexpensive-optimizations -I/usr/X11R6/include -Wall -Wimplicit -pedantic -W -Wstrict-prototypes -Wredundant-decls  -Wimplicit-int -Wimplicit-function-declaration -Wnested-externs -DDARWIN -DBYTESWAPPED -I/usr/include/gmt
ARCHIVE = ar rcv

all:	$(LIBDIR)/libmbaux.a \
	$(LIBDIR)/libmbps.a \
	$(LIBDIR)/libmbxgr.a \
	$(INCDIR)/mb_aux.h \
	$(INCDIR)/mb_xgraphics.h

clean:
	rm -f *.o

### put together the libraries
$(LIBDIR)/libmbaux.a:	\
		mb_spline.o \
		mb_zgrid.o \
		mb_surface.o \
		mb_cheb.o \
		mb_delaun.o \
		mb_track.o \
		mb_truecont.o \
		mb_readgrd.o
	$(ARCHIVE) $(LIBDIR)/libmbaux.a \
		mb_spline.o \
		mb_zgrid.o \
		mb_surface.o \
		mb_cheb.o \
		mb_delaun.o \
		mb_track.o \
		mb_truecont.o \
		mb_readgrd.o
	ranlib $(LIBDIR)/libmbaux.a
$(LIBDIR)/libmbps.a:	\
		mb_pslibface.o
	$(ARCHIVE) $(LIBDIR)/libmbps.a \
		mb_pslibface.o
	ranlib $(LIBDIR)/libmbps.a
$(LIBDIR)/libmbxgr.a:	\
		mb_xgraphics.o
	$(ARCHIVE) $(LIBDIR)/libmbxgr.a \
		mb_xgraphics.o
	ranlib $(LIBDIR)/libmbxgr.a

### compile the source files
mb_spline.o:	mb_spline.c $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h $(INCDIR)/mb_aux.h
	$(CC) -c $(CFLAGS) mb_spline.c
mb_zgrid.o:	mb_zgrid.c $(INCDIR)/mb_define.h $(INCDIR)/mb_aux.h
	$(CC) -c $(CFLAGS) mb_zgrid.c
mb_surface.o:	mb_surface.c $(INCDIR)/mb_aux.h
	$(CC) -c $(CFLAGS) mb_surface.c
mb_cheb.o:	mb_cheb.c $(INCDIR)/mb_status.h $(INCDIR)/mb_aux.h
	$(CC) -c $(CFLAGS) mb_cheb.c
mb_delaun.o:	mb_delaun.c $(INCDIR)/mb_status.h $(INCDIR)/mb_aux.h
	$(CC) -c $(CFLAGS) mb_delaun.c
mb_pslibface.o:	mb_pslibface.c  $(INCDIR)/mb_status.h  $(INCDIR)/mb_define.h $(INCDIR)/mb_aux.h
	$(CC) -c $(CFLAGS) -I$(GMTINCDIR) -I$(NETCDFINCDIR) mb_pslibface.c
mb_track.o:	mb_track.c $(INCDIR)/mb_status.h $(INCDIR)/mb_aux.h
	$(CC) -c $(CFLAGS) mb_track.c
mb_truecont.o:	mb_truecont.c $(INCDIR)/mb_status.h $(INCDIR)/mb_aux.h
	$(CC) -c $(CFLAGS) mb_truecont.c
mb_readgrd.o:	mb_readgrd.c $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h $(INCDIR)/mb_aux.h
	$(CC) -c $(CFLAGS) -I$(GMTINCDIR) -I$(NETCDFINCDIR) mb_readgrd.c
mb_xgraphics.o:	mb_xgraphics.c $(INCDIR)/mb_status.h $(INCDIR)/mb_xgraphics.h
	$(CC) -c $(CFLAGS) mb_xgraphics.c

### copy the include files to the include file directory
$(INCDIR)/mb_aux.h:	mb_aux.h
	cp mb_aux.h $(INCDIR)/mb_aux.h
	chmod 664 $(INCDIR)/mb_aux.h
$(INCDIR)/mb_xgraphics.h:	mb_xgraphics.h
	cp mb_xgraphics.h $(INCDIR)/mb_xgraphics.h
	chmod 664 $(INCDIR)/mb_xgraphics.h
