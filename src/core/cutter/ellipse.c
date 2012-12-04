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
 * @file		ellipse.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "ellipse.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */

tb_void_t g2_cutter_ellipse_init(g2_cutter_ellipse_t* cutter, g2_cutter_ellipse_func_t func, tb_pointer_t data)
{
	// check
	tb_assert_and_check_return(cutter);

	// clear
	tb_memset(cutter, 0, sizeof(g2_cutter_ellipse_t));

	// init
	cutter->func = func;
	cutter->data = data;
}

/*!cutter ellipse
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
 * q = 2 * pi / n;
 *
 * d = r * (1 - cos(q)) ~= r * q * q / 2 < e
 *
 * n > pi * sqrt(2 / e) * sqrt(r)
 *
 * e = 0.125: n > 4 * pi * sqrt(r)
 *
 * y = pi * sqrt(x):
 * x < 90: y = (1 / 3) * x
 * x > 90: y = (0.08) * x + 23
 *
 * r < 90: n > (4 / 3) * r + 16
 * r > 90: n > (1 / 3) * r + 92
 *
 * rx = ry = 1:
 * xx = x * cos(q) - y * sin(q)
 * yy = x * sin(q) + y * cos(q)
 * 
 * if (q < 1)
 * cos(q) ~= 1 - q * q / 2
 * sin(q) ~= q - q * q * q / 6
 *
 * </pre>
 */
tb_void_t g2_cutter_ellipse_done(g2_cutter_ellipse_t* cutter, g2_ellipse_t const* ellipse)
{
	// check
	tb_assert(cutter->func);

	// init
	tb_size_t 	rxi = (tb_size_t)g2_float_to_long(ellipse->rx);
	tb_size_t 	ryi = (tb_size_t)g2_float_to_long(ellipse->ry);
	tb_int64_t 	rxf = (tb_int64_t)g2_float_to_fixed(ellipse->rx);
	tb_int64_t 	ryf = (tb_int64_t)g2_float_to_fixed(ellipse->ry);
	tb_int64_t 	pi = (tb_int64_t)TB_FIXED_PI;
	tb_size_t 	xn = rxi < 90? ((rxi << 2) / 3 + 16): ((rxi / 3) + 92);
	tb_size_t 	yn = ryi < 90? ((ryi << 2) / 3 + 16): ((ryi / 3) + 92);
	tb_size_t 	n = (xn + yn) >> 1;
	tb_int64_t 	a = TB_FIXED_ONE - (((pi * pi) / (n * n)) >> 15);
	tb_int64_t 	b = (pi << 1) / n - (((pi * pi * pi) / (3 * n * n * n)) >> 30);

	tb_int64_t 	x0 = (tb_int64_t)g2_float_to_fixed(ellipse->c0.x);
	tb_int64_t 	y0 = (tb_int64_t)g2_float_to_fixed(ellipse->c0.y);
	tb_int64_t 	x1 = TB_FIXED_ONE;
	tb_int64_t 	y1 = 0;
	tb_int64_t 	x2 = 0;
	tb_int64_t 	y2 = 0;

	// head
	g2_point_t pb, pt;
	pb.x = g2_fixed_to_float(x0 + rxf);
	pb.y = g2_fixed_to_float(y0);

	// done
	cutter->func(cutter, &pb);

	// walk
	while (n--)
	{
		x2 = (a * x1 - b * y1) >> 16;
		y2 = (b * x1 + a * y1) >> 16;

		pt.x = g2_fixed_to_float(x0 + ((x2 * rxf) >> 16));
		pt.y = g2_fixed_to_float(y0 - ((y2 * ryf) >> 16));

		// done
		cutter->func(cutter, &pt);

		// next
		x1 = x2;
		y1 = y2;
	}
	
	// close 
	cutter->func(cutter, &pb);
}


