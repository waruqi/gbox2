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
tb_handle_t 		g2_init(tb_handle_t surface);
tb_void_t 			g2_exit(tb_handle_t painter);

// save & load
tb_void_t 			g2_save(tb_handle_t painter);
tb_void_t 			g2_load(tb_handle_t painter);

// style
tb_handle_t 		g2_style(tb_handle_t painter);
tb_void_t 			g2_style_set(tb_handle_t painter, tb_handle_t style);

// clipper
tb_handle_t 		g2_clipper(tb_handle_t painter, tb_handle_t clipper);

// matrix
g2_matrix_t const* 	g2_matrix(tb_handle_t painter);
tb_void_t 			g2_matrix_set(tb_handle_t painter, g2_matrix_t const* matrix);

tb_void_t 			g2_rotate(tb_handle_t painter, g2_scalar_t degrees);
tb_void_t 			g2_scale(tb_handle_t painter, g2_scalar_t sx, g2_scalar_t sy);
tb_void_t 			g2_translate(tb_handle_t painter, g2_scalar_t dx, g2_scalar_t dy);

// clear
tb_void_t 			g2_clear(tb_handle_t painter, g2_color_t color);

// draw path
tb_void_t 			g2_draw_path(tb_handle_t painter, tb_handle_t path);

// draw 
tb_void_t 			g2_draw_arc(tb_handle_t painter, 			g2_arc_t const* arc);
tb_void_t 			g2_draw_rect(tb_handle_t painter, 			g2_rect_t const* rect);
tb_void_t 			g2_draw_line(tb_handle_t painter, 			g2_line_t const* line);
tb_void_t 			g2_draw_point(tb_handle_t painter, 			g2_point_t const* point);
tb_void_t 			g2_draw_circle(tb_handle_t painter, 		g2_circle_t const* circle);
tb_void_t 			g2_draw_ellipse(tb_handle_t painter, 		g2_ellipse_t const* ellipse);
tb_void_t 			g2_draw_triangle(tb_handle_t painter, 		g2_triangle_t const* triangle);

tb_void_t 			g2_drawi_arc(tb_handle_t painter, 			g2_iarc_t const* arc);
tb_void_t 			g2_drawi_rect(tb_handle_t painter, 			g2_irect_t const* rect);
tb_void_t 			g2_drawi_line(tb_handle_t painter, 			g2_iline_t const* line);
tb_void_t 			g2_drawi_point(tb_handle_t painter, 		g2_ipoint_t const* point);
tb_void_t 			g2_drawi_circle(tb_handle_t painter, 		g2_icircle_t const* circle);
tb_void_t 			g2_drawi_ellipse(tb_handle_t painter, 		g2_iellipse_t const* ellipse);
tb_void_t 			g2_drawi_triangle(tb_handle_t painter, 		g2_itriangle_t const* triangle);

tb_void_t 			g2_draw2_arc(tb_handle_t painter, 			g2_scalar_t x0, g2_scalar_t y0, g2_scalar_t rx, g2_scalar_t ry, g2_scalar_t ab, g2_scalar_t an);
tb_void_t 			g2_draw2_line(tb_handle_t painter, 			g2_scalar_t x0, g2_scalar_t y0, g2_scalar_t x1, g2_scalar_t y1);
tb_void_t 			g2_draw2_rect(tb_handle_t painter, 			g2_scalar_t x, g2_scalar_t y, g2_scalar_t w, g2_scalar_t h);
tb_void_t 			g2_draw2_point(tb_handle_t painter, 		g2_scalar_t x, g2_scalar_t y);
tb_void_t 			g2_draw2_circle(tb_handle_t painter, 		g2_scalar_t x0, g2_scalar_t y0, g2_scalar_t r);
tb_void_t 			g2_draw2_ellipse(tb_handle_t painter, 		g2_scalar_t x0, g2_scalar_t y0, g2_scalar_t rx, g2_scalar_t ry);
tb_void_t 			g2_draw2_triangle(tb_handle_t painter, 		g2_scalar_t x0, g2_scalar_t y0, g2_scalar_t x1, g2_scalar_t y1, g2_scalar_t x2, g2_scalar_t y2);

tb_void_t 			g2_draw2i_arc(tb_handle_t painter, 			tb_long_t x0, tb_long_t y0, tb_size_t rx, tb_size_t ry, tb_size_t ab, tb_size_t an);
tb_void_t 			g2_draw2i_line(tb_handle_t painter, 		tb_long_t x0, tb_long_t y0, tb_long_t x1, tb_long_t y1);
tb_void_t 			g2_draw2i_rect(tb_handle_t painter, 		tb_long_t x, tb_long_t y, tb_size_t w, tb_size_t h);
tb_void_t 			g2_draw2i_point(tb_handle_t painter, 		tb_long_t x, tb_long_t y);
tb_void_t 			g2_draw2i_circle(tb_handle_t painter, 		tb_long_t x0, tb_long_t y0, tb_size_t r);
tb_void_t 			g2_draw2i_ellipse(tb_handle_t painter, 		tb_long_t x0, tb_long_t y0, tb_size_t rx, tb_size_t ry);
tb_void_t 			g2_draw2i_triangle(tb_handle_t painter, 	tb_long_t x0, tb_long_t y0, tb_long_t x1, tb_long_t y1, tb_long_t x2, tb_long_t y2);

// c plus plus
#ifdef __cplusplus
}
#endif

#endif
