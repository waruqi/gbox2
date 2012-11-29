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

// move to
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

// line to
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

// quad to
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

// cube to
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

// arc to
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

// add line
tb_void_t g2_path_add_line2(tb_handle_t path, g2_float_t x0, g2_float_t y0, g2_float_t x1, g2_float_t y1)
{
	g2_line_t l;

	l.p0.x = x0;
	l.p0.y = y0;
	l.p1.x = x1;
	l.p1.y = y1;

	g2_path_add_line(path, &l);
}
tb_void_t g2_path_add_iline(tb_handle_t path, g2_iline_t const* line)
{
	g2_line_t l = g2_iline_to_line(line);
	g2_path_add_line(path, &l);
}
tb_void_t g2_path_add_iline2(tb_handle_t path, tb_long_t x0, tb_long_t y0, tb_long_t x1, tb_long_t y1)
{
	g2_line_t l;

	l.p0.x = g2_long_to_float(x0);
	l.p0.y = g2_long_to_float(y0);
	l.p1.x = g2_long_to_float(x1);
	l.p1.y = g2_long_to_float(y1);

	g2_path_add_line(path, &l);
}

// add arc
tb_void_t g2_path_add_arc2(tb_handle_t path, g2_float_t x0, g2_float_t y0, g2_float_t rx, g2_float_t ry, g2_float_t ab, g2_float_t an)
{
	g2_iarc_t a;

	a.c0.x 	= x0;
	a.c0.y 	= y0;
	a.rx 	= rx;
	a.ry 	= ry;
	a.ab 	= ab;
	a.an 	= an;

	g2_path_add_arc(path, &a);
}
tb_void_t g2_path_add_iarc(tb_handle_t path, g2_iarc_t const* arc)
{
	g2_arc_t a = g2_iarc_to_arc(arc);
	g2_path_add_arc(path, &a);
}
tb_void_t g2_path_add_iarc2(tb_handle_t path, tb_long_t x0, tb_long_t y0, tb_size_t rx, tb_size_t ry, tb_size_t ab, tb_size_t an)
{
	g2_arc_t a;

	a.c0.x 	= g2_long_to_float(x0);
	a.c0.y 	= g2_long_to_float(y0);
	a.rx 	= g2_long_to_float(rx);
	a.ry 	= g2_long_to_float(ry);
	a.ab 	= g2_long_to_float(ab);
	a.an 	= g2_long_to_float(an);

	g2_path_add_arc(path, &a);
}

// add triangle
tb_void_t g2_path_add_triangle2(tb_handle_t path, g2_float_t x0, g2_float_t y0, g2_float_t x1, g2_float_t y1, g2_float_t x2, g2_float_t y2)
{
	g2_triangle_t t;

	t.p0.x = x0;
	t.p0.y = y0;
	t.p1.x = x1;
	t.p1.y = y1;
	t.p2.x = x2;
	t.p2.y = y2;

	g2_path_add_triangle(path, &t);
}
tb_void_t g2_path_add_itriangle(tb_handle_t path, g2_itriangle_t const* triangle)
{
	g2_triangle_t t = g2_itriangle_to_triangle(triangle);
	g2_path_add_triangle(path, &t);
}
tb_void_t g2_path_add_itriangle2(tb_handle_t path, tb_long_t x0, tb_long_t y0, tb_long_t x1, tb_long_t y1, tb_long_t x2, tb_long_t y2)
{
	g2_triangle_t t;

	t.p0.x = g2_long_to_float(x0);
	t.p0.y = g2_long_to_float(y0);
	t.p1.x = g2_long_to_float(x1);
	t.p1.y = g2_long_to_float(y1);
	t.p2.x = g2_long_to_float(x2);
	t.p2.y = g2_long_to_float(y2);

	g2_path_add_triangle(path, &t);
}

// add rect
tb_void_t g2_path_add_rect2(tb_handle_t path, g2_float_t x, g2_float_t y, g2_float_t w, g2_float_t h)
{
	g2_rect_t r;

	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;

	g2_path_add_rect(path, &r);
}
tb_void_t g2_path_add_irect(tb_handle_t path, g2_irect_t const* rect)
{
	g2_rect_t r = g2_irect_to_rect(rect);
	g2_path_add_rect(path, &r);
}
tb_void_t g2_path_add_irect2(tb_handle_t path, tb_long_t x, tb_long_t y, tb_size_t w, tb_size_t h)
{
	g2_rect_t r;
	
	r.x = g2_long_to_float(x);
	r.y = g2_long_to_float(y);
	r.w = g2_long_to_float(w);
	r.h = g2_long_to_float(h);

	g2_path_add_rect(path, &r);
}

// add circle
tb_void_t g2_path_add_circle2(tb_handle_t path, g2_float_t x0, g2_float_t y0, g2_float_t r)
{
	g2_circle_t c;

	c.c.x 	= x0;
	c.c.y 	= y0;
	c.r 	= r;

	g2_path_add_circle(path, &c);
}
tb_void_t g2_path_add_icircle(tb_handle_t path, g2_icircle_t const* circle)
{
	g2_circle_t c = g2_icircle_to_circle(circle);
	g2_path_add_circle(path, &c);
}
tb_void_t g2_path_add_icircle2(tb_handle_t path, tb_long_t x0, tb_long_t y0, tb_size_t r)
{
	g2_circle_t c;

	c.c.x 	= g2_long_to_float(x0);
	c.c.y 	= g2_long_to_float(y0);
	c.r 	= g2_long_to_float(r);

	g2_path_add_circle(path, &c);
}

// add ellipse
tb_void_t g2_path_add_ellipse2(tb_handle_t path, g2_float_t x0, g2_float_t y0, g2_float_t rx, g2_float_t ry)
{
	g2_ellipse_t e;

	e.c0.x 	= x0;
	e.c0.y 	= y0;
	e.rx 	= rx;
	e.ry 	= ry;

	g2_path_add_ellipse(path, &e);
}
tb_void_t g2_path_add_iellipse(tb_handle_t path, g2_iellipse_t const* ellipse)
{
	g2_ellipse_t e = g2_iellipse_to_ellipse(ellipse);
	g2_path_add_ellipse(path, &e);
}
tb_void_t g2_path_add_iellipse2(tb_handle_t path, tb_long_t x0, tb_long_t y0, tb_size_t rx, tb_size_t ry)
{
	g2_ellipse_t e;

	e.c0.x 	= g2_long_to_float(x0);
	e.c0.y 	= g2_long_to_float(y0);
	e.rx 	= g2_long_to_float(rx);
	e.ry 	= g2_long_to_float(ry);

	g2_path_add_ellipse(path, &e);
}

