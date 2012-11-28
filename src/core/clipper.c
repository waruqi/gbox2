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
 * @file		clipper.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "clipper.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */
#ifdef TB_CONFIG_MEMORY_MODE_SMALL
# 	define G2_CLIPPER_GROW_SIZE 			(4)
#else
# 	define G2_CLIPPER_GROW_SIZE 			(8)
#endif

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */

tb_handle_t g2_clipper_init()
{
	// ok
	return (tb_handle_t)tb_vector_init(G2_CLIPPER_GROW_SIZE, tb_item_func_ifm(sizeof(g2_clipper_item_t), TB_NULL, TB_NULL));
}
tb_void_t g2_clipper_exit(tb_handle_t clipper)
{
	if (clipper) tb_vector_exit((tb_vector_t*)clipper);
}
tb_void_t g2_clipper_clear(tb_handle_t clipper)
{
	if (clipper) tb_vector_clear((tb_vector_t*)clipper);
}
tb_void_t g2_clipper_path(tb_handle_t clipper, tb_size_t mode, tb_handle_t path)
{
	// check
	tb_vector_t* vclipper = (tb_vector_t*)clipper;
	tb_assert_and_check_return(vclipper && path);
	tb_assert_and_check_return(mode & G2_CLIPPER_MODE_MASK);

	// init item	
	g2_clipper_item_t item;
	item.mode = mode;
	item.type = G2_CLIPPER_ITEM_PATH;
	item.u.path = path;

	// op: replace? clear it first
	if ((mode & G2_CLIPPER_MODE_MASK) == G2_CLIPPER_MODE_REPLACE)
		tb_vector_clear(vclipper);
	
	// add item
	tb_vector_insert_tail(vclipper, &item);
}
tb_void_t g2_clipper_rect(tb_handle_t clipper, tb_size_t mode, g2_rect_t const* rect)
{
	// check
	tb_vector_t* vclipper = (tb_vector_t*)clipper;
	tb_assert_and_check_return(vclipper && rect);
	tb_assert_and_check_return(mode & G2_CLIPPER_MODE_MASK);

	// init item	
	g2_clipper_item_t item;
	item.mode = mode;
	item.type = G2_CLIPPER_ITEM_RECT;
	item.u.rect = *rect;

	// op: replace? clear it first
	if ((mode & G2_CLIPPER_MODE_MASK) == G2_CLIPPER_MODE_REPLACE)
		tb_vector_clear(vclipper);
	
	// add item
	tb_vector_insert_tail(vclipper, &item);
}
tb_void_t g2_clipper_rect2(tb_handle_t clipper, tb_size_t mode, g2_float_t x, g2_float_t y, g2_float_t w, g2_float_t h)
{
	g2_rect_t r;

	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;

	g2_clipper_rect(clipper, mode, &r);
}
tb_void_t g2_clipper_irect(tb_handle_t clipper, tb_size_t mode, g2_irect_t const* rect)
{
	g2_rect_t r = g2_irect_to_rect(rect);
	g2_clipper_rect(clipper, mode, &r);
}
tb_void_t g2_clipper_irect2(tb_handle_t clipper, tb_size_t mode, tb_long_t x, tb_long_t y, tb_size_t w, tb_size_t h)
{
	g2_rect_t r;
	
	r.x = g2_long_to_float(x);
	r.y = g2_long_to_float(y);
	r.w = g2_long_to_float(w);
	r.h = g2_long_to_float(h);

	g2_clipper_rect(clipper, mode, &r);
}

