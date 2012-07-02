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
 * @file		xrgb1555.h
 *
 */
#ifndef G2_CORE_PIXMAP_XRGB565_H
#define G2_CORE_PIXMAP_XRGB565_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#if defined(TB_ARCH_x86)
# 	include "opt/x86/xrgb1555_blend.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */

#ifndef g2_pixmap_xrgb1555_blend
# 	define g2_pixmap_xrgb1555_blend(d, s, a) 		g2_pixmap_xrgb1555_blend_inline(d, s, a)
#endif

#ifndef g2_pixmap_xrgb1555_blend2
# 	define g2_pixmap_xrgb1555_blend2(d, s, a) 	g2_pixmap_xrgb1555_blend2_inline(d, s, a)
#endif

/* ///////////////////////////////////////////////////////////////////////
 * inlines
 */

/* the alpha blend 
 *
 * c: 
 * 0000 0000 0000 0000 arrr rrgg gggb bbbb
 *
 * c | c << 16:
 * arrr rrgg gggb bbbb arrr rrgg gggb bbbb
 *
 * 0x3e07c1f:
 * 0000 0011 1110 0000 0111 1100 0001 1111
 *
 * d = (c | c << 16) & 0x3e07c1f:
 * 0000 00gg ggg0 0000 0rrr rr00 000b bbbb
 *
 * (d & 0xffff) | (d >> 16):
 * 0000 0000 0000 0000 0rrr rrgg gggb bbbb
 *
 * (s * a + d * (32 - a)) >> 5 => ((s - d) * a) >> 5 + d
 */
