#     Copyright (c) 2002-2011 by
#     David W. Caress (caress@mbari.org)
#     and Dale N. Chayes (dale@ldeo.columbia.edu)
HOST := $(shell uname)
TOPDIR := ../..

include $(TOPDIR)/Makefile.$(HOST)

all: $(LIBDIR)/libsapi.a $(INCDIR)/sapi.h

clean:
	rm -f *.o

$(LIBDIR)/libsapi.a:	mem_surf.o pb_math.o sapi_build.o \
		sapi_data.o sapi_files.o sapi_globals.o \
		sapi_simple.o util_surf.o xdr_surf.o
	$(ARCHIVE) $(LIBDIR)/libsapi.a \
		mem_surf.o pb_math.o sapi_build.o \
		sapi_data.o sapi_files.o sapi_globals.o \
		sapi_simple.o util_surf.o xdr_surf.o
	ranlib $(LIBDIR)/libsapi.a

mem_surf.o:      mem_surf.c \
		mem_surf.h sapi.h xdr_surf.h \
		pb_math.h surf.h util_surf.h
	$(CC) -c $(CFLAGS) mem_surf.c
pb_math.o:      pb_math.c  \
		mem_surf.h sapi.h xdr_surf.h \
		pb_math.h surf.h util_surf.h
	$(CC) -c $(CFLAGS) pb_math.c
sapi_build.o:      sapi_build.c  \
		mem_surf.h sapi.h xdr_surf.h \
		pb_math.h surf.h util_surf.h
	$(CC) -c $(CFLAGS) sapi_build.c
sapi_data.o:      sapi_data.c  \
		mem_surf.h sapi.h xdr_surf.h \
		pb_math.h surf.h util_surf.h
	$(CC) -c $(CFLAGS) sapi_data.c
sapi_files.o:      sapi_files.c  \
		mem_surf.h sapi.h xdr_surf.h \
		pb_math.h surf.h util_surf.h
	$(CC) -c $(CFLAGS) sapi_files.c
sapi_globals.o:      sapi_globals.c  \
		mem_surf.h sapi.h xdr_surf.h \
		pb_math.h surf.h util_surf.h
	$(CC) -c $(CFLAGS) sapi_globals.c
sapi_simple.o:      sapi_simple.c  \
		mem_surf.h sapi.h xdr_surf.h \
		pb_math.h surf.h util_surf.h
	$(CC) -c $(CFLAGS) sapi_simple.c
util_surf.o:      util_surf.c  \
		mem_surf.h sapi.h xdr_surf.h \
		pb_math.h surf.h util_surf.h
	$(CC) -c $(CFLAGS) util_surf.c
xdr_surf.o:      xdr_surf.c  \
		mem_surf.h sapi.h xdr_surf.h \
		pb_math.h surf.h util_surf.h
	$(CC) -c $(CFLAGS) xdr_surf.c

### copy the include files to the include file directory
$(INCDIR)/sapi.h:	sapi.h
	cp sapi.h $(INCDIR)/sapi.h
	chmod 664 $(INCDIR)/sapi.h
