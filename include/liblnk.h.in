/*
 * Library to access the Windows Shortcut File (LNK) format
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

#if !defined( _LIBLNK_H )
#define _LIBLNK_H

#include <liblnk/codepage.h>
#include <liblnk/definitions.h>
#include <liblnk/error.h>
#include <liblnk/extern.h>
#include <liblnk/features.h>
#include <liblnk/types.h>

#include <stdio.h>

#if defined( LIBLNK_HAVE_BFIO )
#include <libbfio.h>
#endif

#if defined( __cplusplus )
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Support functions
 * ------------------------------------------------------------------------- */

/* Returns the library version
 */
LIBLNK_EXTERN \
const char *liblnk_get_version(
             void );

/* Returns the access flags for reading
 */
LIBLNK_EXTERN \
int liblnk_get_access_flags_read(
     void );

/* Retrieves the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_get_codepage(
     int *codepage,
     liblnk_error_t **error );

/* Sets the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_set_codepage(
     int codepage,
     liblnk_error_t **error );

/* Determines if a file contains a LNK file signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_check_file_signature(
     const char *filename,
     liblnk_error_t **error );

#if defined( LIBLNK_HAVE_WIDE_CHARACTER_TYPE )

/* Determines if a file contains a LNK file signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_check_file_signature_wide(
     const wchar_t *filename,
     liblnk_error_t **error );

#endif /* defined( LIBLNK_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBLNK_HAVE_BFIO )

/* Determines if a file contains a LNK file signature using a Basic File IO (bfio) handle
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     liblnk_error_t **error );

#endif /* defined( LIBLNK_HAVE_BFIO ) */

/* -------------------------------------------------------------------------
 * Notify functions
 * ------------------------------------------------------------------------- */

/* Sets the verbose notification
 */
LIBLNK_EXTERN \
void liblnk_notify_set_verbose(
      int verbose );

/* Sets the notification stream
 * Returns 1 if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_notify_set_stream(
     FILE *stream,
     liblnk_error_t **error );

/* Opens the notification stream using a filename
 * The stream is opened in append mode
 * Returns 1 if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_notify_stream_open(
     const char *filename,
     liblnk_error_t **error );

/* Closes the notification stream if opened using a filename
 * Returns 0 if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_notify_stream_close(
     liblnk_error_t **error );

/* -------------------------------------------------------------------------
 * Error functions
 * ------------------------------------------------------------------------- */

/* Frees an error
 */
LIBLNK_EXTERN \
void liblnk_error_free(
      liblnk_error_t **error );

/* Prints a descriptive string of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_error_fprint(
     liblnk_error_t *error,
     FILE *stream );

/* Prints a descriptive string of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_error_sprint(
     liblnk_error_t *error,
     char *string,
     size_t size );

/* Prints a backtrace of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_error_backtrace_fprint(
     liblnk_error_t *error,
     FILE *stream );

/* Prints a backtrace of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_error_backtrace_sprint(
     liblnk_error_t *error,
     char *string,
     size_t size );

/* -------------------------------------------------------------------------
 * File functions
 * ------------------------------------------------------------------------- */

/* Creates a file
 * Make sure the value file is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_initialize(
     liblnk_file_t **file,
     liblnk_error_t **error );

/* Frees a file
 * Returns 1 if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_free(
     liblnk_file_t **file,
     liblnk_error_t **error );

/* Signals the file to abort its current activity
 * Returns 1 if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_signal_abort(
     liblnk_file_t *file,
     liblnk_error_t **error );

/* Opens a file
 * Returns 1 if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_open(
     liblnk_file_t *file,
     const char *filename,
     int access_flags,
     liblnk_error_t **error );

#if defined( LIBLNK_HAVE_WIDE_CHARACTER_TYPE )

/* Opens a file
 * Returns 1 if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_open_wide(
     liblnk_file_t *file,
     const wchar_t *filename,
     int access_flags,
     liblnk_error_t **error );

#endif /* defined( LIBLNK_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBLNK_HAVE_BFIO )

/* Opens a file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_open_file_io_handle(
     liblnk_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     liblnk_error_t **error );

#endif /* defined( LIBLNK_HAVE_BFIO ) */

/* Closes a file
 * Returns 0 if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_close(
     liblnk_file_t *file,
     liblnk_error_t **error );

/* Retrieves the file ASCII codepage
 * Returns 1 if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_ascii_codepage(
     liblnk_file_t *file,
     int *ascii_codepage,
     liblnk_error_t **error );

/* Sets the file ASCII codepage
 * Returns 1 if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_set_ascii_codepage(
     liblnk_file_t *file,
     int ascii_codepage,
     liblnk_error_t **error );

/* -------------------------------------------------------------------------
 * Link information functions
 * ------------------------------------------------------------------------- */

