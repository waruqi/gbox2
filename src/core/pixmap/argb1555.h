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
 * @file		argb1555.h
 *
 */
#ifndef G2_CORE_PIXMAP_ARGB1555_H
#define G2_CORE_PIXMAP_ARGB1555_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "xrgb1555.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static g2_pixel_t g2_pixmap_argb1555_pixel(g2_color_t color)
{
	return G2_ARGB_1555(color.a, color.r, color.g, color.b);
}
static g2_color_t g2_pixmap_argb1555_color(g2_pixel_t pixel)
{
	g2_color_t color;
	pixel &= 0xffff;
	color.r = G2_ARGB_1555_R(pixel);
	color.g = G2_ARGB_1555_G(pixel);
	color.b = G2_ARGB_1555_B(pixel);
	color.a = G2_ARGB_1555_A(pixel);
	return color;
}
static g2_pixel_t g2_pixmap_argb1555_pixel_get(tb_cpointer_t data)
{
	return g2_pixmap_xrgb1555_pixel_get(data);
}
static tb_void_t g2_pixmap_argb1555_pixel_set_o(tb_pointer_t data, g2_pixel_t pixel, tb_byte_t alpha)
{
	((tb_uint16_t*)data)[0] = (tb_uint16_t)(pixel & 0xffff);
}
static tb_void_t g2_pixmap_argb1555_pixel_set_a(tb_pointer_t data, g2_pixel_t pixel, tb_byte_t alpha)
{
	g2_pixmap_xrgb1555_pixel_set_a(data, pixel, alpha);
}
static tb_void_t g2_pixmap_argb1555_pixel_cpy_o(tb_pointer_t data, tb_cpointer_t pixel, tb_byte_t alpha)
{
	g2_pixmap_xrgb1555_pixel_cpy_o(data, pixel, 0);
}
static tb_void_t g2_pixmap_argb1555_pixel_cpy_a(tb_pointer_t data, tb_cpointer_t pixel, tb_byte_t alpha)
{
	g2_pixmap_xrgb1555_pixel_cpy_a(data, pixel, alpha);
}
static tb_void_t g2_pixmap_argb1555_color_set_o(tb_pointer_t data, g2_color_t color)
{
	g2_pixmap_argb1555_pixel_set_o(data, g2_pixmap_argb1555_pixel(color), 0);
}
static tb_void_t g2_pixmap_argb1555_color_set_a(tb_pointer_t data, g2_color_t color)
{
	g2_pixmap_xrgb1555_color_set_a(data, color);
}
static g2_color_t g2_pixmap_argb1555_color_get(tb_cpointer_t data)
{
	g2_color_t 	color;
	tb_uint16_t pixel = ((tb_uint16_t*)data)[0];
	color.r = G2_ARGB_1555_R(pixel);
	color.g = G2_ARGB_1555_G(pixel);
	color.b = G2_ARGB_1555_B(pixel);
	color.a = G2_ARGB_1555_A(pixel);
	return color;
}
static tb_void_t g2_pixmap_argb1555_pixels_set_o(tb_pointer_t data, g2_pixel_t pixel, tb_size_t count, tb_byte_t alpha)
{
	g2_pixmap_xrgb1555_pixels_set_o(data, pixel, count, 0);
}
static tb_void_t g2_pixmap_argb1555_pixels_set_a(tb_pointer_t data, g2_pixel_t pixel, tb_size_t count, tb_byte_t alpha)
{
	g2_pixmap_xrgb1555_pixels_set_a(data, pixel, count, alpha);
}

/* ///////////////////////////////////////////////////////////////////////
 * globals
 */

static g2_pixmap_t const g_pixmap_opaque_argb1555 =
{ 	
	"argb1555"
, 	16
, 	2
, 	G2_PIXFMT_ARGB1555
, 	g2_pixmap_argb1555_pixel
, 	g2_pixmap_argb1555_color
,	g2_pixmap_argb1555_pixel_get
,	g2_pixmap_argb1555_pixel_set_o
, 	g2_pixmap_argb1555_pixel_cpy_o
,	g2_pixmap_argb1555_color_get
,	g2_pixmap_argb1555_color_set_o
, 	g2_pixmap_argb1555_pixels_set_o
};

static g2_pixmap_t const g_pixmap_alpha_argb1555 =
{ 	
	"argb1555"
, 	16
, 	2
, 	G2_PIXFMT_ARGB1555
, 	g2_pixmap_argb1555_pixel
, 	g2_pixmap_argb1555_color
,	g2_pixmap_argb1555_pixel_get
,	g2_pixmap_argb1555_pixel_set_a
, 	g2_pixmap_argb1555_pixel_cpy_a
,	g2_pixmap_argb1555_color_get
,	g2_pixmap_argb1555_color_set_a
, 	g2_pixmap_argb1555_pixels_set_a
};

#endif

