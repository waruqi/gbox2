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
 * @file		rgb888.h
 *
 */
#ifndef G2_CORE_PIXMAP_RGB888_H
#define G2_CORE_PIXMAP_RGB888_H

/* //////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////
 * macros
 */

#ifndef g2_pixmap_rgb888_blend
# 	define g2_pixmap_rgb888_blend(d, s, a) 		g2_pixmap_rgb888_blend_inline(d, s, a)
#endif

#ifndef g2_pixmap_rgb888_blend2
# 	define g2_pixmap_rgb888_blend2(d, s, a) 	g2_pixmap_rgb888_blend2_inline(d, s, a)
#endif

/* //////////////////////////////////////////////////////////////////////
 * inlines
 */

static g2_pixel_t g2_pixmap_rgb888_pixel(g2_color_t color);
static g2_color_t g2_pixmap_rgb888_color(g2_pixel_t pixel);
static __tb_inline__ tb_uint32_t g2_pixmap_rgb888_blend_inline(tb_uint32_t d, tb_uint32_t s, tb_byte_t a)
{
	g2_color_t c;
	g2_color_t cs = g2_pixmap_rgb888_color(s & 0x00ffffff);
	g2_color_t cd = g2_pixmap_rgb888_color(d & 0x00ffffff);
	c.r = ((a * (cs.r - cd.r)) >> 8) + cd.r;
	c.g = ((a * (cs.g - cd.g)) >> 8) + cd.g;
	c.b = ((a * (cs.b - cd.b)) >> 8) + cd.b;
	return g2_pixmap_rgb888_pixel(c) & 0x00ffffff;
}
static __tb_inline__ tb_uint32_t g2_pixmap_rgb888_blend2_inline(tb_uint32_t d, g2_color_t s, tb_byte_t a)
{
	g2_color_t c;
	g2_color_t cd = g2_pixmap_rgb888_color(d & 0x00ffffff);
	c.r = ((a * (s.r - cd.r)) >> 8) + cd.r;
	c.g = ((a * (s.g - cd.g)) >> 8) + cd.g;
	c.b = ((a * (s.b - cd.b)) >> 8) + cd.b;
	return g2_pixmap_rgb888_pixel(c) & 0x00ffffff;
}

/* //////////////////////////////////////////////////////////////////////
 * interfaces
 */
static g2_pixel_t g2_pixmap_rgb888_pixel(g2_color_t color)
{
	union __g2_c2p_t
	{
		g2_color_t c;
		g2_pixel_t p;

	}c2p;
	c2p.c = color;
	return c2p.p;
}
static g2_color_t g2_pixmap_rgb888_color(g2_pixel_t pixel)
{
	union __g2_p2c_t
	{
		g2_color_t c;
		g2_pixel_t p;

	}p2c;
	p2c.p = pixel;
	return p2c.c;
}
static g2_pixel_t g2_pixmap_rgb888_pixel_get(tb_cpointer_t data)
{
	return tb_bits_get_u24_be((tb_byte_t const*)data);
}
static tb_void_t g2_pixmap_rgb888_pixel_set_o(tb_pointer_t data, g2_pixel_t pixel, tb_byte_t alpha)
{
	tb_bits_set_u24_be((tb_byte_t*)data, pixel);
}
static tb_void_t g2_pixmap_rgb888_pixel_set_a(tb_pointer_t data, tb_uint32_t pixel, tb_byte_t alpha)
{
	pixel = g2_pixmap_rgb888_blend(tb_bits_get_u24_be((tb_byte_t const*)data), pixel, alpha);
	tb_bits_set_u24_be((tb_byte_t*)data, pixel);
}
static tb_void_t g2_pixmap_rgb888_pixel_cpy_o(tb_pointer_t data, tb_cpointer_t pixel, tb_byte_t alpha)
{
	((tb_byte_t*)data)[0] = ((tb_byte_t const*)pixel)[0];
	((tb_byte_t*)data)[1] = ((tb_byte_t const*)pixel)[1];
	((tb_byte_t*)data)[2] = ((tb_byte_t const*)pixel)[2];
}
static tb_void_t g2_pixmap_rgb888_pixel_cpy_a(tb_pointer_t data, tb_cpointer_t pixel, tb_byte_t alpha)
{
	tb_uint32_t d = g2_pixmap_rgb888_blend(tb_bits_get_u24_be((tb_byte_t const*)data), tb_bits_get_u24_be((tb_byte_t const*)pixel), alpha);
	tb_bits_set_u24_be((tb_byte_t*)data, d);
}
static g2_color_t g2_pixmap_rgb888_color_get(tb_cpointer_t data)
{
	g2_color_t 	color;
	tb_uint32_t pixel = tb_bits_get_u24_be((tb_byte_t const*)data);
	color.r = G2_RGB_888_R(pixel);
	color.g = G2_RGB_888_G(pixel);
	color.b = G2_RGB_888_B(pixel);
	color.a = 0xff;
	return color;
}
static tb_void_t g2_pixmap_rgb888_color_set_o(tb_pointer_t data, g2_color_t color)
{
	g2_pixmap_rgb888_pixel_set_o(data, g2_pixmap_rgb888_pixel(color), 0);
}
static tb_void_t g2_pixmap_rgb888_color_set_a(tb_pointer_t data, g2_color_t color)
{
	tb_uint32_t d = g2_pixmap_rgb888_blend(tb_bits_get_u24_be((tb_byte_t const*)data), G2_RGB_888(color.r, color.g, color.b), color.a);
	tb_bits_set_u24_be((tb_byte_t*)data, d);
}
static tb_void_t g2_pixmap_rgb888_pixels_set_o(tb_pointer_t data, g2_pixel_t pixel, tb_size_t count, tb_byte_t alpha)
{
	tb_memset_u24(data, pixel, count);
}
static tb_void_t g2_pixmap_rgb888_pixels_set_a(tb_pointer_t data, g2_pixel_t pixel, tb_size_t count, tb_byte_t alpha)
{
	tb_uint32_t 	d;
	tb_byte_t* 		p = (tb_byte_t*)data;
	tb_byte_t* 		e = p + count * 3;
	g2_color_t 		s = g2_pixmap_rgb888_color(pixel & 0x00ffffff);
	alpha >>= 2;
	while (p < e)
	{
		d = g2_pixmap_rgb888_blend2(tb_bits_get_u24_be((tb_byte_t const*)p), s, alpha);
		tb_bits_set_u24_be(p, d);
		p += 3;
	}
}

#endif

