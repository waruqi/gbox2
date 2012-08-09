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
#ifndef G2_CONFIG_CORE_SKIA
tb_handle_t g2_path_init()
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_void_t g2_path_exit(tb_handle_t path)
{
	tb_trace_noimpl();
}
tb_void_t g2_path_clear(tb_handle_t path)
{
	tb_trace_noimpl();
}
tb_void_t g2_path_close(tb_handle_t path)
{
	tb_trace_noimpl();
}
tb_bool_t g2_path_null(tb_handle_t path)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_bool_t g2_path_last_pt(tb_handle_t path, g2_point_t* pt)
{
	tb_trace_noimpl();
	return TB_FALSE;
}
tb_void_t g2_path_move_to(tb_handle_t path, g2_point_t const* pt)
{
	tb_trace_noimpl();
}
tb_void_t g2_path_line_to(tb_handle_t path, g2_point_t const* pt)
{
	tb_trace_noimpl();
}
tb_void_t g2_path_quad_to(tb_handle_t path, g2_point_t const* pt, g2_point_t const* cp)
{
	tb_trace_noimpl();
}
tb_void_t g2_path_cube_to(tb_handle_t path, g2_point_t const* pt, g2_point_t const* c0, g2_point_t const* c1)
{
	tb_trace_noimpl();
}
tb_void_t g2_path_arc_to(tb_handle_t path, g2_arc_t const* arc)
{
	tb_trace_noimpl();
}
tb_bool_t g2_path_itor_init(tb_handle_t path)
{
	tb_trace_noimpl();
	return TB_FALSE;
}
tb_size_t g2_path_itor_next(tb_handle_t path, g2_point_t pt[4])
{
	tb_trace_noimpl();
}
tb_void_t g2_path_itor_exit(tb_handle_t path)
{
	tb_trace_noimpl();
}

#endif
tb_void_t g2_path_movei_to(tb_handle_t path, g2_ipoint_t const* pt)
{
	g2_point_t p = g2_ipoint_to_point(pt);
	g2_path_move_to(path, &p);
}
tb_void_t g2_path_move2_to(tb_handle_t path, g2_float_t x, g2_float_t y)
{
	g2_point_t p;
	p.x = x;
	p.y = y;
	g2_path_move_to(path, &p);
}
tb_void_t g2_path_move2i_to(tb_handle_t path, tb_long_t x, tb_long_t y)
{
	g2_point_t p;
	p.x = g2_long_to_float(x);
	p.y = g2_long_to_float(y);
	g2_path_move_to(path, &p);
}
tb_void_t g2_path_linei_to(tb_handle_t path, g2_ipoint_t const* pt)
{
	g2_point_t p = g2_ipoint_to_point(pt);
	g2_path_line_to(path, &p);
}
tb_void_t g2_path_line2_to(tb_handle_t path, g2_float_t x, g2_float_t y)
{
	g2_point_t p;
	p.x = x;
	p.y = y;
	g2_path_line_to(path, &p);
}
tb_void_t g2_path_line2i_to(tb_handle_t path, tb_long_t x, tb_long_t y)
{
	g2_point_t p;
	p.x = g2_long_to_float(x);
	p.y = g2_long_to_float(y);
	g2_path_line_to(path, &p);
}
tb_void_t g2_path_quadi_to(tb_handle_t path, g2_ipoint_t const* cp, g2_ipoint_t const* pt)
{
	g2_point_t p = g2_ipoint_to_point(pt);
	g2_point_t c = g2_ipoint_to_point(cp);
	g2_path_quad_to(path, &c, &p);
}
tb_void_t g2_path_quad2_to(tb_handle_t path, g2_float_t cx, g2_float_t cy, g2_float_t x, g2_float_t y)
{
	g2_point_t p, c;
	p.x = x;
	p.y = y;
	c.x = cx;
	c.y = cy;
	g2_path_quad_to(path, &c, &p);
}
tb_void_t g2_path_quad2i_to(tb_handle_t path, tb_long_t cx, tb_long_t cy, tb_long_t x, tb_long_t y)
{
	g2_point_t p, c;
	p.x = g2_long_to_float(x);
	p.y = g2_long_to_float(y);
	c.x = g2_long_to_float(cx);
	c.y = g2_long_to_float(cy);
	g2_path_quad_to(path, &c, &p);
}
tb_void_t g2_path_cubei_to(tb_handle_t path, g2_ipoint_t const* c0, g2_ipoint_t const* c1, g2_ipoint_t const* pt)
{
	g2_point_t p = g2_ipoint_to_point(pt);
	g2_point_t cp0 = g2_ipoint_to_point(c0);
	g2_point_t cp1 = g2_ipoint_to_point(c1);
	g2_path_cube_to(path, &cp0, &cp1, &p);
}
tb_void_t g2_path_cube2_to(tb_handle_t path, g2_float_t cx0, g2_float_t cy0, g2_float_t cx1, g2_float_t cy1, g2_float_t x, g2_float_t y)
{
	g2_point_t p, cp0, cp1;
	p.x = x;
	p.y = y;
	cp0.x = cx0;
	cp0.y = cy0;
	cp1.x = cx1;
	cp1.y = cy1;
	g2_path_cube_to(path, &cp0, &cp1, &p);
}
tb_void_t g2_path_cube2i_to(tb_handle_t path, tb_long_t cx0, tb_long_t cy0, tb_long_t cx1, tb_long_t cy1, tb_long_t x, tb_long_t y)
{
	g2_point_t p, cp0, cp1;
	p.x = g2_long_to_float(x);
	p.y = g2_long_to_float(y);
	cp0.x = g2_long_to_float(cx0);
	cp0.y = g2_long_to_float(cy0);
	cp1.x = g2_long_to_float(cx1);
	cp1.y = g2_long_to_float(cy1);
	g2_path_cube_to(path, &cp0, &cp1, &p);
}

tb_void_t g2_path_arci_to(tb_handle_t path, g2_iarc_t const* arc)
{
	g2_arc_t a = g2_iarc_to_arc(arc);
	g2_path_arc_to(path, &a);
}
tb_void_t g2_path_arc2_to(tb_handle_t path, g2_float_t x0, g2_float_t y0, g2_float_t rx, g2_float_t ry, g2_float_t ab, g2_float_t an)
{
	g2_iarc_t a;

	a.c0.x 	= x0;
	a.c0.y 	= y0;
	a.rx 	= rx;
	a.ry 	= ry;
	a.ab 	= ab;
	a.an 	= an;

	g2_path_arc_to(path, &a);
}
tb_void_t g2_path_arc2i_to(tb_handle_t path, tb_long_t x0, tb_long_t y0, tb_size_t rx, tb_size_t ry, tb_size_t ab, tb_size_t an)
{
	g2_arc_t a;

	a.c0.x 	= g2_long_to_float(x0);
	a.c0.y 	= g2_long_to_float(y0);
	a.rx 	= g2_long_to_float(rx);
	a.ry 	= g2_long_to_float(ry);
	a.ab 	= g2_long_to_float(ab);
	a.an 	= g2_long_to_float(an);

	g2_path_arc_to(path, &a);
}

