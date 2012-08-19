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
 * @file		bitmap.c
 *
 */
/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the bitmap type
typedef struct __g2_bitmap_t
{
	// the data
	tb_pointer_t 		data;

	// the size
	tb_size_t 			size;

	// the mode
	tb_size_t 			mode;

	// the width
	tb_size_t 			width;

	// the height
	tb_size_t 			height;

	// the lpitch
	tb_size_t 			lpitch;

	// the pixfmt
	tb_size_t 			pixfmt;

}g2_bitmap_t;

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
tb_handle_t g2_bitmap_init(tb_size_t pixfmt, tb_size_t width, tb_size_t height, tb_size_t lpitch)
{
	// alloc
	g2_bitmap_t* bitmap = tb_malloc0(sizeof(g2_bitmap_t));
	tb_assert_and_check_return_val(bitmap, TB_NULL);

	// init
	bitmap->width 	= width;
	bitmap->height 	= height;
	bitmap->lpitch 	= lpitch;
	bitmap->pixfmt 	= pixfmt;

	// ok
	return (tb_handle_t)bitmap;
}
tb_void_t g2_bitmap_exit(tb_handle_t bitmap)
{
	if (bitmap)
	{
		// free it
		tb_free(bitmap);
	}
}
tb_pointer_t g2_bitmap_make(tb_handle_t bitmap)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_size_t g2_bitmap_size(tb_handle_t bitmap)
{
	tb_trace_noimpl();
	return 0;
}
tb_size_t g2_bitmap_flag(tb_handle_t bitmap)
{
	tb_trace_noimpl();
	return 0;
}
tb_void_t g2_bitmap_flag_set(tb_handle_t bitmap, tb_size_t flag)
{
	tb_trace_noimpl();
}
tb_pointer_t g2_bitmap_data(tb_handle_t bitmap)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_void_t g2_bitmap_data_set(tb_handle_t bitmap, tb_pointer_t data)
{
	tb_trace_noimpl();
}
tb_size_t g2_bitmap_width(tb_handle_t bitmap)
{
	g2_bitmap_t* gbitmap = (g2_bitmap_t*)bitmap;
	tb_assert_and_check_return_val(gbitmap, 0);

	return gbitmap->width;
}
tb_size_t g2_bitmap_height(tb_handle_t bitmap)
{
	g2_bitmap_t* gbitmap = (g2_bitmap_t*)bitmap;
	tb_assert_and_check_return_val(gbitmap, 0);

	return gbitmap->height;
}
tb_size_t g2_bitmap_lpitch(tb_handle_t bitmap)
{
	g2_bitmap_t* gbitmap = (g2_bitmap_t*)bitmap;
	tb_assert_and_check_return_val(gbitmap, 0);

	return gbitmap->lpitch;
}
tb_size_t g2_bitmap_pixfmt(tb_handle_t bitmap)
{
	g2_bitmap_t* gbitmap = (g2_bitmap_t*)bitmap;
	tb_assert_and_check_return_val(gbitmap, G2_PIXFMT_NONE);

	return gbitmap->pixfmt;
}
tb_handle_t g2_bitmap_resize(tb_handle_t bitmap, tb_size_t width, tb_size_t height)
{
	g2_bitmap_t* gbitmap = (g2_bitmap_t*)bitmap;
	tb_assert_and_check_return_val(gbitmap, TB_NULL);

	// update size
	gbitmap->width 	= width;
	gbitmap->height = height;

	// ok
	return bitmap;
}