static __tb_inline__ tb_uint16_t g2_pixmap_xrgb1555_blend_inline(tb_uint32_t d, tb_uint32_t s, tb_byte_t a)
{
	// FIXME: s - d? overflow?
	s = (s | (s << 16)) & 0x3e07c1f;
	d = (d | (d << 16)) & 0x3e07c1f;
	d = ((((s - d) * a) >> 5) + d) & 0x3e07c1f;
	return (tb_uint16_t)((d & 0xffff) | (d >> 16) | 0x8000);
}
static __tb_inline__ tb_uint16_t g2_pixmap_xrgb1555_blend2_inline(tb_uint32_t d, tb_uint32_t s, tb_byte_t a)
{
	d = (d | (d << 16)) & 0x3e07c1f;
	d = ((((s - d) * a) >> 5) + d) & 0x3e07c1f;
	return (tb_uint16_t)((d & 0xffff) | (d >> 16) | 0x8000);
}
/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static g2_pixel_t g2_pixmap_xrgb1555_pixel(g2_color_t color)
{
	return G2_XRGB_1555(color.r, color.g, color.b);
}
static g2_color_t g2_pixmap_xrgb1555_color(g2_pixel_t pixel)
{
	g2_color_t color;
	pixel &= 0xffff;
	color.r = G2_XRGB_1555_R(pixel);
	color.g = G2_XRGB_1555_G(pixel);
	color.b = G2_XRGB_1555_B(pixel);
	color.a = 0xff;
	return color;
}
static g2_pixel_t g2_pixmap_xrgb1555_pixel_get(tb_cpointer_t data)
{
	return ((tb_uint16_t*)data)[0];
}
static tb_void_t g2_pixmap_xrgb1555_pixel_set_o(tb_pointer_t data, g2_pixel_t pixel, tb_byte_t alpha)
{
	((tb_uint16_t*)data)[0] = (tb_uint16_t)(pixel & 0xffff);
}
static tb_void_t g2_pixmap_xrgb1555_pixel_set_a(tb_pointer_t data, g2_pixel_t pixel, tb_byte_t alpha)
{
	((tb_uint16_t*)data)[0] = g2_pixmap_xrgb1555_blend(((tb_uint16_t*)data)[0], pixel, alpha >> 3);
}
static tb_void_t g2_pixmap_xrgb1555_pixel_cpy_o(tb_pointer_t data, tb_cpointer_t pixel, tb_byte_t alpha)
{
	((tb_uint16_t*)data)[0] = ((tb_uint16_t*)pixel)[0];
}
static tb_void_t g2_pixmap_xrgb1555_pixel_cpy_a(tb_pointer_t data, tb_cpointer_t pixel, tb_byte_t alpha)
{
	((tb_uint16_t*)data)[0] = g2_pixmap_xrgb1555_blend(((tb_uint16_t*)data)[0], ((tb_uint16_t*)pixel)[0], alpha >> 3);
}
static g2_color_t g2_pixmap_xrgb1555_color_get(tb_cpointer_t data)
{
	g2_color_t 	color;
	tb_uint16_t pixel = ((tb_uint16_t*)data)[0];
	color.r = G2_XRGB_1555_R(pixel);
	color.g = G2_XRGB_1555_G(pixel);
	color.b = G2_XRGB_1555_B(pixel);
	color.a = 0xff;
	return color;
}
static tb_void_t g2_pixmap_xrgb1555_color_set_o(tb_pointer_t data, g2_color_t color)
{
	g2_pixmap_xrgb1555_pixel_set_o(data, g2_pixmap_xrgb1555_pixel(color), 0);
}
static tb_void_t g2_pixmap_xrgb1555_color_set_a(tb_pointer_t data, g2_color_t color)
{
	((tb_uint16_t*)data)[0] = g2_pixmap_xrgb1555_blend(((tb_uint16_t*)data)[0], G2_XRGB_1555(color.r, color.g, color.b), color.a >> 3);
}
static tb_void_t g2_pixmap_xrgb1555_pixels_set_o(tb_pointer_t data, g2_pixel_t pixel, tb_size_t count, tb_byte_t alpha)
{
	tb_memset_u16(data, pixel, count);
}
static tb_void_t g2_pixmap_xrgb1555_pixels_set_a(tb_pointer_t data, g2_pixel_t pixel, tb_size_t count, tb_byte_t alpha)
{
	tb_size_t 		l = count & 0x3; count -= l; alpha >>= 3;
	tb_uint16_t* 	p = (tb_uint16_t*)data;
	tb_uint16_t* 	e = p + count;
	tb_uint32_t 	s = (pixel | (pixel << 16)) & 0x3e07c1f;
	while (p < e)
	{
		p[0] = g2_pixmap_xrgb1555_blend2(p[0], s, alpha);
		p[1] = g2_pixmap_xrgb1555_blend2(p[1], s, alpha);
		p[2] = g2_pixmap_xrgb1555_blend2(p[2], s, alpha);
		p[3] = g2_pixmap_xrgb1555_blend2(p[3], s, alpha);
		p += 4;
	}
	while (l--)
	{
		p[0] = g2_pixmap_xrgb1555_blend2(p[0], s, alpha);
		p++;
	}
}

/* ///////////////////////////////////////////////////////////////////////
 * globals
 */

static g2_pixmap_t const g_pixmap_opaque_xrgb1555 =
{ 	
	"xrgb1555"
, 	16
, 	2
, 	G2_PIXFMT_XRGB1555
, 	g2_pixmap_xrgb1555_pixel
, 	g2_pixmap_xrgb1555_color
,	g2_pixmap_xrgb1555_pixel_get
,	g2_pixmap_xrgb1555_pixel_set_o
, 	g2_pixmap_xrgb1555_pixel_cpy_o
,	g2_pixmap_xrgb1555_color_get
,	g2_pixmap_xrgb1555_color_set_o
, 	g2_pixmap_xrgb1555_pixels_set_o
};

static g2_pixmap_t const g_pixmap_alpha_xrgb1555 =
{ 	
	"xrgb1555"
, 	16
, 	2
, 	G2_PIXFMT_XRGB1555
, 	g2_pixmap_xrgb1555_pixel
, 	g2_pixmap_xrgb1555_color
,	g2_pixmap_xrgb1555_pixel_get
,	g2_pixmap_xrgb1555_pixel_set_a
, 	g2_pixmap_xrgb1555_pixel_cpy_a
,	g2_pixmap_xrgb1555_color_get
,	g2_pixmap_xrgb1555_color_set_a
, 	g2_pixmap_xrgb1555_pixels_set_a
};

#endif

