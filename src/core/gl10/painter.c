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
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
tb_handle_t g2_init(tb_handle_t surface)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_void_t g2_exit(tb_handle_t painter)
{
	tb_trace_noimpl();
}
tb_size_t g2_save(tb_handle_t painter, tb_size_t mode)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_void_t g2_load(tb_handle_t painter)
{
	tb_trace_noimpl();
}
tb_size_t g2_pixfmt(tb_handle_t painter)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_handle_t g2_style(tb_handle_t painter)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_void_t g2_style_set(tb_handle_t painter, tb_handle_t style)
{
	tb_trace_noimpl();
}
g2_matrix_t const* g2_matrix(tb_handle_t painter)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_bool_t g2_rotate(tb_handle_t painter, g2_float_t degrees)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_bool_t g2_skew(tb_handle_t painter, g2_float_t kx, g2_float_t ky)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_bool_t g2_scale(tb_handle_t painter, g2_float_t sx, g2_float_t sy)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_bool_t g2_translate(tb_handle_t painter, g2_float_t dx, g2_float_t dy)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_bool_t g2_multiply(tb_handle_t painter, g2_matrix_t const* matrix)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_void_t g2_matrix_set(tb_handle_t painter, g2_matrix_t const* matrix)
{
	tb_trace_noimpl();
}
tb_bool_t g2_clip_path(tb_handle_t painter, tb_size_t mode, tb_handle_t path)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_bool_t g2_clip_rect(tb_handle_t painter, tb_size_t mode, g2_rect_t const* rect)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_void_t g2_clear(tb_handle_t painter, g2_color_t color)
{
	tb_trace_noimpl();
}
tb_void_t g2_draw_path(tb_handle_t painter, tb_handle_t path)
{
	tb_trace_noimpl();
}
tb_void_t g2_draw_arc(tb_handle_t painter, g2_arc_t const* arc)
{
	tb_trace_noimpl();
}
tb_void_t g2_draw_rect(tb_handle_t painter, g2_rect_t const* rect)
{
	tb_trace_noimpl();
}
tb_void_t g2_draw_line(tb_handle_t painter, g2_line_t const* line)
{
	tb_trace_noimpl();
}
tb_void_t g2_draw_point(tb_handle_t painter, g2_point_t const* point)
{
	tb_trace_noimpl();
}
tb_void_t g2_draw_circle(tb_handle_t painter, g2_circle_t const* circle)
{
	tb_trace_noimpl();
}
tb_void_t g2_draw_ellipse(tb_handle_t painter, g2_ellipse_t const* ellipse)
{
	tb_trace_noimpl();
}
tb_void_t g2_draw_triangle(tb_handle_t painter, g2_triangle_t const* triangle)
{
	tb_trace_noimpl();
}
