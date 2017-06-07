/* include/qb/qbconfig.h.  Generated from qbconfig.h.in by configure.  */
/*
 * Copyright (C) 2011 Red Hat, Inc.
 *
 * All rights reserved.
 *
 * Author: Angus Salkeld <asalkeld@redhat.com>
 *
 * libqb is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * libqb is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libqb.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QB_CONFIG_H_DEFINED
#define QB_CONFIG_H_DEFINED

#include <qb/qbdefs.h>  /* QB_PP_STRINGIFY */

/* need atomic memory barrier */
#define QB_ATOMIC_OP_MEMORY_BARRIER_NEEDED 1

/* Enabling code using __attribute__((section)) */
#define QB_HAVE_ATTRIBUTE_SECTION 1

/* versioning info: MAJOR, MINOR, MICRO, and REST components */
#define QB_VER_MAJOR 1
#define QB_VER_MINOR 0
#define QB_VER_MICRO 1
#define QB_VER_REST ""

#define QB_VER_STR   \
	QB_PP_STRINGIFY(QB_VER_MAJOR) \
	"." \
	QB_PP_STRINGIFY(QB_VER_MINOR) \
	"." \
	QB_PP_STRINGIFY(QB_VER_MICRO) \
	QB_VER_REST

#endif /* QB_CONFIG_H_DEFINED */
