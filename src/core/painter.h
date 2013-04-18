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
#include "matrix.h"

/* ///////////////////////////////////////////////////////////////////////
 * init & exit
 */

// init
tb_handle_t 		g2_init(tb_handle_t context);

// exit
tb_void_t 			g2_exit(tb_handle_t painter);

/* ///////////////////////////////////////////////////////////////////////
 * accessors
 */

// pixfmt
tb_size_t 			g2_pixfmt(tb_handle_t painter);

// context
tb_handle_t 		g2_context(tb_handle_t painter);

// path
tb_handle_t 		g2_path(tb_handle_t painter);

// style
tb_handle_t 		g2_style(tb_handle_t painter);

// matrix
g2_matrix_t* 		g2_matrix(tb_handle_t painter);

// clipper
tb_handle_t 		g2_clipper(tb_handle_t painter);

/* ///////////////////////////////////////////////////////////////////////
 * save & load
 */

// path
tb_handle_t 		g2_save_path(tb_handle_t painter);
tb_void_t 			g2_load_path(tb_handle_t painter);

// style
tb_handle_t 		g2_save_style(tb_handle_t painter);
tb_void_t 			g2_load_style(tb_handle_t painter);

// matrix
g2_matrix_t* 		g2_save_matrix(tb_handle_t painter);
tb_void_t 			g2_load_matrix(tb_handle_t painter);

// clipper
tb_handle_t 		g2_save_clipper(tb_handle_t painter);
tb_void_t 			g2_load_clipper(tb_handle_t painter);

/* ///////////////////////////////////////////////////////////////////////
 * clear
 */

// drawer
tb_void_t 			g2_clear(tb_handle_t painter, g2_color_t color);

// path
tb_void_t 			g2_clear_path(tb_handle_t painter);

// style
tb_void_t 			g2_clear_style(tb_handle_t painter);

// matrix
tb_void_t 			g2_clear_matrix(tb_handle_t painter);

// clipper
tb_void_t 			g2_clear_clipper(tb_handle_t painter);

/* ///////////////////////////////////////////////////////////////////////
 * style
 */

// mode
tb_void_t 			g2_mode(tb_handle_t painter, 				tb_size_t mode);

// flag
tb_void_t 			g2_flag(tb_handle_t painter, 				tb_size_t flag);

// color
tb_void_t 			g2_color(tb_handle_t painter, 				g2_color_t color);

// alpha
tb_void_t 			g2_alpha(tb_handle_t painter, 				tb_byte_t alpha);

// width
tb_void_t 			g2_width(tb_handle_t painter, 				g2_float_t width);

// cap
tb_void_t 			g2_cap(tb_handle_t painter, 				tb_size_t cap);

// join
tb_void_t 			g2_join(tb_handle_t painter, 				tb_size_t join);

// shader
tb_void_t 			g2_shader(tb_handle_t painter, 				tb_handle_t shader);

/* ///////////////////////////////////////////////////////////////////////
 * matrix
 */

// save
g2_matrix_t* 		g2_save_matrix(tb_handle_t painter);

// load
tb_void_t 			g2_load_matrix(tb_handle_t painter);

// rotate
tb_bool_t 			g2_rotate(tb_handle_t painter, 				g2_float_t degrees);
tb_bool_t 			g2_rotate_lhs(tb_handle_t painter, 			g2_float_t degrees);

// rotatep
tb_bool_t 			g2_rotatep(tb_handle_t painter, 			g2_float_t degrees, g2_float_t px, g2_float_t py);
tb_bool_t 			g2_rotatep_lhs(tb_handle_t painter, 		g2_float_t degrees, g2_float_t px, g2_float_t py);

// scale
tb_bool_t 			g2_scale(tb_handle_t painter, 				g2_float_t sx, g2_float_t sy);
tb_bool_t 			g2_scale_lhs(tb_handle_t painter, 			g2_float_t sx, g2_float_t sy);

// scalep
tb_bool_t 			g2_scalep(tb_handle_t painter, 				g2_float_t sx, g2_float_t sy, g2_float_t px, g2_float_t py);
tb_bool_t 			g2_scalep_lhs(tb_handle_t painter, 			g2_float_t sx, g2_float_t sy, g2_float_t px, g2_float_t py);

