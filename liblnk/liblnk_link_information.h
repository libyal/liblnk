/*
 * Link information functions
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

#if !defined( _LIBLNK_LINK_INFORMATION_H )
#define _LIBLNK_LINK_INFORMATION_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "liblnk_extern.h"

#if defined( __cplusplus )
extern "C" {
#endif

LIBLNK_EXTERN int liblnk_file_get_data_flags(
                   liblnk_file_t *file,
                   uint32_t *data_flags,
                   liberror_error_t **error );

LIBLNK_EXTERN int liblnk_file_link_is_file(
                   liblnk_file_t *file,
                   liberror_error_t **error );

LIBLNK_EXTERN int liblnk_file_get_file_attribute_flags(
                   liblnk_file_t *file,
                   uint32_t *file_attribute_flags,
                   liberror_error_t **error );

LIBLNK_EXTERN int liblnk_file_get_file_creation_time(
                   liblnk_file_t *file,
                   uint64_t *creation_time,
                   liberror_error_t **error );

LIBLNK_EXTERN int liblnk_file_get_file_modification_time(
                   liblnk_file_t *file,
                   uint64_t *modification_time,
                   liberror_error_t **error );

LIBLNK_EXTERN int liblnk_file_get_file_access_time(
                   liblnk_file_t *file,
                   uint64_t *access_time,
                   liberror_error_t **error );

LIBLNK_EXTERN int liblnk_file_get_file_size(
                   liblnk_file_t *file,
                   uint32_t *file_size,
                   liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

