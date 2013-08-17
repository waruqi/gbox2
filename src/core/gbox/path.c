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
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
tb_handle_t g2_path_init()
{
	tb_trace_noimpl();
	return tb_null;
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
	return tb_null;
}
tb_bool_t g2_path_last_pt(tb_handle_t path, g2_point_t* pt)
{
	tb_trace_noimpl();
	return tb_false;
}
tb_void_t g2_path_move_to(tb_handle_t path, g2_point_t const* pt)
{
	tb_trace_noimpl();
}
tb_void_t g2_path_line_to(tb_handle_t path, g2_point_t const* pt)
{
	tb_trace_noimpl();
}
tb_void_t g2_path_quad_to(tb_handle_t path, g2_point_t const* cp, g2_point_t const* pt)
{
	tb_trace_noimpl();
}
tb_void_t g2_path_cube_to(tb_handle_t path, g2_point_t const* c0, g2_point_t const* c1, g2_point_t const* pt)
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
	return tb_false;
}
tb_size_t g2_path_itor_next(tb_handle_t path, g2_point_t pt[3])
{
	tb_trace_noimpl();
}
tb_void_t g2_path_itor_exit(tb_handle_t path)
{
	tb_trace_noimpl();
}
tb_void_t g2_path_add_path(tb_handle_t path, tb_handle_t path2)
{
	tb_trace_noimpl();
}
tb_void_t g2_path_add_line(tb_handle_t path, g2_line_t const* line)
{
	tb_trace_noimpl();
}
tb_void_t g2_path_add_arc(tb_handle_t path, g2_arc_t const* arc)
{
	tb_trace_noimpl();
}
tb_void_t g2_path_add_triangle(tb_handle_t path, g2_triangle_t const* triangle)
{
	tb_trace_noimpl();
}
tb_void_t g2_path_add_rect(tb_handle_t path, g2_rect_t const* rect)
{
	tb_trace_noimpl();
}
tb_void_t g2_path_add_circle(tb_handle_t path, g2_circle_t const* circle)
{
	tb_trace_noimpl();
}
tb_void_t g2_path_add_ellipse(tb_handle_t path, g2_ellipse_t const* ellipse)
{
	tb_trace_noimpl();
}
