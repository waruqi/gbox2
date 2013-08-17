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
 * @file		clipper.h
 *
 */
#ifndef G2_CORE_CLIPPER_H
#define G2_CORE_CLIPPER_H

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
tb_handle_t 	g2_clipper_init();
tb_void_t 		g2_clipper_exit(tb_handle_t clipper);

// clear
tb_void_t 		g2_clipper_clear(tb_handle_t clipper);

// path
tb_handle_t 	g2_clipper_path(tb_handle_t clipper, tb_handle_t path);

// clip
//tb_void_t 		g2_clipper(tb_handle_t clipper);
tb_void_t 		g2_clipper_rect(tb_handle_t clipper, 		g2_rect_t const* rect);
tb_void_t 		g2_clipper_circle(tb_handle_t clipper, 		g2_circle_t const* circle);
tb_void_t 		g2_clipper_ellipse(tb_handle_t clipper, 	g2_ellipse_t const* ellipse);
tb_void_t 		g2_clipper_triangle(tb_handle_t clipper, 	g2_triangle_t const* triangle);

// c plus plus
#ifdef __cplusplus
}
#endif

#endif
