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
#include "clipper.h"
#include "matrix.h"
#include "style.h"

/* ///////////////////////////////////////////////////////////////////////
 * clear
 */
tb_void_t g2_clear(tb_handle_t painter, g2_color_t color)
{
	g2_draw_clear(painter, color);
}

// style
tb_void_t g2_clear_style(tb_handle_t painter)
{
	g2_style_clear(g2_style(painter));
}

// matrix
tb_void_t g2_clear_matrix(tb_handle_t painter)
{
	g2_matrix_clear(g2_matrix(painter));
}

// clipper
tb_void_t g2_clear_clipper(tb_handle_t painter)
{
	g2_clipper_clear(g2_clipper(painter));
}

/* ///////////////////////////////////////////////////////////////////////
 * style
 */

// mode
tb_void_t g2_mode(tb_handle_t painter, tb_size_t mode)
{
	g2_style_mode_set(g2_style(painter), mode);
}

// flag
tb_void_t g2_flag(tb_handle_t painter, tb_size_t flag)
{
	g2_style_flag_set(g2_style(painter), flag);
}

// color
tb_void_t g2_color(tb_handle_t painter, g2_color_t color)
{
	g2_style_color_set(g2_style(painter), color);
}

// alpha
tb_void_t g2_alpha(tb_handle_t painter, tb_byte_t alpha)
{
	g2_style_alpha_set(g2_style(painter), alpha);
}

// width
tb_void_t g2_width(tb_handle_t painter, g2_float_t width)
{
	g2_style_width_set(g2_style(painter), width);
}

// cap
tb_void_t g2_cap(tb_handle_t painter, tb_size_t cap)
{
	g2_style_cap_set(g2_style(painter), cap);
}

// join
tb_void_t g2_join(tb_handle_t painter, tb_size_t join)
{
	g2_style_join_set(g2_style(painter), join);
}

// shader
tb_void_t g2_shader(tb_handle_t painter, tb_handle_t shader)
{
	g2_style_shader_set(g2_style(painter), shader);
}

/* ///////////////////////////////////////////////////////////////////////
 * matrix
 */

// save
g2_matrix_t* g2_save(tb_handle_t painter)
{
	return g2_save_matrix(painter);
}

// load
tb_void_t g2_load(tb_handle_t painter)
{
	g2_load_matrix(painter);
}

// rotate
tb_bool_t g2_rotate(tb_handle_t painter, g2_float_t degrees)
{
	return g2_matrix_rotate(g2_matrix(painter), degrees);
}
tb_bool_t g2_rotate_lhs(tb_handle_t painter, g2_float_t degrees)
{
	return g2_matrix_rotate_lhs(g2_matrix(painter), degrees);
}

// rotatep
tb_bool_t g2_rotatep(tb_handle_t painter, g2_float_t degrees, g2_float_t px, g2_float_t py)
{
	return g2_matrix_rotatep(g2_matrix(painter), degrees, px, py);
}
tb_bool_t g2_rotatep_lhs(tb_handle_t painter, g2_float_t degrees, g2_float_t px, g2_float_t py)
{
	return g2_matrix_rotatep_lhs(g2_matrix(painter), degrees, px, py);
}

// scale
tb_bool_t g2_scale(tb_handle_t painter, g2_float_t sx, g2_float_t sy)
{
	return g2_matrix_scale(g2_matrix(painter), sx, sy);
}
tb_bool_t g2_scale_lhs(tb_handle_t painter, g2_float_t sx, g2_float_t sy)
{
	return g2_matrix_scale_lhs(g2_matrix(painter), sx, sy);
}

// scalep
tb_bool_t g2_scalep(tb_handle_t painter, g2_float_t sx, g2_float_t sy, g2_float_t px, g2_float_t py)
{
	return g2_matrix_scalep(g2_matrix(painter), sx, sy, px, py);
}
tb_bool_t g2_scalep_lhs(tb_handle_t painter, g2_float_t sx, g2_float_t sy, g2_float_t px, g2_float_t py)
{
	return g2_matrix_scalep_lhs(g2_matrix(painter), sx, sy, px, py);
}

