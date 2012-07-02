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
 * @file		bitmap.cpp
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static tb_handle_t g2_skia_bitmap_init(tb_size_t pixfmt, tb_size_t width, tb_size_t height)
{
	// check
	tb_assert_and_check_return_val(G2_PIXFMT_OK(pixfmt) && width && height, TB_NULL);

	// alloc
	SkBitmap* sbitmap = new SkBitmap();
	tb_assert_and_check_return_val(sbitmap, TB_NULL);

	// init config
	sbitmap->setConfig(g2_pixfmt_to_skia(pixfmt), width, height);

	// ok
	return sbitmap;
}
static tb_void_t g2_skia_bitmap_exit(tb_handle_t bitmap)
{
	SkBitmap* sbitmap = static_cast<SkBitmap*>(bitmap);
	tb_assert_and_check_return(sbitmap);
 
	// free it
 	delete sbitmap;
}
static tb_pointer_t g2_skia_bitmap_make(tb_handle_t bitmap)
{
	SkBitmap* sbitmap = static_cast<SkBitmap*>(bitmap);
	tb_assert_and_check_return_val(sbitmap, TB_NULL);

	// make data
	if (!sbitmap->getPixels()) sbitmap->allocPixels();

	// ok
	return sbitmap->getPixels();
}
static tb_size_t g2_skia_bitmap_size(tb_handle_t bitmap)
{
	SkBitmap* sbitmap = static_cast<SkBitmap*>(bitmap);
	tb_assert_and_check_return_val(sbitmap, 0);

	return sbitmap->getSize();
}
static tb_size_t g2_skia_bitmap_line(tb_handle_t bitmap)
{
	SkBitmap* sbitmap = static_cast<SkBitmap*>(bitmap);
	tb_assert_and_check_return_val(sbitmap, 0);

	return sbitmap->rowBytes();
}
static tb_pointer_t g2_skia_bitmap_data(tb_handle_t bitmap)
{
	SkBitmap* sbitmap = static_cast<SkBitmap*>(bitmap);
	tb_assert_and_check_return_val(sbitmap, TB_NULL);

	// ok
	return sbitmap->getPixels();
}
static tb_void_t g2_skia_bitmap_data_set(tb_handle_t bitmap, tb_pointer_t data)
{
	SkBitmap* sbitmap = static_cast<SkBitmap*>(bitmap);
	tb_assert_and_check_return(sbitmap);

	sbitmap->setPixels(data);
}
static tb_size_t g2_skia_bitmap_width(tb_handle_t bitmap)
{
	SkBitmap* sbitmap = static_cast<SkBitmap*>(bitmap);
	tb_assert_and_check_return_val(sbitmap, 0);

	return sbitmap->width();
}
static tb_size_t g2_skia_bitmap_height(tb_handle_t bitmap)
{
	SkBitmap* sbitmap = static_cast<SkBitmap*>(bitmap);
	tb_assert_and_check_return_val(sbitmap, 0);

	return sbitmap->height();
}

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */
extern "C"
{
	tb_handle_t g2_bitmap_init(tb_size_t pixfmt, tb_size_t width, tb_size_t height)
	{
		return g2_skia_bitmap_init(pixfmt, width, height);
	}
	tb_void_t g2_bitmap_exit(tb_handle_t bitmap)
	{
		g2_skia_bitmap_exit(bitmap);
	}
	tb_pointer_t g2_bitmap_make(tb_handle_t bitmap)
	{
		return g2_skia_bitmap_make(bitmap);
	}
	tb_size_t g2_bitmap_size(tb_handle_t bitmap)
	{
		return g2_skia_bitmap_size(bitmap);
	}
	tb_size_t g2_bitmap_line(tb_handle_t bitmap)
	{
		return g2_skia_bitmap_line(bitmap);
	}
	tb_pointer_t g2_bitmap_data(tb_handle_t bitmap)
	{
		return g2_skia_bitmap_data(bitmap);
	}
	tb_void_t g2_bitmap_data_set(tb_handle_t bitmap, tb_pointer_t data)
	{
		g2_skia_bitmap_data_set(bitmap, data);
	}
	tb_size_t g2_bitmap_width(tb_handle_t bitmap)
	{
		return g2_skia_bitmap_width(bitmap);
	}
	tb_size_t g2_bitmap_height(tb_handle_t bitmap)
	{
		return g2_skia_bitmap_height(bitmap);
	}
}


