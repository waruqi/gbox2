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
tb_void_t g2_matrix_init_rotate(g2_matrix_t* matrix, g2_scalar_t degrees)
{
#if 0
	g2_scalar_t s;
	g2_scalar_t c;
	tb_trace_noimpl();
	g2_matrix_init_sincos(matrix, s, c);
#endif
}
tb_void_t g2_matrix_init_sincos(g2_matrix_t* matrix, g2_scalar_t sin, g2_scalar_t cos)
{
	g2_matrix_init(matrix, cos, -sin, sin, cos, 0, 0);	
}
tb_void_t g2_matrix_init_skew(g2_matrix_t* matrix, g2_scalar_t kx, g2_scalar_t ky)
{
	g2_matrix_init(matrix, G2_SCALAR_ONE, kx, ky, G2_SCALAR_ONE, 0, 0);
}
tb_void_t g2_matrix_init_scale(g2_matrix_t* matrix, g2_scalar_t sx, g2_scalar_t sy)
{
	g2_matrix_init(matrix, sx, 0, 0, sy, 0, 0);
}
tb_void_t g2_matrix_init_translate(g2_matrix_t* matrix, g2_scalar_t tx, g2_scalar_t ty)
{
	g2_matrix_init(matrix, G2_SCALAR_ONE, 0, 0, G2_SCALAR_ONE, tx, ty);
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
tb_bool_t g2_matrix_scale_rhs(g2_matrix_t* matrix, g2_scalar_t sx, g2_scalar_t sy)
{
	tb_assert_and_check_return_val(matrix, TB_FALSE);

	// scale: 1/1 ?
	tb_check_return_val(sx != G2_SCALAR_ONE || sy != G2_SCALAR_ONE, TB_TRUE);

#if 0
	g2_matrix_t mx;
	g2_matrix_init_scale(&mx, sx, sy);
	return g2_matrix_multiply_rhs(matrix, &mx);
#else
	matrix->sx = g2_scalar_mul(matrix->sx, sx);
	matrix->kx = g2_scalar_mul(matrix->kx, sx);
	matrix->ky = g2_scalar_mul(matrix->ky, sy);
	matrix->sy = g2_scalar_mul(matrix->sy, sy);
	return TB_TRUE;	
#endif
}
tb_bool_t g2_matrix_scale_lhs(g2_matrix_t* matrix, g2_scalar_t sx, g2_scalar_t sy)
{
	tb_assert_and_check_return_val(matrix, TB_FALSE);

	// scale: 1/1 ?
	tb_check_return_val(sx != G2_SCALAR_ONE || sy != G2_SCALAR_ONE, TB_TRUE);

	g2_matrix_t mx;
	g2_matrix_init_scale(&mx, sx, sy);
	return g2_matrix_multiply_lhs(matrix, &mx);
}
tb_bool_t g2_matrix_translate_rhs(g2_matrix_t* matrix, g2_scalar_t dx, g2_scalar_t dy)
{
	tb_trace_noimpl();
	return TB_FALSE;
}
tb_bool_t g2_matrix_translate_lhs(g2_matrix_t* matrix, g2_scalar_t dx, g2_scalar_t dy)
{
	tb_assert_and_check_return_val(matrix, TB_FALSE);
	tb_trace_noimpl();
	return TB_FALSE;
}
tb_bool_t g2_matrix_skew_rhs(g2_matrix_t* matrix, g2_scalar_t kx, g2_scalar_t ky)
{
	tb_assert_and_check_return_val(matrix, TB_FALSE);	

	g2_matrix_t mx;
	g2_matrix_init_skew(&mx, kx, ky);
	return g2_matrix_multiply_rhs(matrix, &mx);
}
tb_bool_t g2_matrix_skew_lhs(g2_matrix_t* matrix, g2_scalar_t kx, g2_scalar_t ky)
{
	tb_assert_and_check_return_val(matrix, TB_FALSE);

	g2_matrix_t mx;
	g2_matrix_init_skew(&mx, kx, ky);
	return g2_matrix_multiply_lhs(matrix, &mx);
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