// skew
tb_bool_t 			g2_skew(tb_handle_t painter, 				g2_float_t kx, g2_float_t ky);
tb_bool_t 			g2_skew_lhs(tb_handle_t painter, 			g2_float_t kx, g2_float_t ky);

// skewp
tb_bool_t 			g2_skewp(tb_handle_t painter, 				g2_float_t kx, g2_float_t ky, g2_float_t px, g2_float_t py);
tb_bool_t 			g2_skewp_lhs(tb_handle_t painter, 			g2_float_t kx, g2_float_t ky, g2_float_t px, g2_float_t py);

// sincos
tb_bool_t 			g2_sincos(tb_handle_t painter, 				g2_float_t sin, g2_float_t cos);
tb_bool_t 			g2_sincos_lhs(tb_handle_t painter, 			g2_float_t sin, g2_float_t cos);

// sincosp
tb_bool_t 			g2_sincosp(tb_handle_t painter, 			g2_float_t sin, g2_float_t cos, g2_float_t px, g2_float_t py);
tb_bool_t 			g2_sincosp_lhs(tb_handle_t painter, 		g2_float_t sin, g2_float_t cos, g2_float_t px, g2_float_t py);

// translate
tb_bool_t 			g2_translate(tb_handle_t painter, 			g2_float_t dx, g2_float_t dy);
tb_bool_t 			g2_translate_lhs(tb_handle_t painter, 		g2_float_t dx, g2_float_t dy);

// multiply
tb_bool_t 			g2_multiply(tb_handle_t painter, 			g2_matrix_t const* matrix);
tb_bool_t 			g2_multiply_lhs(tb_handle_t painter, 		g2_matrix_t const* matrix);

/* ///////////////////////////////////////////////////////////////////////
 * path
 */

// close
tb_void_t 			g2_close(tb_handle_t painter);

// move to
tb_void_t 			g2_move_to(tb_handle_t painter, 			g2_point_t const* pt);
tb_void_t 			g2_movei_to(tb_handle_t painter, 			g2_ipoint_t const* pt);
tb_void_t 			g2_move2_to(tb_handle_t painter, 			g2_float_t x, g2_float_t y);
tb_void_t 			g2_move2i_to(tb_handle_t painter, 			tb_long_t x, tb_long_t y);

// line to
tb_void_t 			g2_line_to(tb_handle_t painter, 			g2_point_t const* pt);
tb_void_t 			g2_linei_to(tb_handle_t painter, 			g2_ipoint_t const* pt);
tb_void_t 			g2_line2_to(tb_handle_t painter, 			g2_float_t x, g2_float_t y);
tb_void_t 			g2_line2i_to(tb_handle_t painter, 			tb_long_t x, tb_long_t y);

// quad to
tb_void_t 			g2_quad_to(tb_handle_t painter, 			g2_point_t const* cp, g2_point_t const* pt);
tb_void_t 			g2_quadi_to(tb_handle_t painter, 			g2_ipoint_t const* cp, g2_ipoint_t const* pt);
tb_void_t 			g2_quad2_to(tb_handle_t painter, 			g2_float_t cx, g2_float_t cy, g2_float_t x, g2_float_t y);
tb_void_t 			g2_quad2i_to(tb_handle_t painter, 			tb_long_t cx, tb_long_t cy, tb_long_t x, tb_long_t y);

// cube to
tb_void_t 			g2_cube_to(tb_handle_t painter, 			g2_point_t const* c0, g2_point_t const* c1, g2_point_t const* pt);
tb_void_t 			g2_cubei_to(tb_handle_t painter, 			g2_ipoint_t const* c0, g2_ipoint_t const* c1, g2_ipoint_t const* pt);
tb_void_t 			g2_cube2_to(tb_handle_t painter, 			g2_float_t cx0, g2_float_t cy0, g2_float_t cx1, g2_float_t cy1, g2_float_t x, g2_float_t y);
tb_void_t 			g2_cube2i_to(tb_handle_t painter, 			tb_long_t cx0, tb_long_t cy0, tb_long_t cx1, tb_long_t cy1, tb_long_t x, tb_long_t y);

