/*
 * Info handle
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

#if !defined( _INFO_HANDLE_H )
#define _INFO_HANDLE_H

#include <common.h>
#include <file_stream.h>
#include <types.h>

#include "lnktools_libcerror.h"
#include "lnktools_liblnk.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct info_handle info_handle_t;

struct info_handle
{
	/* The liblnk input file
	 */
	liblnk_file_t *input_file;

	/* The ascii codepage
	 */
	int ascii_codepage;

	/* The notification output stream
	 */
	FILE *notify_stream;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

void info_handle_file_attribute_flags_fprint(
      uint32_t file_attribute_flags,
      FILE *notify_stream );

int info_handle_initialize(
     info_handle_t **info_handle,
     libcerror_error_t **error );

int info_handle_free(
     info_handle_t **info_handle,
     libcerror_error_t **error );

int info_handle_signal_abort(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_set_ascii_codepage(
     info_handle_t *info_handle,
     const system_character_t *string,
     libcerror_error_t **error );

int info_handle_open_input(
     info_handle_t *info_handle,
     const system_character_t *filename,
     libcerror_error_t **error );

int info_handle_close_input(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_filetime_value_fprint(
     info_handle_t *info_handle,
     const char *value_name,
     uint64_t value_64bit,
     libcerror_error_t **error );

int info_handle_guid_value_fprint(
     info_handle_t *info_handle,
     const char *value_name,
     const uint8_t *guid_data,
     libcerror_error_t **error );

int info_handle_data_flags_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_link_information_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_description_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_relative_path_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_working_directory_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_command_line_arguments_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_icon_location_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_link_target_identifier_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_data_block_fprint(
     info_handle_t *info_handle,
     liblnk_data_block_t *data_block,
     libcerror_error_t **error );

int info_handle_distributed_link_tracking_data_block_fprint(
     info_handle_t *info_handle,
     liblnk_data_block_t *data_block,
     libcerror_error_t **error );

int info_handle_metadata_property_store_data_block_fprint(
     info_handle_t *info_handle,
     liblnk_data_block_t *data_block,
     libcerror_error_t **error );

int info_handle_file_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _INFO_HANDLE_H ) */

