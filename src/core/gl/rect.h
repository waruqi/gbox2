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
 * @file		rect.h
 *
 */
#ifndef G2_CORE_GL_RECT_H
#define G2_CORE_GL_RECT_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * inlines
 */
static __tb_inline__ tb_void_t g2_gl_rect_init(g2_gl_rect_t* rect, tb_float_t x, tb_float_t y)
{
	rect->x1 = x;
	rect->x2 = x;
	rect->y1 = y;
	rect->y2 = y;
}
static __tb_inline__ tb_void_t g2_gl_rect_done(g2_gl_rect_t* rect, tb_float_t x, tb_float_t y)
{
	if (x < rect->x1) rect->x1 = x;
	if (y < rect->y1) rect->y1 = y;
	if (x > rect->x2) rect->x2 = x;
	if (y > rect->y2) rect->y2 = y;
	rect->x2 += 1.0f;
	rect->y2 += 1.0f;
}

#endif
