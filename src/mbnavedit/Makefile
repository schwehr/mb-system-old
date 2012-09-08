#     Copyright (c) 1995-2011 by
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

all: $(BINDIR)/mbnavedit

### link the executable
$(BINDIR)/mbnavedit: mbnavedit.o \
		mbnavedit_creation.o \
		mbnavedit_callbacks.o \
		mbnavedit_util.o \
		mbnavedit_prog.o \
		$(LIBDIR)/libmbaux.a \
		$(LIBDIR)/libmbxgr.a \
		$(LIBDIR)/libmbio.a \
		$(PROJLIB) \
		$(LIBDIR)/libmr1pr.a  \
		$(LIBDIR)/libsapi.a
	$(CC) $(CFLAGS) mbnavedit.o \
		mbnavedit_creation.o \
		mbnavedit_callbacks.o \
		mbnavedit_util.o \
		mbnavedit_prog.o \
		$(LIBDIR)/libmbaux.a \
		$(LIBDIR)/libmbxgr.a \
		$(LIBDIR)/libmbio.a \
		$(PROJLIB) \
		$(LIBDIR)/libmr1pr.a  \
		$(LIBDIR)/libsapi.a \
		$(MOTIFLIBS) $(LFLAGS) \
		-o $(BINDIR)/mbnavedit

### compile the source files
mbnavedit.o: mbnavedit.c mbnavedit_creation.h mbnavedit.h \
	mbnavedit_extrawidgets.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c mbnavedit.c
mbnavedit_creation.o: mbnavedit_creation.c mbnavedit_creation.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c mbnavedit_creation.c
mbnavedit_callbacks.o: mbnavedit_callbacks.c mbnavedit.h mbnavedit_creation.h \
	mbnavedit_extrawidgets.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c mbnavedit_callbacks.c
mbnavedit_util.o: mbnavedit_util.c mbnavedit_creation.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c mbnavedit_util.c
mbnavedit_prog.o: mbnavedit_prog.c mbnavedit.h  $(INCDIR)/mb_format.h \
		$(INCDIR)/mb_io.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c mbnavedit_prog.c

clean: 
	rm -f core *.o