// arc to
tb_void_t 			g2_arc_to(tb_handle_t painter, 				g2_arc_t const* arc);
tb_void_t 			g2_arci_to(tb_handle_t painter, 			g2_iarc_t const* arc);
tb_void_t 			g2_arc2_to(tb_handle_t painter, 			g2_float_t x0, g2_float_t y0, g2_float_t rx, g2_float_t ry, g2_float_t ab, g2_float_t an);
tb_void_t 			g2_arc2i_to(tb_handle_t painter, 			tb_long_t x0, tb_long_t y0, tb_size_t rx, tb_size_t ry, tb_size_t ab, tb_size_t an);

/* ///////////////////////////////////////////////////////////////////////
 * clipper
 */

// path
tb_void_t 			g2_clip_path(tb_handle_t painter, 			tb_size_t mode, tb_handle_t path);

// triangle
tb_void_t 			g2_clip_triangle(tb_handle_t painter, 		tb_size_t mode, g2_triangle_t const* triangle);
tb_void_t 			g2_clip_triangle2(tb_handle_t painter, 		tb_size_t mode, g2_float_t x0, g2_float_t y0, g2_float_t x1, g2_float_t y1, g2_float_t x2, g2_float_t y2);

// itriangle
tb_void_t 			g2_clip_itriangle(tb_handle_t painter, 		tb_size_t mode, g2_itriangle_t const* triangle);
tb_void_t 			g2_clip_itriangle2(tb_handle_t painter, 	tb_size_t mode, tb_long_t x0, tb_long_t y0, tb_long_t x1, tb_long_t y1, tb_long_t x2, tb_long_t y2);

// rect
tb_void_t 			g2_clip_rect(tb_handle_t painter, 			tb_size_t mode, g2_rect_t const* rect);
tb_void_t 			g2_clip_rect2(tb_handle_t painter, 			tb_size_t mode, g2_float_t x, g2_float_t y, g2_float_t w, g2_float_t h);

// irect
tb_void_t 			g2_clip_irect(tb_handle_t painter, 			tb_size_t mode, g2_irect_t const* rect);
tb_void_t 			g2_clip_irect2(tb_handle_t painter, 		tb_size_t mode, tb_long_t x, tb_long_t y, tb_size_t w, tb_size_t h);

// circle
tb_void_t 			g2_clip_circle(tb_handle_t painter, 		tb_size_t mode, g2_circle_t const* circle);
tb_void_t 			g2_clip_circle2(tb_handle_t painter, 		tb_size_t mode, g2_float_t x0, g2_float_t y0, g2_float_t r);

// icircle
tb_void_t 			g2_clip_icircle(tb_handle_t painter, 		tb_size_t mode, g2_icircle_t const* circle);
tb_void_t 			g2_clip_icircle2(tb_handle_t painter, 		tb_size_t mode, tb_long_t x0, tb_long_t y0, tb_size_t r);

// ellipse
tb_void_t 			g2_clip_ellipse(tb_handle_t painter, 		tb_size_t mode, g2_ellipse_t const* ellipse);
tb_void_t 			g2_clip_ellipse2(tb_handle_t painter, 		tb_size_t mode, g2_float_t x0, g2_float_t y0, g2_float_t rx, g2_float_t ry);

// iellipse
tb_void_t 			g2_clip_iellipse(tb_handle_t painter, 		tb_size_t mode, g2_iellipse_t const* ellipse);
tb_void_t 			g2_clip_iellipse2(tb_handle_t painter, 		tb_size_t mode, tb_long_t x0, tb_long_t y0, tb_size_t rx, tb_size_t ry);

/* ///////////////////////////////////////////////////////////////////////
 * drawer
 */

// clear
tb_void_t 			g2_draw_clear(tb_handle_t painter, 			g2_color_t color);

// path
tb_void_t 			g2_draw(tb_handle_t painter);
tb_void_t 			g2_draw_path(tb_handle_t painter, 			tb_handle_t path);

