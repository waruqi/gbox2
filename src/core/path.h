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
 * interfaces
 */

// init & exit
tb_handle_t 	g2_path_init();
tb_void_t 		g2_path_exit(tb_handle_t path);

// clear
tb_void_t 		g2_path_clear(tb_handle_t path);

// close
tb_void_t 		g2_path_close(tb_handle_t path);

// null?
tb_bool_t 		g2_path_null(tb_handle_t path);

// move to
tb_void_t 		g2_path_move_to(tb_handle_t path, g2_point_t const* pt);
tb_void_t 		g2_path_movei_to(tb_handle_t path, g2_ipoint_t const* pt);
tb_void_t 		g2_path_move2_to(tb_handle_t path, g2_scalar_t x, g2_scalar_t y);
tb_void_t 		g2_path_move2i_to(tb_handle_t path, tb_long_t x, tb_long_t y);

// line to
tb_void_t 		g2_path_line_to(tb_handle_t path, g2_point_t const* pt);
tb_void_t 		g2_path_linei_to(tb_handle_t path, g2_ipoint_t const* pt);
tb_void_t 		g2_path_line2_to(tb_handle_t path, g2_scalar_t x, g2_scalar_t y);
tb_void_t 		g2_path_line2i_to(tb_handle_t path, tb_long_t x, tb_long_t y);

// quad to
tb_void_t 		g2_path_quad_to(tb_handle_t path, g2_point_t const* pt, g2_point_t const* cp);
tb_void_t 		g2_path_quadi_to(tb_handle_t path, g2_ipoint_t const* pt, g2_ipoint_t const* cp);
tb_void_t 		g2_path_quad2_to(tb_handle_t path, g2_scalar_t x, g2_scalar_t y, g2_scalar_t cx, g2_scalar_t cy);
tb_void_t 		g2_path_quad2i_to(tb_handle_t path, tb_long_t x, tb_long_t y, tb_long_t cx, tb_long_t cy);

// cube to
tb_void_t 		g2_path_cube_to(tb_handle_t path, g2_point_t const* pt, g2_point_t const* c0, g2_point_t const* c1);
tb_void_t 		g2_path_cubei_to(tb_handle_t path, g2_ipoint_t const* pt, g2_ipoint_t const* c0, g2_ipoint_t const* c1);
tb_void_t 		g2_path_cube2_to(tb_handle_t path, g2_scalar_t x, g2_scalar_t y, g2_scalar_t cx0, g2_scalar_t cy0, g2_scalar_t cx1, g2_scalar_t cy1);
tb_void_t 		g2_path_cube2i_to(tb_handle_t path, tb_long_t x, tb_long_t y, tb_long_t cx0, tb_long_t cy0, tb_long_t cx1, tb_long_t cy1);


// c plus plus
#ifdef __cplusplus
}
#endif

#endif
