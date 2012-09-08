#     Copyright (c) 1993-2011 by David W. Caress and Dale N. Chayes

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

all: $(BINDIR)/mbedit

$(BINDIR)/mbedit: mbedit.o mbedit_prog.o \
		$(LIBDIR)/libmbio.a \
		$(LIBDIR)/libmbaux.a \
		$(PROJLIB) \
		$(LIBDIR)/libsapi.a \
		$(LIBDIR)/libmr1pr.a  \
		$(LIBDIR)/libmbps.a \
		$(LIBDIR)/libmbxgr.a \
		mbedit_callbacks.o \
		mbedit_creation.o mbedit_bxutils.o
	$(CC) $(CFLAGS) mbedit.o mbedit_prog.o \
		$(LIBDIR)/libmbio.a \
		$(LIBDIR)/libmbaux.a \
		$(PROJLIB) \
		$(LIBDIR)/libsapi.a \
		$(LIBDIR)/libmr1pr.a  \
		$(LIBDIR)/libmbps.a \
		$(LIBDIR)/libmbxgr.a \
		mbedit_callbacks.o \
		mbedit_creation.o mbedit_bxutils.o \
		$(MOTIFLIBS) $(LFLAGS) -o $(BINDIR)/mbedit

mbedit.o: mbedit.c mbedit.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c mbedit.c
mbedit_creation.o: mbedit_creation.c
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c mbedit_creation.c
mbedit_bxutils.o: mbedit_bxutils.c
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c mbedit_bxutils.c
mbedit_prog.o: mbedit_prog.c mbedit.h  $(INCDIR)/mb_format.h \
		$(INCDIR)/mb_io.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c mbedit_prog.c
mbedit_callbacks.o: mbedit_callbacks.c mbedit.h  $(INCDIR)/mb_format.h \
		$(INCDIR)/mb_io.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -I$(MOTIFINCDIR) -c mbedit_callbacks.c

clean: 
	rm -f core *.o

