/*
 * Library support functions test program
 *
 * Copyright (C) 2009-2018, Joachim Metz <joachim.metz@gmail.com>
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
#include <file_stream.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "lnk_test_functions.h"
#include "lnk_test_getopt.h"
#include "lnk_test_libbfio.h"
#include "lnk_test_libcerror.h"
#include "lnk_test_liblnk.h"
#include "lnk_test_macros.h"
#include "lnk_test_unused.h"

#if !defined( LIBLNK_HAVE_BFIO )

LIBLNK_EXTERN \
int liblnk_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

#endif /* !defined( LIBLNK_HAVE_BFIO ) */

/* Tests the liblnk_get_version function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_get_version(
     void )
{
	const char *version_string = NULL;
	int result                 = 0;

	version_string = liblnk_get_version();

	result = narrow_string_compare(
	          version_string,
	          LIBLNK_VERSION_STRING,
	          9 );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	return( 1 );

on_error:
	return( 0 );
}

/* Tests the liblnk_get_access_flags_read function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_get_access_flags_read(
     void )
{
	int access_flags = 0;

	access_flags = liblnk_get_access_flags_read();

	LNK_TEST_ASSERT_EQUAL_INT(
	 "access_flags",
	 access_flags,
	 LIBLNK_ACCESS_FLAG_READ );

	return( 1 );

on_error:
	return( 0 );
}

/* Tests the liblnk_get_codepage function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_get_codepage(
     void )
{
	libcerror_error_t *error = NULL;
	int codepage             = 0;
	int result               = 0;

	result = liblnk_get_codepage(
	          &codepage,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = liblnk_get_codepage(
	          NULL,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_set_codepage function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_set_codepage(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	result = liblnk_set_codepage(
	          0,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = liblnk_set_codepage(
	          -1,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_check_file_signature function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_check_file_signature(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = lnk_test_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test check file signature
	 */
	result = liblnk_check_file_signature(
	          narrow_source,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = liblnk_check_file_signature(
	          NULL,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the liblnk_check_file_signature_wide function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_check_file_signature_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = lnk_test_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test check file signature
	 */
	result = liblnk_check_file_signature_wide(
	          wide_source,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = liblnk_check_file_signature_wide(
	          NULL,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the liblnk_check_file_signature_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_check_file_signature_file_io_handle(
     const system_character_t *source )
{
	uint8_t empty_block[ 4096 ];

	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	void *memset_result              = NULL;
	size_t source_length             = 0;
	int result                       = 0;

	/* Initialize test
	 */
	result = libbfio_file_initialize(
	          &file_io_handle,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	source_length = system_string_length(
	                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libbfio_file_set_name_wide(
	          file_io_handle,
	          source,
	          source_length,
	          &error );
#else
	result = libbfio_file_set_name(
	          file_io_handle,
	          source,
	          source_length,
	          &error );
#endif
	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_open(
	          file_io_handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test check file signature
	 */
	result = liblnk_check_file_signature_file_io_handle(
	          file_io_handle,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = liblnk_check_file_signature_file_io_handle(
	          NULL,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libbfio_handle_close(
	          file_io_handle,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_free(
	          &file_io_handle,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "file_io_handle",
	 file_io_handle );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	memset_result = memory_set(
	                 empty_block,
	                 0,
	                 sizeof( uint8_t ) * 4096 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "memset_result",
	 memset_result );

	result = libbfio_memory_range_initialize(
	          &file_io_handle,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_memory_range_set(
	          file_io_handle,
	          empty_block,
	          sizeof( uint8_t ) * 4096,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_open(
	          file_io_handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test check file signature
	 */
	result = liblnk_check_file_signature_file_io_handle(
	          file_io_handle,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libbfio_handle_close(
	          file_io_handle,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_free(
	          &file_io_handle,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "file_io_handle",
	 file_io_handle );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* TODO test file too small */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	system_character_t *source = NULL;
	system_integer_t option    = 0;

	while( ( option = lnk_test_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
	LNK_TEST_RUN(
	 "liblnk_get_version",
	 lnk_test_get_version );

	LNK_TEST_RUN(
	 "liblnk_get_access_flags_read",
	 lnk_test_get_access_flags_read );

	LNK_TEST_RUN(
	 "liblnk_get_codepage",
	 lnk_test_get_codepage );

	LNK_TEST_RUN(
	 "liblnk_set_codepage",
	 lnk_test_set_codepage );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_check_file_signature",
		 lnk_test_check_file_signature,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_check_file_signature_wide",
		 lnk_test_check_file_signature_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_check_file_signature_file_io_handle",
		 lnk_test_check_file_signature_file_io_handle,
		 source );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

