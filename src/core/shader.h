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
 * @file		shader.h
 *
 */
#ifndef G2_CORE_SHADER_H
#define G2_CORE_SHADER_H

// c plus plus
#ifdef __cplusplus
extern "C" {
#endif

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "matrix.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */
	
// init linear gradient shader
tb_handle_t 		g2_shader_init_linear(g2_point_t const* pb, g2_point_t const* pe, g2_gradient_t const* gradient, tb_size_t mode);
tb_handle_t 		g2_shader_init2_linear(g2_float_t xb, g2_float_t yb, g2_float_t xe, g2_float_t ye, g2_gradient_t const* gradient, tb_size_t mode);

tb_handle_t 		g2_shader_initi_linear(g2_ipoint_t const* pb, g2_ipoint_t const* pe, g2_gradient_t const* gradient, tb_size_t mode);
tb_handle_t 		g2_shader_init2i_linear(tb_long_t xb, tb_long_t yb, tb_long_t xe, tb_long_t ye, g2_gradient_t const* gradient, tb_size_t mode);

// init radial gradient shader
tb_handle_t 		g2_shader_init_radial(g2_circle_t const* cp, g2_gradient_t const* gradient, tb_size_t mode);
tb_handle_t 		g2_shader_init2_radial(g2_float_t x0, g2_float_t y0, g2_float_t r, g2_gradient_t const* gradient, tb_size_t mode);

tb_handle_t 		g2_shader_initi_radial(g2_icircle_t const* cp, g2_gradient_t const* gradient, tb_size_t mode);
tb_handle_t 		g2_shader_init2i_radial(tb_long_t x0, tb_long_t y0, tb_size_t r, g2_gradient_t const* gradient, tb_size_t mode);

// init radial2 gradient shader
tb_handle_t 		g2_shader_init_radial2(g2_circle_t const* cb, g2_circle_t const* ce, g2_gradient_t const* gradient, tb_size_t mode);
tb_handle_t 		g2_shader_init2_radial2(g2_float_t xb, g2_float_t yb, g2_float_t rb, g2_float_t xe, g2_float_t ye, g2_float_t re, g2_gradient_t const* gradient, tb_size_t mode);

tb_handle_t 		g2_shader_initi_radial2(g2_icircle_t const* cb, g2_icircle_t const* ce, g2_gradient_t const* gradient, tb_size_t mode);
tb_handle_t 		g2_shader_init2i_radial2(tb_long_t xb, tb_long_t yb, tb_size_t rb, tb_long_t xe, tb_long_t ye, tb_size_t re, g2_gradient_t const* gradient, tb_size_t mode);

// matrix
g2_matrix_t const* 	g2_shader_matrix(tb_handle_t shader);
tb_void_t 			g2_shader_matrix_set(tb_handle_t shader, g2_matrix_t const* matrix);

// exit
tb_void_t 			g2_shader_exit(tb_handle_t shader);

// c plus plus
#ifdef __cplusplus
}
#endif

#endif
