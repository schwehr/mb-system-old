#     Copyright (c) 1993-2011 by
#     David W. Caress (caress@mbari.org)
#     and Dale N. Chayes (dale@ldeo.columbia.edu)

BINDIR = ../../bin
LIBDIR = ../../lib
INCDIR = ../../include

GMTLIBDIR = /sw/lib
GMTINCDIR = /sw/include
NETCDFINCDIR = /sw/include
FFTWLIBDIR = /sw/lib
FFTWINCDIR = /sw/include
### set projlib - could be version supplied with MB-System or other installation
PROJLIB  = $(LIBDIR)/libmbproj.a

all:	$(BINDIR)/mbformat \
	$(BINDIR)/mbdefaults \
	$(BINDIR)/mbdatalist \
	$(BINDIR)/mbinfo \
	$(BINDIR)/mbset \
	$(BINDIR)/mbprocess \
	$(BINDIR)/mbcopy \
	$(BINDIR)/mblist \
	$(BINDIR)/mbnavlist \
	$(BINDIR)/mbsvplist \
	$(BINDIR)/mbbackangle \
	$(BINDIR)/mbclean \
	$(BINDIR)/mbareaclean \
	$(BINDIR)/mbhistogram \
	$(BINDIR)/mbgrid \
	$(BINDIR)/mbmosaic \
	$(BINDIR)/mblevitus \
	$(BINDIR)/mbrollbias \
	$(BINDIR)/mbextractsegy \
	$(BINDIR)/mbsegylist \
	$(BINDIR)/mbsegyinfo \
	$(BINDIR)/mbsegygrid \
	$(BINDIR)/mbsegypsd \
	$(BINDIR)/mbauvnavusbl \
	$(BINDIR)/mbgetesf \
	$(BINDIR)/mbneptune2esf \
	$(BINDIR)/mbps \
	$(BINDIR)/mbstripnan \
	$(BINDIR)/mbrollbias \
	$(BINDIR)/mb7k2jstar \
	$(BINDIR)/mb7kpreprocess \
	$(BINDIR)/mbrolltimelag	\
	$(BINDIR)/mbauvloglist\
	$(BINDIR)/mb7k2ss \
	$(BINDIR)/mbabsorption \
	$(BINDIR)/mbdumpesf\
	$(BINDIR)/mbtime \
	$(BINDIR)/mbctdlist \
	$(BINDIR)/mbfilter \
	$(BINDIR)/mbroutetime \
	$(BINDIR)/mbhysweeppreprocess \
	$(BINDIR)/mbkongsbergpreprocess

clean:
	rm -f *.o

$(BINDIR)/mbformat:	mbformat.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mbformat.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a $(LFLAGS) \
		-o $(BINDIR)/mbformat
$(BINDIR)/mbdefaults:	mbdefaults.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mbdefaults.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a $(LFLAGS) \
		-o $(BINDIR)/mbdefaults
$(BINDIR)/mbdatalist:	mbdatalist.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mbdatalist.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a $(LFLAGS) \
		-o $(BINDIR)/mbdatalist
$(BINDIR)/mbinfo:	mbinfo.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mbinfo.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a $(LFLAGS) \
		-o $(BINDIR)/mbinfo
$(BINDIR)/mbcopy:	mbcopy.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mbcopy.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a $(LFLAGS) \
		-o $(BINDIR)/mbcopy
$(BINDIR)/mblist:	mblist.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mblist.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a $(LFLAGS) \
		-o $(BINDIR)/mblist
$(BINDIR)/mbclean:	mbclean.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mbclean.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a $(LFLAGS) \
		-o $(BINDIR)/mbclean
$(BINDIR)/mbareaclean:	mbareaclean.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mbareaclean.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a $(LFLAGS) \
		-o $(BINDIR)/mbareaclean
$(BINDIR)/mbgrid:	mbgrid.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mbgrid.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a \
		-lgmt -lpsl \
		$(LFLAGS) -o $(BINDIR)/mbgrid
$(BINDIR)/mbmosaic:	mbmosaic.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mbmosaic.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a \
		-lgmt -lpsl \
		$(LFLAGS) -o $(BINDIR)/mbmosaic
$(BINDIR)/mblevitus:	mblevitus.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mblevitus.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a $(LFLAGS) \
		-o $(BINDIR)/mblevitus
$(BINDIR)/mbrollbias:	mbrollbias.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mbrollbias.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a $(LFLAGS) \
		-o $(BINDIR)/mbrollbias
