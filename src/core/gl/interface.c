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
 * @file		interface.c
 *
 */
/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "interface.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */
// define
#define G2_GL_INTERFACE_DEFINE(func) 			g2_##func##_t g2_##func = TB_NULL

// check
#define G2_GL_INTERFACE_CHECK(func) 			tb_assert_and_check_return_val(g2_##func, TB_FALSE)

// check & wrap
#define G2_GL_INTERFACE_CHECKW(func, wrap) 		if (!g2_##func && g2_##wrap) g2_##func = g2_gl_wraper_##func; tb_assert_and_check_return_val(g2_##func, TB_FALSE)

/* ///////////////////////////////////////////////////////////////////////
 * functions
 */

G2_GL_INTERFACE_DEFINE(glActiveTexture);
G2_GL_INTERFACE_DEFINE(glAlphaFunc);
G2_GL_INTERFACE_DEFINE(glAttachShader);
G2_GL_INTERFACE_DEFINE(glBindTexture);
G2_GL_INTERFACE_DEFINE(glBlendFunc);
G2_GL_INTERFACE_DEFINE(glClear);
G2_GL_INTERFACE_DEFINE(glClearColor);
G2_GL_INTERFACE_DEFINE(glClearStencil);
G2_GL_INTERFACE_DEFINE(glColor4f);
G2_GL_INTERFACE_DEFINE(glColorMask);
G2_GL_INTERFACE_DEFINE(glCompileShader);
G2_GL_INTERFACE_DEFINE(glCreateProgram);
G2_GL_INTERFACE_DEFINE(glCreateShader);
G2_GL_INTERFACE_DEFINE(glDeleteProgram);
G2_GL_INTERFACE_DEFINE(glDeleteShader);
G2_GL_INTERFACE_DEFINE(glDeleteTextures);
G2_GL_INTERFACE_DEFINE(glDisable);
G2_GL_INTERFACE_DEFINE(glDisableClientState);
G2_GL_INTERFACE_DEFINE(glDisableVertexAttribArray);
G2_GL_INTERFACE_DEFINE(glDrawArrays);
G2_GL_INTERFACE_DEFINE(glEnable);
G2_GL_INTERFACE_DEFINE(glEnableClientState);
G2_GL_INTERFACE_DEFINE(glEnableVertexAttribArray);
G2_GL_INTERFACE_DEFINE(glGenTextures);
G2_GL_INTERFACE_DEFINE(glGetAttribLocation);
G2_GL_INTERFACE_DEFINE(glGetProgramiv);
G2_GL_INTERFACE_DEFINE(glGetProgramInfoLog);
G2_GL_INTERFACE_DEFINE(glGetShaderiv);
G2_GL_INTERFACE_DEFINE(glGetShaderInfoLog);
G2_GL_INTERFACE_DEFINE(glGetString);
G2_GL_INTERFACE_DEFINE(glGetUniformLocation);
G2_GL_INTERFACE_DEFINE(glIsTexture);
G2_GL_INTERFACE_DEFINE(glLinkProgram);
G2_GL_INTERFACE_DEFINE(glLoadIdentity);
G2_GL_INTERFACE_DEFINE(glLoadMatrixf);
G2_GL_INTERFACE_DEFINE(glMatrixMode);
G2_GL_INTERFACE_DEFINE(glMultMatrixf);
G2_GL_INTERFACE_DEFINE(glOrtho);
G2_GL_INTERFACE_DEFINE(glOrthof);
G2_GL_INTERFACE_DEFINE(glPixelStorei);
G2_GL_INTERFACE_DEFINE(glPopMatrix);
G2_GL_INTERFACE_DEFINE(glPushMatrix);
G2_GL_INTERFACE_DEFINE(glRotatef);
G2_GL_INTERFACE_DEFINE(glScalef);
G2_GL_INTERFACE_DEFINE(glShaderSource);
G2_GL_INTERFACE_DEFINE(glStencilFunc);
G2_GL_INTERFACE_DEFINE(glStencilMask);
G2_GL_INTERFACE_DEFINE(glStencilOp);
G2_GL_INTERFACE_DEFINE(glTexCoordPointer);
G2_GL_INTERFACE_DEFINE(glTexEnvi);
G2_GL_INTERFACE_DEFINE(glTexImage1D);
G2_GL_INTERFACE_DEFINE(glTexImage2D);
G2_GL_INTERFACE_DEFINE(glTexParameterf);
G2_GL_INTERFACE_DEFINE(glTexParameteri);
G2_GL_INTERFACE_DEFINE(glTranslatef);
G2_GL_INTERFACE_DEFINE(glUniform1i);
G2_GL_INTERFACE_DEFINE(glUniformMatrix4fv);
G2_GL_INTERFACE_DEFINE(glUseProgram);
G2_GL_INTERFACE_DEFINE(glVertexAttrib4f);
G2_GL_INTERFACE_DEFINE(glVertexAttribPointer);
G2_GL_INTERFACE_DEFINE(glVertexPointer);
G2_GL_INTERFACE_DEFINE(glViewport);

/* ///////////////////////////////////////////////////////////////////////
 * wraper
 */
