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
 * @file		fill.h
 *
 */
#ifndef G2_CORE_GL2x_FILL_H
#define G2_CORE_GL2x_FILL_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "painter.h"

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

// fill rect
tb_void_t g2_gl2x_fill_rect(g2_gl2x_painter_t* painter, g2_rect_t const* rect);

// fill path
tb_void_t g2_gl2x_fill_path(g2_gl2x_painter_t* painter, g2_gl_path_t const* path);

// fill circle
tb_void_t g2_gl2x_fill_circle(g2_gl2x_painter_t* painter, g2_circle_t const* circle);

// fill ellipse
tb_void_t g2_gl2x_fill_ellipse(g2_gl2x_painter_t* painter, g2_ellipse_t const* ellipse);

// fill triangle
tb_void_t g2_gl2x_fill_triangle(g2_gl2x_painter_t* painter, g2_triangle_t const* triangle);

#endif
