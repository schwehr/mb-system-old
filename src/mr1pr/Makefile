#     Copyright (c) 2003 by
#     David W. Caress (caress@mbari.org)
#     and Dale N. Chayes (dale@ldeo.columbia.edu)

BINDIR = ../../bin
LIBDIR = ../../lib
INCDIR = ../../include

CC = cc
CFLAGS = -O3 -funroll-loops -fexpensive-optimizations -I/usr/X11R6/include -Wall -Wimplicit -pedantic -W -Wstrict-prototypes -Wredundant-decls  -Wimplicit-int -Wimplicit-function-declaration -Wnested-externs -DDARWIN -DBYTESWAPPED -D__APPLE__
ARCHIVE = ar rcv

all:	 $(INCDIR)/mr1pr.h \
	$(INCDIR)/mr1pr_defines.h \
	$(LIBDIR)/libmr1pr.a 

clean:
	rm -f *.o

$(LIBDIR)/libmr1pr.a:	\
		io.o \
		iov1.o \
		misc.o \
		memalloc.o  
	$(ARCHIVE) $(LIBDIR)/libmr1pr.a \
		io.o \
		iov1.o \
		misc.o \
		memalloc.o  
	ranlib $(LIBDIR)/libmr1pr.a

io.o:	io.c $(INCDIR)/mr1pr_defines.h
	$(CC) -c $(CFLAGS) io.c
iov1.o:	iov1.c $(INCDIR)/mr1pr_defines.h
	$(CC) -c $(CFLAGS) iov1.c
misc.o:	misc.c $(INCDIR)/mr1pr_defines.h $(INCDIR)/mem.h
	$(CC) -c $(CFLAGS) misc.c
memalloc.o:	memalloc.c $(INCDIR)/mr1pr_defines.h $(INCDIR)/mem.h
	$(CC) -c $(CFLAGS) memalloc.c

$(INCDIR)/mem.h:	mem.h
	cp mem.h $(INCDIR)/mem.h
	chmod 664 $(INCDIR)/mem.h
$(INCDIR)/mr1pr.h:	mr1pr.h
	cp mr1pr.h $(INCDIR)/mr1pr.h
	chmod 664 $(INCDIR)/mr1pr.h
$(INCDIR)/mr1pr_defines.h:	mr1pr_defines.h mr1pr.h
	cp mr1pr_defines.h $(INCDIR)/mr1pr_defines.h
	chmod 664 $(INCDIR)/mr1pr_defines.h
