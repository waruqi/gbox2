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
#include "rgb16.h"
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
static tb_void_t g2_pixmap_argb1555_color_set_lo(tb_pointer_t data, g2_color_t color)
{
	g2_bits_set_u16_le(data, g2_pixmap_argb1555_pixel(color), 0);
}
static tb_void_t g2_pixmap_argb1555_color_set_bo(tb_pointer_t data, g2_color_t color)
{
	g2_bits_set_u16_be(data, g2_pixmap_argb1555_pixel(color), 0);
}
static g2_color_t g2_pixmap_argb1555_color_get_l(tb_cpointer_t data)
{
	g2_color_t 	color;
	tb_uint16_t pixel = g2_bits_u16_get_le(data);
	color.r = G2_ARGB_1555_R(pixel);
	color.g = G2_ARGB_1555_G(pixel);
	color.b = G2_ARGB_1555_B(pixel);
	color.a = G2_ARGB_1555_A(pixel);
	return color;
}
static g2_color_t g2_pixmap_argb1555_color_get_b(tb_cpointer_t data)
{
	g2_color_t 	color;
	tb_uint16_t pixel = g2_bits_u16_get_be(data);
	color.r = G2_ARGB_1555_R(pixel);
	color.g = G2_ARGB_1555_G(pixel);
	color.b = G2_ARGB_1555_B(pixel);
	color.a = G2_ARGB_1555_A(pixel);
	return color;
}

/* ///////////////////////////////////////////////////////////////////////
 * globals
 */

static g2_pixmap_t const g_pixmap_lo_argb1555 =
{ 	
	"argb1555"
, 	16
, 	2
, 	G2_PIXFMT_ARGB1555
, 	g2_pixmap_argb1555_pixel
, 	g2_pixmap_argb1555_color
,	g2_pixmap_rgb16_pixel_get_l
,	g2_pixmap_rgb16_pixel_set_lo
, 	g2_pixmap_rgb16_pixel_cpy_o
,	g2_pixmap_argb1555_color_get_l
,	g2_pixmap_argb1555_color_set_lo
, 	g2_pixmap_rgb16_pixels_set_lo
};

static g2_pixmap_t const g_pixmap_bo_argb1555 =
{ 	
	"argb1555"
, 	16
, 	2
, 	G2_PIXFMT_ARGB1555
, 	g2_pixmap_argb1555_pixel
, 	g2_pixmap_argb1555_color
,	g2_pixmap_rgb16_pixel_get_b
,	g2_pixmap_rgb16_pixel_set_bo
, 	g2_pixmap_rgb16_pixel_cpy_o
,	g2_pixmap_argb1555_color_get_b
,	g2_pixmap_argb1555_color_set_bo
, 	g2_pixmap_rgb16_pixels_set_bo
};

static g2_pixmap_t const g_pixmap_la_argb1555 =
{ 	
	"argb1555"
, 	16
, 	2
, 	G2_PIXFMT_ARGB1555
, 	g2_pixmap_argb1555_pixel
, 	g2_pixmap_argb1555_color
,	g2_pixmap_rgb16_pixel_get_l
,	g2_pixmap_xrgb1555_pixel_set_la
, 	g2_pixmap_xrgb1555_pixel_cpy_la
,	g2_pixmap_argb1555_color_get_l
,	g2_pixmap_argb1555_color_set_la
, 	g2_pixmap_xrgb1555_pixels_set_la
};

static g2_pixmap_t const g_pixmap_ba_argb1555 =
{ 	
	"argb1555"
, 	16
, 	2
, 	G2_PIXFMT_ARGB1555
, 	g2_pixmap_argb1555_pixel
, 	g2_pixmap_argb1555_color
,	g2_pixmap_rgb16_pixel_get_b
,	g2_pixmap_xrgb1555_pixel_set_ba
, 	g2_pixmap_xrgb1555_pixel_cpy_ba
,	g2_pixmap_argb1555_color_get_b
,	g2_pixmap_argb1555_color_set_ba
, 	g2_pixmap_xrgb1555_pixels_set_ba
};

#endif

