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
 * macros
 */

// gl apicall
#define G2_GL_APICALL 							G2_CONFIG_GL_APICALL

// type
#define G2_GL_INTERFACE_TYPE(func) 				G2_GL_APICALL *g2_##func##_t

// extern
#define G2_GL_INTERFACE_EXTERN(func) 			extern g2_##func##_t g2_##func

// load the static function
#define G2_GL_INTERFACE_LOAD_S(func) 			g2_##func = func

// load the dynamic function
#define G2_GL_INTERFACE_LOAD_D(library, func) 	g2_##func = (g2_##func##_t)tb_dynamic_func(library, #func)

/* ///////////////////////////////////////////////////////////////////////
 * macros for gl
 */

// data type 
#define G2_GL_BYTE 						(0x1400)
#define G2_GL_UNSIGNED_BYTE 			(0x1401)
#define G2_GL_SHORT 					(0x1402)
#define G2_GL_UNSIGNED_SHORT 			(0x1403)
#define G2_GL_FLOAT 					(0x1406)
#define G2_GL_FIXED 					(0x140C)

// boolean
#define G2_GL_FALSE 					(0)
#define G2_GL_TRUE 						(1)

// string name
#define G2_GL_VENDOR 					(0x1F00)
#define G2_GL_RENDERER 					(0x1F01)
#define G2_GL_VERSION 					(0x1F02)
#define G2_GL_EXTENSIONS 				(0x1F03)

// matrix mode
#define G2_GL_MATRIX_MODE 				(0x0BA0)
#define G2_GL_MODELVIEW 				(0x1700)
#define G2_GL_PROJECTION 				(0x1701)
#define G2_GL_TEXTURE 					(0x1702)

// vertex arrays
#define G2_GL_VERTEX_ARRAY 				(0x8074)

// color arrays
#define G2_GL_COLOR_ARRAY 				(0x8076)

// texture arrays
#define G2_GL_TEXTURE_COORD_ARRAY 		(0x8078)

// texture parameter name
#define G2_GL_TEXTURE_WRAP_S 			(0x2802)
#define G2_GL_TEXTURE_WRAP_T 			(0x2803)
#define G2_GL_TEXTURE_MAG_FILTER 		(0x2800)
#define G2_GL_TEXTURE_MIN_FILTER 		(0x2801)

// texture env parameter
#define G2_GL_TEXTURE_ENV_MODE 			(0x2200)
#define g2_GL_TEXTURE_ENV_COLOR 		(0x2201)

// texture env target
#define G2_GL_TEXTURE_ENV 				(0x2300)

// texture env mode
#define G2_GL_MODULATE 					(0x2100)
#define G2_GL_DECAL 					(0x2101)
//#define G2_GL_BLEND
#define G2_GL_ADD 						(0x0104)
//#define G2_GL_REPLACE

// texture mag filter
#define G2_GL_NEAREST 					(0x2600)
#define G2_GL_LINEAR 					(0x2601)

// blending
#define G2_GL_BLEND 					(0x0BE2)
#define G2_GL_BLEND_SRC 				(0x0BE1)
#define G2_GL_BLEND_DST 				(0x0BE0)
#define G2_GL_ZERO 						(0x0)
#define G2_GL_ONE 						(0x1)
#define G2_GL_SRC_COLOR 				(0x0300)
#define G2_GL_ONE_MINUS_SRC_COLOR 		(0x0301)
#define G2_GL_SRC_ALPHA 				(0x0302)
#define G2_GL_ONE_MINUS_SRC_ALPHA 		(0x0303)
#define G2_GL_DST_ALPHA 				(0x0304)
#define G2_GL_ONE_MINUS_DST_ALPHA 		(0x0305)
#define G2_GL_DST_COLOR 				(0x0306)
#define G2_GL_ONE_MINUS_DST_COLOR 		(0x0307)
#define G2_GL_SRC_ALPHA_SATURATE 		(0x0308)

// multisample
#define G2_GL_MULTISAMPLE 				(0x809D)
#define G2_GL_LINE_SMOOTH 				(0x0B20)
#define G2_GL_LINE_SMOOTH_HINT 			(0x0C52)
#define G2_GL_NICEST 					(0x1102)

// stencil op
//#define G2_GL_ZERO
#define G2_GL_KEEP 						(0x1E00)
#define G2_GL_REPLACE 					(0x1E01)
#define G2_GL_INCR 						(0x1E02)
#define G2_GL_DECR 						(0x1E03)
#define G2_GL_INVERT 					(0x150A)
#define G2_GL_INCR_WRAP 				(0x8507)
#define G2_GL_DECR_WRAP 				(0x8508)

