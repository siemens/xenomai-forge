/*
 * Copyright (C) 2001-2013 Philippe Gerum <rpm@xenomai.org>.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
 */
#ifndef _COBALT_POWERPC_ASM_UAPI_SYSCALL_H
#define _COBALT_POWERPC_ASM_UAPI_SYSCALL_H

#define __xn_mux_code(shifted_id,op)	((op << 24)|shifted_id|(sc_nucleus_mux & 0xffff))
#define __xn_mux_shifted_id(id)		((id << 16) & 0xff0000)
#define __xn_mux_unshifted_id(id)	((id >> 16) & 0xff)

#endif /* !_COBALT_POWERPC_ASM_UAPI_SYSCALL_H */