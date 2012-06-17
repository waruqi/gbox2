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
 * @file		painter.c
 *
 */
/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "painter.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
tb_void_t g2_drawi_arc(tb_handle_t painter, g2_iarc_t const* arc)
{
	g2_arc_t a = g2_iarc_to_arc(arc);
	g2_draw_arc(painter, &a);
}
tb_void_t g2_drawi_rect(tb_handle_t painter, g2_irect_t const* rect)
{
	g2_rect_t r = g2_irect_to_rect(rect);
	g2_draw_rect(painter, &r);
}
tb_void_t g2_drawi_line(tb_handle_t painter, g2_iline_t const* line)
{
	g2_line_t l = g2_iline_to_line(line);
	g2_draw_line(painter, &l);
}
tb_void_t g2_drawi_point(tb_handle_t painter, g2_ipoint_t const* point)
{
	g2_point_t p = g2_ipoint_to_point(point);
	g2_draw_point(painter, &p);
}
tb_void_t g2_drawi_circle(tb_handle_t painter, g2_icircle_t const* circle)
{
	g2_circle_t c = g2_icircle_to_circle(circle);
	g2_draw_circle(painter, &c);
}
tb_void_t g2_drawi_ellipse(tb_handle_t painter, g2_iellipse_t const* ellipse)
{
	g2_ellipse_t e = g2_iellipse_to_ellipse(ellipse);
	g2_draw_ellipse(painter, &e);
}
tb_void_t g2_drawi_triangle(tb_handle_t painter, g2_itriangle_t const* triangle)
{
	g2_triangle_t t = g2_itriangle_to_triangle(triangle);
	g2_draw_triangle(painter, &t);
}
tb_void_t g2_draw2_arc(tb_handle_t painter, g2_scalar_t x0, g2_scalar_t y0, g2_scalar_t rx, g2_scalar_t ry, g2_scalar_t ab, g2_scalar_t an)
{
	g2_iarc_t a;

	a.c0.x 	= x0;
	a.c0.y 	= y0;
	a.rx 	= rx;
	a.ry 	= ry;
	a.ab 	= ab;
	a.an 	= an;

	g2_draw_arc(painter, &a);
}
tb_void_t g2_draw2_rect(tb_handle_t painter, g2_scalar_t x, g2_scalar_t y, g2_scalar_t w, g2_scalar_t h)
{
	g2_rect_t r;

	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;

	g2_draw_rect(painter, &r);
}
tb_void_t g2_draw2_line(tb_handle_t painter, g2_scalar_t x0, g2_scalar_t y0, g2_scalar_t x1, g2_scalar_t y1)
{
	g2_line_t l;

	l.p0.x = x0;
	l.p0.y = y0;
	l.p1.x = x1;
	l.p1.y = y1;

	g2_draw_line(painter, &l);
}
tb_void_t g2_draw2_point(tb_handle_t painter, g2_scalar_t x, g2_scalar_t y)
{
	g2_point_t p;

	p.x = x;
	p.y = y;

	g2_draw_point(painter, &p);
}
tb_void_t g2_draw2_circle(tb_handle_t painter, g2_scalar_t x0, g2_scalar_t y0, g2_scalar_t r)
{
	g2_circle_t c;

	c.c.x 	= x0;
	c.c.y 	= y0;
	c.r 	= r;

	g2_draw_circle(painter, &c);
}
tb_void_t g2_draw2_ellipse(tb_handle_t painter, g2_scalar_t x0, g2_scalar_t y0, g2_scalar_t rx, g2_scalar_t ry)
{
	g2_ellipse_t e;

	e.c0.x 	= x0;
	e.c0.y 	= y0;
	e.rx 	= rx;
	e.ry 	= ry;

	g2_draw_ellipse(painter, &e);
}
tb_void_t g2_draw2_triangle(tb_handle_t painter, g2_scalar_t x0, g2_scalar_t y0, g2_scalar_t x1, g2_scalar_t y1, g2_scalar_t x2, g2_scalar_t y2)
{
	g2_triangle_t t;

	t.p0.x = x0;
	t.p0.y = y0;
	t.p1.x = x1;
	t.p1.y = y1;
	t.p2.x = x2;
	t.p2.y = y2;

	g2_draw_triangle(painter, &t);
}
tb_void_t g2_draw2i_arc(tb_handle_t painter, tb_long_t x0, tb_long_t y0, tb_size_t rx, tb_size_t ry, tb_size_t ab, tb_size_t an)
{
	g2_arc_t a;

	a.c0.x 	= g2_int_to_scalar(x0);
	a.c0.y 	= g2_int_to_scalar(y0);
	a.rx 	= g2_int_to_scalar(rx);
	a.ry 	= g2_int_to_scalar(ry);
	a.ab 	= g2_int_to_scalar(ab);
	a.an 	= g2_int_to_scalar(an);

	g2_draw_arc(painter, &a);
}
tb_void_t g2_draw2i_rect(tb_handle_t painter, tb_long_t x, tb_long_t y, tb_size_t w, tb_size_t h)
{
	g2_rect_t r;
	
	r.x = g2_int_to_scalar(x);
	r.y = g2_int_to_scalar(y);
	r.w = g2_int_to_scalar(w);
	r.h = g2_int_to_scalar(h);

	g2_draw_rect(painter, &r);
}
tb_void_t g2_draw2i_line(tb_handle_t painter, tb_long_t x0, tb_long_t y0, tb_long_t x1, tb_long_t y1)
{
	g2_line_t l;

	l.p0.x = g2_int_to_scalar(x0);
	l.p0.y = g2_int_to_scalar(y0);
	l.p1.x = g2_int_to_scalar(x1);
	l.p1.y = g2_int_to_scalar(y1);

	g2_draw_line(painter, &l);
}
tb_void_t g2_draw2i_point(tb_handle_t painter, tb_long_t x, tb_long_t y)
{
	g2_point_t p;
	
	p.x = g2_int_to_scalar(x);
	p.y = g2_int_to_scalar(y);

	g2_draw_point(painter, &p);
}
tb_void_t g2_draw2i_circle(tb_handle_t painter, tb_long_t x0, tb_long_t y0, tb_size_t r)
{
	g2_circle_t c;

	c.c.x 	= g2_int_to_scalar(x0);
	c.c.y 	= g2_int_to_scalar(y0);
	c.r 	= g2_int_to_scalar(r);

	g2_draw_circle(painter, &c);
}
tb_void_t g2_draw2i_ellipse(tb_handle_t painter, tb_long_t x0, tb_long_t y0, tb_size_t rx, tb_size_t ry)
{
	g2_ellipse_t e;

	e.c0.x 	= g2_int_to_scalar(x0);
	e.c0.y 	= g2_int_to_scalar(y0);
	e.rx 	= g2_int_to_scalar(rx);
	e.ry 	= g2_int_to_scalar(ry);

	g2_draw_ellipse(painter, &e);
}
tb_void_t g2_draw2i_triangle(tb_handle_t painter, tb_long_t x0, tb_long_t y0, tb_long_t x1, tb_long_t y1, tb_long_t x2, tb_long_t y2)
{
	g2_triangle_t t;

	t.p0.x = g2_int_to_scalar(x0);
	t.p0.y = g2_int_to_scalar(y0);
	t.p1.x = g2_int_to_scalar(x1);
	t.p1.y = g2_int_to_scalar(y1);
	t.p2.x = g2_int_to_scalar(x2);
	t.p2.y = g2_int_to_scalar(y2);

	g2_draw_triangle(painter, &t);
}