// skew
tb_bool_t g2_skew(tb_handle_t painter, g2_float_t kx, g2_float_t ky)
{
	return g2_matrix_skew(g2_matrix(painter), kx, ky);
}
tb_bool_t g2_skew_lhs(tb_handle_t painter, g2_float_t kx, g2_float_t ky)
{
	return g2_matrix_skew_lhs(g2_matrix(painter), kx, ky);
}

// skewp
tb_bool_t g2_skewp(tb_handle_t painter, g2_float_t kx, g2_float_t ky, g2_float_t px, g2_float_t py)
{
	return g2_matrix_skewp(g2_matrix(painter), kx, ky, px, py);
}
tb_bool_t g2_skewp_lhs(tb_handle_t painter, g2_float_t kx, g2_float_t ky, g2_float_t px, g2_float_t py)
{
	return g2_matrix_skewp_lhs(g2_matrix(painter), kx, ky, px, py);
}

// sincos
tb_bool_t g2_sincos(tb_handle_t painter, g2_float_t sin, g2_float_t cos)
{
	return g2_matrix_sincos(g2_matrix(painter), sin, cos);
}
tb_bool_t g2_sincos_lhs(tb_handle_t painter, g2_float_t sin, g2_float_t cos)
{
	return g2_matrix_sincos_lhs(g2_matrix(painter), sin, cos);
}

// sincosp
tb_bool_t g2_sincosp(tb_handle_t painter, g2_float_t sin, g2_float_t cos, g2_float_t px, g2_float_t py)
{
	return g2_matrix_sincosp(g2_matrix(painter), sin, cos, px, py);
}
tb_bool_t g2_sincosp_lhs(tb_handle_t painter, g2_float_t sin, g2_float_t cos, g2_float_t px, g2_float_t py)
{
	return g2_matrix_sincosp_lhs(g2_matrix(painter), sin, cos, px, py);
}

// translate
tb_bool_t g2_translate(tb_handle_t painter, g2_float_t dx, g2_float_t dy)
{
	return g2_matrix_translate(g2_matrix(painter), dx, dy);
}
tb_bool_t g2_translate_lhs(tb_handle_t painter, g2_float_t dx, g2_float_t dy)
{
	return g2_matrix_translate(g2_matrix(painter), dx, dy);
}

// multiply
tb_bool_t g2_multiply(tb_handle_t painter, g2_matrix_t const* matrix)
{
	return g2_multiply(g2_matrix(painter), matrix);
}
tb_bool_t g2_multiply_lhs(tb_handle_t painter, g2_matrix_t const* matrix)
{
	return g2_multiply_lhs(g2_matrix(painter), matrix);
}

/* ///////////////////////////////////////////////////////////////////////
 * clipper
 */
