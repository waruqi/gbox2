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

// clear
tb_void_t g2_clipper_clear(tb_handle_t clipper)
{
	if (clipper) tb_vector_clear((tb_vector_t*)clipper);
}

// copy
tb_void_t g2_clipper_copy(tb_handle_t clipper, tb_handle_t copy)
{
	tb_assert_and_check_return(clipper && copy);
	tb_vector_copy(clipper, copy);
}

// size
tb_size_t g2_clipper_size(tb_handle_t clipper)
{
	tb_assert_and_check_return_val(clipper, 0);
	return tb_vector_size(clipper);
}

// item
g2_clipper_item_t const* g2_clipper_item(tb_handle_t clipper, tb_size_t item)
{
	tb_assert_and_check_return_val(clipper, TB_NULL);
	return (g2_clipper_item_t const*)tb_iterator_item(clipper, item);
}

// path
tb_void_t g2_clipper_path(tb_handle_t clipper, tb_size_t mode, tb_handle_t path)
{
	// check
	tb_vector_t* vclipper = (tb_vector_t*)clipper;
	tb_assert_and_check_return(vclipper && mode && path);

	// init item	
	g2_clipper_item_t item;
	item.mode = mode;
	item.type = G2_CLIPPER_ITEM_PATH;
	item.u.path = path;

	// op: replace? clear it first
	if (mode == G2_CLIPPER_MODE_REPLACE)
		tb_vector_clear(vclipper);
	
	// add item
	tb_vector_insert_tail(vclipper, &item);
}

