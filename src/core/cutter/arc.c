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
 * @file		arc.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "arc.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */

tb_void_t g2_cutter_arc_init(g2_cutter_arc_t* cutter, g2_cutter_func_t func, tb_pointer_t data)
{
	// check
	tb_assert_and_check_return(cutter);

	// init
	cutter->func = func;
	cutter->data = data;
}

/*! cutter arc
 *
 * <pre>
 *
 *                       *
 *                     * |
 *                   *   |
 *                 *     |
 *           r   *       |
 *             *         |
 *           *           |
 *         *             |
 *       *               |
 *     *                 |
 *   *  q                |
 * **********************|********
 *         r * cos(q)        d
 *
 * q = an / n;
 *
 * d = r * (1 - cos(q)) ~= r * q * q / 2 < e
 *
 * an * sqrt(r) * sqrt(1 / (2 * e)) < n
 *
 * n > an * sqrt(r) * sqrt(1 / (2 * e))
 *
 * e = 0.125: n > 2 * an * sqrt(r)
 *
 * y = 2 * an * sqrt(x):
 * x: [0, 90]: 		y = 0.21 * x * a
 * x: [90, 1000]: 	y = (0.05 * x + 15) * a
 *
 * r: [0, 90]: 		n > 0.25 * x * a + 16
 * r: [90, 1000]: 	n > (0.0625 * x + 15) * a
 *
 * rx = ry = 1:
 * xx = x * cos(q) - y * sin(q)
 * yy = x * sin(q) + y * cos(q)
 * 
 * if (q < 1)
 * a: cos(q) ~= 1 - q * q / 2
 * b: sin(q) ~= q - q * q * q / 6
 *
 * </pre>
 */
tb_void_t g2_cutter_arc_done(g2_cutter_arc_t* cutter, g2_arc_t const* arc)
{
	// check
	tb_assert_and_check_return(cutter->func && arc);

	// the sin & cos for the start angle
	g2_float_t 	bs;
	g2_float_t 	bc;
	g2_sos(g2_degree_to_radian(arc->ab), &bs, &bc);

	// init
	tb_size_t 	rxi = (tb_size_t)g2_float_to_long(arc->rx);
	tb_size_t 	ryi = (tb_size_t)g2_float_to_long(arc->ry);
	tb_int64_t 	rxf = (tb_int64_t)g2_float_to_fixed(arc->rx);
	tb_int64_t 	ryf = (tb_int64_t)g2_float_to_fixed(arc->ry);
	tb_int64_t 	an = (tb_int64_t)g2_float_to_fixed(g2_degree_to_radian(arc->an)); if (an < 0) an = -an;
	tb_size_t 	xn = rxi < 90? ((rxi >> 2) + 16): ((rxi >> 4) + 15);
	tb_size_t 	yn = ryi < 90? ((ryi >> 2) + 16): ((ryi >> 4) + 15);
	tb_size_t 	n = (xn + yn) >> 1;
	tb_int64_t 	a = TB_FIXED_ONE - (((an * an) / (n * n)) >> 17);
	tb_int64_t 	b = an / n - (((an * an * an) / (3 * n * n * n)) >> 33); if (arc->an < 0) b = -b;
	tb_int64_t 	x0 = (tb_int64_t)g2_float_to_fixed(arc->c0.x);
	tb_int64_t 	y0 = (tb_int64_t)g2_float_to_fixed(arc->c0.y);
	tb_int64_t 	x1 = bc;
	tb_int64_t 	y1 = bs;
	tb_int64_t 	x2 = 0;
	tb_int64_t 	y2 = 0;

	// head
	g2_point_t pb, pt;
	pb.x = arc->c0.x + g2_mul(arc->rx, bc);
	pb.y = arc->c0.y + g2_mul(arc->ry, bs);

	// done
	cutter->func(cutter, G2_PATH_CODE_MOVE, &pb);

	// walk
	while (n--)
	{
		x2 = (a * x1 - b * y1) >> 16;
		y2 = (b * x1 + a * y1) >> 16;

		pt.x = g2_fixed_to_float(x0 + ((x2 * rxf) >> 16));
		pt.y = g2_fixed_to_float(y0 + ((y2 * ryf) >> 16));

		// done
		cutter->func(cutter, G2_PATH_CODE_LINE, &pt);

		// next
		x1 = x2;
		y1 = y2;
	}
}
tb_void_t g2_cutter_arc_exit(g2_cutter_arc_t* cutter)
{
}