$(BINDIR)/mbgetesf:	mbgetesf.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mbgetesf.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a $(LFLAGS) \
		-o $(BINDIR)/mbgetesf
$(BINDIR)/mbneptune2esf:	mbneptune2esf.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mbneptune2esf.o $(LIBDIR)/libmbio.a $(LFLAGS) $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a $(LFLAGS) \
		-o $(BINDIR)/mbneptune2esf
$(BINDIR)/mbps:	mbps.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mbps.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a \
		-lgmt -lpsl -lgmtps \
		$(LFLAGS) -o $(BINDIR)/mbps
$(BINDIR)/mbstripnan:	mbstripnan.o
	$(CC) $(CFLAGS) mbstripnan.o $(LFLAGS) -o $(BINDIR)/mbstripnan
$(BINDIR)/mbhistogram:	mbhistogram.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mbhistogram.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a \
		$(LFLAGS) -o $(BINDIR)/mbhistogram
$(BINDIR)/mbbackangle:	mbbackangle.o $(LIBDIR)/libmbio.a $(LIBDIR)/libmbaux.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a
	$(CC) $(CFLAGS) mbbackangle.o $(LIBDIR)/libmbio.a $(LIBDIR)/libmbaux.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a \
		-lgmt -lpsl \
		$(LFLAGS) -o $(BINDIR)/mbbackangle
$(BINDIR)/mbnavlist:	mbnavlist.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mbnavlist.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a \
		$(LFLAGS) -o $(BINDIR)/mbnavlist
$(BINDIR)/mbsvplist:	mbsvplist.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mbsvplist.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a \
		$(LFLAGS) -o $(BINDIR)/mbsvplist
$(BINDIR)/mbset:	mbset.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mbset.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a \
		$(LFLAGS) -o $(BINDIR)/mbset
$(BINDIR)/mbprocess:	mbprocess.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mbprocess.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a \
		-lgmt -lpsl \
		$(LFLAGS) -o $(BINDIR)/mbprocess
$(BINDIR)/mbextractsegy:	mbextractsegy.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mbextractsegy.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a \
		$(LFLAGS) -o $(BINDIR)/mbextractsegy
$(BINDIR)/mbsegylist:	mbsegylist.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mbsegylist.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmbaux.a \
		$(LFLAGS) -o $(BINDIR)/mbsegylist
$(BINDIR)/mbsegyinfo:	mbsegyinfo.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mbsegyinfo.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmbaux.a \
		$(LFLAGS) -o $(BINDIR)/mbsegyinfo
$(BINDIR)/mbsegygrid:	mbsegygrid.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mbsegygrid.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmbaux.a \
		-lgmt -lpsl \
		$(LFLAGS) -o $(BINDIR)/mbsegygrid
$(BINDIR)/mbauvnavusbl:	mbauvnavusbl.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mbauvnavusbl.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmbaux.a \
		$(LFLAGS) -o $(BINDIR)/mbauvnavusbl
$(BINDIR)/mb7k2jstar:	mb7k2jstar.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mb7k2jstar.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a $(LIBDIR)/libmbaux.a \
		$(LFLAGS) -o $(BINDIR)/mb7k2jstar
$(BINDIR)/mb7kpreprocess:	mb7kpreprocess.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmbaux.a $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a
	$(CC) $(CFLAGS) mb7kpreprocess.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmbaux.a $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a \
		$(LFLAGS) -o $(BINDIR)/mb7kpreprocess
$(BINDIR)/mbrolltimelag:	mbrolltimelag.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmbaux.a $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a
	$(CC) $(CFLAGS) mbrolltimelag.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmbaux.a $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a \
		$(LFLAGS) -o $(BINDIR)/mbrolltimelag
$(BINDIR)/mbauvloglist:	mbauvloglist.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmbaux.a $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a
	$(CC) $(CFLAGS) mbauvloglist.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmbaux.a $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a \
		$(LFLAGS) -o $(BINDIR)/mbauvloglist
$(BINDIR)/mb7k2ss:	mb7k2ss.o $(LIBDIR)/libmbio.a $(LIBDIR)/libmbaux.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a
	$(CC) $(CFLAGS) mb7k2ss.o $(LIBDIR)/libmbio.a $(LIBDIR)/libmbaux.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a \
		-lgmt \
		$(LFLAGS) -o $(BINDIR)/mb7k2ss
