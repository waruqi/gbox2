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
tb_handle_t 	g2_init(tb_handle_t hsurface);
tb_void_t 		g2_exit(tb_handle_t hpainter);

// save & load
tb_void_t 		g2_save(tb_handle_t hpainter);
tb_void_t 		g2_load(tb_handle_t hpainter);

// draw
tb_void_t 		g2_draw_clear(tb_handle_t hpainter);
tb_void_t 		g2_draw_arc(tb_handle_t hpainter, 		g2_arc_t const* arc);
tb_void_t 		g2_draw_pie(tb_handle_t hpainter, 		g2_pie_t const* pie);
tb_void_t 		g2_draw_path(tb_handle_t hpainter, 		g2_path_t const* path);
tb_void_t 		g2_draw_rect(tb_handle_t hpainter, 		g2_rect_t const* rect);
tb_void_t 		g2_draw_line(tb_handle_t hpainter, 		g2_line_t const* line);
tb_void_t 		g2_draw_text(tb_handle_t hpainter, 		g2_text_t const* text);
tb_void_t 		g2_draw_lines(tb_handle_t hpainter, 	g2_lines_t const* lines);
tb_void_t 		g2_draw_chord(tb_handle_t hpainter, 	g2_chord_t const* chord);
tb_void_t 		g2_draw_curve1(tb_handle_t hpainter, 	g2_curve1_t const* curve1);
tb_void_t 		g2_draw_curve2(tb_handle_t hpainter, 	g2_curve2_t const* curve2);
tb_void_t 		g2_draw_circle(tb_handle_t hpainter, 	g2_circle_t const* circle);
tb_void_t 		g2_draw_ellipse(tb_handle_t hpainter, 	g2_ellipse_t const* ellipse);
tb_void_t 		g2_draw_polygon(tb_handle_t hpainter, 	g2_polygon_t const* polygon);
tb_void_t 		g2_draw_triangle(tb_handle_t hpainter, 	g2_triangle_t const* triangle);

// clip
tb_void_t 		g2_clip_clear(tb_handle_t hpainter);
tb_void_t 		g2_clip_pie(tb_handle_t hpainter, 		g2_pie_t const* pie);
tb_void_t 		g2_clip_path(tb_handle_t hpainter, 		g2_path_t const* path);
tb_void_t 		g2_clip_rect(tb_handle_t hpainter, 		g2_rect_t const* rect);
tb_void_t 		g2_clip_circle(tb_handle_t hpainter, 	g2_circle_t const* circle);
tb_void_t 		g2_clip_ellipse(tb_handle_t hpainter, 	g2_ellipse_t const* ellipse);
tb_void_t 		g2_clip_polygon(tb_handle_t hpainter, 	g2_polygon_t const* polygon);
tb_void_t 		g2_clip_triangle(tb_handle_t hpainter, 	g2_triangle_t const* triangle);

// c plus plus
#ifdef __cplusplus
}
#endif

#endif
