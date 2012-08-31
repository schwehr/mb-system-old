#     Copyright (c) 2009-2011 by 
#     David W. Caress (caress@mbari.org)
#     and Dale N. Chayes (dale@ldeo.columbia.edu)
BINDIR = ../../bin
LIBDIR = ../../lib
INCDIR = ../../include

OTPSDIR = /usr/local/OTPSnc
CC = cc
CFLAGS = -O3 -funroll-loops -fexpensive-optimizations -I/usr/X11R6/include -Wall -Wimplicit -pedantic -W -Wstrict-prototypes -Wredundant-decls  -Wimplicit-int -Wimplicit-function-declaration -Wnested-externs -DBYTESWAPPED
LFLAGS = -Wl -lm -lnetcdf

### set projlib - could be version supplied with MB-System or other installation
PROJLIB  = $(LIBDIR)/libmbproj.a

all:	$(BINDIR)/mbotps 

clean:
	rm -f *.o

$(BINDIR)/mbotps: mbotps.o \
		$(LIBDIR)/libmbio.a  \
		$(LIBDIR)/libmbaux.a  \
		$(PROJLIB) \
		$(LIBDIR)/libsapi.a  \
		$(LIBDIR)/libmr1pr.a
	$(CC) $(CFLAGS) mbotps.o \
		$(LIBDIR)/libmbio.a \
		$(LIBDIR)/libmbaux.a \
		$(PROJLIB) \
		$(LIBDIR)/libsapi.a \
		$(LIBDIR)/libmr1pr.a  \
		$(LFLAGS) -o $(BINDIR)/mbotps

mbotps.o:	mbotps.c $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	echo "	char *otps_location = "'"$(OTPSDIR)"'";" > otps.h
	$(CC) -c $(CFLAGS) mbotps.c

