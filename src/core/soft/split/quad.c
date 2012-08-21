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
 * @file		quad.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "quad.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */

/* split the quad bezier curve using binary segmentation
 *
 *            cp
 *            . -----------------------------------
 *           / \                          |
 *          /   \
 *         /     \
 *        /       \
 *    cpb/----.----\ cpe                  e
 *      /     p0    \
 *     /             \
 *    /               \
 *   /                 \
 *  /                   \                 |
 * /                     \ ------------------------
 * pb                    pe
 *
 *
 * (pb, cp, pe) => (pb, cpb, p0) & (p0, cpe, pe)
 *
 * a = pe.y - pb.y
 * b = pb.x - pe.x
 * c = pb.y * pe.x - pb.x * pe.y
 * d = a * cp.x + b * cp.y + c
 *
 * e = |cp - pb_pe| = |d| / (a * a + b * b)^.5 < 2
 *
 * e * e = (d * d) / (a * a + b * b) < 4
 *
 * n = d * d < (a * a + b * b) * 4 = m
 *                          
 */
static tb_void_t g2_soft_split_quad_impl(g2_soft_split_quad_t* split, g2_point_t const* pb, g2_point_t const* cp, g2_point_t const* pe)
{
	g2_float_t a = pe->y - pb->y;
	g2_float_t b = pb->x - pe->x;
	g2_float_t c = g2_mul(pb->y, pe->x) - g2_mul(pb->x, pe->y);
	g2_float_t m = g2_lsh(g2_mul(a, a) + g2_mul(b, b), 2);

	g2_float_t d = g2_mul(a, cp->x) + g2_mul(b, cp->y) + c;
	g2_float_t n = g2_mul(d, d);

	if (n < m || g2_ez(m))
	{
		if (split->func) split->func(split, pe);
	}
	else
	{
		g2_point_t p0, cpb, cpe;
		cpb.x = g2_rsh(pb->x + cp->x, 1);
		cpb.y = g2_rsh(pb->y + cp->y, 1);
		cpe.x = g2_rsh(cp->x + pe->x, 1);
		cpe.y = g2_rsh(cp->y + pe->y, 1);
		p0.x = g2_rsh(cpb.x + cpe.x, 1);
		p0.y = g2_rsh(cpb.y + cpe.y, 1);

		g2_soft_split_quad_impl(split, pb, &cpb, &p0);
		g2_soft_split_quad_impl(split, &p0, &cpe, pe);
	}
}

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

tb_void_t g2_soft_split_quad_init(g2_soft_split_quad_t* split, g2_soft_split_quad_func_t func, tb_pointer_t data)
{
	// check
	tb_assert_and_check_return(split);

	// clear
	tb_memset(split, 0, sizeof(g2_soft_split_quad_t));

	// init
	split->func = func;
	split->data = data;
}
tb_void_t g2_soft_split_quad_done(g2_soft_split_quad_t* split, g2_point_t const* pb, g2_point_t const* cp, g2_point_t const* pe)
{
	// check
	tb_assert_return(split && pb && cp && pe);

	// line to?
	if (g2_mul(cp->x - pb->x, pe->y - pb->y) == g2_mul(cp->y - pb->y, pe->x - pb->x))
	{
		if (split->func) split->func(split, pe);
		return ;
	}

	// done
	return g2_soft_split_quad_impl(split, pb, cp, pe);
}


