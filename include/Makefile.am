include_HEADERS = \
	liblnk.h

pkginclude_HEADERS = \
	liblnk/codepage.h \
	liblnk/definitions.h \
	liblnk/error.h \
	liblnk/extern.h \
	liblnk/features.h \
	liblnk/types.h

EXTRA_DIST = \
	liblnk.h.in \
	liblnk/definitions.h.in \
	liblnk/features.h.in \
	liblnk/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f liblnk.h
	-rm -f liblnk/definitions.h
	-rm -f liblnk/features.h
	-rm -f liblnk/types.h
	-rm -f Makefile

