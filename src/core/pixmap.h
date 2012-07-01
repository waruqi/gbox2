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
 * @file		pixmap.h
 *
 */
#ifndef G2_CORE_PIXMAP_H
#define G2_CORE_PIXMAP_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the pixel operation type
typedef g2_pixel_t 		(*g2_pixmap_op_pixel_t)(g2_color_t color);
typedef g2_color_t 		(*g2_pixmap_op_color_t)(g2_pixel_t pixel);

typedef g2_pixel_t 		(*g2_pixmap_op_pixel_get_t)(tb_cpointer_t data);
typedef tb_void_t 		(*g2_pixmap_op_pixel_set_t)(tb_pointer_t data, g2_pixel_t pixel, tb_byte_t alpha);
typedef tb_void_t 		(*g2_pixmap_op_pixel_cpy_t)(tb_pointer_t data, tb_cpointer_t pixel, tb_byte_t alpha);

typedef g2_color_t 		(*g2_pixmap_op_color_get_t)(tb_cpointer_t data);
typedef tb_void_t 		(*g2_pixmap_op_color_set_t)(tb_pointer_t data, g2_color_t pixel);

typedef tb_void_t 		(*g2_pixmap_op_pixels_set_t)(tb_pointer_t data, g2_pixel_t pixel, tb_size_t src_n, tb_byte_t alpha);

// the pixel map type
typedef struct __g2_pixmap_t
{
	// the pixel name
	tb_char_t const* 	name;

	// the bits per pixel
	tb_size_t 			bpp 	: 8;

	// the bytes per pixel
	tb_size_t 			btp 	: 8;

	// the pixel format
	tb_size_t 			pixfmt 	: 16;

	// color => pixel
	g2_pixel_t 			(*pixel)(g2_color_t color);
	// pixel => color
	g2_color_t 			(*color)(g2_pixel_t pixel);

	// pixel
	g2_pixel_t 			(*pixel_get)(tb_cpointer_t data);
	tb_void_t 			(*pixel_set)(tb_pointer_t data, g2_pixel_t pixel, tb_byte_t alpha);
	tb_void_t 			(*pixel_cpy)(tb_pointer_t data, tb_cpointer_t pixel, tb_byte_t alpha);

	// color
	g2_color_t 			(*color_get)(tb_cpointer_t data);
	tb_void_t 			(*color_set)(tb_pointer_t data, g2_color_t color);

	// pixels
	tb_void_t 			(*pixels_set)(tb_pointer_t data, g2_pixel_t pixel, tb_size_t count, tb_byte_t alpha);

}g2_pixmap_t;

/* ////////////////////////////////////////////////////////////////////////
 * interfaces
 */

// the pixmap from the pixel format 
g2_pixmap_t* 		g2_pixmap(tb_handle_t painter, tb_size_t pixfmt, tb_byte_t alpha);


#endif