// point
tb_void_t 			g2_draw_point(tb_handle_t painter, 			g2_point_t const* point);
tb_void_t 			g2_draw_point2(tb_handle_t painter, 		g2_float_t x, g2_float_t y);

// ipoint
tb_void_t 			g2_draw_ipoint(tb_handle_t painter, 		g2_ipoint_t const* point);
tb_void_t 			g2_draw_ipoint2(tb_handle_t painter, 		tb_long_t x, tb_long_t y);

// line
tb_void_t 			g2_draw_line(tb_handle_t painter, 			g2_line_t const* line);
tb_void_t 			g2_draw_line2(tb_handle_t painter, 			g2_float_t x0, g2_float_t y0, g2_float_t x1, g2_float_t y1);

// iline
tb_void_t 			g2_draw_iline(tb_handle_t painter, 			g2_iline_t const* line);
tb_void_t 			g2_draw_iline2(tb_handle_t painter, 		tb_long_t x0, tb_long_t y0, tb_long_t x1, tb_long_t y1);

// arc
tb_void_t 			g2_draw_arc(tb_handle_t painter, 			g2_arc_t const* arc);
tb_void_t 			g2_draw_arc2(tb_handle_t painter, 			g2_float_t x0, g2_float_t y0, g2_float_t rx, g2_float_t ry, g2_float_t ab, g2_float_t an);

// iarc
tb_void_t 			g2_draw_iarc(tb_handle_t painter, 			g2_iarc_t const* arc);
tb_void_t 			g2_draw_iarc2(tb_handle_t painter, 			tb_long_t x0, tb_long_t y0, tb_size_t rx, tb_size_t ry, tb_size_t ab, tb_size_t an);

// triangle
tb_void_t 			g2_draw_triangle(tb_handle_t painter, 		g2_triangle_t const* triangle);
tb_void_t 			g2_draw_triangle2(tb_handle_t painter, 		g2_float_t x0, g2_float_t y0, g2_float_t x1, g2_float_t y1, g2_float_t x2, g2_float_t y2);

// itriangle
tb_void_t 			g2_draw_itriangle(tb_handle_t painter, 		g2_itriangle_t const* triangle);
tb_void_t 			g2_draw_itriangle2(tb_handle_t painter, 	tb_long_t x0, tb_long_t y0, tb_long_t x1, tb_long_t y1, tb_long_t x2, tb_long_t y2);

// rect
tb_void_t 			g2_draw_rect(tb_handle_t painter, 			g2_rect_t const* rect);
tb_void_t 			g2_draw_rect2(tb_handle_t painter, 			g2_float_t x, g2_float_t y, g2_float_t w, g2_float_t h);

// irect
tb_void_t 			g2_draw_irect(tb_handle_t painter, 			g2_irect_t const* rect);
tb_void_t 			g2_draw_irect2(tb_handle_t painter, 		tb_long_t x, tb_long_t y, tb_size_t w, tb_size_t h);

// circle
tb_void_t 			g2_draw_circle(tb_handle_t painter, 		g2_circle_t const* circle);
tb_void_t 			g2_draw_circle2(tb_handle_t painter, 		g2_float_t x0, g2_float_t y0, g2_float_t r);

// icircle
tb_void_t 			g2_draw_icircle(tb_handle_t painter, 		g2_icircle_t const* circle);
tb_void_t 			g2_draw_icircle2(tb_handle_t painter, 		tb_long_t x0, tb_long_t y0, tb_size_t r);

// ellipse
tb_void_t 			g2_draw_ellipse(tb_handle_t painter, 		g2_ellipse_t const* ellipse);
tb_void_t 			g2_draw_ellipse2(tb_handle_t painter, 		g2_float_t x0, g2_float_t y0, g2_float_t rx, g2_float_t ry);

// iellipse
tb_void_t 			g2_draw_iellipse(tb_handle_t painter, 		g2_iellipse_t const* ellipse);
tb_void_t 			g2_draw_iellipse2(tb_handle_t painter, 		tb_long_t x0, tb_long_t y0, tb_size_t rx, tb_size_t ry);

// c plus plus
#ifdef __cplusplus
}
#endif

#endif