// stencil function
#define G2_GL_NEVER 					(0x0200)
#define G2_GL_LESS 						(0x0201)
#define G2_GL_EQUAL 					(0x0202)
#define G2_GL_LEQUAL 					(0x0203)
#define G2_GL_GREATER 					(0x0204)
#define G2_GL_NOTEQUAL 					(0x0205)
#define G2_GL_GEQUAL 					(0x0206)
#define G2_GL_ALWAYS 					(0x0207)

// enable cap
#define G2_GL_TEXTURE_2D 				(0x0DE1)
#define G2_GL_BLEND 					(0x0BE2)
#define G2_GL_DITHER 					(0x0BD0)
#define G2_GL_STENCIL_TEST 				(0x0B90)
#define G2_GL_DEPTH_TEST 				(0x0B71)
#define G2_GL_SCISSOR_TEST 				(0x0C11)

// texture wrap mode
#define G2_GL_REPEAT 					(0x2901)
#define G2_GL_CLAMP_TO_EDGE 			(0x812F)
#define G2_GL_MIRRORED_REPEAT 			(0x8370)
#define G2_GL_CLAMP_TO_BORDER 			(0x812D)

// clear buffer mask 
#define G2_GL_DEPTH_BUFFER_BIT 			(0x00000100)
#define G2_GL_STENCIL_BUFFER_BIT 		(0x00000400)
#define G2_GL_COLOR_BUFFER_BIT 			(0x00004000)

// pixel format 
#define G2_GL_ALPHA 					(0x1906)
#define G2_GL_RGB 						(0x1907)
#define G2_GL_RGBA 						(0x1908)
#define G2_GL_LUMINANCE 				(0x1909)
#define G2_GL_LUMINANCE_ALPHA 			(0x190A)
#define G2_GL_BGR 						(0x80E0)
#define G2_GL_BGRA 						(0x80E1)

// pixel type
//#define G2_GL_UNSIGNED_BYTE
#define G2_GL_UNSIGNED_SHORT_4_4_4_4 	(0x8033)
#define G2_GL_UNSIGNED_SHORT_5_5_5_1 	(0x8034)
#define G2_GL_UNSIGNED_SHORT_5_6_5 		(0x8363)

// pixel store parameter
#define G2_GL_UNPACK_ALIGNMENT 			(0x0CF5)
#define G2_GL_PACK_ALIGNMENT 			(0x0D05)

// begin mode 
#define G2_GL_POINTS 					(0x0000)
#define G2_GL_LINES 					(0x0001)
#define G2_GL_LINE_LOOP					(0x0002)
#define G2_GL_LINE_STRIP				(0x0003)
#define G2_GL_TRIANGLES 				(0x0004)
#define G2_GL_TRIANGLE_STRIP 			(0x0005)
#define G2_GL_TRIANGLE_FAN 				(0x0006)

// shaders
#define G2_GL_FRAGMENT_SHADER 			(0x8B30)
#define G2_GL_VERTEX_SHADER 			(0x8B31)
#define G2_GL_SHADER_TYPE 				(0x8B4F)
#define G2_GL_DELETE_STATUS 			(0x8B80)
#define G2_GL_LINK_STATUS 				(0x8B82)
#define G2_GL_VALIDATE_STATUS 			(0x8B83)
#define G2_GL_ATTACHED_SHADERS 			(0x8B85)

// shader source
#define G2_GL_COMPILE_STATUS 			(0x8B81)
#define G2_GL_INFO_LOG_LENGTH 			(0x8B84)
#define G2_GL_SHADER_SOURCE_LENGTH 		(0x8B88)
#define G2_GL_SHADER_COMPILER    		(0x8DFA)