/* Retrieves the data flags
 * The data flags contain information about the available link information
 * Returns 1 if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_data_flags(
     liblnk_file_t *file,
     uint32_t *data_flags,
     liblnk_error_t **error );

/* Determines if the link refers to a file
 * Returns 1 if the link refers to a file, 0 if not or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_link_refers_to_file(
     liblnk_file_t *file,
     liblnk_error_t **error );

/* Retrieves the 64-bit FILETIME value containing the linked file's creation date and time
 * The creation time is only set when the link refers to a file
 * Returns 1 if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_file_creation_time(
     liblnk_file_t *file,
     uint64_t *filetime,
     liblnk_error_t **error );

/* Retrieves the 64-bit FILETIME value containing the linked file's last modification date and time
 * The modification time is only set when the link refers to a file
 * Returns 1 if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_file_modification_time(
     liblnk_file_t *file,
     uint64_t *filetime,
     liblnk_error_t **error );

/* Retrieves the 64-bit FILETIME value containing the linked file's last access date and time
 * The access time is only set when the link refers to a file
 * Returns 1 if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_file_access_time(
     liblnk_file_t *file,
     uint64_t *filetime,
     liblnk_error_t **error );

/* Retrieves the linked file's size
 * The file size is only set if the link refers to a file
 * Returns 1 if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_file_size(
     liblnk_file_t *file,
     uint32_t *file_size,
     liblnk_error_t **error );

/* Retrieves the icon index
 * Returns 1 if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_icon_index(
     liblnk_file_t *file,
     uint32_t *icon_index,
     liblnk_error_t **error );

/* Retrieves the show window value
 * Returns 1 if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_show_window_value(
     liblnk_file_t *file,
     uint32_t *show_window_value,
     liblnk_error_t **error );

/* Retrieves the hot key value
 * Returns 1 if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_hot_key_value(
     liblnk_file_t *file,
     uint16_t *hot_key_value,
     liblnk_error_t **error );

/* Retrieves the linked file's attribute flags
 * The file attribute flags are only set when the link refers to a file
 * Returns 1 if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_file_attribute_flags(
     liblnk_file_t *file,
     uint32_t *file_attribute_flags,
     liblnk_error_t **error );

/* Retrieves the linked file's drive type
 * The drive type is only set if the link refers to a file on a local volume
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_drive_type(
     liblnk_file_t *file,
     uint32_t *drive_type,
     liblnk_error_t **error );

/* Retrieves the linked file's drive serial number
 * The drive serial number is only set if the link refers to a file on a local volume
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_drive_serial_number(
     liblnk_file_t *file,
     uint32_t *drive_serial_number,
     liblnk_error_t **error );

/* Retrieves the size of the UTF-8 encoded volume label
 * The size includes the end of string character
 * The volume label is only set if the link refers to a file on a local volume
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf8_volume_label_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     liblnk_error_t **error );

/* Retrieves the UTF-8 encoded volume label
 * The size should include the end of string character
 * The volume label is only set if the link refers to a file on a local volume
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf8_volume_label(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     liblnk_error_t **error );

/* Retrieves the size of the UTF-16 encoded volume label
 * The size includes the end of string character
 * The volume label is only set if the link refers to a file on a local volume
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf16_volume_label_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     liblnk_error_t **error );

/* Retrieves the UTF-16 encoded volume label
 * The size should include the end of string character
 * The volume label is only set if the link refers to a file on a local volume
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf16_volume_label(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     liblnk_error_t **error );

/* Retrieves the size of the UTF-8 encoded local path
 * The size includes the end of string character
 * The local path is only set if the link refers to a file on a local volume
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf8_local_path_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     liblnk_error_t **error );

/* Retrieves the UTF-8 encoded local path
 * The size should include the end of string character
 * The local path is only set if the link refers to a file on a local volume
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf8_local_path(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     liblnk_error_t **error );

/* Retrieves the size of the UTF-16 encoded local path
 * The size includes the end of string character
 * The local path is only set if the link refers to a file on a local volume
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf16_local_path_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     liblnk_error_t **error );

/* Retrieves the UTF-16 encoded local path
 * The size should include the end of string character
 * The local path is only set if the link refers to a file on a local volume
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf16_local_path(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     liblnk_error_t **error );

/* Retrieves the size of the UTF-8 encoded network path
 * The size includes the end of string character
 * The network path is only set if the link refers to a file on a network share
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf8_network_path_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     liblnk_error_t **error );

/* Retrieves the UTF-8 encoded network path
 * The size should include the end of string character
 * The network path is only set if the link refers to a file on a network share
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf8_network_path(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     liblnk_error_t **error );

/* Retrieves the size of the UTF-16 encoded network path
 * The size includes the end of string character
 * The network path is only set if the link refers to a file on a network share
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf16_network_path_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     liblnk_error_t **error );

/* Retrieves the UTF-16 encoded network path
 * The size should include the end of string character
 * The network path is only set if the link refers to a file on a network share
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf16_network_path(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     liblnk_error_t **error );

/* Retrieves the size of the UTF-8 encoded description
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf8_description_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     liblnk_error_t **error );

/* Retrieves the UTF-8 encoded description
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf8_description(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     liblnk_error_t **error );

/* Retrieves the size of the UTF-16 encoded description
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf16_description_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     liblnk_error_t **error );

/* Retrieves the UTF-16 encoded description
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf16_description(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     liblnk_error_t **error );

/* Retrieves the size of the UTF-8 encoded relative path
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf8_relative_path_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     liblnk_error_t **error );

/* Retrieves the UTF-8 encoded relative path
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf8_relative_path(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     liblnk_error_t **error );

/* Retrieves the size of the UTF-16 encoded relative path
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf16_relative_path_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     liblnk_error_t **error );

/* Retrieves the UTF-16 encoded relative path
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf16_relative_path(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     liblnk_error_t **error );

/* Retrieves the size of the UTF-8 encoded working directory
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf8_working_directory_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     liblnk_error_t **error );

/* Retrieves the UTF-8 encoded working directory
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf8_working_directory(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     liblnk_error_t **error );

/* Retrieves the size of the UTF-16 encoded working directory
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf16_working_directory_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     liblnk_error_t **error );

/* Retrieves the UTF-16 encoded working directory
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf16_working_directory(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     liblnk_error_t **error );

/* Retrieves the size of the UTF-8 encoded command line arguments
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf8_command_line_arguments_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     liblnk_error_t **error );

/* Retrieves the UTF-8 encoded command line arguments
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf8_command_line_arguments(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     liblnk_error_t **error );

/* Retrieves the size of the UTF-16 encoded command line arguments
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf16_command_line_arguments_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     liblnk_error_t **error );

/* Retrieves the UTF-16 encoded command line arguments
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf16_command_line_arguments(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     liblnk_error_t **error );

/* Retrieves the size of the UTF-8 encoded icon location
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf8_icon_location_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     liblnk_error_t **error );

/* Retrieves the UTF-8 encoded icon location
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf8_icon_location(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     liblnk_error_t **error );

/* Retrieves the size of the UTF-16 encoded icon location
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf16_icon_location_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     liblnk_error_t **error );

/* Retrieves the UTF-16 encoded icon location
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf16_icon_location(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     liblnk_error_t **error );

/* Retrieves the size of the UTF-8 encoded environment variables location
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf8_environment_variables_location_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     liblnk_error_t **error );

/* Retrieves the UTF-8 encoded environment variables location
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf8_environment_variables_location(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     liblnk_error_t **error );

/* Retrieves the size of the UTF-16 encoded environment variables location
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf16_environment_variables_location_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     liblnk_error_t **error );

/* Retrieves the UTF-16 encoded environment variables location
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf16_environment_variables_location(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     liblnk_error_t **error );

/* Retrieves the link target identifier data size
 * The link target identifier contains a shell item (identifier) list
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_link_target_identifier_data_size(
     liblnk_file_t *file,
     size_t *data_size,
     liblnk_error_t **error );

/* Copies the link target identifier data to the buffer
 * The link target identifier contains a shell item (identifier) list
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_copy_link_target_identifier_data(
     liblnk_file_t *file,
     uint8_t *data,
     size_t data_size,
     liblnk_error_t **error );

/* -------------------------------------------------------------------------
 * Distributed link tracking data functions
 * ------------------------------------------------------------------------- */

