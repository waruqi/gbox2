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
 * @file		rgb24.h
 *
 */
#ifndef G2_CORE_PIXMAP_RGB24_H
#define G2_CORE_PIXMAP_RGB24_H

/* //////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////
 * implementation
 */
static __tb_inline__ g2_pixel_t g2_pixmap_rgb24_pixel_get_l(tb_cpointer_t data)
{
	return g2_bits_get_u24_le(data);
}
static __tb_inline__ g2_pixel_t g2_pixmap_rgb24_pixel_get_b(tb_cpointer_t data)
{
	return g2_bits_get_u24_be(data);
}
static __tb_inline__ tb_void_t g2_pixmap_rgb24_pixel_set_lo(tb_pointer_t data, g2_pixel_t pixel, tb_byte_t alpha)
{
	g2_bits_set_u24_le(data, pixel);
}
static __tb_inline__ tb_void_t g2_pixmap_rgb24_pixel_set_bo(tb_pointer_t data, g2_pixel_t pixel, tb_byte_t alpha)
{
	g2_bits_set_u24_be(data, pixel);
}
static __tb_inline__ tb_void_t g2_pixmap_rgb24_pixel_cpy_o(tb_pointer_t data, tb_cpointer_t pixel, tb_byte_t alpha)
{
	((tb_byte_t*)data)[0] = ((tb_byte_t const*)pixel)[0];
	((tb_byte_t*)data)[1] = ((tb_byte_t const*)pixel)[1];
	((tb_byte_t*)data)[2] = ((tb_byte_t const*)pixel)[2];
}
static __tb_inline__ tb_void_t g2_pixmap_rgb24_pixels_set_lo(tb_pointer_t data, g2_pixel_t pixel, tb_size_t count, tb_byte_t alpha)
{
	tb_memset_u24(data, tb_bits_ne_to_le_u24(pixel), count);
}
static __tb_inline__ tb_void_t g2_pixmap_rgb24_pixels_set_bo(tb_pointer_t data, g2_pixel_t pixel, tb_size_t count, tb_byte_t alpha)
{
	tb_memset_u24(data, tb_bits_ne_to_be_u24(pixel), count);
}

#endif

