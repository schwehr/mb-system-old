#     Copyright (c) 1993-2011 by David W. Caress and D. N. Chayes

all:
	cd src; make all

clean:
	- cd bin; rm -f *
	- cd lib; rm -f *
	- cd include; rm -f *
	- cd src; make clean

