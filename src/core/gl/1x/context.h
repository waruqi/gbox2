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
 * @file		context.h
 *
 */
#ifndef G2_CORE_GL1x_CONTEXT_H
#define G2_CORE_GL1x_CONTEXT_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "shader.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */

// the texture maxn
#ifdef TB_CONFIG_MEMORY_MODE_SMALL
# 	define G2_GL1x_TEXTURE_MAXN 		(256)
#else
# 	define G2_GL1x_TEXTURE_MAXN 		(1024)
#endif

// the used
#define G2_GL1x_TEXTURE_USED 			(1)
#define G2_GL1x_SHADERS_USED 			(2)

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the gl1x context type
typedef struct __g2_gl1x_context_t
{
	// the surface
	tb_handle_t 		surface;

	// the version
	tb_byte_t 			version;

	// the extensions
	tb_byte_t 			extensions[G2_GL_EXT_MAXN];

	// the used
	tb_byte_t 			used[G2_GL1x_TEXTURE_MAXN];

	// the texture
	tb_uint_t 			texture[G2_GL1x_TEXTURE_MAXN];
	tb_size_t 			texture_pred;

	// the shaders
	g2_gl1x_shader_t	shaders[G2_GL1x_TEXTURE_MAXN];
	tb_size_t 			shaders_pred;

}g2_gl1x_context_t;

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

// the context texture
tb_uint_t* 			g2_gl1x_context_texture_alc(g2_gl1x_context_t* context);
tb_void_t 			g2_gl1x_context_texture_del(g2_gl1x_context_t* context, tb_uint_t const* texture);

// the context shader
g2_gl1x_shader_t* 	g2_gl1x_context_shader_alc(g2_gl1x_context_t* context);
tb_void_t 			g2_gl1x_context_shader_del(g2_gl1x_context_t* context, g2_gl1x_shader_t const* shader);


#endif
