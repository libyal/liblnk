#! /usr/bin/env python
#
# Python script to open and close Windows Shortcut (LNK) file(s) using pylnk
# and a file object
#
# Author:            Joachim Metz
# Creation date:     March 7, 2012
# Modification date: March 7, 2012
#

__author__    = "Joachim Metz"
__version__   = "20120307"
__date__      = "Mar 7, 2012"
__copyright__ = "Copyright (c) 2009-2012, Joachim Metz <jbmetz@users.sourceforge.net>"
__license__   = "GNU LGPL version 3"

import sys
import pylnk

# ----------------------------------------------------------------------------
# Main
# ----------------------------------------------------------------------------

print "open_close_file_object.py " + __version__ + " (liblnk " + pylnk.get_version() + ")\n"

argc = len( sys.argv )

if argc < 2:
	print "Usage: open_close_file_object.py filename\n"

	sys.exit( 1 )

lnk_file = pylnk.new_file();

if lnk_file == None:
	print "Missing LNK file object\n"

	sys.exit( 1 )

try:
	file_object = file( 
	               sys.argv[ 1 ] )

	lnk_file.open_file_object(
	 file_object,
	 pylnk.get_access_flags_read() )

except:
	print "Unable to open file\n"
	print sys.exc_info()[ 1 ]

	sys.exit( 1 )

try:
	lnk_file.close()
	file_object.close()
except:
	print "Unable to close file\n"
	print sys.exc_info()
 
	sys.exit( 1 )

sys.exit( 0 )

