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
 * @file		context.cpp
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "../bitmap.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static tb_handle_t g2_skia_context_init(tb_handle_t bitmap)
{
	return bitmap;
}
static tb_void_t g2_skia_context_exit(tb_handle_t context)
{
}
static tb_size_t g2_skia_context_width(tb_handle_t context)
{
	return g2_bitmap_width(context);
}
static tb_size_t g2_skia_context_height(tb_handle_t context)
{
	return g2_bitmap_height(context);
}
static tb_void_t g2_skia_context_resize(tb_handle_t context, tb_size_t width, tb_size_t height)
{
	g2_bitmap_resize(context, width, height);
}

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */
extern "C"
{
	tb_handle_t g2_context_init(tb_handle_t bitmap)
	{
		return g2_skia_context_init(bitmap);
	}
	tb_void_t g2_context_exit(tb_handle_t context)
	{
		g2_skia_context_exit(context);
	}
	tb_size_t g2_context_width(tb_handle_t context)
	{
		return g2_skia_context_width(context);
	}
	tb_size_t g2_context_height(tb_handle_t context)
	{
		return g2_skia_context_height(context);
	}
	tb_void_t g2_context_resize(tb_handle_t context, tb_size_t width, tb_size_t height)
	{
		g2_skia_context_resize(context, width, height);
	}
}


