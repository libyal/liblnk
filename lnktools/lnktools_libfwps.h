/*
 * The libfwps header wrapper
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

#if !defined( _LNKTOOLS_LIBFWPS_H )
#define _LNKTOOLS_LIBFWPS_H

#include <common.h>

/* Define HAVE_LOCAL_LIBFWPS for local use of libfwps
 */
#if defined( HAVE_LOCAL_LIBFWPS )

#include <libfwps_definitions.h>
#include <libfwps_format_class_identifier.h>
#include <libfwps_property_identifier.h>
#include <libfwps_record.h>
#include <libfwps_set.h>
#include <libfwps_store.h>
#include <libfwps_types.h>

#else

/* If libtool DLL support is enabled set LIBFWPS_DLL_IMPORT
 * before including libfwps.h
 */
#if defined( _WIN32 ) && defined( DLL_IMPORT )
#define LIBFWPS_DLL_IMPORT
#endif

#include <libfwps.h>

#endif /* defined( HAVE_LOCAL_LIBFWPS ) */

#endif /* !defined( _LNKTOOLS_LIBFWPS_H ) */

