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

#define g2_int_to_scalar(x) 		tb_int_to_fixed(x)
#define g2_scalar_to_int(x) 		tb_fixed_to_int(x)

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
#define g2_scalar_ilog2(x) 			tb_fixed_ilog2(x)
#define g2_scalar_iclog2(x) 		tb_fixed_iclog2(x)
#define g2_scalar_irlog2(x) 		tb_fixed_irlog2(x)

#elif defined(TB_CONFIG_TYPE_FLOAT)

#define G2_SCALAR_ONE 				TB_FLOAT_ONE
#define G2_SCALAR_HALF 				TB_FLOAT_HALF
#define G2_SCALAR_MAX 				TB_FLOAT_MAX
#define G2_SCALAR_MIN 				TB_FLOAT_MIN
#define G2_SCALAR_NAN 				TB_FLOAT_NAN
#define G2_SCALAR_INF 				TB_FLOAT_INF
#define G2_SCALAR_PI 				TB_FLOAT_PI
#define G2_SCALAR_SQRT2 			TB_FLOAT_SQRT2

// conversion
#ifdef TB_CONFIG_TYPE_FLOAT
# 	define g2_scalar_to_float(x) 	tb_float_to_float(x)
# 	define g2_float_to_scalar(x) 	tb_float_to_float(x)
#endif

#define g2_int_to_scalar(x) 		tb_int_to_float(x)
#define g2_scalar_to_int(x) 		tb_float_to_int(x)

#define g2_fixed_to_scalar(x) 		tb_fixed_to_float(x)
#define g2_scalar_to_fixed(x) 		tb_float_to_fixed(x)

#define g2_fixed6_to_scalar(x) 		tb_fixed6_to_float(x)
#define g2_scalar_to_fixed6(x) 		tb_float_to_fixed6(x)

#define g2_fixed30_to_scalar(x) 	tb_fixed30_to_float(x)
#define g2_scalar_to_fixed30(x) 	tb_float_to_fixed30(x)

// round
#define g2_scalar_round(x) 			tb_float_round(x)
#define g2_scalar_ceil(x) 			tb_float_ceil(x)
#define g2_scalar_floor(x) 			tb_float_floor(x)

// functions
#define g2_scalar_abs(x) 			tb_float_abs(x)
#define g2_scalar_avg(x, y) 		tb_float_avg(x, y)
#define g2_scalar_lsh(x, y) 		tb_float_lsh(x, y)
#define g2_scalar_rsh(x, y) 		tb_float_rsh(x, y)
#define g2_scalar_mul(x, y) 		tb_float_mul(x, y)
#define g2_scalar_div(x, y) 		tb_float_div(x, y)
#define g2_scalar_imul(x, y) 		tb_float_imul(x, y)
#define g2_scalar_idiv(x, y) 		tb_float_idiv(x, y)
#define g2_scalar_invert(x) 		tb_float_invert(x)
#define g2_scalar_sqre(x) 			tb_float_sqre(x)
#define g2_scalar_sqrt(x) 			tb_float_sqrt(x)
#define g2_scalar_sin(x) 			tb_float_sin(x)
#define g2_scalar_cos(x) 			tb_float_cos(x)
#define g2_scalar_sincos(x, s, c) 	tb_float_sincos(x, s, c)
#define g2_scalar_tan(x) 			tb_float_tan(x)
#define g2_scalar_asin(x) 			tb_float_asin(x)
#define g2_scalar_acos(x) 			tb_float_acos(x)
#define g2_scalar_atan(x) 			tb_float_atan(x)
#define g2_scalar_atan2(y, x) 		tb_float_atan2(y, x)
#define g2_scalar_exp(x) 			tb_float_exp(x)
#define g2_scalar_exp1(x) 			tb_float_exp1(x)
#define g2_scalar_expi(x) 			tb_float_expi(x)
#define g2_scalar_ilog2(x) 			tb_float_ilog2(x)
#define g2_scalar_iclog2(x) 		tb_float_iclog2(x)
#define g2_scalar_irlog2(x) 		tb_float_irlog2(x)

#else
# 	error float is not supported.
#endif

#endif

