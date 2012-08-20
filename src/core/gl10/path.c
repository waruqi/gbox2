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
tb_bool_t g2_gl10_path_make_fill(g2_gl10_path_t* path)
{
	// check
	tb_assert_and_check_return_val(path, TB_FALSE);

	// already been maked?
	tb_check_return_val(!path->fill.size || !tb_vector_size(path->fill.size), TB_TRUE);

	// only moveto?
	tb_check_return_val(path->flag & (G2_GL10_PATH_FLAG_LINE | G2_GL10_PATH_FLAG_QUAD | G2_GL10_PATH_FLAG_CUBE), TB_FALSE);

	// init itor
	if (!g2_path_itor_init(path)) return TB_FALSE;

	// init fill data
	if (!path->fill.data)
	{
		path->fill.data = tb_vector_init(G2_PATH_DATA_GROW, tb_item_func_ifm(sizeof(GLfloat) << 1, TB_NULL, TB_NULL));
		tb_assert_and_check_return_val(path->fill.data, TB_FALSE);
	}
	else tb_vector_clear(path->fill.data);

	// init fill size
	if (!path->fill.size)
	{
		path->fill.size = tb_vector_init(G2_PATH_DATA_GROW, tb_item_func_uint16());
		tb_assert_and_check_return_val(path->fill.size, TB_FALSE);
	}
	else tb_vector_clear(path->fill.size);

	// walk
	GLfloat 	temp[2];
	g2_point_t 	data[3];
	g2_point_t 	head;
	tb_size_t 	code = G2_PATH_CODE_NONE;
	tb_size_t 	size = 0;
	while (code = g2_path_itor_next(path, data))
	{
		// done
		switch (code)
		{
		case G2_PATH_CODE_MOVE:
			{
				size = 0;
				head = data[0];
				temp[0] = g2_float_to_tb(data[0].x);
				temp[1] = g2_float_to_tb(data[0].y);
				tb_print("move: %f %f", temp[0], temp[1]);
				tb_vector_insert_tail(path->fill.data, temp);
				tb_vector_insert_tail(path->fill.size, size);
			}
			break;
		case G2_PATH_CODE_LINE:
			{
				size++;
				temp[0] = g2_float_to_tb(data[0].x);
				temp[1] = g2_float_to_tb(data[0].y);
				tb_print("line: %f %f", temp[0], temp[1]);
				tb_vector_insert_tail(path->fill.data, temp);
				tb_vector_replace_last(path->fill.size, size);
			}
			break;
		case G2_PATH_CODE_QUAD:
			{
				size++;
				temp[0] = g2_float_to_tb(data[1].x);
				temp[1] = g2_float_to_tb(data[1].y);
				tb_print("quad: %f %f", temp[0], temp[1]);
				tb_vector_insert_tail(path->fill.data, temp);
				tb_vector_replace_last(path->fill.size, size);
			}
			break;
		case G2_PATH_CODE_CUBE:
			{
				size++;
				temp[0] = g2_float_to_tb(data[2].x);
				temp[1] = g2_float_to_tb(data[2].y);
				tb_print("cube: %f %f", temp[0], temp[1]);
				tb_vector_insert_tail(path->fill.data, temp);
				tb_vector_replace_last(path->fill.size, size);
			}
			break;
		case G2_PATH_CODE_CLOS:
			{
				size++;
				temp[0] = g2_float_to_tb(head.x);
				temp[1] = g2_float_to_tb(head.y);
				tb_print("close: %f %f", temp[0], temp[1]);
				tb_vector_insert_tail(path->fill.data, temp);
				tb_vector_replace_last(path->fill.size, size);
			}
			break;
		default:
			break;
		}
	}

	// exit itor
	g2_path_itor_exit(path);

	// ok
	return TB_TRUE;
}
tb_bool_t g2_gl10_path_make_stok(g2_gl10_path_t* path)
{
	tb_trace_noimpl();
	return TB_FALSE;
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

	// init flag
	path->flag = G2_GL10_PATH_FLAG_NONE;

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

	// clear flag
	gpath->flag = G2_GL10_PATH_FLAG_NONE;

	// clear code
	if (gpath->code) tb_vector_clear(gpath->code);

	// clear data
	if (gpath->data) tb_vector_clear(gpath->data);
}
tb_void_t g2_path_close(tb_handle_t path)
{
	g2_gl10_path_t* gpath = (g2_gl10_path_t*)path;
	tb_assert_and_check_return(gpath && gpath->code);

	// close it, no double closed
	if (!tb_vector_size(gpath->code) || (tb_byte_t)tb_vector_last(gpath->code) != G2_PATH_CODE_CLOS) 
		tb_vector_insert_tail(gpath->code, G2_PATH_CODE_CLOS);

	// close it
	gpath->flag &= ~G2_GL10_PATH_FLAG_OPEN;

	// clear the fill path
	if (gpath->fill.size && tb_vector_size(gpath->fill.size))
		tb_vector_clear(gpath->fill.size);
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
	if (!tb_vector_size(gpath->code) || (tb_byte_t)tb_vector_last(gpath->code) != G2_PATH_CODE_MOVE) 
	{
		tb_vector_insert_tail(gpath->code, G2_PATH_CODE_MOVE);
		tb_vector_insert_tail(gpath->data, pt);
	}
	// avoid a lone move-to
	else tb_vector_replace_last(gpath->data, pt);

	// open it
	gpath->flag |= G2_GL10_PATH_FLAG_OPEN | G2_GL10_PATH_FLAG_MOVE;

	// clear the fill path
	if (gpath->fill.size && tb_vector_size(gpath->fill.size))
		tb_vector_clear(gpath->fill.size);
}
tb_void_t g2_path_line_to(tb_handle_t path, g2_point_t const* pt)
{
	g2_gl10_path_t* gpath = (g2_gl10_path_t*)path;
	tb_assert_and_check_return(gpath && gpath->code && gpath->data && pt);

	// patch move-to
	if (!(gpath->flag & G2_GL10_PATH_FLAG_OPEN)) 
	{
		// the last
		g2_point_t 			null = {0};
		g2_point_t const* 	last = TB_NULL;
		if (tb_vector_size(gpath->data)) last = tb_vector_last(gpath->data);

		// move to the last
		g2_path_move_to(path, last? last : &null);
	}

	// line to
	gpath->flag |= G2_GL10_PATH_FLAG_LINE;
	tb_vector_insert_tail(gpath->code, G2_PATH_CODE_LINE);
	tb_vector_insert_tail(gpath->data, pt);

	// clear the fill path
	if (gpath->fill.size && tb_vector_size(gpath->fill.size))
		tb_vector_clear(gpath->fill.size);
}
tb_void_t g2_path_quad_to(tb_handle_t path, g2_point_t const* cp, g2_point_t const* pt)
{
	g2_gl10_path_t* gpath = (g2_gl10_path_t*)path;
	tb_assert_and_check_return(gpath && gpath->code && gpath->data && cp && pt);

	// patch move-to
	if (!(gpath->flag & G2_GL10_PATH_FLAG_OPEN)) 
	{
		// the last
		g2_point_t 			null = {0};
		g2_point_t const* 	last = TB_NULL;
		if (tb_vector_size(gpath->data)) last = tb_vector_last(gpath->data);

		// move to the last
		g2_path_move_to(path, last? last : &null);
	}

	// quad to
	gpath->flag |= G2_GL10_PATH_FLAG_QUAD;
	tb_vector_insert_tail(gpath->code, G2_PATH_CODE_QUAD);
	tb_vector_insert_tail(gpath->data, cp);
	tb_vector_insert_tail(gpath->data, pt);

	// clear the fill path
	if (gpath->fill.size && tb_vector_size(gpath->fill.size))
		tb_vector_clear(gpath->fill.size);
}
tb_void_t g2_path_cube_to(tb_handle_t path, g2_point_t const* c0, g2_point_t const* c1, g2_point_t const* pt)
{
	g2_gl10_path_t* gpath = (g2_gl10_path_t*)path;
	tb_assert_and_check_return(gpath && gpath->code && gpath->data && c0 && c1 && pt);

	// patch move-to
	if (!(gpath->flag & G2_GL10_PATH_FLAG_OPEN)) 
	{
		// the last
		g2_point_t 			null = {0};
		g2_point_t const* 	last = TB_NULL;
		if (tb_vector_size(gpath->data)) last = tb_vector_last(gpath->data);

		// move to the last
		g2_path_move_to(path, last? last : &null);
	}

	// cube to
	gpath->flag |= G2_GL10_PATH_FLAG_CUBE;
	tb_vector_insert_tail(gpath->code, G2_PATH_CODE_CUBE);
	tb_vector_insert_tail(gpath->data, c0);
	tb_vector_insert_tail(gpath->data, c1);
	tb_vector_insert_tail(gpath->data, pt);

	// clear the fill path
	if (gpath->fill.size && tb_vector_size(gpath->fill.size))
		tb_vector_clear(gpath->fill.size);
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
		if (data) tb_memcpy(pt, data, step * sizeof(g2_point_t));
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

