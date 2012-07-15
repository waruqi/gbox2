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

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static tb_handle_t g2_skia_context_init(tb_size_t pixfmt, tb_pointer_t data, tb_size_t width, tb_size_t height, tb_size_t lpitch)
{
	// check
	tb_assert_and_check_return_val(G2_PIXFMT_OK(pixfmt) && width && height, TB_NULL);

	// init 
	tb_handle_t context = g2_bitmap_init(pixfmt, width, height, lpitch);
	tb_assert_and_check_return_val(context, TB_NULL);

	// make
	g2_bitmap_data_set(context, data);
	if (!data) if (!g2_bitmap_make(context)) goto fail;

	// ok
	return context;

fail:
	if (context) g2_bitmap_exit(context);
	return TB_NULL;
}
static tb_void_t g2_skia_context_exit(tb_handle_t context)
{
	if (context) g2_bitmap_exit(context);
}
static tb_handle_t g2_skia_context_surface(tb_handle_t context)
{
	return context;
}
static tb_handle_t g2_skia_context_resize(tb_handle_t context, tb_size_t width, tb_size_t height)
{
	return g2_bitmap_resize(context, width, height);
}

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */
extern "C"
{
	tb_handle_t g2_context_init_skia(tb_size_t pixfmt, tb_pointer_t data, tb_size_t width, tb_size_t height, tb_size_t lpitch)
	{
		return g2_skia_context_init(pixfmt, data, width, height, lpitch);
	}
	tb_void_t g2_context_exit(tb_handle_t context)
	{
		g2_skia_context_exit(context);
	}
	tb_handle_t g2_context_surface(tb_handle_t context)
	{
		return g2_skia_context_surface(context);
	}
	tb_handle_t g2_context_resize(tb_handle_t context, tb_size_t width, tb_size_t height)
	{
		return g2_skia_context_resize(context, width, height);
	}
}


