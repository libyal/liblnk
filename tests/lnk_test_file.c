/*
 * Library file type test program
 *
 * Copyright (C) 2009-2019, Joachim Metz <joachim.metz@gmail.com>
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
#include "lnk_test_memory.h"
#include "lnk_test_unused.h"

#include "../liblnk/liblnk_file.h"

#if !defined( LIBLNK_HAVE_BFIO )

LIBLNK_EXTERN \
int liblnk_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_open_file_io_handle(
     liblnk_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     liblnk_error_t **error );

#endif /* !defined( LIBLNK_HAVE_BFIO ) */

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make lnk_test_file generate verbose output
#define LNK_TEST_FILE_VERBOSE
 */

/* Creates and opens a source file
 * Returns 1 if successful or -1 on error
 */
int lnk_test_file_open_source(
     liblnk_file_t **file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "lnk_test_file_open_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( liblnk_file_initialize(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize file.",
		 function );

		goto on_error;
	}
	result = liblnk_file_open_file_io_handle(
	          *file,
	          file_io_handle,
	          LIBLNK_OPEN_READ,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *file != NULL )
	{
		liblnk_file_free(
		 file,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source file
 * Returns 1 if successful or -1 on error
 */
int lnk_test_file_close_source(
     liblnk_file_t **file,
     libcerror_error_t **error )
{
	static char *function = "lnk_test_file_close_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( liblnk_file_close(
	     *file,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close file.",
		 function );

		result = -1;
	}
	if( liblnk_file_free(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free file.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the liblnk_file_initialize function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	liblnk_file_t *file             = NULL;
	int result                      = 0;

#if defined( HAVE_LNK_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = liblnk_file_initialize(
	          &file,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = liblnk_file_free(
	          &file,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = liblnk_file_initialize(
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

	file = (liblnk_file_t *) 0x12345678UL;

	result = liblnk_file_initialize(
	          &file,
	          &error );

	file = NULL;

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_LNK_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test liblnk_file_initialize with malloc failing
		 */
		lnk_test_malloc_attempts_before_fail = test_number;

		result = liblnk_file_initialize(
		          &file,
		          &error );

		if( lnk_test_malloc_attempts_before_fail != -1 )
		{
			lnk_test_malloc_attempts_before_fail = -1;

			if( file != NULL )
			{
				liblnk_file_free(
				 &file,
				 NULL );
			}
		}
		else
		{
			LNK_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			LNK_TEST_ASSERT_IS_NULL(
			 "file",
			 file );

			LNK_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test liblnk_file_initialize with memset failing
		 */
		lnk_test_memset_attempts_before_fail = test_number;

		result = liblnk_file_initialize(
		          &file,
		          &error );

		if( lnk_test_memset_attempts_before_fail != -1 )
		{
			lnk_test_memset_attempts_before_fail = -1;

			if( file != NULL )
			{
				liblnk_file_free(
				 &file,
				 NULL );
			}
		}
		else
		{
			LNK_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			LNK_TEST_ASSERT_IS_NULL(
			 "file",
			 file );

			LNK_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_LNK_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		liblnk_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the liblnk_file_free function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = liblnk_file_free(
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

/* Tests the liblnk_file_open function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	liblnk_file_t *file      = NULL;
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

	result = liblnk_file_initialize(
	          &file,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = liblnk_file_open(
	          file,
	          narrow_source,
	          LIBLNK_OPEN_READ,
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
	result = liblnk_file_open(
	          NULL,
	          narrow_source,
	          LIBLNK_OPEN_READ,
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

	result = liblnk_file_open(
	          file,
	          NULL,
	          LIBLNK_OPEN_READ,
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

	result = liblnk_file_open(
	          file,
	          narrow_source,
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

	/* Test open when already opened
	 */
	result = liblnk_file_open(
	          file,
	          narrow_source,
	          LIBLNK_OPEN_READ,
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
	result = liblnk_file_free(
	          &file,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		liblnk_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the liblnk_file_open_wide function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	liblnk_file_t *file      = NULL;
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

	result = liblnk_file_initialize(
	          &file,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = liblnk_file_open_wide(
	          file,
	          wide_source,
	          LIBLNK_OPEN_READ,
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
	result = liblnk_file_open_wide(
	          NULL,
	          wide_source,
	          LIBLNK_OPEN_READ,
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

	result = liblnk_file_open_wide(
	          file,
	          NULL,
	          LIBLNK_OPEN_READ,
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

	result = liblnk_file_open_wide(
	          file,
	          wide_source,
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

	/* Test open when already opened
	 */
	result = liblnk_file_open_wide(
	          file,
	          wide_source,
	          LIBLNK_OPEN_READ,
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
	result = liblnk_file_free(
	          &file,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		liblnk_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the liblnk_file_open_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_open_file_io_handle(
     const system_character_t *source )
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	liblnk_file_t *file              = NULL;
	size_t string_length             = 0;
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

	string_length = system_string_length(
	                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libbfio_file_set_name_wide(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#else
	result = libbfio_file_set_name(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#endif
	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        LNK_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = liblnk_file_initialize(
	          &file,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = liblnk_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          LIBLNK_OPEN_READ,
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
	result = liblnk_file_open_file_io_handle(
	          NULL,
	          file_io_handle,
	          LIBLNK_OPEN_READ,
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

	result = liblnk_file_open_file_io_handle(
	          file,
	          NULL,
	          LIBLNK_OPEN_READ,
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

	result = liblnk_file_open_file_io_handle(
	          file,
	          file_io_handle,
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

	/* Test open when already opened
	 */
	result = liblnk_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          LIBLNK_OPEN_READ,
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
	result = liblnk_file_free(
	          &file,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		liblnk_file_free(
		 &file,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the liblnk_file_close function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_close(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = liblnk_file_close(
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

/* Tests the liblnk_file_open and liblnk_file_close functions
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_open_close(
     const system_character_t *source )
{
	libcerror_error_t *error = NULL;
	liblnk_file_t *file      = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = liblnk_file_initialize(
	          &file,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = liblnk_file_open_wide(
	          file,
	          source,
	          LIBLNK_OPEN_READ,
	          &error );
#else
	result = liblnk_file_open(
	          file,
	          source,
	          LIBLNK_OPEN_READ,
	          &error );
#endif

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = liblnk_file_close(
	          file,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close a second time to validate clean up on close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = liblnk_file_open_wide(
	          file,
	          source,
	          LIBLNK_OPEN_READ,
	          &error );
#else
	result = liblnk_file_open(
	          file,
	          source,
	          LIBLNK_OPEN_READ,
	          &error );
#endif

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = liblnk_file_close(
	          file,
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
	result = liblnk_file_free(
	          &file,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		liblnk_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the liblnk_file_signal_abort function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_signal_abort(
     liblnk_file_t *file )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = liblnk_file_signal_abort(
	          file,
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
	result = liblnk_file_signal_abort(
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

/* Tests the liblnk_file_get_ascii_codepage function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_ascii_codepage(
     liblnk_file_t *file )
{
	libcerror_error_t *error  = NULL;
	int ascii_codepage        = 0;
	int ascii_codepage_is_set = 0;
	int result                = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_ascii_codepage(
	          file,
	          &ascii_codepage,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	ascii_codepage_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_ascii_codepage(
	          NULL,
	          &ascii_codepage,
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

	if( ascii_codepage_is_set != 0 )
	{
		result = liblnk_file_get_ascii_codepage(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_set_ascii_codepage function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_set_ascii_codepage(
     liblnk_file_t *file )
{
	int supported_codepages[ 15 ] = {
		LIBLNK_CODEPAGE_ASCII,
		LIBLNK_CODEPAGE_WINDOWS_874,
		LIBLNK_CODEPAGE_WINDOWS_932,
		LIBLNK_CODEPAGE_WINDOWS_936,
		LIBLNK_CODEPAGE_WINDOWS_949,
		LIBLNK_CODEPAGE_WINDOWS_950,
		LIBLNK_CODEPAGE_WINDOWS_1250,
		LIBLNK_CODEPAGE_WINDOWS_1251,
		LIBLNK_CODEPAGE_WINDOWS_1252,
		LIBLNK_CODEPAGE_WINDOWS_1253,
		LIBLNK_CODEPAGE_WINDOWS_1254,
		LIBLNK_CODEPAGE_WINDOWS_1255,
		LIBLNK_CODEPAGE_WINDOWS_1256,
		LIBLNK_CODEPAGE_WINDOWS_1257,
		LIBLNK_CODEPAGE_WINDOWS_1258 };

	int unsupported_codepages[ 17 ] = {
		LIBLNK_CODEPAGE_ISO_8859_1,
		LIBLNK_CODEPAGE_ISO_8859_2,
		LIBLNK_CODEPAGE_ISO_8859_3,
		LIBLNK_CODEPAGE_ISO_8859_4,
		LIBLNK_CODEPAGE_ISO_8859_5,
		LIBLNK_CODEPAGE_ISO_8859_6,
		LIBLNK_CODEPAGE_ISO_8859_7,
		LIBLNK_CODEPAGE_ISO_8859_8,
		LIBLNK_CODEPAGE_ISO_8859_9,
		LIBLNK_CODEPAGE_ISO_8859_10,
		LIBLNK_CODEPAGE_ISO_8859_11,
		LIBLNK_CODEPAGE_ISO_8859_13,
		LIBLNK_CODEPAGE_ISO_8859_14,
		LIBLNK_CODEPAGE_ISO_8859_15,
		LIBLNK_CODEPAGE_ISO_8859_16,
		LIBLNK_CODEPAGE_KOI8_R,
		LIBLNK_CODEPAGE_KOI8_U };

	libcerror_error_t *error = NULL;
	int codepage             = 0;
	int index                = 0;
	int result               = 0;

	/* Test set ASCII codepage
	 */
	for( index = 0;
	     index < 15;
	     index++ )
	{
		codepage = supported_codepages[ index ];

		result = liblnk_file_set_ascii_codepage(
		          file,
		          codepage,
		          &error );

		LNK_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		LNK_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = liblnk_file_set_ascii_codepage(
	          NULL,
	          LIBLNK_CODEPAGE_ASCII,
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

	for( index = 0;
	     index < 17;
	     index++ )
	{
		codepage = unsupported_codepages[ index ];

		result = liblnk_file_set_ascii_codepage(
		          file,
		          codepage,
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
	}
	/* Clean up
	 */
	result = liblnk_file_set_ascii_codepage(
	          file,
	          LIBLNK_CODEPAGE_WINDOWS_1252,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_data_flags function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_data_flags(
     liblnk_file_t *file )
{
	libcerror_error_t *error = NULL;
	uint32_t data_flags      = 0;
	int data_flags_is_set    = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_data_flags(
	          file,
	          &data_flags,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	data_flags_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_data_flags(
	          NULL,
	          &data_flags,
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

	if( data_flags_is_set != 0 )
	{
		result = liblnk_file_get_data_flags(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_file_creation_time function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_file_creation_time(
     liblnk_file_t *file )
{
	libcerror_error_t *error      = NULL;
	uint64_t file_creation_time   = 0;
	int file_creation_time_is_set = 0;
	int result                    = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_file_creation_time(
	          file,
	          &file_creation_time,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	file_creation_time_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_file_creation_time(
	          NULL,
	          &file_creation_time,
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

	if( file_creation_time_is_set != 0 )
	{
		result = liblnk_file_get_file_creation_time(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_file_modification_time function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_file_modification_time(
     liblnk_file_t *file )
{
	libcerror_error_t *error          = NULL;
	uint64_t file_modification_time   = 0;
	int file_modification_time_is_set = 0;
	int result                        = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_file_modification_time(
	          file,
	          &file_modification_time,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	file_modification_time_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_file_modification_time(
	          NULL,
	          &file_modification_time,
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

	if( file_modification_time_is_set != 0 )
	{
		result = liblnk_file_get_file_modification_time(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_file_access_time function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_file_access_time(
     liblnk_file_t *file )
{
	libcerror_error_t *error    = NULL;
	uint64_t file_access_time   = 0;
	int file_access_time_is_set = 0;
	int result                  = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_file_access_time(
	          file,
	          &file_access_time,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	file_access_time_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_file_access_time(
	          NULL,
	          &file_access_time,
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

	if( file_access_time_is_set != 0 )
	{
		result = liblnk_file_get_file_access_time(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_file_size function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_file_size(
     liblnk_file_t *file )
{
	libcerror_error_t *error = NULL;
	uint32_t file_size       = 0;
	int file_size_is_set     = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_file_size(
	          file,
	          &file_size,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	file_size_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_file_size(
	          NULL,
	          &file_size,
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

	if( file_size_is_set != 0 )
	{
		result = liblnk_file_get_file_size(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_icon_index function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_icon_index(
     liblnk_file_t *file )
{
	libcerror_error_t *error = NULL;
	uint32_t icon_index      = 0;
	int icon_index_is_set    = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_icon_index(
	          file,
	          &icon_index,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	icon_index_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_icon_index(
	          NULL,
	          &icon_index,
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

	if( icon_index_is_set != 0 )
	{
		result = liblnk_file_get_icon_index(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_show_window_value function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_show_window_value(
     liblnk_file_t *file )
{
	libcerror_error_t *error     = NULL;
	uint32_t show_window_value   = 0;
	int result                   = 0;
	int show_window_value_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_show_window_value(
	          file,
	          &show_window_value,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	show_window_value_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_show_window_value(
	          NULL,
	          &show_window_value,
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

	if( show_window_value_is_set != 0 )
	{
		result = liblnk_file_get_show_window_value(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_hot_key_value function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_hot_key_value(
     liblnk_file_t *file )
{
	libcerror_error_t *error = NULL;
	uint16_t hot_key_value   = 0;
	int hot_key_value_is_set = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_hot_key_value(
	          file,
	          &hot_key_value,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	hot_key_value_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_hot_key_value(
	          NULL,
	          &hot_key_value,
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

	if( hot_key_value_is_set != 0 )
	{
		result = liblnk_file_get_hot_key_value(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_file_attribute_flags function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_file_attribute_flags(
     liblnk_file_t *file )
{
	libcerror_error_t *error        = NULL;
	uint32_t file_attribute_flags   = 0;
	int file_attribute_flags_is_set = 0;
	int result                      = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_file_attribute_flags(
	          file,
	          &file_attribute_flags,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	file_attribute_flags_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_file_attribute_flags(
	          NULL,
	          &file_attribute_flags,
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

	if( file_attribute_flags_is_set != 0 )
	{
		result = liblnk_file_get_file_attribute_flags(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_drive_type function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_drive_type(
     liblnk_file_t *file )
{
	libcerror_error_t *error = NULL;
	uint32_t drive_type      = 0;
	int drive_type_is_set    = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_drive_type(
	          file,
	          &drive_type,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	drive_type_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_drive_type(
	          NULL,
	          &drive_type,
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

	if( drive_type_is_set != 0 )
	{
		result = liblnk_file_get_drive_type(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_drive_serial_number function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_drive_serial_number(
     liblnk_file_t *file )
{
	libcerror_error_t *error       = NULL;
	uint32_t drive_serial_number   = 0;
	int drive_serial_number_is_set = 0;
	int result                     = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_drive_serial_number(
	          file,
	          &drive_serial_number,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	drive_serial_number_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_drive_serial_number(
	          NULL,
	          &drive_serial_number,
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

	if( drive_serial_number_is_set != 0 )
	{
		result = liblnk_file_get_drive_serial_number(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf8_volume_label_size function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf8_volume_label_size(
     liblnk_file_t *file )
{
	libcerror_error_t *error          = NULL;
	size_t utf8_volume_label_size     = 0;
	int result                        = 0;
	int utf8_volume_label_size_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf8_volume_label_size(
	          file,
	          &utf8_volume_label_size,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_volume_label_size_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf8_volume_label_size(
	          NULL,
	          &utf8_volume_label_size,
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

	if( utf8_volume_label_size_is_set != 0 )
	{
		result = liblnk_file_get_utf8_volume_label_size(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf8_volume_label function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf8_volume_label(
     liblnk_file_t *file )
{
	uint8_t utf8_volume_label[ 512 ];

	libcerror_error_t *error     = NULL;
	int result                   = 0;
	int utf8_volume_label_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf8_volume_label(
	          file,
	          utf8_volume_label,
	          512,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_volume_label_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf8_volume_label(
	          NULL,
	          utf8_volume_label,
	          512,
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

	if( utf8_volume_label_is_set != 0 )
	{
		result = liblnk_file_get_utf8_volume_label(
		          file,
		          NULL,
		          512,
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

		result = liblnk_file_get_utf8_volume_label(
		          file,
		          utf8_volume_label,
		          0,
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

		result = liblnk_file_get_utf8_volume_label(
		          file,
		          utf8_volume_label,
		          (size_t) SSIZE_MAX + 1,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf16_volume_label_size function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf16_volume_label_size(
     liblnk_file_t *file )
{
	libcerror_error_t *error           = NULL;
	size_t utf16_volume_label_size     = 0;
	int result                         = 0;
	int utf16_volume_label_size_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf16_volume_label_size(
	          file,
	          &utf16_volume_label_size,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_volume_label_size_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf16_volume_label_size(
	          NULL,
	          &utf16_volume_label_size,
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

	if( utf16_volume_label_size_is_set != 0 )
	{
		result = liblnk_file_get_utf16_volume_label_size(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf16_volume_label function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf16_volume_label(
     liblnk_file_t *file )
{
	uint16_t utf16_volume_label[ 512 ];

	libcerror_error_t *error      = NULL;
	int result                    = 0;
	int utf16_volume_label_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf16_volume_label(
	          file,
	          utf16_volume_label,
	          512,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_volume_label_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf16_volume_label(
	          NULL,
	          utf16_volume_label,
	          512,
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

	if( utf16_volume_label_is_set != 0 )
	{
		result = liblnk_file_get_utf16_volume_label(
		          file,
		          NULL,
		          512,
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

		result = liblnk_file_get_utf16_volume_label(
		          file,
		          utf16_volume_label,
		          0,
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

		result = liblnk_file_get_utf16_volume_label(
		          file,
		          utf16_volume_label,
		          (size_t) SSIZE_MAX + 1,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf8_local_path_size function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf8_local_path_size(
     liblnk_file_t *file )
{
	libcerror_error_t *error        = NULL;
	size_t utf8_local_path_size     = 0;
	int result                      = 0;
	int utf8_local_path_size_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf8_local_path_size(
	          file,
	          &utf8_local_path_size,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_local_path_size_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf8_local_path_size(
	          NULL,
	          &utf8_local_path_size,
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

	if( utf8_local_path_size_is_set != 0 )
	{
		result = liblnk_file_get_utf8_local_path_size(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf8_local_path function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf8_local_path(
     liblnk_file_t *file )
{
	uint8_t utf8_local_path[ 512 ];

	libcerror_error_t *error   = NULL;
	int result                 = 0;
	int utf8_local_path_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf8_local_path(
	          file,
	          utf8_local_path,
	          512,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_local_path_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf8_local_path(
	          NULL,
	          utf8_local_path,
	          512,
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

	if( utf8_local_path_is_set != 0 )
	{
		result = liblnk_file_get_utf8_local_path(
		          file,
		          NULL,
		          512,
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

		result = liblnk_file_get_utf8_local_path(
		          file,
		          utf8_local_path,
		          0,
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

		result = liblnk_file_get_utf8_local_path(
		          file,
		          utf8_local_path,
		          (size_t) SSIZE_MAX + 1,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf16_local_path_size function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf16_local_path_size(
     liblnk_file_t *file )
{
	libcerror_error_t *error         = NULL;
	size_t utf16_local_path_size     = 0;
	int result                       = 0;
	int utf16_local_path_size_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf16_local_path_size(
	          file,
	          &utf16_local_path_size,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_local_path_size_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf16_local_path_size(
	          NULL,
	          &utf16_local_path_size,
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

	if( utf16_local_path_size_is_set != 0 )
	{
		result = liblnk_file_get_utf16_local_path_size(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf16_local_path function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf16_local_path(
     liblnk_file_t *file )
{
	uint16_t utf16_local_path[ 512 ];

	libcerror_error_t *error    = NULL;
	int result                  = 0;
	int utf16_local_path_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf16_local_path(
	          file,
	          utf16_local_path,
	          512,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_local_path_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf16_local_path(
	          NULL,
	          utf16_local_path,
	          512,
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

	if( utf16_local_path_is_set != 0 )
	{
		result = liblnk_file_get_utf16_local_path(
		          file,
		          NULL,
		          512,
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

		result = liblnk_file_get_utf16_local_path(
		          file,
		          utf16_local_path,
		          0,
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

		result = liblnk_file_get_utf16_local_path(
		          file,
		          utf16_local_path,
		          (size_t) SSIZE_MAX + 1,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf8_network_path_size function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf8_network_path_size(
     liblnk_file_t *file )
{
	libcerror_error_t *error          = NULL;
	size_t utf8_network_path_size     = 0;
	int result                        = 0;
	int utf8_network_path_size_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf8_network_path_size(
	          file,
	          &utf8_network_path_size,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_network_path_size_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf8_network_path_size(
	          NULL,
	          &utf8_network_path_size,
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

	if( utf8_network_path_size_is_set != 0 )
	{
		result = liblnk_file_get_utf8_network_path_size(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf8_network_path function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf8_network_path(
     liblnk_file_t *file )
{
	uint8_t utf8_network_path[ 512 ];

	libcerror_error_t *error     = NULL;
	int result                   = 0;
	int utf8_network_path_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf8_network_path(
	          file,
	          utf8_network_path,
	          512,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_network_path_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf8_network_path(
	          NULL,
	          utf8_network_path,
	          512,
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

	if( utf8_network_path_is_set != 0 )
	{
		result = liblnk_file_get_utf8_network_path(
		          file,
		          NULL,
		          512,
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

		result = liblnk_file_get_utf8_network_path(
		          file,
		          utf8_network_path,
		          0,
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

		result = liblnk_file_get_utf8_network_path(
		          file,
		          utf8_network_path,
		          (size_t) SSIZE_MAX + 1,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf16_network_path_size function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf16_network_path_size(
     liblnk_file_t *file )
{
	libcerror_error_t *error           = NULL;
	size_t utf16_network_path_size     = 0;
	int result                         = 0;
	int utf16_network_path_size_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf16_network_path_size(
	          file,
	          &utf16_network_path_size,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_network_path_size_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf16_network_path_size(
	          NULL,
	          &utf16_network_path_size,
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

	if( utf16_network_path_size_is_set != 0 )
	{
		result = liblnk_file_get_utf16_network_path_size(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf16_network_path function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf16_network_path(
     liblnk_file_t *file )
{
	uint16_t utf16_network_path[ 512 ];

	libcerror_error_t *error      = NULL;
	int result                    = 0;
	int utf16_network_path_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf16_network_path(
	          file,
	          utf16_network_path,
	          512,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_network_path_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf16_network_path(
	          NULL,
	          utf16_network_path,
	          512,
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

	if( utf16_network_path_is_set != 0 )
	{
		result = liblnk_file_get_utf16_network_path(
		          file,
		          NULL,
		          512,
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

		result = liblnk_file_get_utf16_network_path(
		          file,
		          utf16_network_path,
		          0,
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

		result = liblnk_file_get_utf16_network_path(
		          file,
		          utf16_network_path,
		          (size_t) SSIZE_MAX + 1,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf8_description_size function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf8_description_size(
     liblnk_file_t *file )
{
	libcerror_error_t *error         = NULL;
	size_t utf8_description_size     = 0;
	int result                       = 0;
	int utf8_description_size_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf8_description_size(
	          file,
	          &utf8_description_size,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_description_size_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf8_description_size(
	          NULL,
	          &utf8_description_size,
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

	if( utf8_description_size_is_set != 0 )
	{
		result = liblnk_file_get_utf8_description_size(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf8_description function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf8_description(
     liblnk_file_t *file )
{
	uint8_t utf8_description[ 512 ];

	libcerror_error_t *error    = NULL;
	int result                  = 0;
	int utf8_description_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf8_description(
	          file,
	          utf8_description,
	          512,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_description_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf8_description(
	          NULL,
	          utf8_description,
	          512,
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

	if( utf8_description_is_set != 0 )
	{
		result = liblnk_file_get_utf8_description(
		          file,
		          NULL,
		          512,
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

		result = liblnk_file_get_utf8_description(
		          file,
		          utf8_description,
		          0,
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

		result = liblnk_file_get_utf8_description(
		          file,
		          utf8_description,
		          (size_t) SSIZE_MAX + 1,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf16_description_size function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf16_description_size(
     liblnk_file_t *file )
{
	libcerror_error_t *error          = NULL;
	size_t utf16_description_size     = 0;
	int result                        = 0;
	int utf16_description_size_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf16_description_size(
	          file,
	          &utf16_description_size,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_description_size_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf16_description_size(
	          NULL,
	          &utf16_description_size,
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

	if( utf16_description_size_is_set != 0 )
	{
		result = liblnk_file_get_utf16_description_size(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf16_description function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf16_description(
     liblnk_file_t *file )
{
	uint16_t utf16_description[ 512 ];

	libcerror_error_t *error     = NULL;
	int result                   = 0;
	int utf16_description_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf16_description(
	          file,
	          utf16_description,
	          512,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_description_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf16_description(
	          NULL,
	          utf16_description,
	          512,
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

	if( utf16_description_is_set != 0 )
	{
		result = liblnk_file_get_utf16_description(
		          file,
		          NULL,
		          512,
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

		result = liblnk_file_get_utf16_description(
		          file,
		          utf16_description,
		          0,
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

		result = liblnk_file_get_utf16_description(
		          file,
		          utf16_description,
		          (size_t) SSIZE_MAX + 1,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf8_relative_path_size function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf8_relative_path_size(
     liblnk_file_t *file )
{
	libcerror_error_t *error           = NULL;
	size_t utf8_relative_path_size     = 0;
	int result                         = 0;
	int utf8_relative_path_size_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf8_relative_path_size(
	          file,
	          &utf8_relative_path_size,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_relative_path_size_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf8_relative_path_size(
	          NULL,
	          &utf8_relative_path_size,
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

	if( utf8_relative_path_size_is_set != 0 )
	{
		result = liblnk_file_get_utf8_relative_path_size(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf8_relative_path function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf8_relative_path(
     liblnk_file_t *file )
{
	uint8_t utf8_relative_path[ 512 ];

	libcerror_error_t *error      = NULL;
	int result                    = 0;
	int utf8_relative_path_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf8_relative_path(
	          file,
	          utf8_relative_path,
	          512,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_relative_path_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf8_relative_path(
	          NULL,
	          utf8_relative_path,
	          512,
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

	if( utf8_relative_path_is_set != 0 )
	{
		result = liblnk_file_get_utf8_relative_path(
		          file,
		          NULL,
		          512,
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

		result = liblnk_file_get_utf8_relative_path(
		          file,
		          utf8_relative_path,
		          0,
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

		result = liblnk_file_get_utf8_relative_path(
		          file,
		          utf8_relative_path,
		          (size_t) SSIZE_MAX + 1,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf16_relative_path_size function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf16_relative_path_size(
     liblnk_file_t *file )
{
	libcerror_error_t *error            = NULL;
	size_t utf16_relative_path_size     = 0;
	int result                          = 0;
	int utf16_relative_path_size_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf16_relative_path_size(
	          file,
	          &utf16_relative_path_size,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_relative_path_size_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf16_relative_path_size(
	          NULL,
	          &utf16_relative_path_size,
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

	if( utf16_relative_path_size_is_set != 0 )
	{
		result = liblnk_file_get_utf16_relative_path_size(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf16_relative_path function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf16_relative_path(
     liblnk_file_t *file )
{
	uint16_t utf16_relative_path[ 512 ];

	libcerror_error_t *error       = NULL;
	int result                     = 0;
	int utf16_relative_path_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf16_relative_path(
	          file,
	          utf16_relative_path,
	          512,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_relative_path_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf16_relative_path(
	          NULL,
	          utf16_relative_path,
	          512,
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

	if( utf16_relative_path_is_set != 0 )
	{
		result = liblnk_file_get_utf16_relative_path(
		          file,
		          NULL,
		          512,
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

		result = liblnk_file_get_utf16_relative_path(
		          file,
		          utf16_relative_path,
		          0,
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

		result = liblnk_file_get_utf16_relative_path(
		          file,
		          utf16_relative_path,
		          (size_t) SSIZE_MAX + 1,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf8_working_directory_size function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf8_working_directory_size(
     liblnk_file_t *file )
{
	libcerror_error_t *error               = NULL;
	size_t utf8_working_directory_size     = 0;
	int result                             = 0;
	int utf8_working_directory_size_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf8_working_directory_size(
	          file,
	          &utf8_working_directory_size,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_working_directory_size_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf8_working_directory_size(
	          NULL,
	          &utf8_working_directory_size,
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

	if( utf8_working_directory_size_is_set != 0 )
	{
		result = liblnk_file_get_utf8_working_directory_size(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf8_working_directory function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf8_working_directory(
     liblnk_file_t *file )
{
	uint8_t utf8_working_directory[ 512 ];

	libcerror_error_t *error          = NULL;
	int result                        = 0;
	int utf8_working_directory_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf8_working_directory(
	          file,
	          utf8_working_directory,
	          512,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_working_directory_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf8_working_directory(
	          NULL,
	          utf8_working_directory,
	          512,
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

	if( utf8_working_directory_is_set != 0 )
	{
		result = liblnk_file_get_utf8_working_directory(
		          file,
		          NULL,
		          512,
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

		result = liblnk_file_get_utf8_working_directory(
		          file,
		          utf8_working_directory,
		          0,
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

		result = liblnk_file_get_utf8_working_directory(
		          file,
		          utf8_working_directory,
		          (size_t) SSIZE_MAX + 1,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf16_working_directory_size function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf16_working_directory_size(
     liblnk_file_t *file )
{
	libcerror_error_t *error                = NULL;
	size_t utf16_working_directory_size     = 0;
	int result                              = 0;
	int utf16_working_directory_size_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf16_working_directory_size(
	          file,
	          &utf16_working_directory_size,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_working_directory_size_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf16_working_directory_size(
	          NULL,
	          &utf16_working_directory_size,
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

	if( utf16_working_directory_size_is_set != 0 )
	{
		result = liblnk_file_get_utf16_working_directory_size(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf16_working_directory function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf16_working_directory(
     liblnk_file_t *file )
{
	uint16_t utf16_working_directory[ 512 ];

	libcerror_error_t *error           = NULL;
	int result                         = 0;
	int utf16_working_directory_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf16_working_directory(
	          file,
	          utf16_working_directory,
	          512,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_working_directory_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf16_working_directory(
	          NULL,
	          utf16_working_directory,
	          512,
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

	if( utf16_working_directory_is_set != 0 )
	{
		result = liblnk_file_get_utf16_working_directory(
		          file,
		          NULL,
		          512,
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

		result = liblnk_file_get_utf16_working_directory(
		          file,
		          utf16_working_directory,
		          0,
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

		result = liblnk_file_get_utf16_working_directory(
		          file,
		          utf16_working_directory,
		          (size_t) SSIZE_MAX + 1,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf8_command_line_arguments_size function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf8_command_line_arguments_size(
     liblnk_file_t *file )
{
	libcerror_error_t *error                    = NULL;
	size_t utf8_command_line_arguments_size     = 0;
	int result                                  = 0;
	int utf8_command_line_arguments_size_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf8_command_line_arguments_size(
	          file,
	          &utf8_command_line_arguments_size,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_command_line_arguments_size_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf8_command_line_arguments_size(
	          NULL,
	          &utf8_command_line_arguments_size,
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

	if( utf8_command_line_arguments_size_is_set != 0 )
	{
		result = liblnk_file_get_utf8_command_line_arguments_size(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf8_command_line_arguments function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf8_command_line_arguments(
     liblnk_file_t *file )
{
	uint8_t utf8_command_line_arguments[ 512 ];

	libcerror_error_t *error               = NULL;
	int result                             = 0;
	int utf8_command_line_arguments_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf8_command_line_arguments(
	          file,
	          utf8_command_line_arguments,
	          512,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_command_line_arguments_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf8_command_line_arguments(
	          NULL,
	          utf8_command_line_arguments,
	          512,
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

	if( utf8_command_line_arguments_is_set != 0 )
	{
		result = liblnk_file_get_utf8_command_line_arguments(
		          file,
		          NULL,
		          512,
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

		result = liblnk_file_get_utf8_command_line_arguments(
		          file,
		          utf8_command_line_arguments,
		          0,
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

		result = liblnk_file_get_utf8_command_line_arguments(
		          file,
		          utf8_command_line_arguments,
		          (size_t) SSIZE_MAX + 1,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf16_command_line_arguments_size function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf16_command_line_arguments_size(
     liblnk_file_t *file )
{
	libcerror_error_t *error                     = NULL;
	size_t utf16_command_line_arguments_size     = 0;
	int result                                   = 0;
	int utf16_command_line_arguments_size_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf16_command_line_arguments_size(
	          file,
	          &utf16_command_line_arguments_size,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_command_line_arguments_size_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf16_command_line_arguments_size(
	          NULL,
	          &utf16_command_line_arguments_size,
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

	if( utf16_command_line_arguments_size_is_set != 0 )
	{
		result = liblnk_file_get_utf16_command_line_arguments_size(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf16_command_line_arguments function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf16_command_line_arguments(
     liblnk_file_t *file )
{
	uint16_t utf16_command_line_arguments[ 512 ];

	libcerror_error_t *error                = NULL;
	int result                              = 0;
	int utf16_command_line_arguments_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf16_command_line_arguments(
	          file,
	          utf16_command_line_arguments,
	          512,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_command_line_arguments_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf16_command_line_arguments(
	          NULL,
	          utf16_command_line_arguments,
	          512,
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

	if( utf16_command_line_arguments_is_set != 0 )
	{
		result = liblnk_file_get_utf16_command_line_arguments(
		          file,
		          NULL,
		          512,
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

		result = liblnk_file_get_utf16_command_line_arguments(
		          file,
		          utf16_command_line_arguments,
		          0,
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

		result = liblnk_file_get_utf16_command_line_arguments(
		          file,
		          utf16_command_line_arguments,
		          (size_t) SSIZE_MAX + 1,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf8_icon_location_size function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf8_icon_location_size(
     liblnk_file_t *file )
{
	libcerror_error_t *error           = NULL;
	size_t utf8_icon_location_size     = 0;
	int result                         = 0;
	int utf8_icon_location_size_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf8_icon_location_size(
	          file,
	          &utf8_icon_location_size,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_icon_location_size_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf8_icon_location_size(
	          NULL,
	          &utf8_icon_location_size,
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

	if( utf8_icon_location_size_is_set != 0 )
	{
		result = liblnk_file_get_utf8_icon_location_size(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf8_icon_location function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf8_icon_location(
     liblnk_file_t *file )
{
	uint8_t utf8_icon_location[ 512 ];

	libcerror_error_t *error      = NULL;
	int result                    = 0;
	int utf8_icon_location_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf8_icon_location(
	          file,
	          utf8_icon_location,
	          512,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_icon_location_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf8_icon_location(
	          NULL,
	          utf8_icon_location,
	          512,
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

	if( utf8_icon_location_is_set != 0 )
	{
		result = liblnk_file_get_utf8_icon_location(
		          file,
		          NULL,
		          512,
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

		result = liblnk_file_get_utf8_icon_location(
		          file,
		          utf8_icon_location,
		          0,
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

		result = liblnk_file_get_utf8_icon_location(
		          file,
		          utf8_icon_location,
		          (size_t) SSIZE_MAX + 1,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf16_icon_location_size function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf16_icon_location_size(
     liblnk_file_t *file )
{
	libcerror_error_t *error            = NULL;
	size_t utf16_icon_location_size     = 0;
	int result                          = 0;
	int utf16_icon_location_size_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf16_icon_location_size(
	          file,
	          &utf16_icon_location_size,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_icon_location_size_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf16_icon_location_size(
	          NULL,
	          &utf16_icon_location_size,
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

	if( utf16_icon_location_size_is_set != 0 )
	{
		result = liblnk_file_get_utf16_icon_location_size(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf16_icon_location function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf16_icon_location(
     liblnk_file_t *file )
{
	uint16_t utf16_icon_location[ 512 ];

	libcerror_error_t *error       = NULL;
	int result                     = 0;
	int utf16_icon_location_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf16_icon_location(
	          file,
	          utf16_icon_location,
	          512,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_icon_location_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf16_icon_location(
	          NULL,
	          utf16_icon_location,
	          512,
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

	if( utf16_icon_location_is_set != 0 )
	{
		result = liblnk_file_get_utf16_icon_location(
		          file,
		          NULL,
		          512,
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

		result = liblnk_file_get_utf16_icon_location(
		          file,
		          utf16_icon_location,
		          0,
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

		result = liblnk_file_get_utf16_icon_location(
		          file,
		          utf16_icon_location,
		          (size_t) SSIZE_MAX + 1,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf8_environment_variables_location_size function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf8_environment_variables_location_size(
     liblnk_file_t *file )
{
	libcerror_error_t *error                            = NULL;
	size_t utf8_environment_variables_location_size     = 0;
	int result                                          = 0;
	int utf8_environment_variables_location_size_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf8_environment_variables_location_size(
	          file,
	          &utf8_environment_variables_location_size,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_environment_variables_location_size_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf8_environment_variables_location_size(
	          NULL,
	          &utf8_environment_variables_location_size,
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

	if( utf8_environment_variables_location_size_is_set != 0 )
	{
		result = liblnk_file_get_utf8_environment_variables_location_size(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf8_environment_variables_location function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf8_environment_variables_location(
     liblnk_file_t *file )
{
	uint8_t utf8_environment_variables_location[ 512 ];

	libcerror_error_t *error                       = NULL;
	int result                                     = 0;
	int utf8_environment_variables_location_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf8_environment_variables_location(
	          file,
	          utf8_environment_variables_location,
	          512,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_environment_variables_location_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf8_environment_variables_location(
	          NULL,
	          utf8_environment_variables_location,
	          512,
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

	if( utf8_environment_variables_location_is_set != 0 )
	{
		result = liblnk_file_get_utf8_environment_variables_location(
		          file,
		          NULL,
		          512,
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

		result = liblnk_file_get_utf8_environment_variables_location(
		          file,
		          utf8_environment_variables_location,
		          0,
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

		result = liblnk_file_get_utf8_environment_variables_location(
		          file,
		          utf8_environment_variables_location,
		          (size_t) SSIZE_MAX + 1,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf16_environment_variables_location_size function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf16_environment_variables_location_size(
     liblnk_file_t *file )
{
	libcerror_error_t *error                             = NULL;
	size_t utf16_environment_variables_location_size     = 0;
	int result                                           = 0;
	int utf16_environment_variables_location_size_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf16_environment_variables_location_size(
	          file,
	          &utf16_environment_variables_location_size,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_environment_variables_location_size_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf16_environment_variables_location_size(
	          NULL,
	          &utf16_environment_variables_location_size,
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

	if( utf16_environment_variables_location_size_is_set != 0 )
	{
		result = liblnk_file_get_utf16_environment_variables_location_size(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf16_environment_variables_location function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf16_environment_variables_location(
     liblnk_file_t *file )
{
	uint16_t utf16_environment_variables_location[ 512 ];

	libcerror_error_t *error                        = NULL;
	int result                                      = 0;
	int utf16_environment_variables_location_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf16_environment_variables_location(
	          file,
	          utf16_environment_variables_location,
	          512,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_environment_variables_location_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf16_environment_variables_location(
	          NULL,
	          utf16_environment_variables_location,
	          512,
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

	if( utf16_environment_variables_location_is_set != 0 )
	{
		result = liblnk_file_get_utf16_environment_variables_location(
		          file,
		          NULL,
		          512,
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

		result = liblnk_file_get_utf16_environment_variables_location(
		          file,
		          utf16_environment_variables_location,
		          0,
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

		result = liblnk_file_get_utf16_environment_variables_location(
		          file,
		          utf16_environment_variables_location,
		          (size_t) SSIZE_MAX + 1,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_link_target_identifier_data_size function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_link_target_identifier_data_size(
     liblnk_file_t *file )
{
	libcerror_error_t *error                    = NULL;
	size_t link_target_identifier_data_size     = 0;
	int link_target_identifier_data_size_is_set = 0;
	int result                                  = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_link_target_identifier_data_size(
	          file,
	          &link_target_identifier_data_size,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	link_target_identifier_data_size_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_link_target_identifier_data_size(
	          NULL,
	          &link_target_identifier_data_size,
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

	if( link_target_identifier_data_size_is_set != 0 )
	{
		result = liblnk_file_get_link_target_identifier_data_size(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf8_machine_identifier_size function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf8_machine_identifier_size(
     liblnk_file_t *file )
{
	libcerror_error_t *error                = NULL;
	size_t utf8_machine_identifier_size     = 0;
	int result                              = 0;
	int utf8_machine_identifier_size_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf8_machine_identifier_size(
	          file,
	          &utf8_machine_identifier_size,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_machine_identifier_size_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf8_machine_identifier_size(
	          NULL,
	          &utf8_machine_identifier_size,
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

	if( utf8_machine_identifier_size_is_set != 0 )
	{
		result = liblnk_file_get_utf8_machine_identifier_size(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf8_machine_identifier function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf8_machine_identifier(
     liblnk_file_t *file )
{
	uint8_t utf8_machine_identifier[ 512 ];

	libcerror_error_t *error           = NULL;
	int result                         = 0;
	int utf8_machine_identifier_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf8_machine_identifier(
	          file,
	          utf8_machine_identifier,
	          512,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_machine_identifier_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf8_machine_identifier(
	          NULL,
	          utf8_machine_identifier,
	          512,
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

	if( utf8_machine_identifier_is_set != 0 )
	{
		result = liblnk_file_get_utf8_machine_identifier(
		          file,
		          NULL,
		          512,
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

		result = liblnk_file_get_utf8_machine_identifier(
		          file,
		          utf8_machine_identifier,
		          0,
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

		result = liblnk_file_get_utf8_machine_identifier(
		          file,
		          utf8_machine_identifier,
		          (size_t) SSIZE_MAX + 1,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf16_machine_identifier_size function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf16_machine_identifier_size(
     liblnk_file_t *file )
{
	libcerror_error_t *error                 = NULL;
	size_t utf16_machine_identifier_size     = 0;
	int result                               = 0;
	int utf16_machine_identifier_size_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf16_machine_identifier_size(
	          file,
	          &utf16_machine_identifier_size,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_machine_identifier_size_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf16_machine_identifier_size(
	          NULL,
	          &utf16_machine_identifier_size,
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

	if( utf16_machine_identifier_size_is_set != 0 )
	{
		result = liblnk_file_get_utf16_machine_identifier_size(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_utf16_machine_identifier function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_utf16_machine_identifier(
     liblnk_file_t *file )
{
	uint16_t utf16_machine_identifier[ 512 ];

	libcerror_error_t *error            = NULL;
	int result                          = 0;
	int utf16_machine_identifier_is_set = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_utf16_machine_identifier(
	          file,
	          utf16_machine_identifier,
	          512,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_machine_identifier_is_set = result;

	/* Test error cases
	 */
	result = liblnk_file_get_utf16_machine_identifier(
	          NULL,
	          utf16_machine_identifier,
	          512,
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

	if( utf16_machine_identifier_is_set != 0 )
	{
		result = liblnk_file_get_utf16_machine_identifier(
		          file,
		          NULL,
		          512,
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

		result = liblnk_file_get_utf16_machine_identifier(
		          file,
		          utf16_machine_identifier,
		          0,
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

		result = liblnk_file_get_utf16_machine_identifier(
		          file,
		          utf16_machine_identifier,
		          (size_t) SSIZE_MAX + 1,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the liblnk_file_get_droid_volume_identifier function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_droid_volume_identifier(
     liblnk_file_t *file )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_droid_volume_identifier(
	          file,
	          guid_data,
	          16,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = liblnk_file_get_droid_volume_identifier(
	          NULL,
	          guid_data,
	          16,
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

	result = liblnk_file_get_droid_volume_identifier(
	          file,
	          NULL,
	          16,
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

	result = liblnk_file_get_droid_volume_identifier(
	          file,
	          guid_data,
	          0,
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

	result = liblnk_file_get_droid_volume_identifier(
	          file,
	          guid_data,
	          (size_t) SSIZE_MAX + 1,
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

/* Tests the liblnk_file_get_droid_file_identifier function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_droid_file_identifier(
     liblnk_file_t *file )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_droid_file_identifier(
	          file,
	          guid_data,
	          16,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = liblnk_file_get_droid_file_identifier(
	          NULL,
	          guid_data,
	          16,
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

	result = liblnk_file_get_droid_file_identifier(
	          file,
	          NULL,
	          16,
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

	result = liblnk_file_get_droid_file_identifier(
	          file,
	          guid_data,
	          0,
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

	result = liblnk_file_get_droid_file_identifier(
	          file,
	          guid_data,
	          (size_t) SSIZE_MAX + 1,
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

/* Tests the liblnk_file_get_birth_droid_volume_identifier function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_birth_droid_volume_identifier(
     liblnk_file_t *file )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_birth_droid_volume_identifier(
	          file,
	          guid_data,
	          16,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = liblnk_file_get_birth_droid_volume_identifier(
	          NULL,
	          guid_data,
	          16,
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

	result = liblnk_file_get_birth_droid_volume_identifier(
	          file,
	          NULL,
	          16,
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

	result = liblnk_file_get_birth_droid_volume_identifier(
	          file,
	          guid_data,
	          0,
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

	result = liblnk_file_get_birth_droid_volume_identifier(
	          file,
	          guid_data,
	          (size_t) SSIZE_MAX + 1,
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

/* Tests the liblnk_file_get_birth_droid_file_identifier function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_get_birth_droid_file_identifier(
     liblnk_file_t *file )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = liblnk_file_get_birth_droid_file_identifier(
	          file,
	          guid_data,
	          16,
	          &error );

	LNK_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = liblnk_file_get_birth_droid_file_identifier(
	          NULL,
	          guid_data,
	          16,
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

	result = liblnk_file_get_birth_droid_file_identifier(
	          file,
	          NULL,
	          16,
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

	result = liblnk_file_get_birth_droid_file_identifier(
	          file,
	          guid_data,
	          0,
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

	result = liblnk_file_get_birth_droid_file_identifier(
	          file,
	          guid_data,
	          (size_t) SSIZE_MAX + 1,
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
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	liblnk_file_t *file              = NULL;
	system_character_t *source       = NULL;
	system_integer_t option          = 0;
	size_t string_length             = 0;
	int result                       = 0;

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
#if defined( HAVE_DEBUG_OUTPUT ) && defined( LNK_TEST_FILE_VERBOSE )
	liblnk_notify_set_verbose(
	 1 );
	liblnk_notify_set_stream(
	 stderr,
	 NULL );
#endif

	LNK_TEST_RUN(
	 "liblnk_file_initialize",
	 lnk_test_file_initialize );

	LNK_TEST_RUN(
	 "liblnk_file_free",
	 lnk_test_file_free );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
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

		string_length = system_string_length(
		                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libbfio_file_set_name_wide(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#else
		result = libbfio_file_set_name(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#endif
		LNK_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        LNK_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		result = liblnk_check_file_signature_file_io_handle(
		          file_io_handle,
		          &error );

		LNK_TEST_ASSERT_NOT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		LNK_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( result != 0 )
	{
		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_open",
		 lnk_test_file_open,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_open_wide",
		 lnk_test_file_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_open_file_io_handle",
		 lnk_test_file_open_file_io_handle,
		 source );

		LNK_TEST_RUN(
		 "liblnk_file_close",
		 lnk_test_file_close );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_open_close",
		 lnk_test_file_open_close,
		 source );

		/* Initialize file for tests
		 */
		result = lnk_test_file_open_source(
		          &file,
		          file_io_handle,
		          &error );

		LNK_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		LNK_TEST_ASSERT_IS_NOT_NULL(
		 "file",
		 file );

		LNK_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_signal_abort",
		 lnk_test_file_signal_abort,
		 file );

#if defined( __GNUC__ ) && !defined( LIBLNK_DLL_IMPORT )

		/* TODO: add tests for liblnk_file_open_read */

#endif /* defined( __GNUC__ ) && !defined( LIBLNK_DLL_IMPORT ) */

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_ascii_codepage",
		 lnk_test_file_get_ascii_codepage,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_set_ascii_codepage",
		 lnk_test_file_set_ascii_codepage,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_data_flags",
		 lnk_test_file_get_data_flags,
		 file );

		/* TODO: add tests for liblnk_file_link_refers_to_file */

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_file_creation_time",
		 lnk_test_file_get_file_creation_time,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_file_modification_time",
		 lnk_test_file_get_file_modification_time,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_file_access_time",
		 lnk_test_file_get_file_access_time,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_file_size",
		 lnk_test_file_get_file_size,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_icon_index",
		 lnk_test_file_get_icon_index,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_show_window_value",
		 lnk_test_file_get_show_window_value,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_hot_key_value",
		 lnk_test_file_get_hot_key_value,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_file_attribute_flags",
		 lnk_test_file_get_file_attribute_flags,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_drive_type",
		 lnk_test_file_get_drive_type,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_drive_serial_number",
		 lnk_test_file_get_drive_serial_number,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf8_volume_label_size",
		 lnk_test_file_get_utf8_volume_label_size,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf8_volume_label",
		 lnk_test_file_get_utf8_volume_label,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf16_volume_label_size",
		 lnk_test_file_get_utf16_volume_label_size,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf16_volume_label",
		 lnk_test_file_get_utf16_volume_label,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf8_local_path_size",
		 lnk_test_file_get_utf8_local_path_size,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf8_local_path",
		 lnk_test_file_get_utf8_local_path,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf16_local_path_size",
		 lnk_test_file_get_utf16_local_path_size,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf16_local_path",
		 lnk_test_file_get_utf16_local_path,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf8_network_path_size",
		 lnk_test_file_get_utf8_network_path_size,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf8_network_path",
		 lnk_test_file_get_utf8_network_path,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf16_network_path_size",
		 lnk_test_file_get_utf16_network_path_size,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf16_network_path",
		 lnk_test_file_get_utf16_network_path,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf8_description_size",
		 lnk_test_file_get_utf8_description_size,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf8_description",
		 lnk_test_file_get_utf8_description,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf16_description_size",
		 lnk_test_file_get_utf16_description_size,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf16_description",
		 lnk_test_file_get_utf16_description,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf8_relative_path_size",
		 lnk_test_file_get_utf8_relative_path_size,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf8_relative_path",
		 lnk_test_file_get_utf8_relative_path,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf16_relative_path_size",
		 lnk_test_file_get_utf16_relative_path_size,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf16_relative_path",
		 lnk_test_file_get_utf16_relative_path,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf8_working_directory_size",
		 lnk_test_file_get_utf8_working_directory_size,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf8_working_directory",
		 lnk_test_file_get_utf8_working_directory,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf16_working_directory_size",
		 lnk_test_file_get_utf16_working_directory_size,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf16_working_directory",
		 lnk_test_file_get_utf16_working_directory,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf8_command_line_arguments_size",
		 lnk_test_file_get_utf8_command_line_arguments_size,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf8_command_line_arguments",
		 lnk_test_file_get_utf8_command_line_arguments,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf16_command_line_arguments_size",
		 lnk_test_file_get_utf16_command_line_arguments_size,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf16_command_line_arguments",
		 lnk_test_file_get_utf16_command_line_arguments,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf8_icon_location_size",
		 lnk_test_file_get_utf8_icon_location_size,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf8_icon_location",
		 lnk_test_file_get_utf8_icon_location,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf16_icon_location_size",
		 lnk_test_file_get_utf16_icon_location_size,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf16_icon_location",
		 lnk_test_file_get_utf16_icon_location,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf8_environment_variables_location_size",
		 lnk_test_file_get_utf8_environment_variables_location_size,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf8_environment_variables_location",
		 lnk_test_file_get_utf8_environment_variables_location,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf16_environment_variables_location_size",
		 lnk_test_file_get_utf16_environment_variables_location_size,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf16_environment_variables_location",
		 lnk_test_file_get_utf16_environment_variables_location,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_link_target_identifier_data_size",
		 lnk_test_file_get_link_target_identifier_data_size,
		 file );

		/* TODO: add tests for liblnk_file_copy_link_target_identifier_data */

		/* TODO: add tests for liblnk_file_has_distributed_link_tracking_data */

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf8_machine_identifier_size",
		 lnk_test_file_get_utf8_machine_identifier_size,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf8_machine_identifier",
		 lnk_test_file_get_utf8_machine_identifier,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf16_machine_identifier_size",
		 lnk_test_file_get_utf16_machine_identifier_size,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_utf16_machine_identifier",
		 lnk_test_file_get_utf16_machine_identifier,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_droid_volume_identifier",
		 lnk_test_file_get_droid_volume_identifier,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_droid_file_identifier",
		 lnk_test_file_get_droid_file_identifier,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_birth_droid_volume_identifier",
		 lnk_test_file_get_birth_droid_volume_identifier,
		 file );

		LNK_TEST_RUN_WITH_ARGS(
		 "liblnk_file_get_birth_droid_file_identifier",
		 lnk_test_file_get_birth_droid_file_identifier,
		 file );

		/* Clean up
		 */
		result = lnk_test_file_close_source(
		          &file,
		          &error );

		LNK_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		LNK_TEST_ASSERT_IS_NULL(
		 "file",
		 file );

		LNK_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( file_io_handle != NULL )
	{
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
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		liblnk_file_free(
		 &file,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

