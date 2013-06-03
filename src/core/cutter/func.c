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
 * @file		func.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "func.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
tb_void_t g2_cutter_func_path_append(g2_cutter_t* cutter, tb_size_t code, g2_point_t const* pt)
{
	// check
	tb_handle_t path = (tb_handle_t)cutter->data;
	tb_assert_and_check_return(path);

	// done
	switch (code)
	{
	case G2_PATH_CODE_MOVE:
		if (pt) g2_path_move_to(path, pt);
		break;
	case G2_PATH_CODE_LINE:
		if (pt) g2_path_line_to(path, pt);
		break;
	case G2_PATH_CODE_CLOS:
		g2_path_close(path);
		break;
	default:
		break;
	}
}
tb_void_t g2_cutter_func_path_append_to(g2_cutter_t* cutter, tb_size_t code, g2_point_t const* pt)
{
	// check
	tb_handle_t path = (tb_handle_t)cutter->data;
	tb_assert_and_check_return(path);

	// done
	switch (code)
	{
	case G2_PATH_CODE_MOVE:
	case G2_PATH_CODE_LINE:
		if (pt) g2_path_line_to(path, pt);
		break;
	case G2_PATH_CODE_CLOS:
		g2_path_close(path);
		break;
	default:
		break;
	}
}
