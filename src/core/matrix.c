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
 * types
 */
#ifdef G2_CONFIG_FLOAT_FIXED
typedef g2_float_t 		g2_invdet_t;
#else
typedef tb_double_t 	g2_invdet_t;
#endif

/* ///////////////////////////////////////////////////////////////////////
 * helpers
 */

#ifdef G2_CONFIG_FLOAT_FIXED
static __tb_inline__ g2_float_t g2_matrix_mul(g2_float_t a, g2_float_t b, g2_float_t c, g2_float_t d)
{
	return (g2_float_t)(((tb_hong_t)a * b + (tb_hong_t)c * d) >> 16);
}
static __tb_inline__ g2_float_t g2_matrix_det(g2_float_t sx, g2_float_t sy, g2_float_t kx, g2_float_t ky)
{
	tb_hong_t det = (tb_hong_t)sx * sy - (tb_hong_t)kx * ky;
	if (!det) return 0;
	return (g2_float_t)(((tb_hong_t)1 << 32) / det);
}
#else
static __tb_inline__ g2_float_t g2_matrix_mul(g2_float_t a, g2_float_t b, g2_float_t c, g2_float_t d)
{
	return (g2_float_t)((tb_double_t)a * b + (tb_double_t)c * d);
}
static __tb_inline__ tb_double_t g2_matrix_det(g2_float_t sx, g2_float_t sy, g2_float_t kx, g2_float_t ky)
{
	tb_double_t det = (tb_double_t)sx * sy - (tb_double_t)kx * ky;
	if (g2_fabs(det) < G2_NEAR0 * G2_NEAR0 * G2_NEAR0) return 0.;
	return 1. / det;
}
#endif

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */

tb_void_t g2_matrix_init(g2_matrix_t* matrix, g2_float_t sx, g2_float_t kx, g2_float_t ky, g2_float_t sy, g2_float_t tx, g2_float_t ty)
{
	matrix->sx = sx;
	matrix->kx = kx;
	matrix->ky = ky;
	matrix->sy = sy;
	matrix->tx = tx;
	matrix->ty = ty;
}
tb_void_t g2_matrix_init_rotate(g2_matrix_t* matrix, g2_float_t degrees)
{
	g2_float_t s;
	g2_float_t c;
	g2_sincos(g2_degree_to_radian(degrees), &s, &c);
	g2_matrix_init_sincos(matrix, s, c);
}
tb_void_t g2_matrix_init_sincos(g2_matrix_t* matrix, g2_float_t sin, g2_float_t cos)
{
	g2_matrix_init(matrix, cos, -sin, sin, cos, 0, 0);	
}
tb_void_t g2_matrix_init_skew(g2_matrix_t* matrix, g2_float_t kx, g2_float_t ky)
{
	g2_matrix_init(matrix, G2_ONE, kx, ky, G2_ONE, 0, 0);
}
tb_void_t g2_matrix_init_scale(g2_matrix_t* matrix, g2_float_t sx, g2_float_t sy)
{
	g2_matrix_init(matrix, sx, 0, 0, sy, 0, 0);
}
tb_void_t g2_matrix_init_translate(g2_matrix_t* matrix, g2_float_t tx, g2_float_t ty)
{
	g2_matrix_init(matrix, G2_ONE, 0, 0, G2_ONE, tx, ty);
}
tb_void_t g2_matrix_exit(g2_matrix_t* matrix)
{
	g2_matrix_clear(matrix);
}
tb_void_t g2_matrix_clear(g2_matrix_t* matrix)
{
	g2_matrix_init(matrix, G2_ONE, 0, 0, G2_ONE, 0, 0);
}
tb_bool_t g2_matrix_invert(g2_matrix_t* matrix)
{
	// identity?
	if (g2_matrix_identity(matrix)) return TB_TRUE;

	// no rotate?
	g2_matrix_t mx;
	if (g2_ez(matrix->kx) && g2_ez(matrix->ky))
	{
		// invert it if sx != 1.0
		if (g2_n1(matrix->sx))
		{
			tb_assert_and_check_return_val(g2_fabs(matrix->sx) >= G2_NEAR0, TB_FALSE);
			mx.sx = g2_invert(matrix->sx);
			mx.tx = g2_div(-matrix->tx, matrix->sx);
		}

		// invert it if sy != 1.0
		if (g2_n1(matrix->sy))
		{
			tb_assert_and_check_return_val(g2_fabs(matrix->sy) > G2_NEAR0, TB_FALSE);
			mx.sy = g2_invert(matrix->sy);
			mx.ty = g2_div(-matrix->ty, matrix->sy);
		}
	}
	else
	{
		/* 1 / det(A): 1 / |A|
		 *
		 * adj(A)
		 *
		 * (sx, kx)     (sy, -kx)
		 *          => 
		 * (ky, sy)     (-ky, sx)
		 */
		g2_invdet_t det = g2_matrix_det(matrix->sx, matrix->sy, matrix->kx, matrix->ky);
		tb_assert_and_check_return_val(det, TB_FALSE);

		// invert
#ifdef G2_CONFIG_FLOAT_FIXED
		mx.sx = tb_fixed_mul(matrix->sy, det);
		mx.sy = tb_fixed_mul(matrix->sx, det);
		mx.kx = tb_fixed_mul(-matrix->kx, det);
		mx.ky = tb_fixed_mul(-matrix->ky, det);
		mx.tx = (tb_fixed_t)((((tb_hong_t)matrix->kx * matrix->ty - (tb_hong_t)matrix->sy * matrix->tx) * det) >> 16);
		mx.ty = (tb_fixed_t)((((tb_hong_t)matrix->ky * matrix->tx - (tb_hong_t)matrix->sx * matrix->ty) * det) >> 16);
#else
		mx.sx = (tb_float_t)(matrix->sy * det);
		mx.sy = (tb_float_t)(matrix->sx * det);
		mx.kx = (tb_float_t)(-matrix->kx * det);
		mx.ky = (tb_float_t)(-matrix->ky * det);
		mx.tx = (tb_float_t)(((tb_double_t)matrix->kx * matrix->ty - (tb_double_t)matrix->sy * matrix->tx) * det);
		mx.ty = (tb_float_t)(((tb_double_t)matrix->ky * matrix->tx - (tb_double_t)matrix->sx * matrix->ty) * det);
#endif
	}

	// ok
	*matrix = mx;
	return TB_TRUE;
}
tb_bool_t g2_matrix_identity(g2_matrix_t const* matrix)
{
	return (g2_e1(matrix->sx) && g2_e1(matrix->sy)
		&& g2_ez(matrix->kx) && g2_ez(matrix->ky)
		&& g2_ez(matrix->tx) && g2_ez(matrix->ty))? TB_TRUE : TB_FALSE;
}
tb_bool_t g2_matrix_rotate(g2_matrix_t* matrix, g2_float_t degrees)
{
	// 0 ?
	tb_check_return_val(g2_nz(degrees), TB_TRUE);

	// rotate
	g2_matrix_t mx;
	g2_matrix_init_rotate(&mx, degrees);
	return g2_matrix_multiply(matrix, &mx);
}
tb_bool_t g2_matrix_rotate_lhs(g2_matrix_t* matrix, g2_float_t degrees)
{
	// 0 ?
	tb_check_return_val(g2_nz(degrees), TB_TRUE);

	// rotate
	g2_matrix_t mx;
	g2_matrix_init_rotate(&mx, degrees);
	return g2_matrix_multiply_lhs(matrix, &mx);
}
tb_bool_t g2_matrix_scale(g2_matrix_t* matrix, g2_float_t sx, g2_float_t sy)
{
	// 1/1 ?
	tb_check_return_val(g2_n1(sx) || g2_n1(sy), TB_TRUE);

	// scale
#if 0
	g2_matrix_t mx;
	g2_matrix_init_scale(&mx, sx, sy);
	return g2_matrix_multiply(matrix, &mx);
#else
	matrix->sx = g2_mul(matrix->sx, sx);
	matrix->kx = g2_mul(matrix->kx, sx);
	matrix->ky = g2_mul(matrix->ky, sy);
	matrix->sy = g2_mul(matrix->sy, sy);
	return TB_TRUE;	
#endif
}
tb_bool_t g2_matrix_scale_lhs(g2_matrix_t* matrix, g2_float_t sx, g2_float_t sy)
{
	// 1/1 ?
	tb_check_return_val(g2_n1(sx) || g2_n1(sy), TB_TRUE);

	// scale
	g2_matrix_t mx;
	g2_matrix_init_scale(&mx, sx, sy);
	return g2_matrix_multiply_lhs(matrix, &mx);
}
tb_bool_t g2_matrix_translate(g2_matrix_t* matrix, g2_float_t dx, g2_float_t dy)
{
	// 0, 0 ?
	tb_check_return_val(g2_nz(dx) || g2_nz(dy), TB_TRUE);

	// translate
	matrix->tx = g2_matrix_mul(matrix->sx, dx, matrix->kx, dy) + matrix->tx;
	matrix->ty = g2_matrix_mul(matrix->ky, dx, matrix->sy, dy) + matrix->ty;

	// ok
	return TB_TRUE;
}
tb_bool_t g2_matrix_translate_lhs(g2_matrix_t* matrix, g2_float_t dx, g2_float_t dy)
{
	// translate
	matrix->tx += dx;
	matrix->ty += dy;

	// ok
	return TB_TRUE;
}
tb_bool_t g2_matrix_skew(g2_matrix_t* matrix, g2_float_t kx, g2_float_t ky)
{
	// skew
	g2_matrix_t mx;
	g2_matrix_init_skew(&mx, kx, ky);
	return g2_matrix_multiply(matrix, &mx);
}
tb_bool_t g2_matrix_skew_lhs(g2_matrix_t* matrix, g2_float_t kx, g2_float_t ky)
{
	// skew
	g2_matrix_t mx;
	g2_matrix_init_skew(&mx, kx, ky);
	return g2_matrix_multiply_lhs(matrix, &mx);
}
tb_bool_t g2_matrix_multiply(g2_matrix_t* matrix, g2_matrix_t const* mx)
{
	// identity?
	if (g2_matrix_identity(mx)) return TB_TRUE;

	// multiply
	g2_matrix_t mt;
	mt.sx = g2_matrix_mul(matrix->sx, mx->sx, matrix->kx, mx->ky);
	mt.ky = g2_matrix_mul(matrix->ky, mx->sx, matrix->sy, mx->ky);

	mt.kx = g2_matrix_mul(matrix->sx, mx->kx, matrix->kx, mx->sy);
	mt.sy = g2_matrix_mul(matrix->ky, mx->kx, matrix->sy, mx->sy);

	mt.tx = g2_matrix_mul(matrix->sx, mx->tx, matrix->kx, mx->ty) + matrix->tx;
	mt.ty = g2_matrix_mul(matrix->ky, mx->tx, matrix->sy, mx->ty) + matrix->ty;

	// ok
	*matrix = mt;
	return TB_TRUE;
}
tb_bool_t g2_matrix_multiply_lhs(g2_matrix_t* matrix, g2_matrix_t const* mx)
{
	// identity?
	if (g2_matrix_identity(mx)) return TB_TRUE;
	
	// multiply
	g2_matrix_t mt = *mx;
	tb_bool_t 	ok = g2_matrix_multiply(&mt, matrix);
	*matrix = mt;

	// ok?
	return ok;
}