/* Determines if the file contains distributed link tracking data
 * Returns 1 if the file contains such data, 0 if not or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_has_distributed_link_tracking_data(
     liblnk_file_t *file,
     liblnk_error_t **error );

/* Retrieves the size of the UTF-8 encoded local path
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf8_machine_identifier_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     liblnk_error_t **error );

/* Retrieves the UTF-8 encoded local path
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf8_machine_identifier(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     liblnk_error_t **error );

/* Retrieves the size of the UTF-16 encoded local path
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf16_machine_identifier_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     liblnk_error_t **error );

/* Retrieves the UTF-16 encoded local path
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_utf16_machine_identifier(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     liblnk_error_t **error );

/* Retrieves the droid volume identifier
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_droid_volume_identifier(
     liblnk_file_t *file,
     uint8_t *guid_data,
     size_t guid_data_size,
     liblnk_error_t **error );

/* Retrieves the droid file identifier
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_droid_file_identifier(
     liblnk_file_t *file,
     uint8_t *guid_data,
     size_t guid_data_size,
     liblnk_error_t **error );

/* Retrieves the birth droid volume identifier
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_birth_droid_volume_identifier(
     liblnk_file_t *file,
     uint8_t *guid_data,
     size_t guid_data_size,
     liblnk_error_t **error );

/* Retrieves the birth droid file identifier
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_get_birth_droid_file_identifier(
     liblnk_file_t *file,
     uint8_t *guid_data,
     size_t guid_data_size,
     liblnk_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBLNK_H ) */