tb_void_t g2_clip_path(tb_handle_t painter, tb_size_t mode, tb_handle_t path)
{
	g2_clipper_matrix(g2_clipper(painter), g2_matrix(painter));
	g2_clipper_path(g2_clipper(painter), mode, path);
}
tb_void_t g2_clip_rect(tb_handle_t painter, tb_size_t mode, g2_rect_t const* rect)
{
	g2_clipper_matrix(g2_clipper(painter), g2_matrix(painter));
	g2_clipper_rect(g2_clipper(painter), mode, rect);
}
tb_void_t g2_clip_rect2(tb_handle_t painter, tb_size_t mode, g2_float_t x, g2_float_t y, g2_float_t w, g2_float_t h)
{
	g2_rect_t r;

	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;

	g2_clip_rect(painter, mode, &r);
}
tb_void_t g2_clip_irect(tb_handle_t painter, tb_size_t mode, g2_irect_t const* rect)
{
	g2_rect_t r = g2_irect_to_rect(rect);
	g2_clip_rect(painter, mode, &r);
}
tb_void_t g2_clip_irect2(tb_handle_t painter, tb_size_t mode, tb_long_t x, tb_long_t y, tb_size_t w, tb_size_t h)
{
	g2_rect_t r;
	
	r.x = g2_long_to_float(x);
	r.y = g2_long_to_float(y);
	r.w = g2_long_to_float(w);
	r.h = g2_long_to_float(h);

	g2_clip_rect(painter, mode, &r);
}
tb_void_t g2_clip_triangle(tb_handle_t painter, tb_size_t mode, g2_triangle_t const* triangle)
{
	g2_clipper_matrix(g2_clipper(painter), g2_matrix(painter));
	g2_clipper_triangle(g2_clipper(painter), mode, triangle);
}
tb_void_t g2_clip_triangle2(tb_handle_t painter, tb_size_t mode, g2_float_t x0, g2_float_t y0, g2_float_t x1, g2_float_t y1, g2_float_t x2, g2_float_t y2)
{
	g2_triangle_t t;

	t.p0.x = x0;
	t.p0.y = y0;
	t.p1.x = x1;
	t.p1.y = y1;
	t.p2.x = x2;
	t.p2.y = y2;

	g2_clip_triangle(painter, mode, &t);
}
tb_void_t g2_clip_itriangle(tb_handle_t painter, tb_size_t mode, g2_itriangle_t const* triangle)
{
	g2_triangle_t t = g2_itriangle_to_triangle(triangle);
	g2_clip_triangle(painter, mode, &t);
}
tb_void_t g2_clip_itriangle2(tb_handle_t painter, tb_size_t mode, tb_long_t x0, tb_long_t y0, tb_long_t x1, tb_long_t y1, tb_long_t x2, tb_long_t y2)
{
	g2_triangle_t t;

	t.p0.x = g2_long_to_float(x0);
	t.p0.y = g2_long_to_float(y0);
	t.p1.x = g2_long_to_float(x1);
	t.p1.y = g2_long_to_float(y1);
	t.p2.x = g2_long_to_float(x2);
	t.p2.y = g2_long_to_float(y2);

	g2_clip_triangle(painter, mode, &t);
}
tb_void_t g2_clip_circle(tb_handle_t painter, tb_size_t mode, g2_circle_t const* circle)
{
	g2_clipper_matrix(g2_clipper(painter), g2_matrix(painter));
	g2_clipper_circle(g2_clipper(painter), mode, circle);
}
tb_void_t g2_clip_circle2(tb_handle_t painter, tb_size_t mode, g2_float_t x0, g2_float_t y0, g2_float_t r)
{
	g2_circle_t c;

	c.c.x 	= x0;
	c.c.y 	= y0;
	c.r 	= r;

	g2_clip_circle(painter, mode, &c);
}
tb_void_t g2_clip_icircle(tb_handle_t painter, tb_size_t mode, g2_icircle_t const* circle)
{
	g2_circle_t c = g2_icircle_to_circle(circle);
	g2_clip_circle(painter, mode, &c);
}
tb_void_t g2_clip_icircle2(tb_handle_t painter, tb_size_t mode, tb_long_t x0, tb_long_t y0, tb_size_t r)
{
	g2_circle_t c;

	c.c.x 	= g2_long_to_float(x0);
	c.c.y 	= g2_long_to_float(y0);
	c.r 	= g2_long_to_float(r);

	g2_clip_circle(painter, mode, &c);
}
tb_void_t g2_clip_ellipse(tb_handle_t painter, tb_size_t mode, g2_ellipse_t const* ellipse)
{
	g2_clipper_matrix(g2_clipper(painter), g2_matrix(painter));
	g2_clipper_ellipse(g2_clipper(painter), mode, ellipse);
}
tb_void_t g2_clip_ellipse2(tb_handle_t painter, tb_size_t mode, g2_float_t x0, g2_float_t y0, g2_float_t rx, g2_float_t ry)
{
	g2_ellipse_t e;

	e.c0.x 	= x0;
	e.c0.y 	= y0;
	e.rx 	= rx;
	e.ry 	= ry;

	g2_clip_ellipse(painter, mode, &e);
}
tb_void_t g2_clip_iellipse(tb_handle_t painter, tb_size_t mode, g2_iellipse_t const* ellipse)
{
	g2_ellipse_t e = g2_iellipse_to_ellipse(ellipse);
	g2_clip_ellipse(painter, mode, &e);
}
tb_void_t g2_clip_iellipse2(tb_handle_t painter, tb_size_t mode, tb_long_t x0, tb_long_t y0, tb_size_t rx, tb_size_t ry)
{
	g2_ellipse_t e;

	e.c0.x 	= g2_long_to_float(x0);
	e.c0.y 	= g2_long_to_float(y0);
	e.rx 	= g2_long_to_float(rx);
	e.ry 	= g2_long_to_float(ry);

	g2_clip_ellipse(painter, mode, &e);
}

