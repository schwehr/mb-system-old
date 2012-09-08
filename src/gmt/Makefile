#     Copyright (c) 1993-2009  David W. Caress and Dale N. Chayes

BINDIR = ../../bin
LIBDIR = ../../lib
INCDIR = ../../include

GMTLIBDIR = /sw/lib
GMTINCDIR = /sw/include
NETCDFINCDIR = /sw/include
CC = cc
#
# Compile and load flags:
CFLAGS = -O3 -funroll-loops -fexpensive-optimizations -I/usr/X11R6/include -Wall -Wimplicit -pedantic -W -Wstrict-prototypes -Wredundant-decls  -Wimplicit-int -Wimplicit-function-declaration -Wnested-externs -DDARWIN -DBYTESWAPPED -I/usr/include/gmt
LFLAGS = -Wl -lm -lnetcdf

### set projlib - could be version supplied with MB-System or other installation
PROJLIB  = $(LIBDIR)/libmbproj.a

### make all makes the MB-system macros and man pages
all:	$(BINDIR)/mbcontour \
	$(BINDIR)/mbswath \
	$(BINDIR)/mbgrdtiff 

### make clean removes the object files
clean:
	rm -f *.o

### link or copy the executables
$(BINDIR)/mbcontour: mbcontour.o \
		$(LIBDIR)/libmbio.a  \
		$(PROJLIB) \
		$(LIBDIR)/libsapi.a  \
		$(LIBDIR)/libmr1pr.a  \
		$(LIBDIR)/libmbaux.a \
		$(LIBDIR)/libmbps.a
	$(CC) $(CFLAGS) mbcontour.o \
		$(LIBDIR)/libmbio.a \
		$(PROJLIB) \
		$(LIBDIR)/libsapi.a \
		$(LIBDIR)/libmr1pr.a  \
		$(LIBDIR)/libmbaux.a \
		$(LIBDIR)/libmbps.a \
		-lgmt -lpsl -lgmtps \
		$(LFLAGS) -o $(BINDIR)/mbcontour
$(BINDIR)/mbswath: mbswath.o \
		$(LIBDIR)/libmbio.a  \
		$(LIBDIR)/libmbaux.a \
		$(PROJLIB) \
		$(LIBDIR)/libsapi.a \
		$(LIBDIR)/libmr1pr.a
	$(CC) $(CFLAGS) mbswath.o \
		$(LIBDIR)/libmbio.a  \
		$(LIBDIR)/libmbaux.a \
		$(PROJLIB) \
		$(LIBDIR)/libsapi.a \
		$(LIBDIR)/libmr1pr.a  \
		-lgmt -lpsl -lgmtps \
		$(LFLAGS) -o $(BINDIR)/mbswath
$(BINDIR)/mbgrdtiff: mbgrdtiff.o \
		$(LIBDIR)/libmbio.a 
	$(CC) $(CFLAGS) mbgrdtiff.o \
		$(LIBDIR)/libmbio.a \
		-lgmt -lpsl -lgmtps \
		$(LFLAGS) -o $(BINDIR)/mbgrdtiff

### compile the source files
mbcontour.o:	mbcontour.c $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h $(INCDIR)/mb_aux.h
	$(CC) -c $(CFLAGS) -I$(GMTINCDIR) mbcontour.c
mbswath.o:	mbswath.c $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h $(INCDIR)/mb_format.h
	$(CC) -c $(CFLAGS) -I$(GMTINCDIR) -I$(NETCDFINCDIR) mbswath.c
mbgrdtiff.o:	mbgrdtiff.c $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h $(INCDIR)/mb_format.h
	$(CC) -c $(CFLAGS) -I$(GMTINCDIR) -I$(NETCDFINCDIR) mbgrdtiff.c

