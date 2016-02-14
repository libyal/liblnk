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
	/bin/rm -f liblnk.h
	/bin/rm -f liblnk/definitions.h
	/bin/rm -f liblnk/features.h
	/bin/rm -f liblnk/types.h
	/bin/rm -f Makefile

