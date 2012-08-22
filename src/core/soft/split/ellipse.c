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

tb_void_t g2_soft_split_ellipse_init(g2_soft_split_ellipse_t* split, g2_soft_split_ellipse_func_t func, tb_pointer_t data)
{
	// check
	tb_assert_and_check_return(split);

	// clear
	tb_memset(split, 0, sizeof(g2_soft_split_ellipse_t));

	// init
	split->func = func;
	split->data = data;
}

/*!split ellipse
 *
 * <pre>
 *
 *                 /
 *               /
 *             /
 *           /
 *         /
 *       /
 *     /
 *   /  q
 * /----------------------|--|
 *            r            e
 *
 * q = 2 * pi / n;
 * (r + e) - (r + e) * cos(q/2) = 2 * e
 *
 * q <~ 1 => cos(q/2) ~= 1 - q * q / 8
 * n = 0.5 * pi * sqrt(r / e + 1) ~= 0.5 * pi * sqrt(r / e)
 *
 * if e < 0.4, n >= 2.5 * pi * sqrt(r)
 * ~=>: 
 * if (r <= 90) n ~= |r / 4| + 6
 * if (r > 90) n ~= |r / 16| + 23
 *
 * r = 1:
 * xx = x * cos(q) - y * sin(q)
 * yy = x * sin(q) + y * cos(q)
 *
 * if (q < 1)
 * cos(q) ~= 1 - q * q / 2
 * sin(q) ~= q - q * q * q / 6
 *
 * </pre>
 */
tb_void_t g2_soft_split_ellipse_done(g2_soft_split_ellipse_t* split, g2_ellipse_t const* ellipse)
{

}


