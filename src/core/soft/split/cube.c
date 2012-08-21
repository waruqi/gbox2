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
 * @file		cube.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "cube.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */

/* split the cube bezier curve using binary segmentation
 *
 *          cpb      cp0      cpe
 *          --------------------
 *         /                    \
 *        /    pb0---------pe0   \
 *       /           p0           \
 *  cp1 /                          \ cp2
 *     /                            \
 *    /                              \
 *   /                                \
 *  /                                  \
 * /                                    \
 * pb                                   pe
 *
 * pb0 = (cp1 + cp0) / 2
 * pe0 = (cp0 + cp2) / 2
 * p0 = (pb0 + pe0) / 2
 *
 * (pb, cpb, cpe, pe) => (pb, cp1, pb0, p0) & (p0, pe0, cp2, pe)
 *
 * a = pe.y - pb.y
 * b = pb.x - pe.x
 * c = pb.y * pe.x - pb.x * pe.y
 * db = a * cpb.x + b * cpb.y + c
 * de = a * cpe.x + b * cpe.y + c
 *
 * eb = |cpb - pb_pe| = |d| / (a * a + b * b)^.5 < 2
 * ee = |cpe - pb_pe| = |d| / (a * a + b * b)^.5 < 2
 *
 * eb * eb = (db * db) / (a * a + b * b) < 4
 * ee * ee = (de * de) / (a * a + b * b) < 4
 *
 * nb = db * db < (a * a + b * b) * 4 = m
 * ne = de * de < (a * a + b * b) * 4 = m
 *
 *
 * eb = |cpb - (pb + pe) * 2 / 3|
 *
 * eb *3 = 3 * cpb - 2 * pb - 2 * pe
 *                          
 */