$(BINDIR)/mbabsorption:	mbabsorption.o $(LIBDIR)/libmbio.a
	$(CC) $(CFLAGS) mbabsorption.o $(LIBDIR)/libmbio.a \
		$(LFLAGS) -o $(BINDIR)/mbabsorption
$(BINDIR)/mbdumpesf:	mbdumpesf.o $(LIBDIR)/libmbio.a
	$(CC) $(CFLAGS) mbdumpesf.o $(LIBDIR)/libmbio.a \
		$(LFLAGS) -o $(BINDIR)/mbdumpesf
$(BINDIR)/mbtime:	mbtime.o $(LIBDIR)/libmbio.a
	$(CC) $(CFLAGS) mbtime.o $(LIBDIR)/libmbio.a \
		$(LFLAGS) -o $(BINDIR)/mbtime
$(BINDIR)/mbctdlist:	mbctdlist.o $(LIBDIR)/libmbio.a $(LIBDIR)/libmbaux.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a
	$(CC) $(CFLAGS) mbctdlist.o $(LIBDIR)/libmbio.a $(LIBDIR)/libmbaux.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a \
		$(LFLAGS) -o $(BINDIR)/mbctdlist
$(BINDIR)/mbfilter:	mbfilter.o $(LIBDIR)/libmbio.a $(LIBDIR)/libmbaux.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a
	$(CC) $(CFLAGS) mbfilter.o $(LIBDIR)/libmbio.a $(LIBDIR)/libmbaux.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a \
		$(LFLAGS) -o $(BINDIR)/mbfilter
$(BINDIR)/mbroutetime:	mbroutetime.o $(LIBDIR)/libmbio.a $(LIBDIR)/libmbaux.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a
	$(CC) $(CFLAGS) mbroutetime.o $(LIBDIR)/libmbio.a $(LIBDIR)/libmbaux.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a \
		$(LFLAGS) -o $(BINDIR)/mbroutetime
$(BINDIR)/mbkongsbergpreprocess:	mbkongsbergpreprocess.o $(LIBDIR)/libmbio.a $(LIBDIR)/libmbaux.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a
	$(CC) $(CFLAGS) mbkongsbergpreprocess.o $(LIBDIR)/libmbio.a $(LIBDIR)/libmbaux.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a \
		$(LFLAGS) -o $(BINDIR)/mbkongsbergpreprocess
$(BINDIR)/mbhysweeppreprocess:	mbhysweeppreprocess.o $(LIBDIR)/libmbio.a $(LIBDIR)/libmbaux.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a
	$(CC) $(CFLAGS) mbhysweeppreprocess.o $(LIBDIR)/libmbio.a $(LIBDIR)/libmbaux.a $(PROJLIB) $(LIBDIR)/libmr1pr.a $(LIBDIR)/libsapi.a \
		$(LFLAGS) -o $(BINDIR)/mbhysweeppreprocess
$(BINDIR)/mbsegypsd:	mbsegypsd.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mbsegypsd.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmbaux.a \
		-lgmt -lpsl -lfftw3 \
		$(LFLAGS) -o $(BINDIR)/mbsegypsd
$(BINDIR)/mbprofilepsd:	mbprofilepsd.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmbaux.a
	$(CC) $(CFLAGS) mbprofilepsd.o $(LIBDIR)/libmbio.a $(PROJLIB) $(LIBDIR)/libmbaux.a \
		-lgmt -lpsl -lfftw3 \
		$(LFLAGS) -o $(BINDIR)/mbprofilepsd

### compile the source files
mbformat.o:	mbformat.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) mbformat.c
mbdefaults.o:	mbdefaults.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) mbdefaults.c
mbdatalist.o:	mbdatalist.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) mbdatalist.c
mbinfo.o:	mbinfo.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) mbinfo.c
mbcopy.o:	mbcopy.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) mbcopy.c
mblist.o:	mblist.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h $(INCDIR)/mbsys_simrad2.h
	$(CC) -c $(CFLAGS) -I$(GMTINCDIR) mblist.c
mbclean.o:	mbclean.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) mbclean.c
mbareaclean.o:	mbareaclean.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) mbareaclean.c
mbgrid.o:	mbgrid.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) $(BIGFLAG) -I$(GMTINCDIR) -I$(NETCDFINCDIR) mbgrid.c
mbmosaic.o:	mbmosaic.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) $(BIGFLAG) -I$(GMTINCDIR) -I$(NETCDFINCDIR) mbmosaic.c
mblevitus.o:	mblevitus.c $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h Makefile
	echo "	char *ifile = "'"$(LEVITUS)"'";" > levitus.h
	$(CC) -c $(CFLAGS) mblevitus.c
