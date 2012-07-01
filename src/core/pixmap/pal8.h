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
 * @file		pal8.h
 *
 */
#ifndef G2_CORE_PIXMAP_PAL8_H
#define G2_CORE_PIXMAP_PAL8_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

static g2_pixel_t g2_pixmap_pal8_pixel(g2_color_t color)
{
	tb_trace_noimpl();
	return 0;
}
static g2_color_t g2_pixmap_pal8_color(g2_pixel_t pixel)
{
	tb_trace_noimpl();
	return G2_COLOR_DEFAULT;
}
static g2_pixel_t g2_pixmap_pal8_pixel_get(tb_cpointer_t data)
{
	return ((tb_byte_t*)data)[0];
}
static tb_void_t g2_pixmap_pal8_pixel_set_o(tb_pointer_t data, g2_pixel_t pixel, tb_byte_t alpha)
{
	((tb_byte_t*)data)[0] = (tb_byte_t)(pixel & 0xff);
}
static tb_void_t g2_pixmap_pal8_pixel_set_a(tb_pointer_t data, g2_pixel_t pixel, tb_byte_t alpha)
{
	((tb_byte_t*)data)[0] = (tb_byte_t)(pixel & 0xff);
}
static tb_void_t g2_pixmap_pal8_pixel_cpy_o(tb_pointer_t data, tb_cpointer_t pixel, tb_byte_t alpha)
{
	tb_memcpy(data, pixel, 1);
}
static tb_void_t g2_pixmap_pal8_pixel_cpy_a(tb_pointer_t data, tb_cpointer_t pixel, tb_byte_t alpha)
{
	tb_memcpy(data, pixel, 1);
}
static g2_color_t g2_pixmap_pal8_color_get(tb_cpointer_t data)
{
	tb_trace_noimpl();
	return G2_COLOR_DEFAULT;
}
static tb_void_t g2_pixmap_pal8_color_set_o(tb_pointer_t data, g2_color_t color)
{
	tb_trace_noimpl();
}
static tb_void_t g2_pixmap_pal8_color_set_a(tb_pointer_t data, g2_color_t color)
{
	tb_trace_noimpl();
}
static tb_void_t g2_pixmap_pal8_pixels_set_o(tb_pointer_t data, g2_pixel_t pixel, tb_size_t count, tb_byte_t alpha)
{
	tb_memset(data, (tb_byte_t)pixel, count);
}
static tb_void_t g2_pixmap_pal8_pixels_set_a(tb_pointer_t data, g2_pixel_t pixel, tb_size_t count, tb_byte_t alpha)
{
	tb_memset(data, (tb_byte_t)pixel, count);
}

#endif

