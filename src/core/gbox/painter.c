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
#include "../painter.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
tb_handle_t g2_init(tb_handle_t context)
{
	tb_trace_noimpl();
	return tb_null;
}
tb_void_t g2_exit(tb_handle_t painter)
{
	tb_trace_noimpl();
}
tb_size_t g2_pixfmt(tb_handle_t painter)
{
	tb_trace_noimpl();
	return 0;
}
tb_handle_t g2_context(tb_handle_t painter)
{
	tb_trace_noimpl();
	return tb_null;
}
tb_handle_t g2_path(tb_handle_t painter)
{
	tb_trace_noimpl();
	return tb_null;
}
tb_handle_t g2_save_path(tb_handle_t painter)
{
	tb_trace_noimpl();
	return tb_null;
}
tb_void_t g2_load_path(tb_handle_t painter)
{
	tb_trace_noimpl();
}
g2_matrix_t* g2_matrix(tb_handle_t painter)
{
	tb_trace_noimpl();
	return tb_null;
}
g2_matrix_t* g2_save_matrix(tb_handle_t painter)
{
	tb_trace_noimpl();
	return tb_null;
}
tb_void_t g2_load_matrix(tb_handle_t painter)
{
	tb_trace_noimpl();
}
tb_handle_t g2_style(tb_handle_t painter)
{
	tb_trace_noimpl();
	return tb_null;
}
tb_handle_t g2_save_style(tb_handle_t painter)
{
	tb_trace_noimpl();
	return tb_null;
}
tb_void_t g2_load_style(tb_handle_t painter)
{
	tb_trace_noimpl();
}
tb_handle_t g2_clipper(tb_handle_t painter)
{
	tb_trace_noimpl();
	return tb_null;
}
tb_handle_t g2_save_clipper(tb_handle_t painter)
{
	tb_trace_noimpl();
	return tb_null;
}
tb_void_t g2_load_clipper(tb_handle_t painter)
{
	tb_trace_noimpl();
}
tb_void_t g2_draw_clear(tb_handle_t painter, g2_color_t color)
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