static g2_GLvoid_t G2_GL_APICALL g2_gl_wraper_glOrthof(g2_GLfloat_t left, g2_GLfloat_t right, g2_GLfloat_t bottom, g2_GLfloat_t top, g2_GLfloat_t near, g2_GLfloat_t far)
{
	g2_glOrtho(left, right, bottom, top, near, far);
}

/* ///////////////////////////////////////////////////////////////////////
 * checker
 */

tb_bool_t g2_gl_interface_check(tb_byte_t version)
{
	// check interfaces for common
	G2_GL_INTERFACE_CHECK 	(glActiveTexture);
//	G2_GL_INTERFACE_CHECK 	(glAlphaFunc);
	G2_GL_INTERFACE_CHECK 	(glBindTexture);
	G2_GL_INTERFACE_CHECK 	(glBlendFunc);
	G2_GL_INTERFACE_CHECK 	(glClear);
	G2_GL_INTERFACE_CHECK 	(glClearColor);
//	G2_GL_INTERFACE_CHECK 	(glClearStencil);
	G2_GL_INTERFACE_CHECK 	(glColorMask);
	G2_GL_INTERFACE_CHECK 	(glDeleteTextures);
	G2_GL_INTERFACE_CHECK 	(glDisable);
	G2_GL_INTERFACE_CHECK 	(glDrawArrays);
	G2_GL_INTERFACE_CHECK 	(glEnable);
	G2_GL_INTERFACE_CHECK 	(glGenTextures);
	G2_GL_INTERFACE_CHECK 	(glGetString);
//	G2_GL_INTERFACE_CHECK 	(glIsTexture);
//	G2_GL_INTERFACE_CHECK 	(glPixelStorei);
	G2_GL_INTERFACE_CHECK 	(glStencilFunc);
	G2_GL_INTERFACE_CHECK 	(glStencilMask);
	G2_GL_INTERFACE_CHECK 	(glStencilOp);
#ifndef G2_CONFIG_CORE_GLES
	G2_GL_INTERFACE_CHECK 	(glTexImage1D);
#endif
	G2_GL_INTERFACE_CHECK 	(glTexImage2D);
	G2_GL_INTERFACE_CHECK 	(glTexParameterf);
	G2_GL_INTERFACE_CHECK 	(glTexParameteri);
	G2_GL_INTERFACE_CHECK 	(glViewport);

	// check interfaces for gl 1.x
	if (version < 0x20)
	{
		G2_GL_INTERFACE_CHECK 	(glColor4f);
		G2_GL_INTERFACE_CHECK 	(glDisableClientState);
		G2_GL_INTERFACE_CHECK 	(glEnableClientState);
		G2_GL_INTERFACE_CHECK 	(glLoadIdentity);
		G2_GL_INTERFACE_CHECK 	(glLoadMatrixf);
		G2_GL_INTERFACE_CHECK 	(glMatrixMode);
		G2_GL_INTERFACE_CHECK 	(glMultMatrixf);
		G2_GL_INTERFACE_CHECKW 	(glOrthof, glOrtho);
		G2_GL_INTERFACE_CHECK 	(glPopMatrix);
		G2_GL_INTERFACE_CHECK 	(glPushMatrix);
//		G2_GL_INTERFACE_CHECK 	(glRotatef);
//		G2_GL_INTERFACE_CHECK 	(glScalef);
		G2_GL_INTERFACE_CHECK 	(glTexCoordPointer);
		G2_GL_INTERFACE_CHECK 	(glTexEnvi);
//		G2_GL_INTERFACE_CHECK 	(glTranslatef);
		G2_GL_INTERFACE_CHECK 	(glVertexPointer);
	}
	// check interfaces for gl >= 2.0
	else
	{
		G2_GL_INTERFACE_CHECK 	(glAttachShader);
		G2_GL_INTERFACE_CHECK 	(glCompileShader);
		G2_GL_INTERFACE_CHECK 	(glCreateProgram);
		G2_GL_INTERFACE_CHECK 	(glCreateShader);
		G2_GL_INTERFACE_CHECK 	(glDeleteProgram);
		G2_GL_INTERFACE_CHECK 	(glDeleteShader);
		G2_GL_INTERFACE_CHECK 	(glDisableVertexAttribArray);
		G2_GL_INTERFACE_CHECK 	(glEnableVertexAttribArray);
		G2_GL_INTERFACE_CHECK 	(glGetAttribLocation);
		G2_GL_INTERFACE_CHECK 	(glGetProgramiv);
		G2_GL_INTERFACE_CHECK 	(glGetProgramInfoLog);
		G2_GL_INTERFACE_CHECK 	(glGetShaderiv);
		G2_GL_INTERFACE_CHECK 	(glGetShaderInfoLog);
		G2_GL_INTERFACE_CHECK 	(glGetUniformLocation);
		G2_GL_INTERFACE_CHECK 	(glLinkProgram);
		G2_GL_INTERFACE_CHECK 	(glShaderSource);
		G2_GL_INTERFACE_CHECK 	(glUniform1i);
		G2_GL_INTERFACE_CHECK 	(glUniformMatrix4fv);
		G2_GL_INTERFACE_CHECK 	(glUseProgram);
		G2_GL_INTERFACE_CHECK 	(glVertexAttrib4f);
		G2_GL_INTERFACE_CHECK 	(glVertexAttribPointer);
	}


	// ok
	return TB_TRUE;
}
