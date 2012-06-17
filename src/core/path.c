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
 * @file		path.c
 *
 */
/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "path.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */

tb_void_t g2_path_movei_to(tb_handle_t path, g2_ipoint_t const* pt)
{
	g2_point_t p = g2_ipoint_to_point(pt);
	g2_path_move_to(path, &p);
}
tb_void_t g2_path_move2_to(tb_handle_t path, g2_scalar_t x, g2_scalar_t y)
{
	g2_point_t p;
	p.x = x;
	p.y = y;
	g2_path_move_to(path, &p);
}
tb_void_t g2_path_move2i_to(tb_handle_t path, tb_long_t x, tb_long_t y)
{
	g2_point_t p;
	p.x = g2_int_to_scalar(x);
	p.y = g2_int_to_scalar(y);
	g2_path_move_to(path, &p);
}
tb_void_t g2_path_linei_to(tb_handle_t path, g2_ipoint_t const* pt)
{
	g2_point_t p = g2_ipoint_to_point(pt);
	g2_path_line_to(path, &p);
}
tb_void_t g2_path_line2_to(tb_handle_t path, g2_scalar_t x, g2_scalar_t y)
{
	g2_point_t p;
	p.x = x;
	p.y = y;
	g2_path_line_to(path, &p);
}
tb_void_t g2_path_line2i_to(tb_handle_t path, tb_long_t x, tb_long_t y)
{
	g2_point_t p;
	p.x = g2_int_to_scalar(x);
	p.y = g2_int_to_scalar(y);
	g2_path_line_to(path, &p);
}
tb_void_t g2_path_quadi_to(tb_handle_t path, g2_ipoint_t const* pt, g2_ipoint_t const* cp)
{
	g2_point_t p = g2_ipoint_to_point(pt);
	g2_point_t c = g2_ipoint_to_point(cp);
	g2_path_quad_to(path, &p, &c);
}
tb_void_t g2_path_quad2_to(tb_handle_t path, g2_scalar_t x, g2_scalar_t y, g2_scalar_t cx, g2_scalar_t cy)
{
	g2_point_t p, c;
	p.x = x;
	p.y = y;
	c.x = cx;
	c.y = cy;
	g2_path_quad_to(path, &p, &c);
}
tb_void_t g2_path_quad2i_to(tb_handle_t path, tb_long_t x, tb_long_t y, tb_long_t cx, tb_long_t cy)
{
	g2_point_t p, c;
	p.x = g2_int_to_scalar(x);
	p.y = g2_int_to_scalar(y);
	c.x = g2_int_to_scalar(cx);
	c.y = g2_int_to_scalar(cy);
	g2_path_quad_to(path, &p, &c);
}
tb_void_t g2_path_cubei_to(tb_handle_t path, g2_ipoint_t const* pt, g2_ipoint_t const* c0, g2_ipoint_t const* c1)
{
	g2_point_t p = g2_ipoint_to_point(pt);
	g2_point_t cp0 = g2_ipoint_to_point(c0);
	g2_point_t cp1 = g2_ipoint_to_point(c1);
	g2_path_cube_to(path, &p, &cp0, &cp1);
}
tb_void_t g2_path_cube2_to(tb_handle_t path, g2_scalar_t x, g2_scalar_t y, g2_scalar_t cx0, g2_scalar_t cy0, g2_scalar_t cx1, g2_scalar_t cy1)
{
	g2_point_t p, cp0, cp1;
	p.x = x;
	p.y = y;
	cp0.x = cx0;
	cp0.y = cy0;
	cp1.x = cx1;
	cp1.y = cy1;
	g2_path_cube_to(path, &p, &cp0, &cp1);
}
tb_void_t g2_path_cube2i_to(tb_handle_t path, tb_long_t x, tb_long_t y, tb_long_t cx0, tb_long_t cy0, tb_long_t cx1, tb_long_t cy1)
{
	g2_point_t p, cp0, cp1;
	p.x = g2_int_to_scalar(x);
	p.y = g2_int_to_scalar(y);
	cp0.x = g2_int_to_scalar(cx0);
	cp0.y = g2_int_to_scalar(cy0);
	cp1.x = g2_int_to_scalar(cx1);
	cp1.y = g2_int_to_scalar(cy1);
	g2_path_cube_to(path, &p, &cp0, &cp1);
}


