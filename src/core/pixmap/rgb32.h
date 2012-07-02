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
 * @file		rgb32.h
 *
 */
#ifndef G2_CORE_PIXMAP_RGB32_H
#define G2_CORE_PIXMAP_RGB32_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static g2_pixel_t g2_pixmap_rgb32_pixel(g2_color_t color)
{
	union __g2_c2p_t
	{
		g2_color_t c;
		g2_pixel_t p;

	}c2p;
	c2p.c = color;
	return c2p.p;
}
static g2_color_t g2_pixmap_rgb32_color(g2_pixel_t pixel)
{
	union __g2_p2c_t
	{
		g2_color_t c;
		g2_pixel_t p;

	}p2c;
	p2c.p = pixel;
	return p2c.c;
}
static g2_pixel_t g2_pixmap_rgb32_pixel_get_l(tb_cpointer_t data)
{
	return g2_bits_get_u32_le(data);
}
static g2_pixel_t g2_pixmap_rgb32_pixel_get_b(tb_cpointer_t data)
{
	return g2_bits_get_u32_be(data);
}
static tb_void_t g2_pixmap_rgb32_pixel_set_lo(tb_pointer_t data, g2_pixel_t pixel, tb_byte_t alpha)
{
	g2_bits_set_u32_le(data, pixel);
}
static tb_void_t g2_pixmap_rgb32_pixel_set_bo(tb_pointer_t data, g2_pixel_t pixel, tb_byte_t alpha)
{
	g2_bits_set_u32_be(data, pixel);
}
static tb_void_t g2_pixmap_rgb32_pixel_cpy_o(tb_pointer_t data, tb_cpointer_t pixel, tb_byte_t alpha)
{
	*((tb_uint32_t*)data) = *((tb_uint32_t*)pixel);
}
static tb_void_t g2_pixmap_rgb32_pixels_set_lo(tb_pointer_t data, g2_pixel_t pixel, tb_size_t count, tb_byte_t alpha)
{
	tb_memset_u32(data, tb_bits_ne_to_le_u32(pixel), count);
}
static tb_void_t g2_pixmap_rgb32_pixels_set_bo(tb_pointer_t data, g2_pixel_t pixel, tb_size_t count, tb_byte_t alpha)
{
	tb_memset_u32(data, tb_bits_ne_to_be_u32(pixel), count);
}


#endif

