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
 * e = min(|(cpb - pb) * 2 + cpb - pe|, |(cpe - pe) * 2 + cpe - pb|) <= 1
 *                          
 */

tb_void_t g2_soft_split_cube_done(g2_soft_split_cube_t* split, g2_point_t const* pb, g2_point_t const* cpb, g2_point_t const* cpe, g2_point_t const* pe)
{
	g2_float_t mxb = g2_lsh(cpb->x - pb->x, 1) + cpb->x - pe->x;
	g2_float_t myb = g2_lsh(cpb->y - pb->y, 1) + cpb->y - pe->y;
	g2_float_t mxe = g2_lsh(cpe->x - pe->x, 1) + cpe->x - pb->x;
	g2_float_t mye = g2_lsh(cpe->y - pe->y, 1) + cpe->y - pb->y;

	mxb = g2_fabs(mxb);
	myb = g2_fabs(myb);
	mxe = g2_fabs(mxe);
	mye = g2_fabs(mye);

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

		g2_soft_split_cube_done(split, pb, &cp1, &pb0, &p0);
		g2_soft_split_cube_done(split, &p0, &pe0, &cp2, pe);

	}
}


