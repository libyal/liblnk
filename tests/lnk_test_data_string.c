/*
 * Library data_string type test program
 *
 * Copyright (C) 2009-2023, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "lnk_test_functions.h"
#include "lnk_test_libcerror.h"
#include "lnk_test_liblnk.h"
#include "lnk_test_macros.h"
#include "lnk_test_memory.h"
#include "lnk_test_unused.h"

#include "../liblnk/liblnk_data_string.h"
#include "../liblnk/liblnk_io_handle.h"

uint8_t lnk_test_data_string_data1[ 60 ] = {
	0x1d, 0x00, 0x25, 0x00, 0x77, 0x00, 0x69, 0x00, 0x6e, 0x00, 0x64, 0x00, 0x69, 0x00, 0x72, 0x00,
	0x25, 0x00, 0x5c, 0x00, 0x73, 0x00, 0x79, 0x00, 0x73, 0x00, 0x74, 0x00, 0x65, 0x00, 0x6d, 0x00,
	0x33, 0x00, 0x32, 0x00, 0x5c, 0x00, 0x6d, 0x00, 0x73, 0x00, 0x70, 0x00, 0x61, 0x00, 0x69, 0x00,
	0x6e, 0x00, 0x74, 0x00, 0x2e, 0x00, 0x65, 0x00, 0x78, 0x00, 0x65, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBLNK_DLL_IMPORT )

/* Tests the liblnk_data_string_initialize function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_data_string_initialize(
     void )
{
	libcerror_error_t *error          = NULL;
	liblnk_data_string_t *data_string = NULL;
	int result                        = 0;

#if defined( HAVE_LNK_TEST_MEMORY )
	int number_of_malloc_fail_tests   = 1;
	int number_of_memset_fail_tests   = 1;
	int test_number                   = 0;
#endif

	/* Test regular cases
	 */
	result = liblnk_data_string_initialize(
	          &data_string,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "data_string",
	 data_string );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = liblnk_data_string_free(
	          &data_string,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "data_string",
	 data_string );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = liblnk_data_string_initialize(
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

	data_string = (liblnk_data_string_t *) 0x12345678UL;

	result = liblnk_data_string_initialize(
	          &data_string,
	          &error );

	data_string = NULL;

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
		/* Test liblnk_data_string_initialize with malloc failing
		 */
		lnk_test_malloc_attempts_before_fail = test_number;

		result = liblnk_data_string_initialize(
		          &data_string,
		          &error );

		if( lnk_test_malloc_attempts_before_fail != -1 )
		{
			lnk_test_malloc_attempts_before_fail = -1;

			if( data_string != NULL )
			{
				liblnk_data_string_free(
				 &data_string,
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
			 "data_string",
			 data_string );

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
		/* Test liblnk_data_string_initialize with memset failing
		 */
		lnk_test_memset_attempts_before_fail = test_number;

		result = liblnk_data_string_initialize(
		          &data_string,
		          &error );

		if( lnk_test_memset_attempts_before_fail != -1 )
		{
			lnk_test_memset_attempts_before_fail = -1;

			if( data_string != NULL )
			{
				liblnk_data_string_free(
				 &data_string,
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
			 "data_string",
			 data_string );

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
	if( data_string != NULL )
	{
		liblnk_data_string_free(
		 &data_string,
		 NULL );
	}
	return( 0 );
}

/* Tests the liblnk_data_string_free function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_data_string_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = liblnk_data_string_free(
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

/* Tests the liblnk_data_string_read_data function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_data_string_read_data(
     void )
{
	libcerror_error_t *error          = NULL;
	liblnk_data_string_t *data_string = NULL;
	liblnk_io_handle_t *io_handle     = NULL;
	int result                        = 0;

	/* Initialize test
	 */
	result = liblnk_io_handle_initialize(
	          &io_handle,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	io_handle->is_unicode = 1;

	result = liblnk_data_string_initialize(
	          &data_string,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "data_string",
	 data_string );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = liblnk_data_string_read_data(
	          data_string,
	          io_handle,
	          lnk_test_data_string_data1,
	          60,
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
	result = liblnk_data_string_read_data(
	          data_string,
	          io_handle,
	          lnk_test_data_string_data1,
	          60,
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
	result = liblnk_data_string_free(
	          &data_string,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "data_string",
	 data_string );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = liblnk_data_string_initialize(
	          &data_string,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "data_string",
	 data_string );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = liblnk_data_string_read_data(
	          NULL,
	          io_handle,
	          lnk_test_data_string_data1,
	          60,
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

	result = liblnk_data_string_read_data(
	          data_string,
	          NULL,
	          lnk_test_data_string_data1,
	          60,
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

	result = liblnk_data_string_read_data(
	          data_string,
	          io_handle,
	          NULL,
	          60,
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

	result = liblnk_data_string_read_data(
	          data_string,
	          io_handle,
	          lnk_test_data_string_data1,
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

	result = liblnk_data_string_read_data(
	          data_string,
	          io_handle,
	          lnk_test_data_string_data1,
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

	/* Clean up
	 */
	result = liblnk_data_string_free(
	          &data_string,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "data_string",
	 data_string );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = liblnk_io_handle_free(
	          &io_handle,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

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
	if( data_string != NULL )
	{
		liblnk_data_string_free(
		 &data_string,
		 NULL );
	}
	if( io_handle != NULL )
	{
		liblnk_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the liblnk_data_string_read_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_data_string_read_file_io_handle(
     void )
{
	libbfio_handle_t *file_io_handle  = NULL;
	libcerror_error_t *error          = NULL;
	liblnk_data_string_t *data_string = NULL;
	liblnk_io_handle_t *io_handle     = NULL;
	int result                        = 0;

	/* Initialize test
	 */
	result = liblnk_io_handle_initialize(
	          &io_handle,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	io_handle->is_unicode = 1;

	result = liblnk_data_string_initialize(
	          &data_string,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "data_string",
	 data_string );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize file IO handle
	 */
	result = lnk_test_open_file_io_handle(
	          &file_io_handle,
	          lnk_test_data_string_data1,
	          60,
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

	/* Test regular cases
	 */
	result = liblnk_data_string_read_file_io_handle(
	          data_string,
	          io_handle,
	          file_io_handle,
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
	result = liblnk_data_string_read_file_io_handle(
	          data_string,
	          io_handle,
	          file_io_handle,
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

	/* Clean up
	 */
	result = liblnk_data_string_free(
	          &data_string,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "data_string",
	 data_string );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = liblnk_data_string_initialize(
	          &data_string,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "data_string",
	 data_string );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = liblnk_data_string_read_file_io_handle(
	          NULL,
	          io_handle,
	          file_io_handle,
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

	result = liblnk_data_string_read_file_io_handle(
	          data_string,
	          NULL,
	          file_io_handle,
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

	result = liblnk_data_string_read_file_io_handle(
	          data_string,
	          io_handle,
	          NULL,
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

	result = liblnk_data_string_read_file_io_handle(
	          data_string,
	          io_handle,
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

	/* Clean up file IO handle
	 */
	result = lnk_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test data too small
	 */
	result = lnk_test_open_file_io_handle(
	          &file_io_handle,
	          lnk_test_data_string_data1,
	          1,
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

	result = liblnk_data_string_read_file_io_handle(
	          data_string,
	          io_handle,
	          file_io_handle,
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

	result = lnk_test_close_file_io_handle(
	          &file_io_handle,
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
	result = liblnk_data_string_free(
	          &data_string,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "data_string",
	 data_string );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = liblnk_io_handle_free(
	          &io_handle,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

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
	if( data_string != NULL )
	{
		liblnk_data_string_free(
		 &data_string,
		 NULL );
	}
	if( io_handle != NULL )
	{
		liblnk_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the liblnk_data_string_get_utf8_string_size function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_data_string_get_utf8_string_size(
     liblnk_data_string_t *data_string )
{
	libcerror_error_t *error = NULL;
	size_t utf8_string_size  = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = liblnk_data_string_get_utf8_string_size(
	          data_string,
	          LIBLNK_CODEPAGE_WINDOWS_1252,
	          &utf8_string_size,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	LNK_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_size",
	 utf8_string_size,
	 (size_t) 30 );

	/* Test error cases
	 */
	result = liblnk_data_string_get_utf8_string_size(
	          NULL,
	          LIBLNK_CODEPAGE_WINDOWS_1252,
	          &utf8_string_size,
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

	result = liblnk_data_string_get_utf8_string_size(
	          data_string,
	          LIBLNK_CODEPAGE_WINDOWS_1252,
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

/* Tests the liblnk_data_string_get_utf8_string function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_data_string_get_utf8_string(
     liblnk_data_string_t *data_string )
{
	uint8_t utf8_string[ 64 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = liblnk_data_string_get_utf8_string(
	          data_string,
	          LIBLNK_CODEPAGE_WINDOWS_1252,
	          utf8_string,
	          64,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

/* TODO check value of utf8_string */

	/* Test error cases
	 */
	result = liblnk_data_string_get_utf8_string(
	          NULL,
	          LIBLNK_CODEPAGE_WINDOWS_1252,
	          utf8_string,
	          64,
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

	result = liblnk_data_string_get_utf8_string(
	          data_string,
	          LIBLNK_CODEPAGE_WINDOWS_1252,
	          NULL,
	          64,
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

	result = liblnk_data_string_get_utf8_string(
	          data_string,
	          LIBLNK_CODEPAGE_WINDOWS_1252,
	          utf8_string,
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

/* Tests the liblnk_data_string_get_utf16_string_size function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_data_string_get_utf16_string_size(
     liblnk_data_string_t *data_string )
{
	libcerror_error_t *error = NULL;
	size_t utf16_string_size = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = liblnk_data_string_get_utf16_string_size(
	          data_string,
	          LIBLNK_CODEPAGE_WINDOWS_1252,
	          &utf16_string_size,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	LNK_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 30 );

	/* Test error cases
	 */
	result = liblnk_data_string_get_utf16_string_size(
	          NULL,
	          LIBLNK_CODEPAGE_WINDOWS_1252,
	          &utf16_string_size,
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

	result = liblnk_data_string_get_utf16_string_size(
	          data_string,
	          LIBLNK_CODEPAGE_WINDOWS_1252,
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

/* Tests the liblnk_data_string_get_utf16_string function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_data_string_get_utf16_string(
     liblnk_data_string_t *data_string )
{
	uint16_t utf16_string[ 64 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = liblnk_data_string_get_utf16_string(
	          data_string,
	          LIBLNK_CODEPAGE_WINDOWS_1252,
	          utf16_string,
	          64,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

/* TODO check value of utf16_string */

	/* Test error cases
	 */
	result = liblnk_data_string_get_utf16_string(
	          NULL,
	          LIBLNK_CODEPAGE_WINDOWS_1252,
	          utf16_string,
	          64,
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

	result = liblnk_data_string_get_utf16_string(
	          data_string,
	          LIBLNK_CODEPAGE_WINDOWS_1252,
	          NULL,
	          64,
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

	result = liblnk_data_string_get_utf16_string(
	          data_string,
	          LIBLNK_CODEPAGE_WINDOWS_1252,
	          utf16_string,
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

#endif /* defined( __GNUC__ ) && !defined( LIBLNK_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc LNK_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] LNK_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc LNK_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] LNK_TEST_ATTRIBUTE_UNUSED )
#endif
{
#if defined( __GNUC__ ) && !defined( LIBLNK_DLL_IMPORT )
	libcerror_error_t *error          = NULL;
	liblnk_data_string_t *data_string = NULL;
	liblnk_io_handle_t *io_handle     = NULL;
	int result                        = 0;
#endif

	LNK_TEST_UNREFERENCED_PARAMETER( argc )
	LNK_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBLNK_DLL_IMPORT )

	LNK_TEST_RUN(
	 "liblnk_data_string_initialize",
	 lnk_test_data_string_initialize );

	LNK_TEST_RUN(
	 "liblnk_data_string_free",
	 lnk_test_data_string_free );

	LNK_TEST_RUN(
	 "liblnk_data_string_read_data",
	 lnk_test_data_string_read_data );

	LNK_TEST_RUN(
	 "liblnk_data_string_read_file_io_handle",
	 lnk_test_data_string_read_file_io_handle );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize data_string for tests
	 */
	result = liblnk_io_handle_initialize(
	          &io_handle,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	io_handle->is_unicode = 1;

	result = liblnk_data_string_initialize(
	          &data_string,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "data_string",
	 data_string );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = liblnk_data_string_read_data(
	          data_string,
	          io_handle,
	          lnk_test_data_string_data1,
	          60,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Run tests
	 */
	LNK_TEST_RUN_WITH_ARGS(
	 "liblnk_data_string_get_utf8_string_size",
	 lnk_test_data_string_get_utf8_string_size,
	 data_string );

	LNK_TEST_RUN_WITH_ARGS(
	 "liblnk_data_string_get_utf8_string",
	 lnk_test_data_string_get_utf8_string,
	 data_string );

	LNK_TEST_RUN_WITH_ARGS(
	 "liblnk_data_string_get_utf16_string_size",
	 lnk_test_data_string_get_utf16_string_size,
	 data_string );

	LNK_TEST_RUN_WITH_ARGS(
	 "liblnk_data_string_get_utf16_string",
	 lnk_test_data_string_get_utf16_string,
	 data_string );

	/* Clean up
	 */
	result = liblnk_data_string_free(
	          &data_string,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "data_string",
	 data_string );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = liblnk_io_handle_free(
	          &io_handle,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

#endif /* defined( __GNUC__ ) && !defined( LIBLNK_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBLNK_DLL_IMPORT )

on_error:
#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( data_string != NULL )
	{
		liblnk_data_string_free(
		 &data_string,
		 NULL );
	}
	if( io_handle != NULL )
	{
		liblnk_io_handle_free(
		 &io_handle,
		 NULL );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBLNK_DLL_IMPORT ) */
}

