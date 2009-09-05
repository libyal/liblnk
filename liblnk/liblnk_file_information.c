/*
 * File information functions
 *
 * Copyright (c) 2009, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations. All rights reserved.
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
#include <memory.h>
#include <types.h>

#include <liberror.h>

#include "liblnk_file_information.h"

/* Creates file information
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_information_initialize(
     liblnk_file_information_t **file_information,
     liberror_error_t **error )
{
	static char *function = "liblnk_file_information_initialize";

	if( file_information == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file information.",
		 function );

		return( -1 );
	}
	if( *file_information == NULL )
	{
		*file_information = (liblnk_file_information_t *) memory_allocate(
		                                                   sizeof( liblnk_file_information_t ) );

		if( *file_information == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create file information.",
			 function );

			return( -1 );
		}
		if( memory_set(
		     *file_information,
		     0,
		     sizeof( liblnk_file_information_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear file information.",
			 function );

			memory_free(
			 *file_information );

			*file_information = NULL;

			return( -1 );
		}
	}
	return( 1 );
}

/* Frees file information
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_information_free(
     liblnk_file_information_t **file_information,
     liberror_error_t **error )
{
	static char *function = "liblnk_file_information_free";

	if( file_information == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file information.",
		 function );

		return( -1 );
	}
	if( *file_information != NULL )
	{
		memory_free(
		 *file_information );

		*file_information = NULL;
	}
	return( 1 );
}

