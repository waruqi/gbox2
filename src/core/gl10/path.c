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

