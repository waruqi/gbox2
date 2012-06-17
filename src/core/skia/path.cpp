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
 * @file		path.cpp
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "../path.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static tb_handle_t g2_skia_path_init()
{
	// alloc
	SkPath* spath = new SkPath();
	tb_assert_and_check_return_val(spath, TB_NULL);

	// ok
	return spath;
}
static tb_void_t g2_skia_path_exit(tb_handle_t path)
{
	SkPath* spath = static_cast<SkPath*>(path);
	tb_assert_and_check_return(spath);
 
	// free it
 	delete spath;
}
static tb_void_t g2_skia_path_clear(tb_handle_t path)
{
	SkPath* spath = static_cast<SkPath*>(path);
	tb_assert_and_check_return(spath);

	spath->reset();
}
static tb_void_t g2_skia_path_close(tb_handle_t path)
{
	SkPath* spath = static_cast<SkPath*>(path);
	tb_assert_and_check_return(spath);

	spath->close();
}
static tb_bool_t g2_skia_path_null(tb_handle_t path)
{	
	SkPath const* spath = static_cast<SkPath const*>(path);
	tb_assert_and_check_return_val(spath, TB_TRUE);

	return spath->isEmpty()? TB_TRUE : TB_FALSE;
}
static tb_void_t g2_skia_path_move_to(tb_handle_t path, g2_point_t const* pt)
{
	SkPath* spath = static_cast<SkPath*>(path);
	tb_assert_and_check_return(spath && pt);

	spath->moveTo(pt->x, pt->y);
}
static tb_void_t g2_skia_path_line_to(tb_handle_t path, g2_point_t const* pt)
{
	SkPath* spath = static_cast<SkPath*>(path);
	tb_assert_and_check_return(spath && pt);

	spath->lineTo(pt->x, pt->y);
}
static tb_void_t g2_skia_path_quad_to(tb_handle_t path, g2_point_t const* pt, g2_point_t const* cp)
{
	SkPath* spath = static_cast<SkPath*>(path);
	tb_assert_and_check_return(spath && pt && cp);

	spath->quadTo(cp->x, cp->y, pt->x, pt->y);
}
static tb_void_t g2_skia_path_cube_to(tb_handle_t path, g2_point_t const* pt, g2_point_t const* c0, g2_point_t const* c1)
{
	SkPath* spath = static_cast<SkPath*>(path);
	tb_assert_and_check_return(spath && pt && c0 && c1);

	spath->cubicTo(c0->x, c0->y, c1->x, c1->y, pt->x, pt->y);
}

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */
extern "C"
{
	tb_handle_t g2_path_init()
	{
		return g2_skia_path_init();
	}
	tb_void_t g2_path_exit(tb_handle_t path)
	{
		g2_skia_path_exit(path);
	}
	tb_void_t g2_path_clear(tb_handle_t path)
	{
		g2_skia_path_clear(path);
	}
	tb_void_t g2_path_close(tb_handle_t path)
	{
		g2_skia_path_close(path);
	}
	tb_bool_t g2_path_null(tb_handle_t path)
	{
		return g2_skia_path_null(path);		
	}
	tb_void_t g2_path_move_to(tb_handle_t path, g2_point_t const* pt)
	{
		g2_skia_path_move_to(path, pt);		
	}
	tb_void_t g2_path_line_to(tb_handle_t path, g2_point_t const* pt)
	{
		g2_skia_path_line_to(path, pt);		
	}
	tb_void_t g2_path_quad_to(tb_handle_t path, g2_point_t const* pt, g2_point_t const* cp)
	{
		g2_skia_path_quad_to(path, pt, cp);		
	}
	tb_void_t g2_path_cube_to(tb_handle_t path, g2_point_t const* pt, g2_point_t const* c0, g2_point_t const* c1)
	{
		g2_skia_path_cube_to(path, pt, c0, c1);		
	}
}