/* ///////////////////////////////////////////////////////////////////////
 * drawer
 */

// point
tb_void_t g2_draw_point2(tb_handle_t painter, g2_float_t x, g2_float_t y)
{
	g2_point_t p;

	p.x = x;
	p.y = y;

	g2_draw_point(painter, &p);
}
tb_void_t g2_draw_ipoint(tb_handle_t painter, g2_ipoint_t const* point)
{
	g2_point_t p = g2_ipoint_to_point(point);
	g2_draw_point(painter, &p);
}
tb_void_t g2_draw_ipoint2(tb_handle_t painter, tb_long_t x, tb_long_t y)
{
	g2_point_t p;
	
	p.x = g2_long_to_float(x);
	p.y = g2_long_to_float(y);

	g2_draw_point(painter, &p);
}
// line
tb_void_t g2_draw_line2(tb_handle_t painter, g2_float_t x0, g2_float_t y0, g2_float_t x1, g2_float_t y1)
{
	g2_line_t l;

	l.p0.x = x0;
	l.p0.y = y0;
	l.p1.x = x1;
	l.p1.y = y1;

	g2_draw_line(painter, &l);
}
tb_void_t g2_draw_iline(tb_handle_t painter, g2_iline_t const* line)
{
	g2_line_t l = g2_iline_to_line(line);
	g2_draw_line(painter, &l);
}
tb_void_t g2_draw_iline2(tb_handle_t painter, tb_long_t x0, tb_long_t y0, tb_long_t x1, tb_long_t y1)
{
	g2_line_t l;

	l.p0.x = g2_long_to_float(x0);
	l.p0.y = g2_long_to_float(y0);
	l.p1.x = g2_long_to_float(x1);
	l.p1.y = g2_long_to_float(y1);

	g2_draw_line(painter, &l);
}
// arc
tb_void_t g2_draw_arc2(tb_handle_t painter, g2_float_t x0, g2_float_t y0, g2_float_t rx, g2_float_t ry, g2_float_t ab, g2_float_t an)
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
tb_void_t g2_draw_iarc(tb_handle_t painter, g2_iarc_t const* arc)
{
	g2_arc_t a = g2_iarc_to_arc(arc);
	g2_draw_arc(painter, &a);
}
tb_void_t g2_draw_iarc2(tb_handle_t painter, tb_long_t x0, tb_long_t y0, tb_size_t rx, tb_size_t ry, tb_size_t ab, tb_size_t an)
{
	g2_arc_t a;

	a.c0.x 	= g2_long_to_float(x0);
	a.c0.y 	= g2_long_to_float(y0);
	a.rx 	= g2_long_to_float(rx);
	a.ry 	= g2_long_to_float(ry);
	a.ab 	= g2_long_to_float(ab);
	a.an 	= g2_long_to_float(an);

	g2_draw_arc(painter, &a);
}

