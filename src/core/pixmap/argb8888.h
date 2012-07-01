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
 * @file		argb8888.h
 *
 */
#ifndef G2_CORE_PIXMAP_ARGB8888_H
#define G2_CORE_PIXMAP_ARGB8888_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "xrgb8888.h"

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */
static g2_pixel_t g2_pixmap_argb8888_pixel(g2_color_t color)
{
	union __g2_c2p_t
	{
		g2_color_t c;
		g2_pixel_t p;

	}c2p;
	c2p.c = color;
	return c2p.p;
}
static g2_color_t g2_pixmap_argb8888_color(g2_pixel_t pixel)
{
	union __g2_p2c_t
	{
		g2_color_t c;
		g2_pixel_t p;

	}p2c;
	p2c.p = pixel;
	return p2c.c;
}
static g2_pixel_t g2_pixmap_argb8888_pixel_get(tb_cpointer_t data)
{
	return ((tb_uint32_t*)data)[0];
}
static tb_void_t g2_pixmap_argb8888_pixel_set_o(tb_pointer_t data, g2_pixel_t pixel, tb_byte_t alpha)
{
	((tb_uint32_t*)data)[0] = pixel;
}
static tb_void_t g2_pixmap_argb8888_pixel_set_a(tb_pointer_t data, g2_pixel_t pixel, tb_byte_t alpha)
{
	g2_pixmap_xrgb8888_pixel_set_a(data, pixel, alpha);
}
static tb_void_t g2_pixmap_argb8888_pixel_cpy_o(tb_pointer_t data, tb_cpointer_t pixel, tb_byte_t alpha)
{
	*((tb_uint32_t*)data) = *((tb_uint32_t*)pixel);
}
static tb_void_t g2_pixmap_argb8888_pixel_cpy_a(tb_pointer_t data, tb_cpointer_t pixel, tb_byte_t alpha)
{
	g2_pixmap_xrgb8888_pixel_cpy_a(data, pixel, alpha);
}
static tb_void_t g2_pixmap_argb8888_color_set_o(tb_pointer_t data, g2_color_t color)
{
	g2_pixmap_argb8888_pixel_set_o(data, g2_pixmap_argb8888_pixel(color), 0);
}
static tb_void_t g2_pixmap_argb8888_color_set_a(tb_pointer_t data, g2_color_t color)
{
	g2_pixmap_xrgb8888_color_set_a(data, color);
}
static g2_color_t g2_pixmap_argb8888_color_get(tb_cpointer_t data)
{
	g2_color_t 	color;
	tb_uint32_t pixel = ((tb_uint32_t*)data)[0];
	color.r = G2_ARGB_8888_R(pixel);
	color.g = G2_ARGB_8888_G(pixel);
	color.b = G2_ARGB_8888_B(pixel);
	color.a = G2_ARGB_8888_A(pixel);
	return color;
}
static tb_void_t g2_pixmap_argb8888_pixels_set_o(tb_pointer_t data, g2_pixel_t pixel, tb_size_t count, tb_byte_t alpha)
{
	g2_pixmap_xrgb8888_pixels_set_o(data, pixel, count, 0);
}
static tb_void_t g2_pixmap_argb8888_pixels_set_a(tb_pointer_t data, g2_pixel_t pixel, tb_size_t count, tb_byte_t alpha)
{
	g2_pixmap_xrgb8888_pixels_set_a(data, pixel, count, alpha);
}


#endif