// texture unit
#define G2_GL_TEXTURE0    				(0x84C0)
#define G2_GL_TEXTURE1    				(0x84C1)
#define G2_GL_TEXTURE2    				(0x84C2)
#define G2_GL_TEXTURE3    				(0x84C3)
#define G2_GL_TEXTURE4    				(0x84C4)
#define G2_GL_TEXTURE5    				(0x84C5)
#define G2_GL_TEXTURE6    				(0x84C6)
#define G2_GL_TEXTURE7    				(0x84C7)
#define G2_GL_TEXTURE8    				(0x84C8)
#define G2_GL_TEXTURE9    				(0x84C9)
#define G2_GL_TEXTURE10    				(0x84CA)
#define G2_GL_TEXTURE11    				(0x84CB)
#define G2_GL_TEXTURE12    				(0x84CC)
#define G2_GL_TEXTURE13    				(0x84CD)
#define G2_GL_TEXTURE14    				(0x84CE)
#define G2_GL_TEXTURE15    				(0x84CF)
#define G2_GL_TEXTURE16    				(0x84D0)
#define G2_GL_TEXTURE17    				(0x84D1)
#define G2_GL_TEXTURE18    				(0x84D2)
#define G2_GL_TEXTURE19    				(0x84D3)
#define G2_GL_TEXTURE20    				(0x84D4)
#define G2_GL_TEXTURE21    				(0x84D5)
#define G2_GL_TEXTURE22    				(0x84D6)
#define G2_GL_TEXTURE23    				(0x84D7)
#define G2_GL_TEXTURE24    				(0x84D8)
#define G2_GL_TEXTURE25    				(0x84D9)
#define G2_GL_TEXTURE26    				(0x84DA)
#define G2_GL_TEXTURE27    				(0x84DB)
#define G2_GL_TEXTURE28    				(0x84DC)
#define G2_GL_TEXTURE29    				(0x84DD)
#define G2_GL_TEXTURE30    				(0x84DE)
#define G2_GL_TEXTURE31    				(0x84DF)
#define G2_GL_ACTIVE_TEXTURE    		(0x84E0)

/* ///////////////////////////////////////////////////////////////////////
 * basic type
 */