// triangle
tb_void_t g2_draw_triangle2(tb_handle_t painter, g2_float_t x0, g2_float_t y0, g2_float_t x1, g2_float_t y1, g2_float_t x2, g2_float_t y2)
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
tb_void_t g2_draw_itriangle(tb_handle_t painter, g2_itriangle_t const* triangle)
{
	g2_triangle_t t = g2_itriangle_to_triangle(triangle);
	g2_draw_triangle(painter, &t);
}
tb_void_t g2_draw_itriangle2(tb_handle_t painter, tb_long_t x0, tb_long_t y0, tb_long_t x1, tb_long_t y1, tb_long_t x2, tb_long_t y2)
{
	g2_triangle_t t;

	t.p0.x = g2_long_to_float(x0);
	t.p0.y = g2_long_to_float(y0);
	t.p1.x = g2_long_to_float(x1);
	t.p1.y = g2_long_to_float(y1);
	t.p2.x = g2_long_to_float(x2);
	t.p2.y = g2_long_to_float(y2);

	g2_draw_triangle(painter, &t);
}

// rect
tb_void_t g2_draw_rect2(tb_handle_t painter, g2_float_t x, g2_float_t y, g2_float_t w, g2_float_t h)
{
	g2_rect_t r;

	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;

	g2_draw_rect(painter, &r);
}
tb_void_t g2_draw_irect(tb_handle_t painter, g2_irect_t const* rect)
{
	g2_rect_t r = g2_irect_to_rect(rect);
	g2_draw_rect(painter, &r);
}
tb_void_t g2_draw_irect2(tb_handle_t painter, tb_long_t x, tb_long_t y, tb_size_t w, tb_size_t h)
{
	g2_rect_t r;
	
	r.x = g2_long_to_float(x);
	r.y = g2_long_to_float(y);
	r.w = g2_long_to_float(w);
	r.h = g2_long_to_float(h);

	g2_draw_rect(painter, &r);
}

// circle
tb_void_t g2_draw_circle2(tb_handle_t painter, g2_float_t x0, g2_float_t y0, g2_float_t r)
{
	g2_circle_t c;

	c.c.x 	= x0;
	c.c.y 	= y0;
	c.r 	= r;

	g2_draw_circle(painter, &c);
}
tb_void_t g2_draw_icircle(tb_handle_t painter, g2_icircle_t const* circle)
{
	g2_circle_t c = g2_icircle_to_circle(circle);
	g2_draw_circle(painter, &c);
}
tb_void_t g2_draw_icircle2(tb_handle_t painter, tb_long_t x0, tb_long_t y0, tb_size_t r)
{
	g2_circle_t c;

	c.c.x 	= g2_long_to_float(x0);
	c.c.y 	= g2_long_to_float(y0);
	c.r 	= g2_long_to_float(r);

	g2_draw_circle(painter, &c);
}

// ellipse
tb_void_t g2_draw_ellipse2(tb_handle_t painter, g2_float_t x0, g2_float_t y0, g2_float_t rx, g2_float_t ry)
{
	g2_ellipse_t e;

	e.c0.x 	= x0;
	e.c0.y 	= y0;
	e.rx 	= rx;
	e.ry 	= ry;

	g2_draw_ellipse(painter, &e);
}
tb_void_t g2_draw_iellipse(tb_handle_t painter, g2_iellipse_t const* ellipse)
{
	g2_ellipse_t e = g2_iellipse_to_ellipse(ellipse);
	g2_draw_ellipse(painter, &e);
}
tb_void_t g2_draw_iellipse2(tb_handle_t painter, tb_long_t x0, tb_long_t y0, tb_size_t rx, tb_size_t ry)
{
	g2_ellipse_t e;

	e.c0.x 	= g2_long_to_float(x0);
	e.c0.y 	= g2_long_to_float(y0);
	e.rx 	= g2_long_to_float(rx);
	e.ry 	= g2_long_to_float(ry);

	g2_draw_ellipse(painter, &e);
}

