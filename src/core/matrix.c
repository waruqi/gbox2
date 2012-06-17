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
 * @file		matrix.c
 *
 */
/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "matrix.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */

tb_void_t g2_matrix_init(g2_matrix_t* matrix, g2_scalar_t sx, g2_scalar_t kx, g2_scalar_t ky, g2_scalar_t sy, g2_scalar_t tx, g2_scalar_t ty)
{
	tb_assert_and_check_return(matrix);
	matrix->sx = sx;
	matrix->kx = kx;
	matrix->ky = ky;
	matrix->sy = sy;
	matrix->tx = tx;
	matrix->ty = ty;
}
tb_void_t g2_matrix_exit(g2_matrix_t* matrix)
{
	g2_matrix_clear(matrix);
}
tb_void_t g2_matrix_clear(g2_matrix_t* matrix)
{
	g2_matrix_init(matrix, G2_SCALAR_ONE, 0, 0, G2_SCALAR_ONE, 0, 0);
}
tb_bool_t g2_matrix_invert(g2_matrix_t* matrix)
{
	tb_trace_noimpl();
	return TB_FALSE;
}
tb_bool_t g2_matrix_identity(g2_matrix_t const* matrix)
{
	tb_trace_noimpl();
	return TB_FALSE;
}
tb_size_t g2_matrix_mode(g2_matrix_t const* matrix)
{
	tb_trace_noimpl();
	return 0;
}
tb_void_t g2_matrix_mode_set(g2_matrix_t* matrix, tb_size_t mode)
{
	tb_trace_noimpl();
}
tb_bool_t g2_matrix_rotate_rhs(g2_matrix_t* matrix, g2_scalar_t degrees)
{
	tb_trace_noimpl();
	return TB_FALSE;
}
tb_bool_t g2_matrix_rotate_lhs(g2_matrix_t* matrix, g2_scalar_t degrees)
{
	tb_trace_noimpl();
	return TB_FALSE;
}
tb_void_t g2_matrix_rotate_set(g2_matrix_t* matrix, g2_scalar_t degrees)
{
	tb_trace_noimpl();
}
tb_bool_t g2_matrix_scale_rhs(g2_matrix_t* matrix, g2_scalar_t sx, g2_scalar_t sy)
{
	tb_trace_noimpl();
	return TB_FALSE;
}
tb_bool_t g2_matrix_scale_lhs(g2_matrix_t* matrix, g2_scalar_t sx, g2_scalar_t sy)
{
	tb_trace_noimpl();
	return TB_FALSE;
}
tb_void_t g2_matrix_scale_set(g2_matrix_t* matrix, g2_scalar_t sx, g2_scalar_t sy)
{
	tb_trace_noimpl();
}
tb_void_t g2_matrix_scale_set_x(g2_matrix_t* matrix, g2_scalar_t sx)
{
	tb_trace_noimpl();
}
tb_void_t g2_matrix_scale_set_y(g2_matrix_t* matrix, g2_scalar_t sy)
{
	tb_trace_noimpl();
}
g2_scalar_t g2_matrix_scale_get_x(g2_matrix_t const* matrix)
{
	tb_trace_noimpl();
	return G2_SCALAR_ONE;
}
g2_scalar_t g2_matrix_scale_get_y(g2_matrix_t const* matrix)
{
	tb_trace_noimpl();
	return G2_SCALAR_ONE;
}
tb_bool_t g2_matrix_translate_rhs(g2_matrix_t* matrix, g2_scalar_t dx, g2_scalar_t dy)
{
	tb_trace_noimpl();
	return TB_FALSE;
}
tb_bool_t g2_matrix_translate_lhs(g2_matrix_t* matrix, g2_scalar_t dx, g2_scalar_t dy)
{
	tb_trace_noimpl();
	return TB_FALSE;
}
tb_void_t g2_matrix_translate_set(g2_matrix_t* matrix, g2_scalar_t tx, g2_scalar_t ty)
{
	tb_trace_noimpl();
}
tb_void_t g2_matrix_translate_set_x(g2_matrix_t* matrix, g2_scalar_t tx)
{
	tb_trace_noimpl();
}
tb_void_t g2_matrix_translate_set_y(g2_matrix_t* matrix, g2_scalar_t ty)
{
	tb_trace_noimpl();
}
g2_scalar_t g2_matrix_translate_get_x(g2_matrix_t const* matrix)
{
	tb_trace_noimpl();
	return G2_SCALAR_ONE;
}
g2_scalar_t g2_matrix_translate_get_y(g2_matrix_t const* matrix)
{
	tb_trace_noimpl();
	return G2_SCALAR_ONE;
}
tb_bool_t g2_matrix_skew_rhs(g2_matrix_t* matrix, g2_scalar_t kx, g2_scalar_t ky)
{
	tb_trace_noimpl();
	return TB_FALSE;
}
tb_bool_t g2_matrix_skew_lhs(g2_matrix_t* matrix, g2_scalar_t kx, g2_scalar_t ky)
{
	tb_trace_noimpl();
	return TB_FALSE;
}
tb_void_t g2_matrix_skew_set(g2_matrix_t* matrix, g2_scalar_t kx, g2_scalar_t ky)
{
	tb_trace_noimpl();
}
tb_void_t g2_matrix_skew_set_x(g2_matrix_t* matrix, g2_scalar_t kx)
{
	tb_trace_noimpl();
}
tb_void_t g2_matrix_skew_set_y(g2_matrix_t* matrix, g2_scalar_t ky)
{
	tb_trace_noimpl();
}
g2_scalar_t g2_matrix_skew_get_x(g2_matrix_t const* matrix)
{
	tb_trace_noimpl();
	return G2_SCALAR_ONE;
}
g2_scalar_t g2_matrix_skew_get_y(g2_matrix_t const* matrix)
{
	tb_trace_noimpl();
	return G2_SCALAR_ONE;
}
tb_bool_t g2_matrix_multiply_set(g2_matrix_t* matrix, g2_matrix_t const* mx, g2_matrix_t const* my)
{
	tb_trace_noimpl();
	return TB_FALSE;
}
tb_bool_t g2_matrix_multiply_rhs(g2_matrix_t* matrix, g2_matrix_t const* mx)
{
	tb_trace_noimpl();
	return TB_FALSE;
}
tb_bool_t g2_matrix_multiply_lhs(g2_matrix_t* matrix, g2_matrix_t const* mx)
{
	tb_trace_noimpl();
	return TB_FALSE;
}

