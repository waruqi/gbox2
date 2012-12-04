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

tb_void_t g2_cutter_quad_init(g2_cutter_quad_t* cutter, g2_cutter_quad_func_t func, tb_pointer_t data)
{
	// check
	tb_assert_and_check_return(cutter);

	// clear
	tb_memset(cutter, 0, sizeof(g2_cutter_quad_t));

	// init
	cutter->func = func;
	cutter->data = data;
}

/*!cutter the quad bezier curve using binary segmentation
 *
 * <pre>
 *            cp
 *            . 
 *           / \
 *          /   \
 *         /     \
 *        /       \
 *    cpb/----.----\ cpe                  
 *      /     p0    \
 *     /             \
 *    /               \
 *   /                 \
 *  /                   \
 * /                     \
 * pb                    pe
 *
 *
 * (pb, cp, pe) => (pb, cpb, p0) & (p0, cpe, pe)
 *
 * e = |cp - (pb + pe) / 2| <= 1
 *
 * </pre>
 */
tb_void_t g2_cutter_quad_done(g2_cutter_quad_t* cutter, g2_point_t const* pb, g2_point_t const* cp, g2_point_t const* pe)
{
	g2_float_t mx = cp->x - g2_rsh(pb->x + pe->x, 1);
	g2_float_t my = cp->y - g2_rsh(pb->y + pe->y, 1);

	// check
	tb_assert(cutter->func);

	// ok?
	if (g2_fabs(mx) + g2_fabs(my) <= G2_ONE)
		cutter->func(cutter, pe);
	else
	{
		g2_point_t p0, cpb, cpe;
		cpb.x = g2_rsh(pb->x + cp->x, 1);
		cpb.y = g2_rsh(pb->y + cp->y, 1);
		cpe.x = g2_rsh(cp->x + pe->x, 1);
		cpe.y = g2_rsh(cp->y + pe->y, 1);
		p0.x = g2_rsh(cpb.x + cpe.x, 1);
		p0.y = g2_rsh(cpb.y + cpe.y, 1);

		g2_cutter_quad_done(cutter, pb, &cpb, &p0);
		g2_cutter_quad_done(cutter, &p0, &cpe, pe);
	}
}


