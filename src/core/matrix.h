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
 * @file		matrix.h
 *
 */
#ifndef G2_CORE_MATRIX_H
#define G2_CORE_MATRIX_H

// c plus plus
#ifdef __cplusplus
extern "C" {
#endif

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

/*!the matrix type
 *
 * <pre>
 * sx: scale x
 * sy: scale y
 * kx: skew x
 * ky: skew y
 * tx: translate x
 * ty: translate y
 *
 * x' = x * sx + y * kx + tx
 * y' = x * ky + y * sy + ty
 * 
 *                        (sx, kx)
 * (x', y') = (x, y, 1) * (ky, sy)
 *                        (tx, ty)
 *
 * The following table describes how the members of the matrix are used for each type of
 * operation:
 *                    sx                kx               ky              sy                tx     ty
 * rotation           sx * cos          sx * -sin        sy * sin        sy * cos          0      0
 * scaling            sx                0                0               sy                0      0
 * translation        0                 0                0               0                 tx     ty
 * ...
 *
 * </pre>
 *
 */
typedef struct __g2_matrix_t
{
	g2_float_t 		sx, kx, tx;
	g2_float_t 		ky, sy, ty;

}g2_matrix_t;

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

// init & exit
tb_void_t 		g2_matrix_init(g2_matrix_t* matrix, g2_float_t sx, g2_float_t kx, g2_float_t ky, g2_float_t sy, g2_float_t tx, g2_float_t ty);
tb_void_t 		g2_matrix_init_rotate(g2_matrix_t* matrix, g2_float_t degrees);
tb_void_t 		g2_matrix_init_sincos(g2_matrix_t* matrix, g2_float_t sin, g2_float_t cos);
tb_void_t 		g2_matrix_init_skew(g2_matrix_t* matrix, g2_float_t kx, g2_float_t ky);
tb_void_t 		g2_matrix_init_scale(g2_matrix_t* matrix, g2_float_t sx, g2_float_t sy);
tb_void_t 		g2_matrix_init_translate(g2_matrix_t* matrix, g2_float_t tx, g2_float_t ty);
tb_void_t 		g2_matrix_exit(g2_matrix_t* matrix);

// clear
tb_void_t 		g2_matrix_clear(g2_matrix_t* matrix);

// invert
tb_bool_t 		g2_matrix_invert(g2_matrix_t* matrix);

// identity?
tb_bool_t 		g2_matrix_identity(g2_matrix_t const* matrix);

// rotate
tb_bool_t 		g2_matrix_rotate(g2_matrix_t* matrix, g2_float_t degrees);
tb_bool_t 		g2_matrix_rotate_lhs(g2_matrix_t* matrix, g2_float_t degrees);

// scale
tb_bool_t 		g2_matrix_scale(g2_matrix_t* matrix, g2_float_t sx, g2_float_t sy);
tb_bool_t 		g2_matrix_scale_lhs(g2_matrix_t* matrix, g2_float_t sx, g2_float_t sy);

// translate
tb_bool_t 		g2_matrix_translate(g2_matrix_t* matrix, g2_float_t dx, g2_float_t dy);
tb_bool_t 		g2_matrix_translate_lhs(g2_matrix_t* matrix, g2_float_t dx, g2_float_t dy);

// skew
tb_bool_t 		g2_matrix_skew(g2_matrix_t* matrix, g2_float_t kx, g2_float_t ky);
tb_bool_t 		g2_matrix_skew_lhs(g2_matrix_t* matrix, g2_float_t kx, g2_float_t ky);

// multiply
tb_bool_t 		g2_matrix_multiply(g2_matrix_t* matrix, g2_matrix_t const* mx);
tb_bool_t 		g2_matrix_multiply_lhs(g2_matrix_t* matrix, g2_matrix_t const* mx);

// c plus plus
#ifdef __cplusplus
}
#endif

#endif
