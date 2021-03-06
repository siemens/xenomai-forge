/*
 *   Generic arithmetic/conversion routines.
 *   Copyright &copy; 2005 Stelian Pop.
 *   Copyright &copy; 2005 Gilles Chanteperdrix.
 *
 *   Xenomai is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, Inc., 675 Mass Ave, Cambridge MA 02139,
 *   USA; either version 2 of the License, or (at your option) any later
 *   version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#ifndef _COBALT_KERNEL_ARITH_H
#define _COBALT_KERNEL_ARITH_H

#include <asm/byteorder.h>
#include <asm/div64.h>

#ifdef __BIG_ENDIAN
#define endianstruct { unsigned int _h; unsigned int _l; }
#else /* __LITTLE_ENDIAN */
#define endianstruct { unsigned int _l; unsigned int _h; }
#endif

#include <asm/xenomai/uapi/arith.h>

#endif /* _COBALT_KERNEL_ARITH_H */
