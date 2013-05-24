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
 * @file		stok.h
 *
 */
#ifndef G2_CORE_GL_STOK_H
#define G2_CORE_GL_STOK_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "painter.h"

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

// stok arc
tb_void_t g2_gl_stok_arc(g2_gl_painter_t* painter, g2_arc_t const* arc);

// stok line
tb_void_t g2_gl_stok_line(g2_gl_painter_t* painter, g2_line_t const* line);

// stok rect
tb_void_t g2_gl_stok_rect(g2_gl_painter_t* painter, g2_rect_t const* rect);

// stok path
tb_void_t g2_gl_stok_path(g2_gl_painter_t* painter, g2_gl_path_t const* path);

// stok point
tb_void_t g2_gl_stok_point(g2_gl_painter_t* painter, g2_point_t const* point);

// stok circle
tb_void_t g2_gl_stok_circle(g2_gl_painter_t* painter, g2_circle_t const* circle);

// stok ellipse
tb_void_t g2_gl_stok_ellipse(g2_gl_painter_t* painter, g2_ellipse_t const* ellipse);

// stok triangle
tb_void_t g2_gl_stok_triangle(g2_gl_painter_t* painter, g2_triangle_t const* triangle);

#endif
