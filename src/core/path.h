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
 * @file		path.h
 *
 */
#ifndef G2_CORE_PATH_H
#define G2_CORE_PATH_H

// c plus plus
#ifdef __cplusplus
extern "C" {
#endif

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the path code enum
typedef enum __g2_path_code_e
{
	G2_PATH_CODE_NONE	= 0
,	G2_PATH_CODE_MOVE 	= 1
,	G2_PATH_CODE_LINE 	= 2
,	G2_PATH_CODE_QUAD	= 3
,	G2_PATH_CODE_CUBE	= 4
,	G2_PATH_CODE_CLOS	= 5

}g2_path_code_e;

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

// init & exit
tb_handle_t 	g2_path_init();
tb_void_t 		g2_path_exit(tb_handle_t path);

// clear
tb_void_t 		g2_path_clear(tb_handle_t path);

// close
tb_void_t 		g2_path_close(tb_handle_t path);

// copy
tb_void_t 		g2_path_copy(tb_handle_t path, 				tb_handle_t copy);

// null?
tb_bool_t 		g2_path_null(tb_handle_t path);

// iterator
tb_bool_t 		g2_path_itor_init(tb_handle_t path);
tb_size_t 		g2_path_itor_next(tb_handle_t path, 		g2_point_t pt[3]);
tb_void_t 		g2_path_itor_exit(tb_handle_t path);

// last pt
tb_bool_t 		g2_path_last_pt(tb_handle_t path, 			g2_point_t* pt);

// move to
tb_void_t 		g2_path_move_to(tb_handle_t path, 			g2_point_t const* pt);
tb_void_t 		g2_path_movei_to(tb_handle_t path, 			g2_ipoint_t const* pt);
tb_void_t 		g2_path_move2_to(tb_handle_t path, 			g2_float_t x, g2_float_t y);
tb_void_t 		g2_path_move2i_to(tb_handle_t path, 		tb_long_t x, tb_long_t y);

// line to
tb_void_t 		g2_path_line_to(tb_handle_t path, 			g2_point_t const* pt);
tb_void_t 		g2_path_linei_to(tb_handle_t path, 			g2_ipoint_t const* pt);
tb_void_t 		g2_path_line2_to(tb_handle_t path, 			g2_float_t x, g2_float_t y);
tb_void_t 		g2_path_line2i_to(tb_handle_t path, 		tb_long_t x, tb_long_t y);

// quad to
tb_void_t 		g2_path_quad_to(tb_handle_t path, 			g2_point_t const* cp, g2_point_t const* pt);
tb_void_t 		g2_path_quadi_to(tb_handle_t path, 			g2_ipoint_t const* cp, g2_ipoint_t const* pt);
tb_void_t 		g2_path_quad2_to(tb_handle_t path, 			g2_float_t cx, g2_float_t cy, g2_float_t x, g2_float_t y);
tb_void_t 		g2_path_quad2i_to(tb_handle_t path, 		tb_long_t cx, tb_long_t cy, tb_long_t x, tb_long_t y);

// cube to
tb_void_t 		g2_path_cube_to(tb_handle_t path, 			g2_point_t const* c0, g2_point_t const* c1, g2_point_t const* pt);
tb_void_t 		g2_path_cubei_to(tb_handle_t path, 			g2_ipoint_t const* c0, g2_ipoint_t const* c1, g2_ipoint_t const* pt);
tb_void_t 		g2_path_cube2_to(tb_handle_t path, 			g2_float_t cx0, g2_float_t cy0, g2_float_t cx1, g2_float_t cy1, g2_float_t x, g2_float_t y);
tb_void_t 		g2_path_cube2i_to(tb_handle_t path, 		tb_long_t cx0, tb_long_t cy0, tb_long_t cx1, tb_long_t cy1, tb_long_t x, tb_long_t y);

// arc to
tb_void_t 		g2_path_arc_to(tb_handle_t path, 			g2_arc_t const* arc);
tb_void_t 		g2_path_arci_to(tb_handle_t path, 			g2_iarc_t const* arc);
tb_void_t 		g2_path_arc2_to(tb_handle_t path, 			g2_float_t x0, g2_float_t y0, g2_float_t rx, g2_float_t ry, g2_float_t ab, g2_float_t an);
tb_void_t 		g2_path_arc2i_to(tb_handle_t path, 			tb_long_t x0, tb_long_t y0, tb_size_t rx, tb_size_t ry, tb_size_t ab, tb_size_t an);

// add path
tb_void_t 		g2_path_add_path(tb_handle_t path, 			tb_handle_t path2);

// add line
tb_void_t 		g2_path_add_line(tb_handle_t path, 			g2_line_t const* line);
tb_void_t 		g2_path_add_line2(tb_handle_t path, 		g2_float_t x0, g2_float_t y0, g2_float_t x1, g2_float_t y1);

// add iline
tb_void_t 		g2_path_add_iline(tb_handle_t path, 		g2_iline_t const* line);
tb_void_t 		g2_path_add_iline2(tb_handle_t path, 		tb_long_t x0, tb_long_t y0, tb_long_t x1, tb_long_t y1);

// add arc
tb_void_t 		g2_path_add_arc(tb_handle_t path, 			g2_arc_t const* arc);
tb_void_t 		g2_path_add_arc2(tb_handle_t path, 			g2_float_t x0, g2_float_t y0, g2_float_t rx, g2_float_t ry, g2_float_t ab, g2_float_t an);

// add iarc
tb_void_t 		g2_path_add_iarc(tb_handle_t path, 			g2_iarc_t const* arc);
tb_void_t 		g2_path_add_iarc2(tb_handle_t path, 		tb_long_t x0, tb_long_t y0, tb_size_t rx, tb_size_t ry, tb_size_t ab, tb_size_t an);

// add triangle
tb_void_t 		g2_path_add_triangle(tb_handle_t path, 		g2_triangle_t const* triangle);
tb_void_t 		g2_path_add_triangle2(tb_handle_t path, 	g2_float_t x0, g2_float_t y0, g2_float_t x1, g2_float_t y1, g2_float_t x2, g2_float_t y2);

// add itriangle
tb_void_t 		g2_path_add_itriangle(tb_handle_t path, 	g2_itriangle_t const* triangle);
tb_void_t 		g2_path_add_itriangle2(tb_handle_t path, 	tb_long_t x0, tb_long_t y0, tb_long_t x1, tb_long_t y1, tb_long_t x2, tb_long_t y2);

// add rect
tb_void_t 		g2_path_add_rect(tb_handle_t path, 			g2_rect_t const* rect);
tb_void_t 		g2_path_add_rect2(tb_handle_t path, 		g2_float_t x, g2_float_t y, g2_float_t w, g2_float_t h);

// add irect
tb_void_t 		g2_path_add_irect(tb_handle_t path, 		g2_irect_t const* rect);
tb_void_t 		g2_path_add_irect2(tb_handle_t path, 		tb_long_t x, tb_long_t y, tb_size_t w, tb_size_t h);

// add circle
tb_void_t 		g2_path_add_circle(tb_handle_t path, 		g2_circle_t const* circle);
tb_void_t 		g2_path_add_circle2(tb_handle_t path, 		g2_float_t x0, g2_float_t y0, g2_float_t r);

// add icircle
tb_void_t 		g2_path_add_icircle(tb_handle_t path, 		g2_icircle_t const* circle);
tb_void_t 		g2_path_add_icircle2(tb_handle_t path, 		tb_long_t x0, tb_long_t y0, tb_size_t r);

// add ellipse
tb_void_t 		g2_path_add_ellipse(tb_handle_t path, 		g2_ellipse_t const* ellipse);
tb_void_t 		g2_path_add_ellipse2(tb_handle_t path, 		g2_float_t x0, g2_float_t y0, g2_float_t rx, g2_float_t ry);

// add iellipse
tb_void_t 		g2_path_add_iellipse(tb_handle_t path, 		g2_iellipse_t const* ellipse);
tb_void_t 		g2_path_add_iellipse2(tb_handle_t path, 	tb_long_t x0, tb_long_t y0, tb_size_t rx, tb_size_t ry);



// c plus plus
#ifdef __cplusplus
}
#endif

#endif
