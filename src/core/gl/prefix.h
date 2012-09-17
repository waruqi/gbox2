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
 * @file		prefix.h
 *
 */
#ifndef G2_CORE_GL_PREFIX_H
#define G2_CORE_GL_PREFIX_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "../prefix.h"
#include "../style.h"
#include "../path.h"
#include "../bitmap.h"
#include "../shader.h"
#include "../matrix.h"
#include "../painter.h"
#include "../context.h"
#include "../../gbox2.h"
#include "type.h"
#include "rect.h"
#include "path.h"
#include "matrix.h"
#include "extensions.h"
#if defined(TB_CONFIG_OS_MAC)
# 	include <OpenGL/gl.h>
# 	include <OpenGL/glu.h>
# 	include <GLUT/glut.h>
#elif defined(TB_CONFIG_OS_ANDROID)
# 	include <GLES/gl.h>
# 	include <GLES/glext.h>
#else
# 	define GL_GLEXT_PROTOTYPES
# 	include <GL/glut.h>
# 	include <GL/glext.h>
#endif

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */
#ifdef TB_CONFIG_OS_ANDROID
# 	define glOrtho 				glOrthof
#endif

#ifndef GL_MIRRORED_REPEAT
# 	define GL_MIRRORED_REPEAT 	GL_MIRRORED_REPEAT_ARB
#endif

#endif


