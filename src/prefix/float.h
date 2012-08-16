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
 * @file		float.h
 *
 */
#ifndef G2_PREFIX_FLOAT_H
#define G2_PREFIX_FLOAT_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "config.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */

#ifdef G2_CONFIG_FLOAT_FIXED

// constant
#define G2_ONE 					TB_FIXED_ONE
#define G2_TWO 					(TB_FIXED_ONE + TB_FIXED_ONE)
#define G2_HAF 					TB_FIXED_HALF
#define G2_MAF 					TB_FIXED_MAX
#define G2_MIF 					TB_FIXED_MIN
#define G2_NAN 					TB_FIXED_NAN
#define G2_INF 					TB_FIXED_INF
#define G2_SQRT2 				TB_FIXED_SQRT2
#define G2_PI 					TB_FIXED_PI
#define G2_PI_l_180 			(1143)
#define G2_180_l_PI 			(3754936)
#define G2_NEAR0 				(TB_FIXED_ONE / (1 << 12))

// conversion
#ifdef TB_CONFIG_TYPE_FLOAT
# 	define g2_float_to_tb(x) 	tb_fixed_to_float(x)
# 	define tb_float_to_g2(x) 	tb_float_to_fixed(x)
#endif

#define g2_long_to_float(x) 	tb_long_to_fixed(x)
#define g2_float_to_long(x) 	tb_fixed_to_long(x)

#define g2_fixed_to_float(x) 	(x)
#define g2_float_to_fixed(x) 	(x)

#define g2_fixed6_to_float(x) 	tb_fixed6_to_fixed(x)
#define g2_float_to_fixed6(x) 	tb_fixed_to_fixed6(x)

#define g2_fixed30_to_float(x) 	tb_fixed30_to_fixed(x)
#define g2_float_to_fixed30(x) 	tb_fixed_to_fixed30(x)

#define g2_degree_to_radian(x) 	(tb_fixed_mul((x), G2_PI_l_180))
#define g2_radian_to_degree(x) 	(tb_fixed_mul((x), G2_180_l_PI))

// round
#define g2_round(x) 			tb_fixed_round(x)
#define g2_ceil(x) 				tb_fixed_ceil(x)
#define g2_floor(x) 			tb_fixed_floor(x)

// functions
#define g2_fabs(x) 				tb_fixed_abs(x)
#define g2_avg(x, y) 			tb_fixed_avg(x, y)
#define g2_mul(x, y) 			tb_fixed_mul(x, y)
#define g2_div(x, y) 			tb_fixed_div(x, y)
#define g2_lsh(x, y) 			tb_fixed_lsh(x, y)
#define g2_rsh(x, y) 			tb_fixed_rsh(x, y)
#define g2_imul(x, y) 			tb_fixed_imul(x, y)
#define g2_idiv(x, y) 			tb_fixed_idiv(x, y)
#define g2_invert(x) 			tb_fixed_invert(x)
#define g2_sqre(x) 				tb_fixed_sqre(x)
#define g2_sqrt(x) 				tb_fixed_sqrt(x)
#define g2_sin(x) 				tb_fixed_sin(x)
#define g2_cos(x) 				tb_fixed_cos(x)
#define g2_sincos(x, s, c) 		tb_fixed_sincos(x, s, c)
#define g2_tan(x) 				tb_fixed_tan(x)
#define g2_asin(x) 				tb_fixed_asin(x)
#define g2_acos(x) 				tb_fixed_acos(x)
#define g2_atan(x) 				tb_fixed_atan(x)
#define g2_atan2(y, x) 			tb_fixed_atan2(y, x)
#define g2_exp(x) 				tb_fixed_exp(x)
#define g2_exp1(x) 				tb_fixed_exp1(x)
#define g2_expi(x) 				tb_fixed_expi(x)

// comparison
#define g2_nz(x) 				(x)
#define g2_ez(x) 				(!(x))
#define g2_lz(x) 				((x) < 0)
#define g2_bz(x) 				((x) > 0)

#define g2_n1(x) 				((x) != G2_ONE)
#define g2_e1(x) 				((x) == G2_ONE)
#define g2_l1(x) 				((x) < G2_ONE)
#define g2_b1(x) 				((x) > G2_ONE)

