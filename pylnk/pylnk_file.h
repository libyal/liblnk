/*
 * Python object wrapper of liblnk_file_t
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

#if !defined( _PYLNK_FILE_H )
#define _PYLNK_FILE_H

#include <common.h>
#include <types.h>

#include "pylnk_libbfio.h"
#include "pylnk_liblnk.h"
#include "pylnk_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pylnk_file pylnk_file_t;

struct pylnk_file
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The liblnk file
	 */
	liblnk_file_t *file;

	/* The libbfio file IO handle
	 */
	libbfio_handle_t *file_io_handle;
};

extern PyMethodDef pylnk_file_object_methods[];
extern PyTypeObject pylnk_file_type_object;

int pylnk_file_init(
     pylnk_file_t *pylnk_file );

void pylnk_file_free(
      pylnk_file_t *pylnk_file );

PyObject *pylnk_file_signal_abort(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_open(
           pylnk_file_t *pylnk_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pylnk_file_open_file_object(
           pylnk_file_t *pylnk_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pylnk_file_close(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_ascii_codepage(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

int pylnk_file_set_ascii_codepage_from_string(
     pylnk_file_t *pylnk_file,
     const char *codepage_string );

PyObject *pylnk_file_set_ascii_codepage(
           pylnk_file_t *pylnk_file,
           PyObject *arguments,
           PyObject *keywords );

int pylnk_file_set_ascii_codepage_setter(
     pylnk_file_t *pylnk_file,
     PyObject *string_object,
     void *closure );

PyObject *pylnk_file_is_corrupted(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_data_flags(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_file_creation_time(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_file_creation_time_as_integer(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_file_modification_time(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_file_modification_time_as_integer(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_file_access_time(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_file_access_time_as_integer(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_file_size(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_icon_index(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_show_window_value(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_hot_key_value(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_file_attribute_flags(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_drive_type(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_drive_serial_number(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_volume_label(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_local_path(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_network_path(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_description(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_relative_path(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_working_directory(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_command_line_arguments(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_icon_location(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_environment_variables_location(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_link_target_identifier_data(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_machine_identifier(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_droid_volume_identifier(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_droid_file_identifier(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_birth_droid_volume_identifier(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_birth_droid_file_identifier(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_number_of_data_blocks(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

PyObject *pylnk_file_get_data_block_by_index(
           PyObject *pylnk_file,
           int data_block_index );

PyObject *pylnk_file_get_data_block(
           pylnk_file_t *pylnk_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pylnk_file_get_data_blocks(
           pylnk_file_t *pylnk_file,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYLNK_FILE_H ) */

