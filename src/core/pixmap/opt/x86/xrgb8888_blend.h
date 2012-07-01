/*!The Graphic 2D Box Library
 * 
 * GBox2 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 * 
 * GBox2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with GBox2; 
 * If not, see <a href="http://www.gnu.org/licenses/"> http://www.gnu.org/licenses/</a>
 * 
 * Copyright (C) 2009 - 2012, ruki All rights reserved.
 *
 * @author		ruki
 * @file		xrgb8888_blend.h
 *
 */
#ifndef G2_CORE_PIXMAP_OPT_x86_XRGB8888_BLEND_H
#define G2_CORE_PIXMAP_OPT_x86_XRGB8888_BLEND_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */

#if defined(TB_CONFIG_ASSEMBLER_GAS)
//# 	define g2_pixmap_xrgb8888_blend(d, s, a) 		g2_pixmap_xrgb8888_blend_asm(d, s, a)
//# 	define g2_pixmap_xrgb8888_blend2(d, hs, ls, a) 	g2_pixmap_xrgb8888_blend2_asm(d, hs, ls, a)
#endif

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */

#ifdef TB_CONFIG_ASSEMBLER_GAS
static __tb_inline__ tb_uint32_t g2_pixmap_xrgb8888_blend_asm(tb_uint32_t d, tb_uint32_t s, tb_byte_t a)
{
	__tb_asm__ __tb_volatile__
	(
		"mov %3, 			%%eax\n\t" 			// hs = (s >> 8) & 0x00ff00ff 
		"shr $8, 			%%eax\n\t"
		"and $0x00ff00ff, 	%%eax\n\t"
		"shr $8, 			%%ebx\n\t" 			// hd = (d >> 8) & 0x00ff00ff 
		"and $0x00ff00ff, 	%%ebx\n\t"
		"sub %%ebx, 		%%eax\n\t" 			// hd = (((a * (hs - hd)) >> 8) + hd) & 0x00ff00ff 
		"mul 				%%edx\n\t"
		"shr $8, 			%%eax\n\t"
		"add %%eax, 		%%ebx\n\t"
		"and $0x00ff00ff, 	%%ebx\n\t"
		"shl $8, 			%%ebx\n\t" 			// hd <<= 8 
		"mov %3, 			%%eax\n\t"
		"and $0x00ff00ff, 	%%eax\n\t" 			// ls = s & 0x00ff00ff 
		"and $0x00ff00ff, 	%%ecx\n\t" 			// ld = d & 0x00ff00ff 
		"sub %%ecx, 		%%eax\n\t" 			// ld = (((a * (ls - ld)) >> 8) + ld) & 0x00ff00ff 
		"mul 				%%edx\n\t"
		"shr $8, 			%%eax\n\t"
		"add %%eax, 		%%ecx\n\t"
		"and $0x00ff00ff, 	%%ecx\n\t"
		"or %%ecx, 			%%ebx\n\t" 			// d = hd | ld 
		: "=b"(d)
		: "b" (d), "c" (d), "r" (s), "d" (a)
		: "%eax"
	);

	// FIXME: d => eax, faster?
	return d;
}
static __tb_inline__ tb_uint32_t g2_pixmap_xrgb8888_blend2_asm(tb_uint32_t d, tb_uint32_t hs, tb_uint32_t ls, tb_byte_t a)
{
	__tb_asm__ __tb_volatile__
	(
		"shr $8, 			%%ebx\n\t" 			// hd = (d >> 8) & 0x00ff00ff 
		"and $0x00ff00ff, 	%%ebx\n\t"
		"sub %%ebx, 		%%eax\n\t" 			// hd = (((a * (hs - hd)) >> 8) + hd) & 0x00ff00ff 
		"mul 				%%edx\n\t"
		"shr $8, 			%%eax\n\t"
		"add %%eax, 		%%ebx\n\t"
		"and $0x00ff00ff, 	%%ebx\n\t"
		"shl $8, 			%%ebx\n\t" 			// hd <<= 8 
		"mov %4, 			%%eax\n\t"  		// ls 
		"and $0x00ff00ff, 	%%ecx\n\t" 			// ld = d & 0x00ff00ff 
		"sub %%ecx, 		%%eax\n\t" 			// ld = (((a * (ls - ld)) >> 8) + ld) & 0x00ff00ff 
		"mul 				%%edx\n\t"
		"shr $8, 			%%eax\n\t"
		"add %%eax, 		%%ecx\n\t"
		"and $0x00ff00ff, 	%%ecx\n\t"
		"or %%ecx, 			%%ebx\n\t" 			// d = hd | ld 
		: "=b"(d)
		: "b" (d), "c" (d), "a" (hs), "r" (ls), "d" (a)
	);

	return d;
}
#endif

#endif

