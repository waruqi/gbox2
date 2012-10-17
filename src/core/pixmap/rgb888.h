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
#include "rgb24.h"
#include "rgb32.h"

/* //////////////////////////////////////////////////////////////////////
 * inlines
 */

static g2_pixel_t g2_pixmap_rgb888_pixel(g2_color_t color);
static g2_color_t g2_pixmap_rgb888_color(g2_pixel_t pixel);
static __tb_inline__ tb_uint32_t g2_pixmap_rgb888_blend(tb_uint32_t d, tb_uint32_t s, tb_byte_t a)
{
	g2_color_t c;
	g2_color_t cs = g2_pixmap_rgb888_color(s & 0x00ffffff);
	g2_color_t cd = g2_pixmap_rgb888_color(d & 0x00ffffff);
	c.r = ((a * (cs.r - cd.r)) >> 8) + cd.r;
	c.g = ((a * (cs.g - cd.g)) >> 8) + cd.g;
	c.b = ((a * (cs.b - cd.b)) >> 8) + cd.b;
	return g2_pixmap_rgb888_pixel(c) & 0x00ffffff;
}
static __tb_inline__ tb_uint32_t g2_pixmap_rgb888_blend2(tb_uint32_t d, g2_color_t s, tb_byte_t a)
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
static __tb_inline__ g2_pixel_t g2_pixmap_rgb888_pixel(g2_color_t color)
{
	return g2_pixmap_rgb32_pixel(color) & 0x00ffffff;
}
static __tb_inline__ g2_color_t g2_pixmap_rgb888_color(g2_pixel_t pixel)
{
	return g2_pixmap_rgb32_color(pixel & 0x00ffffff);
}
static __tb_inline__ tb_void_t g2_pixmap_rgb888_pixel_set_la(tb_pointer_t data, tb_uint32_t pixel, tb_byte_t alpha)
{
	g2_bits_set_u24_le(data, g2_pixmap_rgb888_blend(g2_bits_get_u24_le(data), pixel, alpha));
}
static __tb_inline__ tb_void_t g2_pixmap_rgb888_pixel_set_ba(tb_pointer_t data, tb_uint32_t pixel, tb_byte_t alpha)
{
	g2_bits_set_u24_be(data, g2_pixmap_rgb888_blend(g2_bits_get_u24_be(data), pixel, alpha));
}
static __tb_inline__ tb_void_t g2_pixmap_rgb888_pixel_cpy_la(tb_pointer_t data, tb_cpointer_t pixel, tb_byte_t alpha)
{
	g2_bits_set_u24_le(data, g2_pixmap_rgb888_blend(g2_bits_get_u24_le(data), g2_bits_get_u24_le(pixel), alpha));
}
static __tb_inline__ tb_void_t g2_pixmap_rgb888_pixel_cpy_ba(tb_pointer_t data, tb_cpointer_t pixel, tb_byte_t alpha)
{
	g2_bits_set_u24_be(data, g2_pixmap_rgb888_blend(g2_bits_get_u24_be(data), g2_bits_get_u24_be(pixel), alpha));
}
static __tb_inline__ g2_color_t g2_pixmap_rgb888_color_get_l(tb_cpointer_t data)
{
	return g2_pixmap_rgb888_color(g2_bits_get_u24_le(data));
}
static __tb_inline__ g2_color_t g2_pixmap_rgb888_color_get_b(tb_cpointer_t data)
{
	return g2_pixmap_rgb888_color(g2_bits_get_u24_be(data));
}
static __tb_inline__ tb_void_t g2_pixmap_rgb888_color_set_lo(tb_pointer_t data, g2_color_t color)
{
	g2_bits_set_u24_le(data, g2_pixmap_rgb888_pixel(color));
}
static __tb_inline__ tb_void_t g2_pixmap_rgb888_color_set_bo(tb_pointer_t data, g2_color_t color)
{
	g2_bits_set_u24_be(data, g2_pixmap_rgb888_pixel(color));
}
static __tb_inline__ tb_void_t g2_pixmap_rgb888_color_set_la(tb_pointer_t data, g2_color_t color)
{
	g2_bits_set_u24_le(data, g2_pixmap_rgb888_blend(g2_bits_get_u24_le(data), g2_pixmap_rgb888_pixel(color), color.a));
}
static __tb_inline__ tb_void_t g2_pixmap_rgb888_color_set_ba(tb_pointer_t data, g2_color_t color)
{
	g2_bits_set_u24_be(data, g2_pixmap_rgb888_blend(g2_bits_get_u24_be(data), g2_pixmap_rgb888_pixel(color), color.a));
}
static __tb_inline__ tb_void_t g2_pixmap_rgb888_pixels_set_la(tb_pointer_t data, g2_pixel_t pixel, tb_size_t count, tb_byte_t alpha)
{
	tb_byte_t* 		p = (tb_byte_t*)data;
	tb_byte_t* 		e = p + count * 3;
	g2_color_t 		s = g2_pixmap_rgb888_color(pixel);
	while (p < e)
	{
		g2_bits_set_u24_le(p, g2_pixmap_rgb888_blend2(g2_bits_get_u24_le(p), s, alpha));
		p += 3;
	}
}
static __tb_inline__ tb_void_t g2_pixmap_rgb888_pixels_set_ba(tb_pointer_t data, g2_pixel_t pixel, tb_size_t count, tb_byte_t alpha)
{
	tb_byte_t* 		p = (tb_byte_t*)data;
	tb_byte_t* 		e = p + count * 3;
	g2_color_t 		s = g2_pixmap_rgb888_color(pixel);
	while (p < e)
	{
		g2_bits_set_u24_be(p, g2_pixmap_rgb888_blend2(g2_bits_get_u24_be(p), s, alpha));
		p += 3;
	}
}