#if 0
static tb_void_t g2_soft_split_cube_impl(g2_soft_split_cube_t* split, g2_point_t const* pb, g2_point_t const* cpb, g2_point_t const* cpe, g2_point_t const* pe)
{
	g2_float_t a = pe->y - pb->y;
	g2_float_t b = pb->x - pe->x;
	g2_float_t c = g2_mul(pb->y, pe->x) - g2_mul(pb->x, pe->y);
	g2_float_t m = g2_lsh(g2_mul(a, a) + g2_mul(b, b), 2);

	g2_float_t db = g2_mul(a, cpb->x) + g2_mul(b, cpb->y) + c;
	g2_float_t de = g2_mul(a, cpe->x) + g2_mul(b, cpe->y) + c;

	g2_float_t nb = g2_mul(db, db);
	g2_float_t ne = g2_mul(de, de);

	if ((nb < m && ne < m) || g2_ez(m))
	{
		if (split->func) split->func(split, pe);
	}
	else
	{
		g2_point_t cp0, cp1, cp2, pb0, pe0, p0;

		cp0.x = g2_rsh(cpb->x + cpe->x, 1);
		cp0.y = g2_rsh(cpb->y + cpe->y, 1);

		cp1.x = g2_rsh(pb->x + cpb->x, 1);
		cp1.y = g2_rsh(pb->y + cpb->y, 1);

		cp2.x = g2_rsh(cpe->x + pe->x, 1);
		cp2.y = g2_rsh(cpe->y + pe->y, 1);

		pb0.x = g2_rsh(cp0.x + cp1.x, 1);
		pb0.y = g2_rsh(cp0.y + cp1.y, 1);

		pe0.x = g2_rsh(cp0.x + cp2.x, 1);
		pe0.y = g2_rsh(cp0.y + cp2.y, 1);

		p0.x = g2_rsh(pb0.x + pe0.x, 1);
		p0.y = g2_rsh(pb0.y + pe0.y, 1);

		g2_soft_split_cube_impl(split, pb, &cp1, &pb0, &p0);
		g2_soft_split_cube_impl(split, &p0, &pe0, &cp2, pe);

	}
}
#else
static tb_void_t g2_soft_split_cube_impl(g2_soft_split_cube_t* split, g2_point_t const* pb, g2_point_t const* cpb, g2_point_t const* cpe, g2_point_t const* pe)
{
#if 1
	g2_float_t mxb = g2_lsh(cpb->x - pb->x, 1) + cpb->x - pe->x;
	g2_float_t myb = g2_lsh(cpb->y - pb->y, 1) + cpb->y - pe->y;
	g2_float_t mxe = g2_lsh(cpe->x - pe->x, 1) + cpe->x - pb->x;
	g2_float_t mye = g2_lsh(cpe->y - pe->y, 1) + cpe->y - pb->y;
#else
	g2_float_t mxb = cpb->x * 3 - g2_lsh(pb->x, 1) - pe->x;
	g2_float_t myb = cpb->y * 3 - g2_lsh(pb->y, 1) - pe->y;
	g2_float_t mxe = cpe->x * 3 - g2_lsh(pe->x, 1) - pb->x;
	g2_float_t mye = cpe->y * 3 - g2_lsh(pe->y, 1) - pb->y;
#endif

#if 0
	mxb = g2_mul(mxb, mxb);
	myb = g2_mul(myb, myb);
	mxe = g2_mul(mxe, mxe);
	mye = g2_mul(mye, mye);
#else
	mxb = g2_fabs(mxb);
	myb = g2_fabs(myb);
	mxe = g2_fabs(mxe);
	mye = g2_fabs(mye);
#endif

	if (mxe < mxb) mxb = mxe;
	if (mye < myb) myb = mye;

	if (mxb + myb <= G2_ONE)
	{
		if (split->func) split->func(split, pe);
	}
	else
	{
		g2_point_t cp0, cp1, cp2, pb0, pe0, p0;

		cp0.x = g2_rsh(cpb->x + cpe->x, 1);
		cp0.y = g2_rsh(cpb->y + cpe->y, 1);

		cp1.x = g2_rsh(pb->x + cpb->x, 1);
		cp1.y = g2_rsh(pb->y + cpb->y, 1);

		cp2.x = g2_rsh(cpe->x + pe->x, 1);
		cp2.y = g2_rsh(cpe->y + pe->y, 1);

		pb0.x = g2_rsh(cp0.x + cp1.x, 1);
		pb0.y = g2_rsh(cp0.y + cp1.y, 1);

		pe0.x = g2_rsh(cp0.x + cp2.x, 1);
		pe0.y = g2_rsh(cp0.y + cp2.y, 1);

		p0.x = g2_rsh(pb0.x + pe0.x, 1);
		p0.y = g2_rsh(pb0.y + pe0.y, 1);

		g2_soft_split_cube_impl(split, pb, &cp1, &pb0, &p0);
		g2_soft_split_cube_impl(split, &p0, &pe0, &cp2, pe);

	}
}
#endif
/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

tb_void_t g2_soft_split_cube_init(g2_soft_split_cube_t* split, g2_soft_split_cube_func_t func, tb_pointer_t data)
{
	// check
	tb_assert_and_check_return(split);

	// clear
	tb_memset(split, 0, sizeof(g2_soft_split_cube_t));

	// init
	split->func = func;
	split->data = data;
}
tb_void_t g2_soft_split_cube_done(g2_soft_split_cube_t* split, g2_point_t const* pb, g2_point_t const* cpb, g2_point_t const* cpe, g2_point_t const* pe)
{
	// check
	tb_assert_return(split && pb && cpb && cpe && pe);

	// line to?
	if (g2_mul(cpb->x - pb->x, pe->y - pb->y) == g2_mul(cpb->y - pb->y, pe->x - pb->x)
		&& g2_mul(cpe->x - pb->x, pe->y - pb->y) == g2_mul(cpe->y - pb->y, pe->x - pb->x))
	{
		if (split->func) split->func(split, pe);
		return ;
	}

	// done
	return g2_soft_split_cube_impl(split, pb, cpb, cpe, pe);
}


