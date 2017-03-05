/*
 * Library io_handle type test program
 *
 * Copyright (C) 2009-2017, Joachim Metz <joachim.metz@gmail.com>
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

#include "lnk_test_libcerror.h"
#include "lnk_test_liblnk.h"
#include "lnk_test_macros.h"
#include "lnk_test_memory.h"
#include "lnk_test_unused.h"

#include "../liblnk/liblnk_file_information.h"
#include "../liblnk/liblnk_io_handle.h"

uint8_t lnk_test_file_header_data[ 76 ] = {
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

#if defined( __GNUC__ )

/* Tests the liblnk_io_handle_initialize function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_io_handle_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	liblnk_io_handle_t *io_handle   = NULL;
	int result                      = 0;

#if defined( HAVE_LNK_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
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

	/* Test error cases
	 */
	result = liblnk_io_handle_initialize(
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

	io_handle = (liblnk_io_handle_t *) 0x12345678UL;

	result = liblnk_io_handle_initialize(
	          &io_handle,
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

	io_handle = NULL;

#if defined( HAVE_LNK_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test liblnk_io_handle_initialize with malloc failing
		 */
		lnk_test_malloc_attempts_before_fail = test_number;

		result = liblnk_io_handle_initialize(
		          &io_handle,
		          &error );

		if( lnk_test_malloc_attempts_before_fail != -1 )
		{
			lnk_test_malloc_attempts_before_fail = -1;

			if( io_handle != NULL )
			{
				liblnk_io_handle_free(
				 &io_handle,
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
			 "io_handle",
			 io_handle );

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
		/* Test liblnk_io_handle_initialize with memset failing
		 */
		lnk_test_memset_attempts_before_fail = test_number;

		result = liblnk_io_handle_initialize(
		          &io_handle,
		          &error );

		if( lnk_test_memset_attempts_before_fail != -1 )
		{
			lnk_test_memset_attempts_before_fail = -1;

			if( io_handle != NULL )
			{
				liblnk_io_handle_free(
				 &io_handle,
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
			 "io_handle",
			 io_handle );

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
	if( io_handle != NULL )
	{
		liblnk_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the liblnk_io_handle_free function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_io_handle_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = liblnk_io_handle_free(
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

/* Tests the liblnk_io_handle_clear function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_io_handle_clear(
     void )
{
	libcerror_error_t *error      = NULL;
	liblnk_io_handle_t *io_handle = NULL;
	int result                    = 0;

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

	/* Test regular cases
	 */
	result = liblnk_io_handle_clear(
	          io_handle,
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
	result = liblnk_io_handle_clear(
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
	if( io_handle != NULL )
	{
		liblnk_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the liblnk_io_handle_read_file_header_data function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_io_handle_read_file_header_data(
     void )
{
	uint8_t class_identifier[ 16 ];

	libcerror_error_t *error                    = NULL;
	liblnk_file_information_t *file_information = NULL;
	liblnk_io_handle_t *io_handle               = NULL;
	int result                                  = 0;

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

	result = liblnk_file_information_initialize(
	          &file_information,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        LNK_TEST_ASSERT_IS_NOT_NULL(
         "file_information",
         file_information );

        LNK_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test regular cases
	 */
	result = liblnk_io_handle_read_file_header_data(
	          io_handle,
	          lnk_test_file_header_data,
	          76,
	          class_identifier,
	          16,
	          file_information,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        LNK_TEST_ASSERT_IS_NULL(
         "error",
         error );

	LNK_TEST_ASSERT_EQUAL_UINT32(
	 "file_information->size",
	 file_information->size,
	 709904 );

	/* Test error cases
	 */
	result = liblnk_io_handle_read_file_header_data(
	          NULL,
	          lnk_test_file_header_data,
	          76,
	          class_identifier,
	          16,
	          file_information,
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

	result = liblnk_io_handle_read_file_header_data(
	          io_handle,
	          NULL,
	          76,
	          class_identifier,
	          16,
	          file_information,
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

	result = liblnk_io_handle_read_file_header_data(
	          io_handle,
	          lnk_test_file_header_data,
	          75,
	          class_identifier,
	          16,
	          file_information,
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

	result = liblnk_io_handle_read_file_header_data(
	          io_handle,
	          lnk_test_file_header_data,
	          (size_t) SSIZE_MAX + 1,
	          class_identifier,
	          16,
	          file_information,
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

	result = liblnk_io_handle_read_file_header_data(
	          io_handle,
	          lnk_test_file_header_data,
	          76,
	          NULL,
	          16,
	          file_information,
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

	result = liblnk_io_handle_read_file_header_data(
	          io_handle,
	          lnk_test_file_header_data,
	          76,
	          class_identifier,
	          15,
	          file_information,
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

	result = liblnk_io_handle_read_file_header_data(
	          io_handle,
	          lnk_test_file_header_data,
	          76,
	          class_identifier,
	          (size_t) SSIZE_MAX + 1,
	          file_information,
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

	result = liblnk_io_handle_read_file_header_data(
	          io_handle,
	          lnk_test_file_header_data,
	          76,
	          class_identifier,
	          16,
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

	/* Test error case where header size is invalid
	 */
	result = liblnk_io_handle_read_file_header_data(
	          io_handle,
	          lnk_test_file_header_error_data1,
	          76,
	          class_identifier,
	          16,
	          file_information,
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
	result = liblnk_io_handle_read_file_header_data(
	          io_handle,
	          lnk_test_file_header_error_data2,
	          76,
	          class_identifier,
	          16,
	          file_information,
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
	result = liblnk_file_information_free(
	          &file_information,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        LNK_TEST_ASSERT_IS_NULL(
         "file_information",
         file_information );

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
	if( file_information != NULL )
	{
		liblnk_file_information_free(
		 &file_information,
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

#endif /* defined( __GNUC__ ) */

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

#if defined( __GNUC__ )

	LNK_TEST_RUN(
	 "liblnk_io_handle_initialize",
	 lnk_test_io_handle_initialize );

	LNK_TEST_RUN(
	 "liblnk_io_handle_free",
	 lnk_test_io_handle_free );

	LNK_TEST_RUN(
	 "liblnk_io_handle_clear",
	 lnk_test_io_handle_clear );

	/* TODO: add tests for liblnk_io_handle_clear */

	/* TODO: add tests for liblnk_io_handle_read_file_header */

	LNK_TEST_RUN(
	 "liblnk_io_handle_read_file_header_data",
	 lnk_test_io_handle_read_file_header_data );

#endif /* defined( __GNUC__ ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