typedef tb_uint_t 		g2_GLenum_t;
typedef tb_char_t 		g2_GLchar_t;
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
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glActiveTexture)) 			(g2_GLenum_t texture);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glAlphaFunc)) 				(g2_GLenum_t func, g2_GLclampf_t ref);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glAttachShader)) 				(g2_GLuint_t program, g2_GLuint_t shader);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glBindTexture)) 				(g2_GLenum_t target, g2_GLuint_t texture);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glBlendFunc)) 				(g2_GLenum_t sfactor, g2_GLenum_t dfactor);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glClear)) 					(g2_GLbitfield_t mask);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glClearColor)) 				(g2_GLclampf_t red, g2_GLclampf_t green, g2_GLclampf_t blue, g2_GLclampf_t alpha);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glClearStencil)) 				(g2_GLint_t s);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glColor4f)) 					(g2_GLfloat_t red, g2_GLfloat_t green, g2_GLfloat_t blue, g2_GLfloat_t alpha);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glColorMask)) 				(g2_GLboolean_t red, g2_GLboolean_t green, g2_GLboolean_t blue, g2_GLboolean_t alpha);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glColorPointer)) 				(g2_GLint_t size, g2_GLenum_t type, g2_GLsizei_t stride, g2_GLvoid_t const* pointer);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glCompileShader))				(g2_GLuint_t shader);
typedef g2_GLuint_t 			(G2_GL_INTERFACE_TYPE(glCreateProgram))				(g2_GLvoid_t);
typedef g2_GLuint_t 			(G2_GL_INTERFACE_TYPE(glCreateShader)) 				(g2_GLenum_t type);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glDeleteProgram))				(g2_GLuint_t program);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glDeleteShader))				(g2_GLuint_t shader);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glDeleteTextures)) 			(g2_GLsizei_t n, g2_GLuint_t const* textures);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glDisable)) 					(g2_GLenum_t cap);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glDisableClientState)) 		(g2_GLenum_t cap);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glDisableVertexAttribArray)) 	(g2_GLuint_t index);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glDrawArrays)) 				(g2_GLenum_t mode, g2_GLint_t first, g2_GLsizei_t count);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glEnable)) 					(g2_GLenum_t cap);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glEnableClientState)) 		(g2_GLenum_t cap);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glEnableVertexAttribArray)) 	(g2_GLuint_t index);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glGenTextures)) 				(g2_GLsizei_t n, g2_GLuint_t* textures);
typedef g2_GLint_t 				(G2_GL_INTERFACE_TYPE(glGetAttribLocation))			(g2_GLuint_t program, g2_GLchar_t const* name);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glGetProgramiv))				(g2_GLuint_t program, g2_GLenum_t pname, g2_GLint_t* params);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glGetProgramInfoLog))			(g2_GLuint_t program, g2_GLsizei_t bufsize, g2_GLsizei_t* length, g2_GLchar_t* infolog);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glGetShaderiv))				(g2_GLuint_t shader, g2_GLenum_t pname, g2_GLint_t* params);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glGetShaderInfoLog))			(g2_GLuint_t shader, g2_GLsizei_t bufsize, g2_GLsizei_t* length, g2_GLchar_t* infolog);
typedef g2_GLubyte_t const* 	(G2_GL_INTERFACE_TYPE(glGetString)) 				(g2_GLenum_t name);
typedef g2_GLint_t 				(G2_GL_INTERFACE_TYPE(glGetUniformLocation))		(g2_GLuint_t program, g2_GLchar_t const* name);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glHint)) 						(g2_GLenum_t target, g2_GLenum_t mode);
typedef g2_GLboolean_t 			(G2_GL_INTERFACE_TYPE(glIsTexture)) 				(g2_GLuint_t texture);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glLineWidth))					(g2_GLfloat_t width);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glLinkProgram))				(g2_GLuint_t program);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glLoadIdentity)) 				(g2_GLvoid_t);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glLoadMatrixf)) 				(g2_GLfloat_t const* matrix);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glMatrixMode)) 				(g2_GLenum_t mode);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glMultMatrixf)) 				(g2_GLfloat_t const* matrix);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glOrtho)) 					(g2_GLdouble_t left, g2_GLdouble_t right, g2_GLdouble_t bottom, g2_GLdouble_t top, g2_GLdouble_t near, g2_GLdouble_t far);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glOrthof)) 					(g2_GLfloat_t left, g2_GLfloat_t right, g2_GLfloat_t bottom, g2_GLfloat_t top, g2_GLfloat_t near, g2_GLfloat_t far);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glPixelStorei)) 				(g2_GLenum_t pname, g2_GLint_t param);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glPopMatrix)) 				(g2_GLvoid_t);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glPushMatrix)) 				(g2_GLvoid_t);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glRotatef)) 					(g2_GLfloat_t angle, g2_GLfloat_t x, g2_GLfloat_t y, g2_GLfloat_t z);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glScalef)) 					(g2_GLfloat_t x, g2_GLfloat_t y, g2_GLfloat_t z);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glScissor)) 					(g2_GLint_t x, g2_GLint_t y, g2_GLsizei_t width, g2_GLsizei_t height);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glShaderSource))				(g2_GLuint_t shader, g2_GLsizei_t count, g2_GLchar_t const** string, const g2_GLint_t* length);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glStencilFunc)) 				(g2_GLenum_t func, g2_GLint_t ref, g2_GLuint_t mask);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glStencilMask)) 				(g2_GLuint_t mask);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glStencilOp)) 				(g2_GLenum_t fail, g2_GLenum_t zfail, g2_GLenum_t zpass);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glTexCoordPointer)) 			(g2_GLint_t size, g2_GLenum_t type, g2_GLsizei_t stride, g2_GLvoid_t const* ptr);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glTexEnvi)) 					(g2_GLenum_t target, g2_GLenum_t pname, g2_GLint_t param);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glTexImage2D)) 				(g2_GLenum_t target, g2_GLint_t level, g2_GLint_t internalFormat, g2_GLsizei_t width, g2_GLsizei_t height, g2_GLint_t border, g2_GLenum_t format, g2_GLenum_t type, g2_GLvoid_t const* pixels);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glTexParameterf)) 			(g2_GLenum_t target, g2_GLenum_t pname, g2_GLfloat_t param);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glTexParameteri)) 			(g2_GLenum_t target, g2_GLenum_t pname, g2_GLint_t param);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glTranslatef)) 				(g2_GLfloat_t x, g2_GLfloat_t y, g2_GLfloat_t z);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glUniform1i)) 				(g2_GLint_t location, g2_GLint_t x);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glUniformMatrix4fv)) 			(g2_GLint_t location, g2_GLsizei_t count, g2_GLboolean_t transpose, g2_GLfloat_t const* value);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glUseProgram))				(g2_GLuint_t program);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glVertexAttrib4f)) 			(g2_GLuint_t indx, g2_GLfloat_t x, g2_GLfloat_t y, g2_GLfloat_t z, g2_GLfloat_t w);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glVertexAttribPointer)) 		(g2_GLuint_t indx, g2_GLint_t size, g2_GLenum_t type, g2_GLboolean_t normalized, g2_GLsizei_t stride, g2_GLvoid_t const* ptr);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glVertexPointer)) 			(g2_GLint_t size, g2_GLenum_t type, g2_GLsizei_t stride,  g2_GLvoid_t const* ptr);
typedef g2_GLvoid_t 			(G2_GL_INTERFACE_TYPE(glViewport)) 					(g2_GLint_t x, g2_GLint_t y, g2_GLsizei_t width, g2_GLsizei_t height);

/* ///////////////////////////////////////////////////////////////////////
 * functions
 */
