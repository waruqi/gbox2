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
#ifndef G2_CORE_CONTEXT_H
#define G2_CORE_CONTEXT_H

// c plus plus
#ifdef __cplusplus
extern "C" {
#endif

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#if defined(G2_CONFIG_CORE_GL) || defined(G2_CONFIG_CORE_GLES)
# 	include "gl/interface.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

// init & exit
tb_handle_t 		g2_context_init_gl(tb_size_t pixfmt, tb_size_t width, tb_size_t height, tb_byte_t version);
tb_handle_t 		g2_context_init_skia(tb_size_t pixfmt, tb_pointer_t data, tb_size_t width, tb_size_t height, tb_size_t lpitch);
tb_handle_t 		g2_context_init_soft(tb_size_t pixfmt, tb_pointer_t data, tb_size_t width, tb_size_t height, tb_size_t lpitch);
tb_void_t 			g2_context_exit(tb_handle_t context);

// resize
tb_handle_t 		g2_context_resize(tb_handle_t context, tb_size_t width, tb_size_t height);

// surface
tb_handle_t 		g2_context_surface(tb_handle_t context);

// c plus plus
#ifdef __cplusplus
}
#endif

#endif
