/*
 * Tools path_string functions test program
 *
 * Copyright (C) 2009-2025, Joachim Metz <joachim.metz@gmail.com>
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
#include <memory.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "lnk_test_libcerror.h"
#include "lnk_test_liblnk.h"
#include "lnk_test_macros.h"
#include "lnk_test_unused.h"

#include "../lnktools/path_string.h"

/* Tests the path_string_copy_from_file_entry_path function
 * Returns 1 if successful or 0 if not
 */
int lnk_test_tools_path_string_copy_from_file_entry_path(
     void )
{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	system_character_t file_entry_path3[ 5 ] = { 't', 'e', 0x2028, 't', 0 };
#else
	system_character_t file_entry_path3[ 7 ] = { 't', 'e', 0xe2, 0x80, 0xa8, 't', 0 };
#endif
	system_character_t file_entry_path1[ 5 ] = { 't', 'e', 's', 't', 0 };
	system_character_t file_entry_path2[ 5 ] = { 't', 'e', 0x03, 't', 0 };
	system_character_t file_entry_path4[ 5 ] = { 't', 'e', '\\', 't', 0 };
	system_character_t expected_path1[ 5 ]   = { 't', 'e', 's', 't', 0 };
	system_character_t expected_path2[ 8 ]   = { 't', 'e', '\\', 'x', '0', '3', 't', 0 };
	system_character_t expected_path3[ 14 ]  = { 't', 'e', '\\', 'U', '0', '0', '0', '0', '2', '0', '2', '8', 't', 0 };
	system_character_t expected_path4[ 6 ]   = { 't', 'e', '\\', '\\', 't', 0 };
	libcerror_error_t *error                 = NULL;
	system_character_t *path                 = NULL;
	size_t path_size                         = 0;
	int result                               = 0;

	/* Test regular cases
	 */
	result = path_string_copy_from_file_entry_path(
	          &path,
	          &path_size,
	          file_entry_path1,
	          4,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "path",
	 path );

	LNK_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 41 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          path,
	          expected_path1,
	          5 );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 path );

	path = NULL;

	result = path_string_copy_from_file_entry_path(
	          &path,
	          &path_size,
	          file_entry_path2,
	          4,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "path",
	 path );

	LNK_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 41 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          path,
	          expected_path2,
	          8 );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 path );

	path = NULL;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = path_string_copy_from_file_entry_path(
	          &path,
	          &path_size,
	          file_entry_path3,
	          4,
	          &error );
#else
	result = path_string_copy_from_file_entry_path(
	          &path,
	          &path_size,
	          file_entry_path3,
	          6,
	          &error );
#endif
	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "path",
	 path );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	LNK_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 41 );
#else
	LNK_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 61 );
#endif
	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          path,
	          expected_path3,
	          14 );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 path );

	path = NULL;

	result = path_string_copy_from_file_entry_path(
	          &path,
	          &path_size,
	          file_entry_path4,
	          4,
	          &error );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	LNK_TEST_ASSERT_IS_NOT_NULL(
	 "path",
	 path );

	LNK_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 41 );

	LNK_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          path,
	          expected_path4,
	          6 );

	LNK_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 path );

	path = NULL;

	/* Test error cases
	 */
	result = path_string_copy_from_file_entry_path(
	          NULL,
	          &path_size,
	          file_entry_path1,
	          4,
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

	result = path_string_copy_from_file_entry_path(
	          &path,
	          NULL,
	          file_entry_path1,
	          4,
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

	result = path_string_copy_from_file_entry_path(
	          &path,
	          &path_size,
	          NULL,
	          4,
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

	result = path_string_copy_from_file_entry_path(
	          &path,
	          &path_size,
	          file_entry_path1,
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

	result = path_string_copy_from_file_entry_path(
	          &path,
	          &path_size,
	          file_entry_path1,
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
	if( path != NULL )
	{
		memory_free(
		 path );
	}
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

	LNK_TEST_RUN(
	 "path_string_copy_from_file_entry_path",
	 lnk_test_tools_path_string_copy_from_file_entry_path )

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

