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
 * @file		context.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * trace
 */
#define TB_TRACE_IMPL_TAG 		"gbox"

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
tb_handle_t g2_context_init(tb_size_t pixfmt, tb_pointer_t data, tb_size_t width, tb_size_t height, tb_size_t lpitch)
{
	tb_trace_noimpl();
	return tb_null;
}
tb_void_t g2_context_exit(tb_handle_t context)
{
	tb_trace_noimpl();
}
tb_handle_t g2_context_surface(tb_handle_t context)
{
	tb_trace_noimpl();
	return tb_null;
}
tb_handle_t g2_context_resize(tb_handle_t context, tb_size_t width, tb_size_t height)
{
	tb_trace_noimpl();
	return tb_null;
}

