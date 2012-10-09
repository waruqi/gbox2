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
 * @file		interface.h
 *
 */
#ifndef G2_CORE_GL_INTERFACE_H
#define G2_CORE_GL_INTERFACE_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "../prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * basic type
 */

typedef tb_uint_t 		g2_GLenum_t;
typedef tb_byte_t 		g2_GLboolean_t;
typedef tb_uint_t 		g2_GLbitfield_t;
typedef tb_void_t 		g2_GLvoid_t;
typedef tb_char_t 		g2_GLbyte_t;
typedef tb_ushort_t 	g2_GLushort_t;
typedef tb_short_t 		g2_GLshort_t;
typedef tb_int_t 		g2_GLint_t;
typedef tb_byte_t 		g2_GLubyte_t;
typedef tb_uint_t 		g2_GLuint_t;
typedef tb_int_t 		g2_GLsizei_t;
typedef tb_float_t 		g2_GLfloat_t;
typedef tb_float_t 		g2_GLclampf_t;
typedef tb_double_t 	g2_GLdouble_t;
typedef tb_double_t 	g2_GLclampd_t;

/* ///////////////////////////////////////////////////////////////////////
 * interface types
 */

typedef tb_void_t 	(__tb_cdecl__ *g2_glViewport_t)(g2_GLint_t x, g2_GLint_t y, g2_GLsizei_t width, g2_GLsizei_t height);

/* ///////////////////////////////////////////////////////////////////////
 * functions
 */

extern g2_glViewport_t 	g2_glViewport;

#endif
