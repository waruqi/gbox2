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
 * @file		painter.h
 *
 */
#ifndef G2_CORE_PAINTER_H
#define G2_CORE_PAINTER_H

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
tb_handle_t 	g2_init(tb_handle_t surface);
tb_void_t 		g2_exit(tb_handle_t painter);

// save & load
tb_void_t 		g2_save(tb_handle_t painter);
tb_void_t 		g2_load(tb_handle_t painter);

// style
tb_handle_t 	g2_style(tb_handle_t painter);
tb_void_t 		g2_style_set(tb_handle_t painter, tb_handle_t style);

// clipper
tb_handle_t 	g2_clipper(tb_handle_t painter, tb_handle_t clipper);

// path
tb_handle_t 	g2_path(tb_handle_t painter, tb_handle_t path);

// clear
tb_void_t 		g2_clear(tb_handle_t painter, g2_color_t color);

// draw 
tb_void_t 		g2_draw(tb_handle_t painter);
tb_void_t 		g2_draw_arc(tb_handle_t painter, 			g2_arc_t const* arc);
tb_void_t 		g2_draw_rect(tb_handle_t painter, 			g2_rect_t const* rect);
tb_void_t 		g2_draw_line(tb_handle_t painter, 			g2_line_t const* line);
tb_void_t 		g2_draw_point(tb_handle_t painter, 			g2_point_t const* point);
tb_void_t 		g2_draw_circle(tb_handle_t painter, 		g2_circle_t const* circle);
tb_void_t 		g2_draw_ellipse(tb_handle_t painter, 		g2_ellipse_t const* ellipse);
tb_void_t 		g2_draw_triangle(tb_handle_t painter, 		g2_triangle_t const* triangle);

// c plus plus
#ifdef __cplusplus
}
#endif

#endif
