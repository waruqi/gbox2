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

}


