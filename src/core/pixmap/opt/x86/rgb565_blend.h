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
 * @file		rgb565_blend.h
 *
 */
#ifndef G2_CORE_PIXMAP_OPT_x86_RGB565_BLEND_H
#define G2_CORE_PIXMAP_OPT_x86_RGB565_BLEND_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */

#if defined(TB_CONFIG_ASSEMBLER_GAS)
//# 	define g2_pixmap_rgb565_blend(d, s, a) 		g2_pixmap_rgb565_blend_asm(d, s, a)
//# 	define g2_pixmap_rgb565_blend2(d, s, a) 	g2_pixmap_rgb565_blend2_asm(d, s, a)
#endif

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */

#ifdef TB_CONFIG_ASSEMBLER_GAS
static __tb_inline__ tb_uint16_t g2_pixmap_rgb565_blend_asm(tb_uint32_t d, tb_uint32_t s, tb_byte_t a)
{
	__tb_asm__ __tb_volatile__
	(
		"mov %%ax, 			%%cx\n\t"  		// s = (s | (s << 16)) & 0x7e0f81f
		"shl $16, 			%%eax\n\t"
		"mov %%cx, 			%%ax\n\t"
		"and $0x7e0f81f, 	%%eax\n\t"
		"mov %%bx, 			%%cx\n\t" 		// d = (d | (d << 16)) & 0x7e0f81f
		"shl $16, 			%%ebx\n\t"
		"mov %%cx, 			%%bx\n\t"
		"and $0x7e0f81f, 	%%ebx\n\t"
		"sub %%ebx, 		%%eax\n\t" 		// s = ((((s - d) * a) >> 5) + d) & 0x7e0f81f;
		"mul 				%%edx\n\t"
		"shr $5, 			%%eax\n\t"
		"add %%ebx, 		%%eax\n\t"
		"and $0x7e0f81f, 	%%eax\n\t"
		"mov %%eax, 		%%ebx\n\t" 		// d = ((s & 0xffff) | (s >> 16))
		"shr $16, 			%%ebx\n\t"
		"or %%ax, 			%%bx\n\t"
		: "=b"(d)
		: "b" (d), "a" (s), "d" (a)
		: "%ecx"
	);

	// FIXME: d => eax, faster?
	return d;
}
static __tb_inline__ tb_uint16_t g2_pixmap_rgb565_blend2_asm(tb_uint32_t d, tb_uint32_t s, tb_byte_t a)
{
	__tb_asm__ __tb_volatile__
	(
		"mov %%bx, 			%%cx\n\t" 		// d = (d | (d << 16)) & 0x7e0f81f
		"shl $16, 			%%ebx\n\t"
		"mov %%cx, 			%%bx\n\t"
		"and $0x7e0f81f, 	%%ebx\n\t"
		"sub %%ebx, 		%%eax\n\t" 		// s = ((((s - d) * a) >> 5) + d) & 0x7e0f81f
		"mul 				%%edx\n\t"
		"shr $5, 			%%eax\n\t"
		"add %%ebx, 		%%eax\n\t"
		"and $0x7e0f81f, 	%%eax\n\t"
		"mov %%eax, 		%%ebx\n\t" 		// d = ((s & 0xffff) | (s >> 16))
		"shr $16, 			%%ebx\n\t"
		"or %%ax, 			%%bx\n\t"
		: "=b"(d)
		: "b" (d), "a" (s), "d" (a)
		: "%ecx"
	);

	return d;
}
#endif

#endif

