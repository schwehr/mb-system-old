#     Copyright (c) 2000-2011 by 
#     David W. Caress (caress@mbari.org)
#     and Dale N. Chayes (dale@ldeo.columbia.edu)

BINDIR = ../../bin
LIBDIR = ../../lib
INCDIR = ../../include

MOTIFINCDIR = /sw/include
MOTIFLIBS = -L/sw/lib -L/usr/X11R6/lib -lXm -lXt -lX11
CC = cc
CFLAGS = -O3 -funroll-loops -fexpensive-optimizations -I/usr/X11R6/include -Wall -Wimplicit -pedantic -W -Wstrict-prototypes -Wredundant-decls  -Wimplicit-int -Wimplicit-function-declaration -Wnested-externs -DDARWIN -DBYTESWAPPED
LFLAGS = -Wl -lm -lnetcdf

### set projlib - could be version supplied with MB-System or other installation
PROJLIB  = $(LIBDIR)/libmbproj.a

all: $(BINDIR)/mbnavadjust


$(BINDIR)/mbnavadjust: mbnavadjust.o \
		mbnavadjust_creation.o \
		mbnavadjust_callbacks.o \
		mbnavadjust_util.o \
		mbnavadjust_prog.o \
		$(LIBDIR)/libmbio.a \
		$(PROJLIB) \
		$(LIBDIR)/libmr1pr.a  \
		$(LIBDIR)/libsapi.a \
		$(LIBDIR)/libmbaux.a \
		$(LIBDIR)/libmbps.a \
		$(LIBDIR)/libmbxgr.a
	$(CC) $(CFLAGS) mbnavadjust.o \
		mbnavadjust_creation.o \
		mbnavadjust_callbacks.o \
		mbnavadjust_util.o \
		mbnavadjust_prog.o \
		$(LIBDIR)/libmbio.a \
		$(PROJLIB) \
		$(LIBDIR)/libmr1pr.a  \
		$(LIBDIR)/libsapi.a \
		$(LIBDIR)/libmbaux.a \
		$(LIBDIR)/libmbps.a \
		$(LIBDIR)/libmbxgr.a \
		$(MOTIFLIBS) $(LFLAGS) \
		-o $(BINDIR)/mbnavadjust

mbnavadjust.o: mbnavadjust.c mbnavadjust_creation.h mbnavadjust.h \
	mbnavadjust_extrawidgets.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c mbnavadjust.c
mbnavadjust_creation.o: mbnavadjust_creation.c mbnavadjust_creation.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c mbnavadjust_creation.c
mbnavadjust_callbacks.o: mbnavadjust_callbacks.c mbnavadjust.h mbnavadjust_creation.h \
	mbnavadjust_extrawidgets.h $(INCDIR)/mb_xgraphics.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c mbnavadjust_callbacks.c
mbnavadjust_util.o: mbnavadjust_util.c mbnavadjust_creation.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c mbnavadjust_util.c
mbnavadjust_prog.o: mbnavadjust_prog.c mbnavadjust.h  $(INCDIR)/mb_format.h \
		$(INCDIR)/mb_io.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h $(INCDIR)/mb_aux.h $(INCDIR)/mb_xgraphics.h
	$(CC) $(CFLAGS) -I$(INCDIR) -c mbnavadjust_prog.c

clean: 
	rm -f core *.o