G2_GL_INTERFACE_EXTERN(glActiveTexture);
G2_GL_INTERFACE_EXTERN(glAlphaFunc);
G2_GL_INTERFACE_EXTERN(glAttachShader);
G2_GL_INTERFACE_EXTERN(glBindTexture);
G2_GL_INTERFACE_EXTERN(glBlendFunc);
G2_GL_INTERFACE_EXTERN(glClear);
G2_GL_INTERFACE_EXTERN(glClearColor);
G2_GL_INTERFACE_EXTERN(glClearStencil);
G2_GL_INTERFACE_EXTERN(glColor4f);
G2_GL_INTERFACE_EXTERN(glColorMask);
G2_GL_INTERFACE_EXTERN(glColorPointer);
G2_GL_INTERFACE_EXTERN(glCompileShader);
G2_GL_INTERFACE_EXTERN(glCreateProgram);
G2_GL_INTERFACE_EXTERN(glCreateShader);
G2_GL_INTERFACE_EXTERN(glDeleteProgram);
G2_GL_INTERFACE_EXTERN(glDeleteShader);
G2_GL_INTERFACE_EXTERN(glDeleteTextures);
G2_GL_INTERFACE_EXTERN(glDisable);
G2_GL_INTERFACE_EXTERN(glDisableClientState);
G2_GL_INTERFACE_EXTERN(glDisableVertexAttribArray);
G2_GL_INTERFACE_EXTERN(glDrawArrays);
G2_GL_INTERFACE_EXTERN(glEnable);
G2_GL_INTERFACE_EXTERN(glEnableClientState);
G2_GL_INTERFACE_EXTERN(glEnableVertexAttribArray);
G2_GL_INTERFACE_EXTERN(glGenTextures);
G2_GL_INTERFACE_EXTERN(glGetAttribLocation);
G2_GL_INTERFACE_EXTERN(glGetProgramiv);
G2_GL_INTERFACE_EXTERN(glGetProgramInfoLog);
G2_GL_INTERFACE_EXTERN(glGetShaderiv);
G2_GL_INTERFACE_EXTERN(glGetShaderInfoLog);
G2_GL_INTERFACE_EXTERN(glGetString);
G2_GL_INTERFACE_EXTERN(glGetUniformLocation);
G2_GL_INTERFACE_EXTERN(glHint);
G2_GL_INTERFACE_EXTERN(glIsTexture);
G2_GL_INTERFACE_EXTERN(glLineWidth);
G2_GL_INTERFACE_EXTERN(glLinkProgram);
G2_GL_INTERFACE_EXTERN(glLoadIdentity);
G2_GL_INTERFACE_EXTERN(glLoadMatrixf);
G2_GL_INTERFACE_EXTERN(glMatrixMode);
G2_GL_INTERFACE_EXTERN(glMultMatrixf);
G2_GL_INTERFACE_EXTERN(glOrtho);
G2_GL_INTERFACE_EXTERN(glOrthof);
G2_GL_INTERFACE_EXTERN(glPixelStorei);
G2_GL_INTERFACE_EXTERN(glPopMatrix);
G2_GL_INTERFACE_EXTERN(glPushMatrix);
G2_GL_INTERFACE_EXTERN(glRotatef);
G2_GL_INTERFACE_EXTERN(glScalef);
G2_GL_INTERFACE_EXTERN(glScissor);
G2_GL_INTERFACE_EXTERN(glShaderSource);
G2_GL_INTERFACE_EXTERN(glStencilFunc);
G2_GL_INTERFACE_EXTERN(glStencilMask);
G2_GL_INTERFACE_EXTERN(glStencilOp);
G2_GL_INTERFACE_EXTERN(glTexCoordPointer);
G2_GL_INTERFACE_EXTERN(glTexEnvi);
G2_GL_INTERFACE_EXTERN(glTexImage2D);
G2_GL_INTERFACE_EXTERN(glTexParameterf);
G2_GL_INTERFACE_EXTERN(glTexParameteri);
G2_GL_INTERFACE_EXTERN(glTranslatef);
G2_GL_INTERFACE_EXTERN(glUniform1i);
G2_GL_INTERFACE_EXTERN(glUniformMatrix4fv);
G2_GL_INTERFACE_EXTERN(glUseProgram);
G2_GL_INTERFACE_EXTERN(glVertexAttrib4f);
G2_GL_INTERFACE_EXTERN(glVertexAttribPointer);
G2_GL_INTERFACE_EXTERN(glVertexPointer);
G2_GL_INTERFACE_EXTERN(glViewport);

/* ///////////////////////////////////////////////////////////////////////
 * checker
 */
tb_bool_t 	g2_gl_interface_check(tb_byte_t version);

#endif
