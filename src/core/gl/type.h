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
 * @file		type.h
 *
 */
#ifndef G2_CORE_GL_TYPE_H
#define G2_CORE_GL_TYPE_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the gl rect type
typedef struct __g2_gl_rect_t
{
	tb_float_t 		x1;
	tb_float_t 		y1;
	tb_float_t 		x2;
	tb_float_t 		y2;

}g2_gl_rect_t;

// the gl stop type
typedef struct __g2_gl_stop_t
{
	g2_color_t 		color;
	g2_float_t 		radio;

}g2_gl_stop_t;

#endif
