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

	// the flag
	tb_size_t 			flag;

	// the width
	tb_size_t 			width;

	// the height
	tb_size_t 			height;

	// the lpitch
	tb_size_t 			lpitch;

	// the pixmap
	g2_pixmap_t const* 	pixmap;

}g2_bitmap_t;

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
tb_handle_t g2_bitmap_init(tb_size_t pixfmt, tb_size_t width, tb_size_t height, tb_size_t lpitch)
{
	// check
	tb_assert_and_check_return_val(G2_PIXFMT_OK(pixfmt) && width && height, tb_null);

	// alloc
	g2_bitmap_t* bitmap = tb_malloc0(sizeof(g2_bitmap_t));
	tb_assert_and_check_return_val(bitmap, tb_null);

	// init pixmap
	bitmap->pixmap 	= g2_pixmap(pixfmt, 0xff);
	tb_assert_and_check_goto(bitmap->pixmap, fail);

	// init size
	bitmap->width 	= width;
	bitmap->height 	= height;
	bitmap->lpitch 	= lpitch? lpitch : width * bitmap->pixmap->btp;
	bitmap->size 	= bitmap->lpitch * height;
	bitmap->flag 	= G2_BITMAP_FLAG_OWNER | G2_BITMAP_FLAG_ALPHA;

	// ok
	return (tb_handle_t)bitmap;

fail:
	if (bitmap) g2_bitmap_exit(bitmap);
	return tb_null;
}
tb_void_t g2_bitmap_exit(tb_handle_t bitmap)
{
	g2_bitmap_t* gbitmap = (g2_bitmap_t*)bitmap;
	if (gbitmap)
	{
		// free data
		if (gbitmap->flag & G2_BITMAP_FLAG_OWNER && gbitmap->data)
			tb_free(gbitmap->data);

		// free it
		tb_free(gbitmap);
	}
}
tb_pointer_t g2_bitmap_make(tb_handle_t bitmap)
{
	g2_bitmap_t* gbitmap = (g2_bitmap_t*)bitmap;
	tb_assert_and_check_return_val(gbitmap, tb_null);

	// has data?
	if (gbitmap->data && gbitmap->flag & G2_BITMAP_FLAG_OWNER) return gbitmap->data;

	// make data
	gbitmap->data = tb_malloc0(gbitmap->size);
	tb_assert_and_check_return_val(gbitmap->data, tb_null);

	// init flag
	gbitmap->flag |= G2_BITMAP_FLAG_OWNER;

	// ok
	return gbitmap->data;
}
tb_size_t g2_bitmap_size(tb_handle_t bitmap)
{
	g2_bitmap_t* gbitmap = (g2_bitmap_t*)bitmap;
	tb_assert_and_check_return_val(gbitmap, 0);

	return gbitmap->size;
}
tb_size_t g2_bitmap_flag(tb_handle_t bitmap)
{
	g2_bitmap_t* gbitmap = (g2_bitmap_t*)bitmap;
	tb_assert_and_check_return_val(gbitmap, G2_BITMAP_FLAG_NONE);

	return gbitmap->flag;
}
tb_void_t g2_bitmap_flag_set(tb_handle_t bitmap, tb_size_t flag)
{
	g2_bitmap_t* gbitmap = (g2_bitmap_t*)bitmap;
	tb_assert_and_check_return(gbitmap);

	if (flag & G2_BITMAP_FLAG_ALPHA)
		gbitmap->flag |= G2_BITMAP_FLAG_ALPHA;
	else gbitmap->flag &= ~G2_BITMAP_FLAG_ALPHA;
}
tb_pointer_t g2_bitmap_data(tb_handle_t bitmap)
{
	g2_bitmap_t* gbitmap = (g2_bitmap_t*)bitmap;
	tb_assert_and_check_return_val(gbitmap, tb_null);

	return gbitmap->data;
}
tb_void_t g2_bitmap_data_set(tb_handle_t bitmap, tb_pointer_t data)
{
	g2_bitmap_t* gbitmap = (g2_bitmap_t*)bitmap;
	tb_assert_and_check_return(gbitmap);

	// free data
	if (gbitmap->data && gbitmap->flag & G2_BITMAP_FLAG_OWNER)
		tb_free(gbitmap->data);

	// init data
	gbitmap->data = data;

	// init flag
	gbitmap->flag &= ~G2_BITMAP_FLAG_OWNER;
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
	tb_assert_and_check_return_val(gbitmap && gbitmap->pixmap, G2_PIXFMT_NONE);

	return gbitmap->pixmap->pixfmt;
}
tb_handle_t g2_bitmap_resize(tb_handle_t bitmap, tb_size_t width, tb_size_t height)
{
	g2_bitmap_t* gbitmap = (g2_bitmap_t*)bitmap;
	tb_assert_and_check_return_val(gbitmap, tb_null);

	// same?
	tb_check_return_val(gbitmap->width != width || gbitmap->height != height, bitmap);

	// size
	gbitmap->width 	= width;
	gbitmap->height = height;

	// resize
	if (gbitmap->flag & G2_BITMAP_FLAG_OWNER)
	{
		// init lpitch
		gbitmap->lpitch = width * gbitmap->pixmap->btp;

		// init data
		if (gbitmap->data)
		{
			// free data
			tb_free(gbitmap->data);
			gbitmap->data = tb_null;

			// make data
			if (!g2_bitmap_make(bitmap)) return tb_null;
		}
	}

	// ok
	return bitmap;
}

