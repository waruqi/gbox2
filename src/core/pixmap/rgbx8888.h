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
 * @file		rgbx8888.h
 *
 */
#ifndef G2_CORE_PIXMAP_RGBX8888_H
#define G2_CORE_PIXMAP_RGBX8888_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "rgb32.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static __tb_inline__ g2_pixel_t g2_pixmap_rgbx8888_pixel(g2_color_t color)
{
	return ((g2_pixmap_rgb32_pixel(color) << 8) | 0xff);
}
static __tb_inline__ g2_color_t g2_pixmap_rgbx8888_color(g2_pixel_t pixel)
{
	return g2_pixmap_rgb32_color((pixel >> 8) | 0xff000000);
}
static __tb_inline__ tb_void_t g2_pixmap_rgbx8888_pixel_set_la(tb_pointer_t data, g2_pixel_t pixel, tb_byte_t alpha)
{
	g2_bits_set_u32_le(data, g2_pixmap_rgb32_blend(g2_bits_get_u32_le(data), pixel, alpha));
}
static __tb_inline__ tb_void_t g2_pixmap_rgbx8888_pixel_set_ba(tb_pointer_t data, g2_pixel_t pixel, tb_byte_t alpha)
{
	g2_bits_set_u32_be(data, g2_pixmap_rgb32_blend(g2_bits_get_u32_be(data), pixel, alpha));
}
static __tb_inline__ tb_void_t g2_pixmap_rgbx8888_pixel_cpy_la(tb_pointer_t data, tb_cpointer_t pixel, tb_byte_t alpha)
{
	g2_bits_set_u32_le(data, g2_pixmap_rgb32_blend(g2_bits_get_u32_le(data), g2_bits_get_u32_le(pixel), alpha));
}
static __tb_inline__ tb_void_t g2_pixmap_rgbx8888_pixel_cpy_ba(tb_pointer_t data, tb_cpointer_t pixel, tb_byte_t alpha)
{
	g2_bits_set_u32_be(data, g2_pixmap_rgb32_blend(g2_bits_get_u32_be(data), g2_bits_get_u32_be(pixel), alpha));
}
static __tb_inline__ tb_void_t g2_pixmap_rgbx8888_color_set_lo(tb_pointer_t data, g2_color_t color)
{
	g2_bits_set_u32_le(data, g2_pixmap_rgbx8888_pixel(color));
}
static __tb_inline__ tb_void_t g2_pixmap_rgbx8888_color_set_bo(tb_pointer_t data, g2_color_t color)
{
	g2_bits_set_u32_be(data, g2_pixmap_rgbx8888_pixel(color));
}
static __tb_inline__ tb_void_t g2_pixmap_rgbx8888_color_set_la(tb_pointer_t data, g2_color_t color)
{
	g2_bits_set_u32_le(data, g2_pixmap_rgb32_blend(g2_bits_get_u32_le(data), g2_pixmap_rgbx8888_pixel(color), color.a));
}
static __tb_inline__ tb_void_t g2_pixmap_rgbx8888_color_set_ba(tb_pointer_t data, g2_color_t color)
{
	g2_bits_set_u32_be(data, g2_pixmap_rgb32_blend(g2_bits_get_u32_be(data), g2_pixmap_rgbx8888_pixel(color), color.a));
}
static __tb_inline__ g2_color_t g2_pixmap_rgbx8888_color_get_l(tb_cpointer_t data)
{
	return g2_pixmap_rgbx8888_color(g2_bits_get_u32_le(data));
}
static __tb_inline__ g2_color_t g2_pixmap_rgbx8888_color_get_b(tb_cpointer_t data)
{
	return g2_pixmap_rgbx8888_color(g2_bits_get_u32_be(data));
}
static __tb_inline__ tb_void_t g2_pixmap_rgbx8888_pixels_set_la(tb_pointer_t data, g2_pixel_t pixel, tb_size_t count, tb_byte_t alpha)
{
	tb_size_t 		l = count & 0x3; count -= l;
	tb_uint32_t* 	p = (tb_uint32_t*)data;
	tb_uint32_t* 	e = p + count;
	tb_uint32_t 	hs = (pixel >> 8) & 0x00ff00ff;
	tb_uint32_t 	ls = pixel & 0x00ff00ff;
	while (p < e)
	{
		g2_bits_set_u32_le(&p[0], g2_pixmap_rgb32_blend2(g2_bits_get_u32_le(&p[0]), hs, ls, alpha));
		g2_bits_set_u32_le(&p[1], g2_pixmap_rgb32_blend2(g2_bits_get_u32_le(&p[1]), hs, ls, alpha));
		g2_bits_set_u32_le(&p[2], g2_pixmap_rgb32_blend2(g2_bits_get_u32_le(&p[2]), hs, ls, alpha));
		g2_bits_set_u32_le(&p[3], g2_pixmap_rgb32_blend2(g2_bits_get_u32_le(&p[3]), hs, ls, alpha));
		p += 4;
	}
	while (l--)
	{
		g2_bits_set_u32_le(&p[0], g2_pixmap_rgb32_blend2(g2_bits_get_u32_le(&p[0]), hs, ls, alpha));
		p++;
	}
}
static __tb_inline__ tb_void_t g2_pixmap_rgbx8888_pixels_set_ba(tb_pointer_t data, g2_pixel_t pixel, tb_size_t count, tb_byte_t alpha)
{
	tb_size_t 		l = count & 0x3; count -= l;
	tb_uint32_t* 	p = (tb_uint32_t*)data;
	tb_uint32_t* 	e = p + count;
	tb_uint32_t 	hs = (pixel >> 8) & 0x00ff00ff;
	tb_uint32_t 	ls = pixel & 0x00ff00ff;
	while (p < e)
	{
		g2_bits_set_u32_be(&p[0], g2_pixmap_rgb32_blend2(g2_bits_get_u32_be(&p[0]), hs, ls, alpha));
		g2_bits_set_u32_be(&p[1], g2_pixmap_rgb32_blend2(g2_bits_get_u32_be(&p[1]), hs, ls, alpha));
		g2_bits_set_u32_be(&p[2], g2_pixmap_rgb32_blend2(g2_bits_get_u32_be(&p[2]), hs, ls, alpha));
		g2_bits_set_u32_be(&p[3], g2_pixmap_rgb32_blend2(g2_bits_get_u32_be(&p[3]), hs, ls, alpha));
		p += 4;
	}
	while (l--)
	{
		g2_bits_set_u32_be(&p[0], g2_pixmap_rgb32_blend2(g2_bits_get_u32_be(&p[0]), hs, ls, alpha));
		p++;
	}
}
/* ///////////////////////////////////////////////////////////////////////
 * globals
 */