// rect
tb_void_t g2_clipper_rect(tb_handle_t clipper, tb_size_t mode, g2_rect_t const* rect)
{
	// check
	tb_vector_t* vclipper = (tb_vector_t*)clipper;
	tb_assert_and_check_return(vclipper && mode && rect);

	// init item	
	g2_clipper_item_t item;
	item.mode = mode;
	item.type = G2_CLIPPER_ITEM_RECT;
	item.u.rect = *rect;

	// op: replace? clear it first
	if (mode == G2_CLIPPER_MODE_REPLACE)
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

// triangle
tb_void_t g2_clipper_triangle(tb_handle_t clipper, tb_size_t mode, g2_triangle_t const* triangle)
{
	// check
	tb_vector_t* vclipper = (tb_vector_t*)clipper;
	tb_assert_and_check_return(vclipper && mode && triangle);

	// init item	
	g2_clipper_item_t item;
	item.mode = mode;
	item.type = G2_CLIPPER_ITEM_TRIANGLE;
	item.u.triangle = *triangle;

	// op: replace? clear it first
	if (mode == G2_CLIPPER_MODE_REPLACE)
		tb_vector_clear(vclipper);
	
	// add item
	tb_vector_insert_tail(vclipper, &item);
}
tb_void_t g2_clipper_triangle2(tb_handle_t clipper, tb_size_t mode, g2_float_t x0, g2_float_t y0, g2_float_t x1, g2_float_t y1, g2_float_t x2, g2_float_t y2)
{
	g2_triangle_t t;

	t.p0.x = x0;
	t.p0.y = y0;
	t.p1.x = x1;
	t.p1.y = y1;
	t.p2.x = x2;
	t.p2.y = y2;

	g2_clipper_triangle(clipper, mode, &t);
}
tb_void_t g2_clipper_itriangle(tb_handle_t clipper, tb_size_t mode, g2_itriangle_t const* triangle)
{
	g2_triangle_t t = g2_itriangle_to_triangle(triangle);
	g2_clipper_triangle(clipper, mode, &t);
}
tb_void_t g2_clipper_itriangle2(tb_handle_t clipper, tb_size_t mode, tb_long_t x0, tb_long_t y0, tb_long_t x1, tb_long_t y1, tb_long_t x2, tb_long_t y2)
{
	g2_triangle_t t;

	t.p0.x = g2_long_to_float(x0);
	t.p0.y = g2_long_to_float(y0);
	t.p1.x = g2_long_to_float(x1);
	t.p1.y = g2_long_to_float(y1);
	t.p2.x = g2_long_to_float(x2);
	t.p2.y = g2_long_to_float(y2);

	g2_clipper_triangle(clipper, mode, &t);
}

// circle
tb_void_t g2_clipper_circle(tb_handle_t clipper, tb_size_t mode, g2_circle_t const* circle)
{
	// check
	tb_vector_t* vclipper = (tb_vector_t*)clipper;
	tb_assert_and_check_return(vclipper && mode && circle);

	// init item	
	g2_clipper_item_t item;
	item.mode = mode;
	item.type = G2_CLIPPER_ITEM_CIRCLE;
	item.u.circle = *circle;

	// op: replace? clear it first
	if (mode == G2_CLIPPER_MODE_REPLACE)
		tb_vector_clear(vclipper);
	
	// add item
	tb_vector_insert_tail(vclipper, &item);
}
tb_void_t g2_clipper_circle2(tb_handle_t clipper, tb_size_t mode, g2_float_t x0, g2_float_t y0, g2_float_t r)
{
	g2_circle_t c;

	c.c.x 	= x0;
	c.c.y 	= y0;
	c.r 	= r;

	g2_clipper_circle(clipper, mode, &c);
}
tb_void_t g2_clipper_icircle(tb_handle_t clipper, tb_size_t mode, g2_icircle_t const* circle)
{
	g2_circle_t c = g2_icircle_to_circle(circle);
	g2_clipper_circle(clipper, mode, &c);
}
tb_void_t g2_clipper_icircle2(tb_handle_t clipper, tb_size_t mode, tb_long_t x0, tb_long_t y0, tb_size_t r)
{
	g2_circle_t c;

	c.c.x 	= g2_long_to_float(x0);
	c.c.y 	= g2_long_to_float(y0);
	c.r 	= g2_long_to_float(r);

	g2_clipper_circle(clipper, mode, &c);
}

// ellipse
tb_void_t g2_clipper_ellipse(tb_handle_t clipper, tb_size_t mode, g2_ellipse_t const* ellipse)
{
	// check
	tb_vector_t* vclipper = (tb_vector_t*)clipper;
	tb_assert_and_check_return(vclipper && mode && ellipse);

	// init item	
	g2_clipper_item_t item;
	item.mode = mode;
	item.type = G2_CLIPPER_ITEM_ELLIPSE;
	item.u.ellipse = *ellipse;

	// op: replace? clear it first
	if (mode == G2_CLIPPER_MODE_REPLACE)
		tb_vector_clear(vclipper);
	
	// add item
	tb_vector_insert_tail(vclipper, &item);
}
tb_void_t g2_clipper_ellipse2(tb_handle_t clipper, tb_size_t mode, g2_float_t x0, g2_float_t y0, g2_float_t rx, g2_float_t ry)
{
	g2_ellipse_t e;

	e.c0.x 	= x0;
	e.c0.y 	= y0;
	e.rx 	= rx;
	e.ry 	= ry;

	g2_clipper_ellipse(clipper, mode, &e);
}
tb_void_t g2_clipper_iellipse(tb_handle_t clipper, tb_size_t mode, g2_iellipse_t const* ellipse)
{
	g2_ellipse_t e = g2_iellipse_to_ellipse(ellipse);
	g2_clipper_ellipse(clipper, mode, &e);
}
tb_void_t g2_clipper_iellipse2(tb_handle_t clipper, tb_size_t mode, tb_long_t x0, tb_long_t y0, tb_size_t rx, tb_size_t ry)
{
	g2_ellipse_t e;

	e.c0.x 	= g2_long_to_float(x0);
	e.c0.y 	= g2_long_to_float(y0);
	e.rx 	= g2_long_to_float(rx);
	e.ry 	= g2_long_to_float(ry);

	g2_clipper_ellipse(clipper, mode, &e);
}

