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
 * @file		shader.c
 *
 */
/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
tb_handle_t g2_shader_init_linear(g2_point_t const* pb, g2_point_t const* pe, g2_gradient_t const* gradient, tb_size_t mode)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_handle_t g2_shader_init_radial(g2_circle_t const* cp, g2_gradient_t const* gradient, tb_size_t mode)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_handle_t g2_shader_init_radial2(g2_circle_t const* cb, g2_circle_t const* ce, g2_gradient_t const* gradient, tb_size_t mode)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_handle_t g2_shader_init_bitmap(tb_handle_t bitmap, tb_size_t mode)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_void_t g2_shader_exit(tb_handle_t shader)
{
	tb_trace_noimpl();
}
g2_matrix_t const* g2_shader_matrix(tb_handle_t shader)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_void_t g2_shader_matrix_set(tb_handle_t shader, g2_matrix_t const* matrix)
{
	tb_trace_noimpl();
}
