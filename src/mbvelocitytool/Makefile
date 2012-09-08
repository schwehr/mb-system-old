#     Copyright (c) 1993-2011 by
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

PROJLIB  = $(LIBDIR)/libmbproj.a

all: $(BINDIR)/mbvelocitytool 

### link the executable
$(BINDIR)/mbvelocitytool: mbvelocity.o \
		mbvelocity_callbacks.o \
		mbvelocity_creation.o \
		mbvelocity_bxutils.o \
		mbvelocity_prog.o \
		$(LIBDIR)/libmbio.a \
		$(PROJLIB) \
		$(LIBDIR)/libmr1pr.a \
		$(LIBDIR)/libsapi.a \
		$(LIBDIR)/libmbaux.a \
		$(LIBDIR)/libmbxgr.a
	$(CC) $(CFLAGS) mbvelocity.o \
		mbvelocity_callbacks.o \
		mbvelocity_creation.o \
		mbvelocity_bxutils.o \
		mbvelocity_prog.o \
		$(LIBDIR)/libmbio.a \
		$(PROJLIB) \
		$(LIBDIR)/libmr1pr.a \
		$(LIBDIR)/libsapi.a \
		$(LIBDIR)/libmbaux.a \
		$(LIBDIR)/libmbxgr.a \
		$(MOTIFLIBS) $(LFLAGS) \
		-o $(BINDIR)/mbvelocitytool

### compile the source files
mbvelocity.o: mbvelocity.c mbvelocity.h mbvelocity_creation.h 
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c mbvelocity.c
mbvelocity_callbacks.o: mbvelocity_callbacks.c mbvelocity.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c mbvelocity_callbacks.c
mbvelocity_creation.o: mbvelocity_creation.c mbvelocity.h mbvelocity_creation.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c mbvelocity_creation.c
mbvelocity_bxutils.o: mbvelocity_bxutils.c
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MOTIFINCDIR) -c mbvelocity_bxutils.c
mbvelocity_prog.o: mbvelocity_prog.c mbvelocity.h $(INCDIR)/mb_format.h \
		$(INCDIR)/mb_io.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) $(CFLAGS) -I$(INCDIR) -c mbvelocity_prog.c

clean: 
	rm -f core *.o

