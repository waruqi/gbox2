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

// the matrix mode type
typedef enum __g2_matrix_mode_t
{
	G2_MATRIX_MODE_IDENTITY 	= 0 //!< the matrix is identity
,	G2_MATRIX_MODE_TRANSLATE 	= 1 //!< the matrix has translation
,	G2_MATRIX_MODE_SCALE 		= 2 //!< the matrix has x or y scale
,	G2_MATRIX_MODE_AFFINE 		= 4 //!< the matrix has skews or rotates

}g2_matrix_mode_t;

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
	g2_scalar_t 		sx, kx, tx;
	g2_scalar_t 		ky, sy, ty;

}g2_matrix_t;

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

// init & exit
tb_void_t 		g2_matrix_init(g2_matrix_t* matrix, g2_scalar_t sx, g2_scalar_t kx, g2_scalar_t ky, g2_scalar_t sy, g2_scalar_t tx, g2_scalar_t ty);
tb_void_t 		g2_matrix_exit(g2_matrix_t* matrix);

// clear
tb_void_t 		g2_matrix_clear(g2_matrix_t* matrix);

// invert
tb_bool_t 		g2_matrix_invert(g2_matrix_t* matrix);

// identity?
tb_bool_t 		g2_matrix_identity(g2_matrix_t const* matrix);

// mode
tb_size_t 		g2_matrix_mode(g2_matrix_t const* matrix);
tb_void_t 		g2_matrix_mode_set(g2_matrix_t* matrix, tb_size_t mode);

// rotate
tb_bool_t 		g2_matrix_rotate_rhs(g2_matrix_t* matrix, g2_scalar_t degrees);
tb_bool_t 		g2_matrix_rotate_lhs(g2_matrix_t* matrix, g2_scalar_t degrees);
tb_void_t 		g2_matrix_rotate_set(g2_matrix_t* matrix, g2_scalar_t degrees);

// scale
tb_bool_t 		g2_matrix_scale_rhs(g2_matrix_t* matrix, g2_scalar_t sx, g2_scalar_t sy);
tb_bool_t 		g2_matrix_scale_lhs(g2_matrix_t* matrix, g2_scalar_t sx, g2_scalar_t sy);
tb_void_t 		g2_matrix_scale_set(g2_matrix_t* matrix, g2_scalar_t sx, g2_scalar_t sy);
tb_void_t 		g2_matrix_scale_set_x(g2_matrix_t* matrix, g2_scalar_t sx);
tb_void_t 		g2_matrix_scale_set_y(g2_matrix_t* matrix, g2_scalar_t sy);
g2_scalar_t 	g2_matrix_scale_get_x(g2_matrix_t const* matrix);
g2_scalar_t 	g2_matrix_scale_get_y(g2_matrix_t const* matrix);

// translate
tb_bool_t 		g2_matrix_translate_rhs(g2_matrix_t* matrix, g2_scalar_t dx, g2_scalar_t dy);
tb_bool_t 		g2_matrix_translate_lhs(g2_matrix_t* matrix, g2_scalar_t dx, g2_scalar_t dy);
tb_void_t 		g2_matrix_translate_set(g2_matrix_t* matrix, g2_scalar_t tx, g2_scalar_t ty);
tb_void_t 		g2_matrix_translate_set_x(g2_matrix_t* matrix, g2_scalar_t tx);
tb_void_t 		g2_matrix_translate_set_y(g2_matrix_t* matrix, g2_scalar_t ty);
g2_scalar_t 	g2_matrix_translate_get_x(g2_matrix_t const* matrix);
g2_scalar_t 	g2_matrix_translate_get_y(g2_matrix_t const* matrix);

// skew
tb_bool_t 		g2_matrix_skew_rhs(g2_matrix_t* matrix, g2_scalar_t kx, g2_scalar_t ky);
tb_bool_t 		g2_matrix_skew_lhs(g2_matrix_t* matrix, g2_scalar_t kx, g2_scalar_t ky);
tb_void_t 		g2_matrix_skew_set(g2_matrix_t* matrix, g2_scalar_t kx, g2_scalar_t ky);
tb_void_t 		g2_matrix_skew_set_x(g2_matrix_t* matrix, g2_scalar_t kx);
tb_void_t 		g2_matrix_skew_set_y(g2_matrix_t* matrix, g2_scalar_t ky);
g2_scalar_t 	g2_matrix_skew_get_x(g2_matrix_t const* matrix);
g2_scalar_t 	g2_matrix_skew_get_y(g2_matrix_t const* matrix);

// multiply
tb_bool_t 		g2_matrix_multiply_set(g2_matrix_t* matrix, g2_matrix_t const* mx, g2_matrix_t const* my);
tb_bool_t 		g2_matrix_multiply_rhs(g2_matrix_t* matrix, g2_matrix_t const* mx);
tb_bool_t 		g2_matrix_multiply_lhs(g2_matrix_t* matrix, g2_matrix_t const* mx);

// c plus plus
#ifdef __cplusplus
}
#endif

#endif
