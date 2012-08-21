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
 * trace
 */
#define TB_TRACE_IMPL_TAG 		"path"

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
static __tb_inline__ tb_void_t g2_gl10_path_clear_fill(g2_gl10_path_t* path)
{
	// clear fill data
	if (path->fill.data)
	{
		if (path->fill.data != path->data) tb_vector_clear(path->fill.data);
		else path->fill.data = TB_NULL;
	}

	// clear fill size
	if (path->fill.size)
	{
		if (path->fill.size != path->size) tb_vector_clear(path->fill.size);
		else path->fill.size = TB_NULL;
	}

	// clear fill rect
	tb_memset(&path->fill.rect, 0, sizeof(g2_gl10_rect_t));
}
tb_bool_t g2_gl10_path_make_fill(g2_gl10_path_t* path)
{
	// check
	tb_assert_and_check_return_val(path, TB_FALSE);

	// already been maked?
	tb_check_return_val(!path->fill.size || !tb_vector_size(path->fill.size), TB_TRUE);

	// has data?
	tb_check_return_val(tb_vector_size(path->code) && tb_vector_size(path->data), TB_FALSE);

	// only moveto?
	tb_check_return_val(path->flag & (G2_GL10_PATH_FLAG_LINE | G2_GL10_PATH_FLAG_QUAD | G2_GL10_PATH_FLAG_CUBE), TB_FALSE);

#if 1
	// only lineto?
	if (!(path->flag & (G2_GL10_PATH_FLAG_QUAD | G2_GL10_PATH_FLAG_CUBE)))
	{
		// use the raw data directly
		if (path->fill.data != path->data) tb_vector_exit(path->fill.data);
		if (path->fill.size != path->size) tb_vector_exit(path->fill.size);
		path->fill.data = path->data;
		path->fill.size = path->size;
		path->fill.rect = path->rect;
		return TB_TRUE;
	}
	else 
	{
		// detach the previous reference
		if (path->fill.data == path->data) path->fill.data = TB_NULL;
		if (path->fill.size == path->size) path->fill.size = TB_NULL;
	}
#endif

	// init itor
	tb_byte_t const* 	code = tb_vector_data(path->code);
	tb_float_t const* 	data = tb_vector_data(path->data);
	tb_byte_t const* 	cail = code + tb_vector_size(path->code);
	tb_float_t const* 	dail = data + (tb_vector_size(path->data) << 1);
	tb_float_t const* 	head = TB_NULL;
	tb_size_t 			size = 0;
	tb_assert_and_check_return_val(code && data, TB_NULL);

	// init fill data
	if (!path->fill.data)
	{
		path->fill.data = tb_vector_init(G2_PATH_DATA_GROW, tb_item_func_ifm(sizeof(tb_float_t) << 1, TB_NULL, TB_NULL));
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

	// init bounds
	tb_float_t 	bx1 = 0;
	tb_float_t 	by1 = 0;
	tb_float_t 	bx2 = 0;
	tb_float_t 	by2 = 0;

	// walk
	for (; code < cail && data < dail; code++)
	{
		// done
		switch (*code)
		{
		case G2_PATH_CODE_MOVE:
			{
				// size
				size = 1;

				// head
				head = data;

				// move
				tb_trace_impl("move: %f %f", data[0], data[1]);
				tb_vector_insert_tail(path->fill.data, data);
				tb_vector_insert_tail(path->fill.size, size);

				// bounds
				if (data[0] <= bx1) bx1 = data[0];
				if (data[0] <= by1) by1 = data[0];
				if (data[1] >= bx2) bx2 = data[1];
				if (data[1] >= by2) by2 = data[1];

				// next
				data += 2;
			}
			break;
		case G2_PATH_CODE_LINE:
			{
				// size
				size++;

				// line
				tb_trace_impl("line: %f %f", data[0], data[1]);
				tb_vector_insert_tail(path->fill.data, data);
				tb_vector_replace_last(path->fill.size, size);

				// bounds
				if (data[0] <= bx1) bx1 = data[0];
				if (data[0] <= by1) by1 = data[0];
				if (data[1] >= bx2) bx2 = data[1];
				if (data[1] >= by2) by2 = data[1];

				// next
				data += 2;
			}
			break;
		case G2_PATH_CODE_QUAD:
			{
				// size
				size++;

				// quad
				tb_trace_impl("quad: %f %f", data[2], data[3]);
				tb_vector_insert_tail(path->fill.data, &data[2]);
				tb_vector_replace_last(path->fill.size, size);

				// bounds
				if (data[2] <= bx1) bx1 = data[2];
				if (data[2] <= by1) by1 = data[2];
				if (data[3] >= bx2) bx2 = data[3];
				if (data[3] >= by2) by2 = data[3];

				// next
				data += 4;
			}
			break;
		case G2_PATH_CODE_CUBE:
			{
				// size
				size++;

				// cube
				tb_trace_impl("cube: %f %f", data[4], data[5]);
				tb_vector_insert_tail(path->fill.data, &data[4]);
				tb_vector_replace_last(path->fill.size, size);

				// bounds
				if (data[4] <= bx1) bx1 = data[4];
				if (data[4] <= by1) by1 = data[4];
				if (data[5] >= bx2) bx2 = data[5];
				if (data[5] >= by2) by2 = data[5];	

				// next
				data += 6;
			}
			break;
		case G2_PATH_CODE_CLOS:
			{
				// size
				size++;

				// close
				tb_trace_impl("close");
				if (head)
				{
					tb_vector_insert_tail(path->fill.data, head);
					tb_vector_replace_last(path->fill.size, size);

					// bounds
					if (head[0] <= bx1) bx1 = head[0];
					if (head[0] <= by1) by1 = head[0];
					if (head[1] >= bx2) bx2 = head[1];
					if (head[1] >= by2) by2 = head[1];
				}
			}
			break;
		default:
			break;
		}
	}

	// bounds
	path->fill.rect.x1 = bx1;
	path->fill.rect.y1 = by1;
	path->fill.rect.x2 = bx2;
	path->fill.rect.y2 = by2;

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
	path->data = tb_vector_init(G2_PATH_DATA_GROW, tb_item_func_ifm(sizeof(tb_float_t) << 1, TB_NULL, TB_NULL));
	tb_assert_and_check_goto(path->data, fail);

	// init size
	path->size = tb_vector_init(G2_PATH_DATA_GROW, tb_item_func_uint16());
	tb_assert_and_check_goto(path->size, fail);

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
		// exit code
		if (gpath->code) tb_vector_exit(gpath->code);

		// exit data
		if (gpath->data) tb_vector_exit(gpath->data);

		// exit size
		if (gpath->size) tb_vector_exit(gpath->size);

		// exit fill data
		if (gpath->fill.data && gpath->fill.data != gpath->data) tb_vector_exit(gpath->fill.data);

		// exit fill size
		if (gpath->fill.size && gpath->fill.size != gpath->size) tb_vector_exit(gpath->fill.size);

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

	// clear size
	if (gpath->size) tb_vector_clear(gpath->size);

	// clear rect
	tb_memset(&gpath->rect, 0, sizeof(g2_gl10_rect_t));

	// clear fill 
	g2_gl10_path_clear_fill(gpath);
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

	// clear fill
	g2_gl10_path_clear_fill(gpath);
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
	tb_float_t const* last = tb_vector_last(gpath->data);
	if (last) 
	{
		pt->x = last[0];
		pt->y = last[1];
	}

	// ok?
	return last? TB_TRUE : TB_FALSE;
}
tb_void_t g2_path_move_to(tb_handle_t path, g2_point_t const* pt)
{
	g2_gl10_path_t* gpath = (g2_gl10_path_t*)path;
	tb_assert_and_check_return(gpath && gpath->code && gpath->data && gpath->size && pt);

	// data
	tb_float_t data[2];
	data[0] = g2_float_to_tb(pt->x);
	data[1] = g2_float_to_tb(pt->y);

	// bounds
	if (data[0] <= gpath->rect.x1) gpath->rect.x1 = data[0];
	if (data[0] <= gpath->rect.y1) gpath->rect.y1 = data[0];
	if (data[1] >= gpath->rect.x2) gpath->rect.x2 = data[1];
	if (data[1] >= gpath->rect.y2) gpath->rect.y2 = data[1];

	// move to
	if (!tb_vector_size(gpath->code) || (tb_byte_t)tb_vector_last(gpath->code) != G2_PATH_CODE_MOVE) 
	{
		tb_vector_insert_tail(gpath->code, G2_PATH_CODE_MOVE);
		tb_vector_insert_tail(gpath->data, data);
		tb_vector_insert_tail(gpath->size, 1);
	}
	// avoid a lone move-to
	else tb_vector_replace_last(gpath->data, data);

	// open it
	gpath->flag |= G2_GL10_PATH_FLAG_OPEN | G2_GL10_PATH_FLAG_MOVE;

	// clear fill
	g2_gl10_path_clear_fill(gpath);
}
tb_void_t g2_path_line_to(tb_handle_t path, g2_point_t const* pt)
{
	g2_gl10_path_t* gpath = (g2_gl10_path_t*)path;
	tb_assert_and_check_return(gpath && gpath->code && gpath->data && gpath->size && pt);

	// data
	tb_float_t data[2];
	data[0] = g2_float_to_tb(pt->x);
	data[1] = g2_float_to_tb(pt->y);

	// bounds
	if (data[0] <= gpath->rect.x1) gpath->rect.x1 = data[0];
	if (data[0] <= gpath->rect.y1) gpath->rect.y1 = data[0];
	if (data[1] >= gpath->rect.x2) gpath->rect.x2 = data[1];
	if (data[1] >= gpath->rect.y2) gpath->rect.y2 = data[1];

	// patch move-to
	if (!(gpath->flag & G2_GL10_PATH_FLAG_OPEN)) 
	{
		// the last
		tb_float_t 			null[2] = {0};
		tb_float_t const* 	last = TB_NULL;
		if (tb_vector_size(gpath->data)) last = tb_vector_last(gpath->data);

		// move to the last
		g2_path_move_to(path, last? last : null);
	}

	// line to
	gpath->flag |= G2_GL10_PATH_FLAG_LINE;
	tb_vector_insert_tail(gpath->code, G2_PATH_CODE_LINE);
	tb_vector_insert_tail(gpath->data, data);
	tb_vector_replace_last(gpath->size, tb_vector_last(gpath->size) + 1);

	// clear fill
	g2_gl10_path_clear_fill(gpath);
}
tb_void_t g2_path_quad_to(tb_handle_t path, g2_point_t const* cp, g2_point_t const* pt)
{
	g2_gl10_path_t* gpath = (g2_gl10_path_t*)path;
	tb_assert_and_check_return(gpath && gpath->code && gpath->data && gpath->size && cp && pt);

	// data
	tb_float_t data[4];
	data[0] = g2_float_to_tb(cp->x);
	data[1] = g2_float_to_tb(cp->y);
	data[2] = g2_float_to_tb(pt->x);
	data[3] = g2_float_to_tb(pt->y);

	// bounds
	if (data[2] <= gpath->rect.x1) gpath->rect.x1 = data[2];
	if (data[2] <= gpath->rect.y1) gpath->rect.y1 = data[2];
	if (data[3] >= gpath->rect.x2) gpath->rect.x2 = data[3];
	if (data[3] >= gpath->rect.y2) gpath->rect.y2 = data[3];

	// patch move-to
	if (!(gpath->flag & G2_GL10_PATH_FLAG_OPEN)) 
	{
		// the last
		tb_float_t 			null[2] = {0};
		tb_float_t const* 	last = TB_NULL;
		if (tb_vector_size(gpath->data)) last = tb_vector_last(gpath->data);

		// move to the last
		g2_path_move_to(path, last? last : null);
	}

	// quad to
	gpath->flag |= G2_GL10_PATH_FLAG_QUAD;
	tb_vector_insert_tail(gpath->code, G2_PATH_CODE_QUAD);
	tb_vector_insert_tail(gpath->data, &data[0]);
	tb_vector_insert_tail(gpath->data, &data[2]);
	tb_vector_replace_last(gpath->size, tb_vector_last(gpath->size) + 1);

	// clear fill
	g2_gl10_path_clear_fill(gpath);
}
tb_void_t g2_path_cube_to(tb_handle_t path, g2_point_t const* c0, g2_point_t const* c1, g2_point_t const* pt)
{
	g2_gl10_path_t* gpath = (g2_gl10_path_t*)path;
	tb_assert_and_check_return(gpath && gpath->code && gpath->data && gpath->size && c0 && c1 && pt);

	// data
	tb_float_t data[6];
	data[0] = g2_float_to_tb(c0->x);
	data[1] = g2_float_to_tb(c0->y);
	data[2] = g2_float_to_tb(c1->x);
	data[3] = g2_float_to_tb(c1->y);
	data[4] = g2_float_to_tb(pt->x);
	data[5] = g2_float_to_tb(pt->y);

	// bounds
	if (data[4] <= gpath->rect.x1) gpath->rect.x1 = data[4];
	if (data[4] <= gpath->rect.y1) gpath->rect.y1 = data[4];
	if (data[5] >= gpath->rect.x2) gpath->rect.x2 = data[5];
	if (data[5] >= gpath->rect.y2) gpath->rect.y2 = data[5];

	// patch move-to
	if (!(gpath->flag & G2_GL10_PATH_FLAG_OPEN)) 
	{
		// the last
		tb_float_t 			null[2] = {0};
		tb_float_t const* 	last = TB_NULL;
		if (tb_vector_size(gpath->data)) last = tb_vector_last(gpath->data);

		// move to the last
		g2_path_move_to(path, last? last : null);
	}

	// cube to
	gpath->flag |= G2_GL10_PATH_FLAG_CUBE;
	tb_vector_insert_tail(gpath->code, G2_PATH_CODE_CUBE);
	tb_vector_insert_tail(gpath->data, &data[0]);
	tb_vector_insert_tail(gpath->data, &data[2]);
	tb_vector_insert_tail(gpath->data, &data[4]);
	tb_vector_replace_last(gpath->size, tb_vector_last(gpath->size) + 1);

	// clear fill
	g2_gl10_path_clear_fill(gpath);
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
		tb_float_t const* data = (tb_float_t const*)tb_iterator_item(gpath->data, gpath->itor.data);

		// check
		tb_assert(data);

		// copy
		if (data) 
		{
#ifdef G2_CONFIG_FLOAT_FIXED
			switch (step)
			{
			case 1:
				pt[0].x = tb_float_to_g2(data[0]);
				pt[0].y = tb_float_to_g2(data[1]);
				break;
			case 2:
				pt[0].x = tb_float_to_g2(data[0]);
				pt[0].y = tb_float_to_g2(data[1]);
				pt[1].x = tb_float_to_g2(data[2]);
				pt[1].y = tb_float_to_g2(data[3]);
				break;
			case 3:
				pt[0].x = tb_float_to_g2(data[0]);
				pt[0].y = tb_float_to_g2(data[1]);
				pt[1].x = tb_float_to_g2(data[2]);
				pt[1].y = tb_float_to_g2(data[3]);
				pt[2].x = tb_float_to_g2(data[4]);
				pt[2].y = tb_float_to_g2(data[5]);
				break;
			default:
				break;
			}
#else
			if (step) tb_memcpy(pt, data, step * sizeof(tb_float_t) << 1);
#endif
		}
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

