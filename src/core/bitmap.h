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
 * @file		bitmap.h
 *
 */
#ifndef G2_CORE_BITMAP_H
#define G2_CORE_BITMAP_H

// c plus plus
#ifdef __cplusplus
extern "C" {
#endif

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

// init & exit
tb_handle_t 	g2_bitmap_init(tb_size_t pixfmt, tb_size_t width, tb_size_t height, tb_size_t lpitch);
tb_handle_t 	g2_bitmap_init_url(tb_size_t pixfmt, tb_char_t const* url);
tb_handle_t 	g2_bitmap_init_gst(tb_size_t pixfmt, tb_gstream_t* gst);
tb_void_t 		g2_bitmap_exit(tb_handle_t bitmap);

// make
tb_pointer_t 	g2_bitmap_make(tb_handle_t bitmap);

// size
tb_size_t 		g2_bitmap_size(tb_handle_t bitmap);

// data
tb_pointer_t 	g2_bitmap_data(tb_handle_t bitmap);
tb_void_t 		g2_bitmap_data_set(tb_handle_t bitmap, tb_pointer_t data);

// width & height
tb_size_t 		g2_bitmap_width(tb_handle_t bitmap);
tb_size_t 		g2_bitmap_height(tb_handle_t bitmap);

// pixfmt
tb_size_t 		g2_bitmap_pixfmt(tb_handle_t bitmap);

// lpitch
tb_size_t 		g2_bitmap_lpitch(tb_handle_t bitmap);

// resize
tb_handle_t 	g2_bitmap_resize(tb_handle_t bitmap, tb_size_t width, tb_size_t height);


// c plus plus
#ifdef __cplusplus
}
#endif

#endif
