/*
 * Library file_header type test program
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

#include "../liblnk/liblnk_file_header.h"

uint8_t lnk_test_file_header_data1[ 76 ] = {
	0x4c, 0x00, 0x00, 0x00, 0x01, 0x14, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x46, 0x9f, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x8c, 0x37, 0x55,
	0x70, 0xb9, 0xbb, 0x01, 0x00, 0x80, 0x93, 0xfc, 0x7d, 0xb3, 0xcb, 0x01, 0x00, 0x8c, 0x37, 0x55,
	0x70, 0xb9, 0xbb, 0x01, 0x10, 0xd5, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

uint8_t lnk_test_file_header_error_data1[ 76 ] = {
	0x4d, 0x00, 0x00, 0x00, 0x01, 0x14, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x46, 0x9f, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x8c, 0x37, 0x55,
	0x70, 0xb9, 0xbb, 0x01, 0x00, 0x80, 0x93, 0xfc, 0x7d, 0xb3, 0xcb, 0x01, 0x00, 0x8c, 0x37, 0x55,
	0x70, 0xb9, 0xbb, 0x01, 0x10, 0xd5, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

uint8_t lnk_test_file_header_error_data2[ 76 ] = {
	0x4c, 0x00, 0x00, 0x00, 0x01, 0x14, 0x02, 0x00, 0xa0, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x46, 0x9f, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x8c, 0x37, 0x55,
	0x70, 0xb9, 0xbb, 0x01, 0x00, 0x80, 0x93, 0xfc, 0x7d, 0xb3, 0xcb, 0x01, 0x00, 0x8c, 0x37, 0x55,
	0x70, 0xb9, 0xbb, 0x01, 0x10, 0xd5, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBLNK_DLL_IMPORT )

/* Tests the liblnk_file_header_initialize function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_header_initialize(
     void )
{
	libcerror_error_t *error          = NULL;
	liblnk_file_header_t *file_header = NULL;
	int result                        = 0;

#if defined( HAVE_LNK_TEST_MEMORY )
	int number_of_malloc_fail_tests   = 1;
	int number_of_memset_fail_tests   = 1;
	int test_number                   = 0;
#endif

	/* Test regular cases
	 */
	result = liblnk_file_header_initialize(
	          &file_header,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "file_header",
	 file_header );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = liblnk_file_header_free(
	          &file_header,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "file_header",
	 file_header );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = liblnk_file_header_initialize(
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

	file_header = (liblnk_file_header_t *) 0x12345678UL;

	result = liblnk_file_header_initialize(
	          &file_header,
	          &error );

	file_header = NULL;

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
		/* Test liblnk_file_header_initialize with malloc failing
		 */
		lnk_test_malloc_attempts_before_fail = test_number;

		result = liblnk_file_header_initialize(
		          &file_header,
		          &error );

		if( lnk_test_malloc_attempts_before_fail != -1 )
		{
			lnk_test_malloc_attempts_before_fail = -1;

			if( file_header != NULL )
			{
				liblnk_file_header_free(
				 &file_header,
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
			 "file_header",
			 file_header );

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
		/* Test liblnk_file_header_initialize with memset failing
		 */
		lnk_test_memset_attempts_before_fail = test_number;

		result = liblnk_file_header_initialize(
		          &file_header,
		          &error );

		if( lnk_test_memset_attempts_before_fail != -1 )
		{
			lnk_test_memset_attempts_before_fail = -1;

			if( file_header != NULL )
			{
				liblnk_file_header_free(
				 &file_header,
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
			 "file_header",
			 file_header );

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
	if( file_header != NULL )
	{
		liblnk_file_header_free(
		 &file_header,
		 NULL );
	}
	return( 0 );
}

/* Tests the liblnk_file_header_free function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_header_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = liblnk_file_header_free(
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

/* Tests the liblnk_file_header_read_data function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_header_read_data(
     void )
{
	libcerror_error_t *error          = NULL;
	liblnk_file_header_t *file_header = NULL;
	int result                        = 0;

	/* Initialize test
	 */
	result = liblnk_file_header_initialize(
	          &file_header,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "file_header",
	 file_header );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = liblnk_file_header_read_data(
	          file_header,
	          lnk_test_file_header_data1,
	          76,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	LNK_TEST_ASSERT_EQUAL_UINT32(
	 "file_header->size",
	 file_header->size,
	 709904 );

	/* Test error cases
	 */
	result = liblnk_file_header_read_data(
	          NULL,
	          lnk_test_file_header_data1,
	          76,
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

	result = liblnk_file_header_read_data(
	          file_header,
	          NULL,
	          76,
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

	result = liblnk_file_header_read_data(
	          file_header,
	          lnk_test_file_header_data1,
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

	result = liblnk_file_header_read_data(
	          file_header,
	          lnk_test_file_header_data1,
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

#if defined( HAVE_LNK_TEST_MEMORY )

	/* Test lnk_test_file_header_read_data with memcpy failing
	 */
	lnk_test_memcpy_attempts_before_fail = 0;

	result = liblnk_file_header_read_data(
	          file_header,
	          lnk_test_file_header_data1,
	          76,
	          &error );

	if( lnk_test_memcpy_attempts_before_fail != -1 )
	{
		lnk_test_memcpy_attempts_before_fail = -1;
	}
	else
	{
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
#endif /* defined( HAVE_LNK_TEST_MEMORY ) */

	/* Test error case where header size is invalid
	 */
	result = liblnk_file_header_read_data(
	          file_header,
	          lnk_test_file_header_error_data1,
	          76,
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

	/* Test error case where class identifier is invalid
	 */
	result = liblnk_file_header_read_data(
	          file_header,
	          lnk_test_file_header_error_data2,
	          76,
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
	result = liblnk_file_header_free(
	          &file_header,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "file_header",
	 file_header );

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
	if( file_header != NULL )
	{
		liblnk_file_header_free(
		 &file_header,
		 NULL );
	}
	return( 0 );
}

/* Tests the liblnk_file_header_read_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_file_header_read_file_io_handle(
     void )
{
	libbfio_handle_t *file_io_handle    = NULL;
	libcerror_error_t *error            = NULL;
	liblnk_file_header_t *file_header = NULL;
	int result                          = 0;

	/* Initialize test
	 */
	result = liblnk_file_header_initialize(
	          &file_header,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "file_header",
	 file_header );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize file IO handle
	 */
	result = lnk_test_open_file_io_handle(
	          &file_io_handle,
	          lnk_test_file_header_data1,
	          76,
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
	result = liblnk_file_header_read_file_io_handle(
	          file_header,
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
	result = liblnk_file_header_read_file_io_handle(
	          NULL,
	          file_io_handle,
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

	result = liblnk_file_header_read_file_io_handle(
	          file_header,
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
	          lnk_test_file_header_data1,
	          8,
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

	result = liblnk_file_header_read_file_io_handle(
	          file_header,
	          file_io_handle,
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

	/* Test data invalid
	 */
	result = lnk_test_open_file_io_handle(
	          &file_io_handle,
	          lnk_test_file_header_error_data1,
	          76,
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

	result = liblnk_file_header_read_file_io_handle(
	          file_header,
	          file_io_handle,
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
	result = liblnk_file_header_free(
	          &file_header,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NULL(
	 "file_header",
	 file_header );

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
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( file_header != NULL )
	{
		liblnk_file_header_free(
		 &file_header,
		 NULL );
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
	LNK_TEST_UNREFERENCED_PARAMETER( argc )
	LNK_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBLNK_DLL_IMPORT )

	LNK_TEST_RUN(
	 "liblnk_file_header_initialize",
	 lnk_test_file_header_initialize );

	LNK_TEST_RUN(
	 "liblnk_file_header_free",
	 lnk_test_file_header_free );

	LNK_TEST_RUN(
	 "liblnk_file_header_read_data",
	 lnk_test_file_header_read_data );

	LNK_TEST_RUN(
	 "liblnk_file_header_read_file_io_handle",
	 lnk_test_file_header_read_file_io_handle );

#endif /* defined( __GNUC__ ) && !defined( LIBLNK_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

