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
 * @file		xrgb8888.h
 *
 */
#ifndef G2_CORE_PIXMAP_XXRGB88888_H
#define G2_CORE_PIXMAP_XXRGB88888_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "rgb32.h"
#if defined(TB_ARCH_x86)
# 	include "opt/x86/xrgb8888_blend.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */

#ifndef g2_pixmap_xrgb8888_blend
# 	define g2_pixmap_xrgb8888_blend(d, s, a) 		g2_pixmap_xrgb8888_blend_inline(d, s, a)
#endif

#ifndef g2_pixmap_xrgb8888_blend2
# 	define g2_pixmap_xrgb8888_blend2(d, hs, ls, a) 	g2_pixmap_xrgb8888_blend2_inline(d, hs, ls, a)
#endif

/* ///////////////////////////////////////////////////////////////////////
 * inlines
 */

static __tb_inline__ tb_uint32_t g2_pixmap_xrgb8888_blend_inline(tb_uint32_t d, tb_uint32_t s, tb_byte_t a)
{
	tb_uint32_t hs = (s >> 8) & 0x00ff00ff;
	tb_uint32_t hd = (d >> 8) & 0x00ff00ff;
	tb_uint32_t ls = s & 0x00ff00ff;
	tb_uint32_t ld = d & 0x00ff00ff;
	hd = (((a * (hs - hd)) >> 8) + hd) & 0x00ff00ff;
	ld = (((a * (ls - ld)) >> 8) + ld) & 0x00ff00ff;
	return (hd << 8) | ld;
}
static __tb_inline__ tb_uint32_t g2_pixmap_xrgb8888_blend2_inline(tb_uint32_t d, tb_uint32_t hs, tb_uint32_t ls, tb_byte_t a)
{
	tb_uint32_t hd = (d >> 8) & 0x00ff00ff;
	tb_uint32_t ld = d & 0x00ff00ff;
	hd = (((a * (hs - hd)) >> 8) + hd) & 0x00ff00ff;
	ld = (((a * (ls - ld)) >> 8) + ld) & 0x00ff00ff;
	return (hd << 8) | ld;
}

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static g2_pixel_t g2_pixmap_xrgb8888_pixel(g2_color_t color)
{
	union __g2_c2p_t
	{
		g2_color_t c;
		g2_pixel_t p;

	}c2p;
	c2p.c = color;
	return c2p.p;
}
static g2_color_t g2_pixmap_xrgb8888_color(g2_pixel_t pixel)
{
	union __g2_p2c_t
	{
		g2_color_t c;
		g2_pixel_t p;

	}p2c;
	p2c.p = pixel;
	return p2c.c;
}
static tb_void_t g2_pixmap_xrgb8888_pixel_set_la(tb_pointer_t data, g2_pixel_t pixel, tb_byte_t alpha)
{
	g2_bits_set_u32_le(data, g2_pixmap_xrgb8888_blend(g2_bits_get_u32_le(data), pixel, alpha));
}
static tb_void_t g2_pixmap_xrgb8888_pixel_set_ba(tb_pointer_t data, g2_pixel_t pixel, tb_byte_t alpha)
{
	g2_bits_set_u32_be(data, g2_pixmap_xrgb8888_blend(g2_bits_get_u32_be(data), pixel, alpha));
}
static tb_void_t g2_pixmap_xrgb8888_pixel_cpy_la(tb_pointer_t data, tb_cpointer_t pixel, tb_byte_t alpha)
{
	g2_bits_set_u32_le(data, g2_pixmap_xrgb8888_blend(g2_bits_get_u32_le(data), g2_bits_get_u32_le(pixel), alpha));
}
static tb_void_t g2_pixmap_xrgb8888_pixel_cpy_ba(tb_pointer_t data, tb_cpointer_t pixel, tb_byte_t alpha)
{
	g2_bits_set_u32_be(data, g2_pixmap_xrgb8888_blend(g2_bits_get_u32_be(data), g2_bits_get_u32_be(pixel), alpha));
}
static tb_void_t g2_pixmap_xrgb8888_color_set_lo(tb_pointer_t data, g2_color_t color)
{
	g2_bits_set_u32_le(data, g2_pixmap_xrgb8888_pixel(color));
}
static tb_void_t g2_pixmap_xrgb8888_color_set_bo(tb_pointer_t data, g2_color_t color)
{
	g2_bits_set_u32_be(data, g2_pixmap_xrgb8888_pixel(color));
}
static tb_void_t g2_pixmap_xrgb8888_color_set_la(tb_pointer_t data, g2_color_t color)
{
	g2_bits_set_u32_le(data, g2_pixmap_xrgb8888_blend(g2_bits_get_u32_le(data), G2_XRGB_8888(color.r, color.g, color.b), color.a));
}
static tb_void_t g2_pixmap_xrgb8888_color_set_ba(tb_pointer_t data, g2_color_t color)
{
	g2_bits_set_u32_be(data, g2_pixmap_xrgb8888_blend(g2_bits_get_u32_be(data), G2_XRGB_8888(color.r, color.g, color.b), color.a));
}
static g2_color_t g2_pixmap_xrgb8888_color_get_l(tb_cpointer_t data)
{
	return g2_pixmap_xrgb8888_color(g2_bits_get_u32_le(data));
}
static g2_color_t g2_pixmap_xrgb8888_color_get_b(tb_cpointer_t data)
{
	return g2_pixmap_xrgb8888_color(g2_bits_get_u32_be(data));
}
static tb_void_t g2_pixmap_xrgb8888_pixels_set_la(tb_pointer_t data, g2_pixel_t pixel, tb_size_t count, tb_byte_t alpha)
{
	tb_size_t 		l = count & 0x3; count -= l;
	tb_uint32_t* 	p = (tb_uint32_t*)data;
	tb_uint32_t* 	e = p + count;
	tb_uint32_t 	hs = (pixel >> 8) & 0x00ff00ff;
	tb_uint32_t 	ls = pixel & 0x00ff00ff;
	while (p < e)
	{
		g2_bits_set_u32_le(&p[0], g2_pixmap_xrgb8888_blend2(g2_bits_get_u32_le(&p[0]), hs, ls, alpha));
		g2_bits_set_u32_le(&p[1], g2_pixmap_xrgb8888_blend2(g2_bits_get_u32_le(&p[1]), hs, ls, alpha));
		g2_bits_set_u32_le(&p[2], g2_pixmap_xrgb8888_blend2(g2_bits_get_u32_le(&p[2]), hs, ls, alpha));
		g2_bits_set_u32_le(&p[3], g2_pixmap_xrgb8888_blend2(g2_bits_get_u32_le(&p[3]), hs, ls, alpha));
		p += 4;
	}
	while (l--)
	{
		g2_bits_set_u32_le(&p[0], g2_pixmap_xrgb8888_blend2(g2_bits_get_u32_le(&p[0]), hs, ls, alpha));
		p++;
	}
}
static tb_void_t g2_pixmap_xrgb8888_pixels_set_ba(tb_pointer_t data, g2_pixel_t pixel, tb_size_t count, tb_byte_t alpha)
{
	tb_size_t 		l = count & 0x3; count -= l;
	tb_uint32_t* 	p = (tb_uint32_t*)data;
	tb_uint32_t* 	e = p + count;
	tb_uint32_t 	hs = (pixel >> 8) & 0x00ff00ff;
	tb_uint32_t 	ls = pixel & 0x00ff00ff;
	while (p < e)
	{
		g2_bits_set_u32_be(&p[0], g2_pixmap_xrgb8888_blend2(g2_bits_get_u32_be(&p[0]), hs, ls, alpha));
		g2_bits_set_u32_be(&p[1], g2_pixmap_xrgb8888_blend2(g2_bits_get_u32_be(&p[1]), hs, ls, alpha));
		g2_bits_set_u32_be(&p[2], g2_pixmap_xrgb8888_blend2(g2_bits_get_u32_be(&p[2]), hs, ls, alpha));
		g2_bits_set_u32_be(&p[3], g2_pixmap_xrgb8888_blend2(g2_bits_get_u32_be(&p[3]), hs, ls, alpha));
		p += 4;
	}
	while (l--)
	{
		g2_bits_set_u32_be(&p[0], g2_pixmap_xrgb8888_blend2(g2_bits_get_u32_be(&p[0]), hs, ls, alpha));
		p++;
	}
}
/* ///////////////////////////////////////////////////////////////////////
 * globals
 */

