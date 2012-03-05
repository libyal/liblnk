#! /usr/bin/env python
#
# Python script to open and close Windows Shortcut (LNK) file(s) using pylnk
#
# Author:            Joachim Metz
# Creation date:     March 5, 2012
# Modification date: March 5, 2012
#

__author__    = "Joachim Metz"
__version__   = "20110104"
__date__      = "Jan 4, 2011"
__copyright__ = "Copyright (c) 2009-2012, Joachim Metz <jbmetz@users.sourceforge.net>"
__license__   = "GNU LGPL version 3"

import sys
import pylnk

# ----------------------------------------------------------------------------
# Main
# ----------------------------------------------------------------------------

print "open_close.py " + __version__ + " (liblnk " + pylnk.get_version() + ")\n"

argc = len( sys.argv )

if argc < 2:
	print "Usage: open_close.py filename(s)\n"

	sys.exit( 1 )

file = pylnk.new_file();

if file == None:
	print "Missing file object\n"

	sys.exit( 1 )

try:
	file.open(
	 sys.argv[ 1 ],
	 pylnk.get_access_flags_read() )

except:
	print "Unable to open file(s)\n"
	print sys.exc_info()[ 1 ]

	sys.exit( 1 )

try:
	file.close()
except:
	print "Unable to close file(s)\n"
	print sys.exc_info()
 
	sys.exit( 1 )

sys.exit( 0 )

