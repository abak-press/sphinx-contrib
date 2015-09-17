include Makefile.inc

SUBDIRS = \
	  	random_float

.PHONY: all clean install uninstall

all:
	echo make all .
	-for d in $(SUBDIRS); do (cd $$d; $(MAKE) all);done

install:
	echo make install .
	-for d in $(SUBDIRS); do (cd $$d; $(MAKE) install);done

uninstall:
	echo make uninstall .
	-for d in $(SUBDIRS); do (cd $$d; $(MAKE) uninstall);done

clean:
	echo cleaning up in .
	-for d in $(SUBDIRS); do (cd $$d; $(MAKE) clean);done