mbrollbias.o:	mbrollbias.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) mbrollbias.c
mbgetesf.o:	mbgetesf.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) mbgetesf.c
mbneptune2esf.o:	mbneptune2esf.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) mbneptune2esf.c
mbps.o:	mbps.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) -I$(GMTINCDIR) -I$(NETCDFINCDIR) mbps.c
mbstripnan.o:	mbstripnan.c
	$(CC) -c $(CFLAGS) mbstripnan.c
mbhistogram.o:	mbhistogram.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) -I$(GMTINCDIR) mbhistogram.c
mbbackangle.o:	mbbackangle.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) -I$(GMTINCDIR) -I$(NETCDFINCDIR) mbbackangle.c
mbnavlist.o:	mbnavlist.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) mbnavlist.c
mbsvplist.o:	mbsvplist.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) mbsvplist.c
mbset.o:	mbset.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) mbset.c
mbprocess.o:	mbprocess.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) -I$(GMTINCDIR) -I$(NETCDFINCDIR) mbprocess.c
mbextractsegy.o:	mbextractsegy.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h $(INCDIR)/mb_segy.h
	$(CC) -c $(CFLAGS) mbextractsegy.c
mbsegylist.o:	mbsegylist.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h $(INCDIR)/mb_segy.h
	$(CC) -c $(CFLAGS) -I$(GMTINCDIR) mbsegylist.c
mbsegyinfo.o:	mbsegyinfo.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h $(INCDIR)/mb_segy.h
	$(CC) -c $(CFLAGS) -I$(GMTINCDIR) mbsegyinfo.c
mbsegygrid.o:	mbsegygrid.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h $(INCDIR)/mb_segy.h
	$(CC) -c $(CFLAGS) -I$(GMTINCDIR) -I$(NETCDFINCDIR) mbsegygrid.c
mbauvnavusbl.o:	mbauvnavusbl.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) mbauvnavusbl.c
mb7k2jstar.o:	mb7k2jstar.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h $(INCDIR)/mbsys_reson7k.h $(INCDIR)/mbsys_jstar.h
	$(CC) -c $(CFLAGS) mb7k2jstar.c
mb7kpreprocess.o:	mb7kpreprocess.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h $(INCDIR)/mbsys_reson7k.h $(INCDIR)/mbsys_jstar.h
	$(CC) -c $(CFLAGS) mb7kpreprocess.c
mbrolltimelag.o:	mbrolltimelag.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) mbrolltimelag.c
mbauvloglist.o:	mbauvloglist.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) mbauvloglist.c
mb7k2ss.o:	mb7k2ss.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h $(INCDIR)/mbsys_reson7k.h $(INCDIR)/mbsys_ldeoih.h
	$(CC) -c $(CFLAGS) -I$(GMTINCDIR) -I$(NETCDFINCDIR) mb7k2ss.c
mbabsorption.o:	mbabsorption.c $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) mbabsorption.c
mbdumpesf.o:	mbdumpesf.c $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) mbdumpesf.c
mbtime.o:	mbtime.c $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) mbtime.c
mbctdlist.o:	mbctdlist.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) mbctdlist.c
mbfilter.o:	mbfilter.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) mbfilter.c
mbroutetime.o:	mbroutetime.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) mbroutetime.c
mbkongsbergpreprocess.o:	mbkongsbergpreprocess.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) mbkongsbergpreprocess.c
mbhysweeppreprocess.o:	mbhysweeppreprocess.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) mbhysweeppreprocess.c
mbsegypsd.o:	mbsegypsd.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h $(INCDIR)/mb_segy.h
	$(CC) -c $(CFLAGS) -I$(GMTINCDIR) -I$(NETCDFINCDIR) -I$(FFTWINCDIR) mbsegypsd.c
mbprofilepsd.o:	mbprofilepsd.c $(INCDIR)/mb_format.h $(INCDIR)/mb_status.h $(INCDIR)/mb_define.h
	$(CC) -c $(CFLAGS) -I$(GMTINCDIR) -I$(NETCDFINCDIR) -I$(FFTWINCDIR) mbprofilepsd.c