static g2_pixmap_t const g_pixmap_lo_xrgb8888 =
{ 	
	"xrgb8888"
, 	32
, 	4
, 	G2_PIXFMT_XRGB8888
, 	g2_pixmap_xrgb8888_pixel
, 	g2_pixmap_xrgb8888_color
,	g2_pixmap_rgb32_pixel_get_l
,	g2_pixmap_rgb32_pixel_set_lo
, 	g2_pixmap_rgb32_pixel_cpy_o
,	g2_pixmap_xrgb8888_color_get_l
,	g2_pixmap_xrgb8888_color_set_lo
, 	g2_pixmap_rgb32_pixels_set_lo
};

static g2_pixmap_t const g_pixmap_bo_xrgb8888 =
{ 	
	"xrgb8888"
, 	32
, 	4
, 	G2_PIXFMT_XRGB8888
, 	g2_pixmap_xrgb8888_pixel
, 	g2_pixmap_xrgb8888_color
,	g2_pixmap_rgb32_pixel_get_b
,	g2_pixmap_rgb32_pixel_set_bo
, 	g2_pixmap_rgb32_pixel_cpy_o
,	g2_pixmap_xrgb8888_color_get_b
,	g2_pixmap_xrgb8888_color_set_bo
, 	g2_pixmap_rgb32_pixels_set_bo
};

static g2_pixmap_t const g_pixmap_la_xrgb8888 =
{ 	
	"xrgb8888"
, 	32
, 	4
, 	G2_PIXFMT_XRGB8888
, 	g2_pixmap_xrgb8888_pixel
, 	g2_pixmap_xrgb8888_color
,	g2_pixmap_rgb32_pixel_get_l
,	g2_pixmap_xrgb8888_pixel_set_la
, 	g2_pixmap_xrgb8888_pixel_cpy_la
,	g2_pixmap_xrgb8888_color_get_l
,	g2_pixmap_xrgb8888_color_set_la
, 	g2_pixmap_xrgb8888_pixels_set_la
};

static g2_pixmap_t const g_pixmap_ba_xrgb8888 =
{ 	
	"xrgb8888"
, 	32
, 	4
, 	G2_PIXFMT_XRGB8888
, 	g2_pixmap_xrgb8888_pixel
, 	g2_pixmap_xrgb8888_color
,	g2_pixmap_rgb32_pixel_get_b
,	g2_pixmap_xrgb8888_pixel_set_ba
, 	g2_pixmap_xrgb8888_pixel_cpy_ba
,	g2_pixmap_xrgb8888_color_get_b
,	g2_pixmap_xrgb8888_color_set_ba
, 	g2_pixmap_xrgb8888_pixels_set_ba
};


#endif

