/*
 * The internal type definitions
 *
 * Copyright (c) 2009-2011, Joachim Metz <jbmetz@users.sourceforge.net>
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

#if !defined( _LIBLNK_INTERNAL_TYPES_H )
#define _LIBLNK_INTERNAL_TYPES_H

#include <common.h>
#include <types.h>

/* Define HAVE_LOCAL_LIBLNK for local use of liblnk
 * The definitions in <liblnk/types.h> are copied here
 * for local use of liblnk
 */
#if defined( HAVE_LOCAL_LIBLNK )

/* The following type definitions hide internal data structures
 */
typedef intptr_t liblnk_file_t;

#endif

#endif
