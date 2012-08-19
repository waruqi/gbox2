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
 * @file		path.c
 *
 */
/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "path.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */

// grow
#ifdef TB_CONFIG_MEMORY_MODE_SMALL
# 	define G2_PATH_CODE_GROW 				(32)
# 	define G2_PATH_DATA_GROW 				(64)
#else
# 	define G2_PATH_CODE_GROW 				(128)
# 	define G2_PATH_DATA_GROW 				(256)
#endif

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static __tb_inline__ tb_size_t g2_gl10_path_code_step(tb_size_t code)
{
	// step
	static tb_size_t step[] = 
	{
		0
	, 	1
	, 	1
	, 	2
	, 	3
	, 	0
	};

	// check
	tb_assert_return_val(code < tb_arrayn(step), 0);

	// ok
	return step[code];
}

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */
tb_handle_t g2_path_init()
{
	// make
	g2_gl10_path_t* path = tb_malloc0(sizeof(g2_gl10_path_t));
	tb_assert_and_check_return_val(path, TB_NULL);

	// init code
	path->code = tb_vector_init(G2_PATH_CODE_GROW, tb_item_func_uint8());
	tb_assert_and_check_goto(path->code, fail);

	// init data
	path->data = tb_vector_init(G2_PATH_DATA_GROW, tb_item_func_ifm(sizeof(g2_point_t), TB_NULL, TB_NULL));
	tb_assert_and_check_goto(path->data, fail);

	// init itor
	path->itor.code = tb_iterator_tail(path->code);
	path->itor.data = tb_iterator_tail(path->data);

	// ok
	return path;

fail:
	if (path) g2_path_exit(path);
	return TB_NULL;
}
tb_void_t g2_path_exit(tb_handle_t path)
{
	g2_gl10_path_t* gpath = (g2_gl10_path_t*)path;
	if (gpath)
	{
		// exit data
		if (gpath->data) tb_vector_exit(gpath->data);

		// exit code
		if (gpath->code) tb_vector_exit(gpath->code);

		// free path
		tb_free(gpath);
	}
}
tb_void_t g2_path_clear(tb_handle_t path)
{
	g2_gl10_path_t* gpath = (g2_gl10_path_t*)path;
	tb_assert_and_check_return(gpath);

	// clear code
	if (gpath->code) tb_vector_clear(gpath->code);

	// clear data
	if (gpath->data) tb_vector_clear(gpath->data);
}
tb_void_t g2_path_close(tb_handle_t path)
{
	g2_gl10_path_t* gpath = (g2_gl10_path_t*)path;
	tb_assert_and_check_return(gpath && gpath->code);

	// close 
	if (!tb_vector_size(gpath->code) || (tb_byte_t)tb_vector_last(gpath->code) != G2_PATH_CODE_CLOSE) 
		tb_vector_insert_tail(gpath->code, G2_PATH_CODE_CLOSE);
}
tb_bool_t g2_path_null(tb_handle_t path)
{
	g2_gl10_path_t* gpath = (g2_gl10_path_t*)path;
	tb_assert_and_check_return_val(gpath && gpath->data, TB_TRUE);

	return tb_vector_size(gpath->data)? TB_FALSE : TB_TRUE;
}
tb_bool_t g2_path_last_pt(tb_handle_t path, g2_point_t* pt)
{
	g2_gl10_path_t* gpath = (g2_gl10_path_t*)path;
	tb_assert_and_check_return_val(gpath && gpath->data && pt, TB_FALSE);

	// last
	g2_point_t* last = tb_vector_last(gpath->data);
	if (last) *pt = *last;

	// ok?
	return last? TB_TRUE : TB_FALSE;
}
tb_void_t g2_path_move_to(tb_handle_t path, g2_point_t const* pt)
{
	g2_gl10_path_t* gpath = (g2_gl10_path_t*)path;
	tb_assert_and_check_return(gpath && gpath->code && gpath->data && pt);

	// move to
	tb_vector_insert_tail(gpath->code, G2_PATH_CODE_MOVE);
	tb_vector_insert_tail(gpath->data, pt);
}
tb_void_t g2_path_line_to(tb_handle_t path, g2_point_t const* pt)
{
	g2_gl10_path_t* gpath = (g2_gl10_path_t*)path;
	tb_assert_and_check_return(gpath && gpath->code && gpath->data && pt);

	// line to
	tb_vector_insert_tail(gpath->code, G2_PATH_CODE_LINE);
	tb_vector_insert_tail(gpath->data, pt);
}
tb_void_t g2_path_quad_to(tb_handle_t path, g2_point_t const* cp, g2_point_t const* pt)
{
	g2_gl10_path_t* gpath = (g2_gl10_path_t*)path;
	tb_assert_and_check_return(gpath && gpath->code && gpath->data && cp && pt);

	// quad to
	tb_vector_insert_tail(gpath->code, G2_PATH_CODE_QUAD);
	tb_vector_insert_tail(gpath->data, cp);
	tb_vector_insert_tail(gpath->data, pt);
}
tb_void_t g2_path_cube_to(tb_handle_t path, g2_point_t const* c0, g2_point_t const* c1, g2_point_t const* pt)
{
	g2_gl10_path_t* gpath = (g2_gl10_path_t*)path;
	tb_assert_and_check_return(gpath && gpath->code && gpath->data && c0 && c1 && pt);

	// cube to
	tb_vector_insert_tail(gpath->code, G2_PATH_CODE_CUBIC);
	tb_vector_insert_tail(gpath->data, c0);
	tb_vector_insert_tail(gpath->data, c1);
	tb_vector_insert_tail(gpath->data, pt);
}
tb_void_t g2_path_arc_to(tb_handle_t path, g2_arc_t const* arc)
{
	tb_trace_noimpl();
}
tb_bool_t g2_path_itor_init(tb_handle_t path)
{
	g2_gl10_path_t* gpath = (g2_gl10_path_t*)path;
	tb_assert_and_check_return_val(gpath && gpath->code && gpath->data, TB_FALSE);

	// check
	tb_assert_and_check_return_val(tb_iterator_mode(gpath->code) & TB_ITERATOR_MODE_RACCESS, TB_FALSE);
	tb_assert_and_check_return_val(tb_iterator_mode(gpath->data) & TB_ITERATOR_MODE_RACCESS, TB_FALSE);

	// init itor
	gpath->itor.code = tb_iterator_head(gpath->code);
	gpath->itor.data = tb_iterator_head(gpath->data);

	// ok
	return TB_TRUE;
}
tb_size_t g2_path_itor_next(tb_handle_t path, g2_point_t pt[3])
{
	g2_gl10_path_t* gpath = (g2_gl10_path_t*)path;
	tb_assert_and_check_return_val(gpath && gpath->code && gpath->data && pt, G2_PATH_CODE_NONE);

	// tail?
	tb_check_return_val(gpath->itor.code != tb_iterator_tail(gpath->code), G2_PATH_CODE_NONE);

	// code
	tb_size_t code = (tb_size_t)tb_iterator_item(gpath->code, gpath->itor.code);

	// step
	tb_size_t step = g2_gl10_path_code_step(code);

	// data
	if (step)
	{
		// check
		tb_assert(gpath->itor.data + step <= tb_iterator_tail(gpath->data));

		// data
		g2_point_t const* data = (tb_pointer_t const*)tb_iterator_item(gpath->data, gpath->itor.data);

		// check
		tb_assert(data);

		// copy
		if (data) tb_memcpy(pt, data, step * sizeof(tb_pointer_t));
	}

	// next code
	gpath->itor.code++;

	// next data
	gpath->itor.data += step;

	// ok
	return code;
}
tb_void_t g2_path_itor_exit(tb_handle_t path)
{
	g2_gl10_path_t* gpath = (g2_gl10_path_t*)path;
	tb_assert_and_check_return(gpath);

	gpath->itor.code = tb_iterator_tail(gpath->code);
	gpath->itor.data = tb_iterator_tail(gpath->data);
}