/* ///////////////////////////////////////////////////////////////////////
 * globals
 */

static g2_pixmap_t const g_pixmap_lo_rgb888 =
{ 	
	"rgb888"
, 	24
, 	3
, 	G2_PIXFMT_RGB888 | G2_PIXFMT_LENDIAN
, 	g2_pixmap_rgb888_pixel
, 	g2_pixmap_rgb888_color
,	g2_pixmap_rgb24_pixel_get_l
,	g2_pixmap_rgb24_pixel_set_lo
, 	g2_pixmap_rgb24_pixel_cpy_o
,	g2_pixmap_rgb888_color_get_l
,	g2_pixmap_rgb888_color_set_lo
, 	g2_pixmap_rgb24_pixels_set_lo
};

static g2_pixmap_t const g_pixmap_bo_rgb888 =
{ 	
	"rgb888"
, 	24
, 	3
, 	G2_PIXFMT_RGB888 | G2_PIXFMT_BENDIAN
, 	g2_pixmap_rgb888_pixel
, 	g2_pixmap_rgb888_color
,	g2_pixmap_rgb24_pixel_get_b
,	g2_pixmap_rgb24_pixel_set_bo
, 	g2_pixmap_rgb24_pixel_cpy_o
,	g2_pixmap_rgb888_color_get_b
,	g2_pixmap_rgb888_color_set_bo
, 	g2_pixmap_rgb24_pixels_set_bo
};

static g2_pixmap_t const g_pixmap_la_rgb888 =
{ 	
	"rgb888"
, 	24
, 	3
, 	G2_PIXFMT_RGB888 | G2_PIXFMT_LENDIAN
, 	g2_pixmap_rgb888_pixel
, 	g2_pixmap_rgb888_color
,	g2_pixmap_rgb24_pixel_get_l
,	g2_pixmap_rgb888_pixel_set_la
, 	g2_pixmap_rgb888_pixel_cpy_la
,	g2_pixmap_rgb888_color_get_l
,	g2_pixmap_rgb888_color_set_la
, 	g2_pixmap_rgb888_pixels_set_la
};

static g2_pixmap_t const g_pixmap_ba_rgb888 =
{ 	
	"rgb888"
, 	24
, 	3
, 	G2_PIXFMT_RGB888 | G2_PIXFMT_BENDIAN
, 	g2_pixmap_rgb888_pixel
, 	g2_pixmap_rgb888_color
,	g2_pixmap_rgb24_pixel_get_b
,	g2_pixmap_rgb888_pixel_set_ba
, 	g2_pixmap_rgb888_pixel_cpy_ba
,	g2_pixmap_rgb888_color_get_b
,	g2_pixmap_rgb888_color_set_ba
, 	g2_pixmap_rgb888_pixels_set_ba
};

#endif