#elif defined(TB_CONFIG_TYPE_FLOAT)

// constant
#define G2_ONE 					(1.0f)
#define G2_TWO 					(2.0f)
#define G2_HAF 					(0.5f)
#define G2_MAF 					TB_MAF
#define G2_MIF 					TB_MIF
#define G2_NAN 					TB_NAN
#define G2_INF 					TB_INF
#define G2_PI 					TB_PI
#define G2_SQRT2 				(1.414213562)
#define G2_NEAR0 				(1.0f / (1 << 12))

// conversion
#define g2_float_to_tb(x) 		(x)
#define tb_float_to_g2(x) 		(x)

#define g2_long_to_float(x) 	(tb_float_t)(x)
#define g2_float_to_long(x) 	(tb_long_t)(x)

#define g2_fixed_to_float(x) 	tb_fixed_to_float(x)
#define g2_float_to_fixed(x) 	tb_float_to_fixed(x)

#define g2_fixed6_to_float(x) 	tb_fixed6_to_float(x)
#define g2_float_to_fixed6(x) 	tb_float_to_fixed6(x)

#define g2_fixed30_to_float(x) 	tb_fixed30_to_float(x)
#define g2_float_to_fixed30(x) 	tb_float_to_fixed30(x)

#define g2_degree_to_radian(x) 	(((x) * G2_PI) / 180.)
#define g2_radian_to_degree(x) 	(((x) * 180.) / G2_PI)

// round
#define g2_round(x) 			tb_roundf(x)
#define g2_ceil(x) 				tb_ceilf(x)
#define g2_floor(x) 			tb_floorf(x)

// functions
#define g2_fabs(x) 				tb_fabs(x)
#define g2_avg(x, y) 			(((x) + (y)) * 0.5)
#define g2_lsh(x, y) 			((x) * (tb_float_t)(1 << (y)))
#define g2_rsh(x, y) 			((x) / (tb_float_t)(1 << (y)))
#define g2_mul(x, y) 			((x) * (y))
#define g2_div(x, y) 			((x) / (y))
#define g2_imul(x, y) 			((x) * (tb_float_t)(y))
#define g2_idiv(x, y) 			((x) / (tb_float_t)(y))
#define g2_invert(x) 			(1. / (x))
#define g2_sqre(x) 				((x) * (x))
#define g2_sqrt(x) 				tb_sqrtf(x)
#define g2_sin(x) 				tb_sinf(x)
#define g2_cos(x) 				tb_cosf(x)
#define g2_sincos(x, s, c) 		tb_sincosf(x, s, c)
#define g2_tan(x) 				tb_tanf(x)
#define g2_asin(x) 				tb_asinf(x)
#define g2_acos(x) 				tb_acosf(x)
#define g2_atan(x) 				tb_atanf(x)
#define g2_atan2(y, x) 			tb_atan2f(y, x)
#define g2_exp(x) 				tb_expf(x)
#define g2_exp1(x) 				tb_exp1f(x)
#define g2_expi(x) 				tb_expif(x)

// comparison
#define g2_nz(x) 				g2_float_nz(x)
#define g2_ez(x) 				(!g2_nz(x))
#define g2_lz(x) 				(g2_nz(x) < 0)
#define g2_bz(x) 				(g2_nz(x) > 0)

#define g2_n1(x) 				((x) != G2_ONE)
#define g2_e1(x) 				((x) == G2_ONE)
#define g2_l1(x) 				((x) < G2_ONE)
#define g2_b1(x) 				((x) > G2_ONE)

#else
# 	error float is not supported.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * inlines
 */
#ifdef TB_CONFIG_TYPE_FLOAT
static __tb_inline__ tb_long_t g2_float_nz(tb_float_t x)
{
	tb_int32_t y;
	union g2_float_union 
	{
		tb_float_t 	f;
		tb_int32_t 	i;
	}u;
	u.f = x;
	y = u.i;

	if (y < 0) 
	{
		y &= 0x7fffffff;
		y = -y;
	}
	return y;
}
#endif

#endif

