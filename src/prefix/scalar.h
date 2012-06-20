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
 * @file		scalar.h
 *
 */
#ifndef G2_PREFIX_SCALAR_H
#define G2_PREFIX_SCALAR_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "config.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */

#ifdef G2_CONFIG_SCALAR_FIXED

#define G2_SCALAR_ONE 				TB_FIXED_ONE
#define G2_SCALAR_HALF 				TB_FIXED_HALF
#define G2_SCALAR_MAX 				TB_FIXED_MAX
#define G2_SCALAR_MIN 				TB_FIXED_MIN
#define G2_SCALAR_NAN 				TB_FIXED_NAN
#define G2_SCALAR_INF 				TB_FIXED_INF
#define G2_SCALAR_PI 				TB_FIXED_PI
#define G2_SCALAR_SQRT2 			TB_FIXED_SQRT2

// conversion
#ifdef TB_CONFIG_TYPE_FLOAT
# 	define g2_scalar_to_float(x) 	tb_fixed_to_float(x)
# 	define g2_float_to_scalar(x) 	tb_float_to_fixed(x)
#endif

#define g2_long_to_scalar(x) 		tb_long_to_fixed(x)
#define g2_scalar_to_long(x) 		tb_fixed_to_long(x)

#define g2_fixed_to_scalar(x) 		(x)
#define g2_scalar_to_fixed(x) 		(x)

#define g2_fixed6_to_scalar(x) 		tb_fixed6_to_fixed(x)
#define g2_scalar_to_fixed6(x) 		tb_fixed_to_fixed6(x)

#define g2_fixed30_to_scalar(x) 	tb_fixed30_to_fixed(x)
#define g2_scalar_to_fixed30(x) 	tb_fixed_to_fixed30(x)

// round
#define g2_scalar_round(x) 			tb_fixed_round(x)
#define g2_scalar_ceil(x) 			tb_fixed_ceil(x)
#define g2_scalar_floor(x) 			tb_fixed_floor(x)

// functions
#define g2_scalar_abs(x) 			tb_fixed_abs(x)
#define g2_scalar_avg(x, y) 		tb_fixed_avg(x, y)
#define g2_scalar_mul(x, y) 		tb_fixed_mul(x, y)
#define g2_scalar_div(x, y) 		tb_fixed_div(x, y)
#define g2_scalar_lsh(x, y) 		tb_fixed_lsh(x, y)
#define g2_scalar_rsh(x, y) 		tb_fixed_rsh(x, y)
#define g2_scalar_imul(x, y) 		tb_fixed_imul(x, y)
#define g2_scalar_idiv(x, y) 		tb_fixed_idiv(x, y)
#define g2_scalar_invert(x) 		tb_fixed_invert(x)
#define g2_scalar_sqre(x) 			tb_fixed_sqre(x)
#define g2_scalar_sqrt(x) 			tb_fixed_sqrt(x)
#define g2_scalar_sin(x) 			tb_fixed_sin(x)
#define g2_scalar_cos(x) 			tb_fixed_cos(x)
#define g2_scalar_sincos(x, s, c) 	tb_fixed_sincos(x, s, c)
#define g2_scalar_tan(x) 			tb_fixed_tan(x)
#define g2_scalar_asin(x) 			tb_fixed_asin(x)
#define g2_scalar_acos(x) 			tb_fixed_acos(x)
#define g2_scalar_atan(x) 			tb_fixed_atan(x)
#define g2_scalar_atan2(y, x) 		tb_fixed_atan2(y, x)
#define g2_scalar_exp(x) 			tb_fixed_exp(x)
#define g2_scalar_exp1(x) 			tb_fixed_exp1(x)
#define g2_scalar_expi(x) 			tb_fixed_expi(x)

#elif defined(TB_CONFIG_TYPE_FLOAT)

#define G2_SCALAR_ONE 				1.0f
#define G2_SCALAR_HALF 				0.5f
#define G2_SCALAR_MAX 				TB_MAF
#define G2_SCALAR_MIN 				TB_MIF
#define G2_SCALAR_NAN 				TB_NAN
#define G2_SCALAR_INF 				TB_INF
#define G2_SCALAR_PI 				TB_PI
#define G2_SCALAR_SQRT2 			1.414213562

// conversion
#define g2_scalar_to_float(x) 		(x)
#define g2_float_to_scalar(x) 		(x)

#define g2_long_to_scalar(x) 		(tb_float_t)(x)
#define g2_scalar_to_long(x) 		(tb_long_t)(x)

#define g2_fixed_to_scalar(x) 		tb_fixed_to_float(x)
#define g2_scalar_to_fixed(x) 		tb_float_to_fixed(x)

#define g2_fixed6_to_scalar(x) 		tb_fixed6_to_float(x)
#define g2_scalar_to_fixed6(x) 		tb_float_to_fixed6(x)

#define g2_fixed30_to_scalar(x) 	tb_fixed30_to_float(x)
#define g2_scalar_to_fixed30(x) 	tb_float_to_fixed30(x)

// round
#define g2_scalar_round(x) 			tb_roundf(x)
#define g2_scalar_ceil(x) 			tb_ceilf(x)
#define g2_scalar_floor(x) 			tb_floorf(x)

// functions
#define g2_scalar_abs(x) 			tb_fabs(x)
#define g2_scalar_avg(x, y) 		(((x) + (y)) * 0.5)
#define g2_scalar_lsh(x, y) 		((x) * (tb_float_t)(1 << (y)))
#define g2_scalar_rsh(x, y) 		((x) / (tb_float_t)(1 << (y)))
#define g2_scalar_mul(x, y) 		((x) * (y))
#define g2_scalar_div(x, y) 		((x) / (y))
#define g2_scalar_imul(x, y) 		((x) * (tb_float_t)(y))
#define g2_scalar_idiv(x, y) 		((x) / (tb_float_t)(y))
#define g2_scalar_invert(x) 		(1. / (x))
#define g2_scalar_sqre(x) 			((x) * (x))
#define g2_scalar_sqrt(x) 			tb_sqrtf(x)
#define g2_scalar_sin(x) 			tb_sinf(x)
#define g2_scalar_cos(x) 			tb_cosf(x)
#define g2_scalar_sincos(x, s, c) 	tb_sincosf(x, s, c)
#define g2_scalar_tan(x) 			tb_tanf(x)
#define g2_scalar_asin(x) 			tb_asinf(x)
#define g2_scalar_acos(x) 			tb_acosf(x)
#define g2_scalar_atan(x) 			tb_atanf(x)
#define g2_scalar_atan2(y, x) 		tb_atan2f(y, x)
#define g2_scalar_exp(x) 			tb_expf(x)
#define g2_scalar_exp1(x) 			tb_exp1f(x)
#define g2_scalar_expi(x) 			tb_expif(x)

#else
# 	error float is not supported.
#endif

#endif