static g2_pixmap_t const g_pixmap_lo_rgbx8888 =
{ 	
	"rgbx8888"
, 	32
, 	4
, 	G2_PIXFMT_RGBX8888 | G2_PIXFMT_LENDIAN
, 	g2_pixmap_rgbx8888_pixel
, 	g2_pixmap_rgbx8888_color
,	g2_pixmap_rgb32_pixel_get_l
,	g2_pixmap_rgb32_pixel_set_lo
, 	g2_pixmap_rgb32_pixel_cpy_o
,	g2_pixmap_rgbx8888_color_get_l
,	g2_pixmap_rgbx8888_color_set_lo
, 	g2_pixmap_rgb32_pixels_set_lo
};

static g2_pixmap_t const g_pixmap_bo_rgbx8888 =
{ 	
	"rgbx8888"
, 	32
, 	4
, 	G2_PIXFMT_RGBX8888 | G2_PIXFMT_BENDIAN
, 	g2_pixmap_rgbx8888_pixel
, 	g2_pixmap_rgbx8888_color
,	g2_pixmap_rgb32_pixel_get_b
,	g2_pixmap_rgb32_pixel_set_bo
, 	g2_pixmap_rgb32_pixel_cpy_o
,	g2_pixmap_rgbx8888_color_get_b
,	g2_pixmap_rgbx8888_color_set_bo
, 	g2_pixmap_rgb32_pixels_set_bo
};

static g2_pixmap_t const g_pixmap_la_rgbx8888 =
{ 	
	"rgbx8888"
, 	32
, 	4
, 	G2_PIXFMT_RGBX8888 | G2_PIXFMT_LENDIAN
, 	g2_pixmap_rgbx8888_pixel
, 	g2_pixmap_rgbx8888_color
,	g2_pixmap_rgb32_pixel_get_l
,	g2_pixmap_rgbx8888_pixel_set_la
, 	g2_pixmap_rgbx8888_pixel_cpy_la
,	g2_pixmap_rgbx8888_color_get_l
,	g2_pixmap_rgbx8888_color_set_la
, 	g2_pixmap_rgbx8888_pixels_set_la
};

static g2_pixmap_t const g_pixmap_ba_rgbx8888 =
{ 	
	"rgbx8888"
, 	32
, 	4
, 	G2_PIXFMT_RGBX8888 | G2_PIXFMT_BENDIAN
, 	g2_pixmap_rgbx8888_pixel
, 	g2_pixmap_rgbx8888_color
,	g2_pixmap_rgb32_pixel_get_b
,	g2_pixmap_rgbx8888_pixel_set_ba
, 	g2_pixmap_rgbx8888_pixel_cpy_ba
,	g2_pixmap_rgbx8888_color_get_b
,	g2_pixmap_rgbx8888_color_set_ba
, 	g2_pixmap_rgbx8888_pixels_set_ba
};


#endif

