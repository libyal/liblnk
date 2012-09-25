/*
 * Windows Shortcut File (LNK) format library open close testing program
 *
 * Copyright (c) 2009-2012, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include <stdio.h>

#include "lnk_test_libcerror.h"
#include "lnk_test_libcstring.h"
#include "lnk_test_liblnk.h"

/* Tests open and close of a file
 * Returns 1 if successful, 0 if not or -1 on error
 */
int lnk_test_read(
     liblnk_file_t *file,
     off64_t input_offset,
     int input_whence,
     size64_t input_size,
     off64_t expected_offset,
     size64_t expected_size )
{
	libcerror_error_t *error  = NULL;
	const char *whence_string = NULL;
	int result                = 0;

	if( file == NULL )
	{
		return( -1 );
	}
	if( input_whence == SEEK_CUR )
	{
		whence_string = "SEEK_CUR";
	}
	else if( input_whence == SEEK_END )
	{
		whence_string = "SEEK_END";
	}
	else if( input_whence == SEEK_SET )
	{
		whence_string = "SEEK_SET";
	}
	else
	{
		whence_string = "UNKNOWN";
	}
	fprintf(
	 stdout,
	 "Testing reading range with offset: %" PRIi64 ", whence: %s and size: %" PRIu64 "\t",
	 input_offset,
	 whence_string,
	 input_size );

	result = lnk_test_seek_offset(
	          file,
	          input_offset,
	          input_whence,
	          expected_offset );

	if( result == 1 )
	{
		if( input_offset >= 0 )
		{
			result = lnk_test_read_buffer(
				  file,
				  input_size,
				  expected_size );
		}
	}
	if( result == 1 )
	{
		if( input_offset >= 0 )
		{
			result = lnk_test_get_offset(
			          file,
			          input_offset + expected_size,
			          &error );
		}
	}
	if( result != 0 )
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( result == -1 )
	{
		libcerror_error_backtrace_fprint(
		 error,
		 stdout );

		libcerror_error_free(
		 &error );
	}
	return( result );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libcerror_error_t *error = NULL;
	liblnk_file_t *file    = NULL;
	size64_t file_size       = 0;

	if( argc != 2 )
	{
		fprintf(
		 stderr,
		 "Unsupported number of arguments.\n" );

		return( EXIT_FAILURE );
	}
	/* Initialization
	 */
	if( liblnk_file_initialize(
	     &file,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to create file.\n" );

		goto on_error;
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( liblnk_file_open_wide(
	     file,
	     argv[ 1 ],
	     LIBLNK_OPEN_READ,
	     &error ) != 1 )
#else
	if( liblnk_file_open(
	     file,
	     argv[ 1 ],
	     LIBLNK_OPEN_READ,
	     &error ) != 1 )
#endif
	{
		fprintf(
		 stderr,
		 "Unable to open file.\n" );

		goto on_error;
	}
	if( liblnk_file_get_size(
	     file,
	     &file_size,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve file size.\n" );

		goto on_error;
	}
	if( file_size > (size64_t) INT64_MAX )
	{
		fprintf(
		 stderr,
		 "File size exceeds maximum.\n" );

		goto on_error;
	}
	fprintf(
	 stdout,
	 "File size: %" PRIu64 " bytes\n",
	 file_size );

	/* Case 0: test full read
	 */

	/* Test: offset: 0 size: <file_size>
	 * Expected result: offset: 0 size: <file_size>
	 */
	if( lnk_test_read(
	     file,
	     0,
	     SEEK_SET,
	     file_size,
	     0,
	     file_size ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read.\n" );

		goto on_error;
	}
	/* Test: offset: 0 size: <file_size>
	 * Expected result: offset: 0 size: <file_size>
	 */
	if( lnk_test_read(
	     file,
	     0,
	     SEEK_SET,
	     file_size,
	     0,
	     file_size ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read.\n" );

		goto on_error;
	}

	/* Case 1: test random read
	 */

	/* Test: offset: <file_size / 7> size: <file_size / 2>
	 * Expected result: offset: <file_size / 7> size: <file_size / 2>
	 */
	if( lnk_test_read(
	     file,
	     (off64_t) ( file_size / 7 ),
	     SEEK_SET,
	     file_size / 2,
	     (off64_t) ( file_size / 7 ),
	     file_size / 2 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read.\n" );

		goto on_error;
	}
	/* Test: offset: <file_size / 7> size: <file_size / 2>
	 * Expected result: offset: <file_size / 7> size: <file_size / 2>
	 */
	if( lnk_test_read(
	     file,
	     (off64_t) ( file_size / 7 ),
	     SEEK_SET,
	     file_size / 2,
	     (off64_t) ( file_size / 7 ),
	     file_size / 2 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read.\n" );

		goto on_error;
	}

	/* Case 3: test read beyond file size
	 */

	if( file_size < 1024 )
	{
		/* Test: offset: <file_size - 1024> size: 4096
		 * Expected result: offset: -1 size: <undetermined>
		 */
		if( lnk_test_read(
		     file,
		     (off64_t) ( file_size - 1024 ),
		     SEEK_SET,
		     4096,
		     -1,
		     (size64_t) -1 ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test read.\n" );

			goto on_error;
		}
		/* Test: offset: <file_size - 1024> size: 4096
		 * Expected result: offset: -1 size: <undetermined>
		 */
		if( lnk_test_read(
		     file,
		     (off64_t) ( file_size - 1024 ),
		     SEEK_SET,
		     4096,
		     -1,
		     (size64_t) -1 ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test read.\n" );

			goto on_error;
		}
	}
	else
	{
		/* Test: offset: <file_size - 1024> size: 4096
		 * Expected result: offset: <file_size - 1024> size: 1024
		 */
		if( lnk_test_read(
		     file,
		     (off64_t) ( file_size - 1024 ),
		     SEEK_SET,
		     4096,
		     (off64_t) ( file_size - 1024 ),
		     1024 ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test read.\n" );

			goto on_error;
		}
		/* Test: offset: <file_size - 1024> size: 4096
		 * Expected result: offset: <file_size - 1024> size: 1024
		 */
		if( lnk_test_read(
		     file,
		     (off64_t) ( file_size - 1024 ),
		     SEEK_SET,
		     4096,
		     (off64_t) ( file_size - 1024 ),
		     1024 ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test read.\n" );

			goto on_error;
		}
	}
	/* Clean up
	 */
	if( liblnk_file_close(
	     file,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close file.\n" );

		goto on_error;
	}
	if( liblnk_file_free(
	     &file,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free file.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		liblnk_error_backtrace_fprint(
		 error,
		 stderr );
		liblnk_error_free(
		 &error );
	}
	if( file != NULL )
	{
		liblnk_file_close(
		 file,
		 NULL );
		liblnk_file_free(
		 &file,
		 NULL );
	}
	return( EXIT_FAILURE );
}

