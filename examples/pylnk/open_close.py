#! /usr/bin/env python
#
# Python script to open and close Windows a Shortcut File (LNK) using pylnk
#
# Author:            Joachim Metz
# Creation date:     March 5, 2012
# Modification date: March 12, 2012
#

__author__    = "Joachim Metz"
__version__   = "20120312"
__date__      = "Mar 12, 2012"
__copyright__ = "Copyright (c) 2009-2012, Joachim Metz <joachim.metz@gmail.com>"
__license__   = "GNU LGPL version 3"

import sys
import pylnk

# ----------------------------------------------------------------------------
# Main
# ----------------------------------------------------------------------------

print "open_close.py " + __version__ + " (liblnk " + pylnk.get_version() + ")\n"

argc = len( sys.argv )

if argc < 2:
	print "Usage: open_close.py filename\n"

	sys.exit( 1 )

lnk_file = pylnk.file();

if lnk_file == None:
	print "Missing LNK file object\n"

	sys.exit( 1 )

try:
	lnk_file.open(
	 sys.argv[ 1 ],
	 pylnk.get_access_flags_read() )

except:
	print "Unable to open file\n"
	print sys.exc_info()[ 1 ]

	sys.exit( 1 )

try:
	lnk_file.close()
except:
	print "Unable to close file\n"
	print sys.exc_info()
 
	sys.exit( 1 )

sys.exit( 0 )

