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
#include "rect.h"
#include "../soft/split/split.h"

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
 * helper
 */
static __tb_inline__ tb_size_t g2_gl_path_code_step(tb_size_t code)
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
 * fill
 */
static __tb_inline__ tb_void_t g2_gl_path_fill_clear(g2_gl_path_t* path)
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
	tb_memset(&path->fill.rect, 0, sizeof(g2_gl_rect_t));
}
static tb_void_t g2_gl_path_fill_split_quad_func(g2_soft_split_quad_t* split, g2_point_t const* pt)
{
	// path
	g2_gl_path_t* path = (g2_gl_path_t*)split->data;
	tb_assert_return(path);

	// data
	tb_float_t data[2];
	data[0] = g2_float_to_tb(pt->x);
	data[1] = g2_float_to_tb(pt->y);

	// add
	tb_vector_insert_tail(path->fill.data, data);
	tb_vector_replace_last(path->fill.size, tb_vector_last(path->fill.size) + 1);
}
static tb_void_t g2_gl_path_fill_split_cube_func(g2_soft_split_cube_t* split, g2_point_t const* pt)
{
	// path
	g2_gl_path_t* path = (g2_gl_path_t*)split->data;
	tb_assert_return(path);

	// data
	tb_float_t data[2];
	data[0] = g2_float_to_tb(pt->x);
	data[1] = g2_float_to_tb(pt->y);

	// add
	tb_vector_insert_tail(path->fill.data, data);
	tb_vector_replace_last(path->fill.size, tb_vector_last(path->fill.size) + 1);
}

/* ///////////////////////////////////////////////////////////////////////
 * add
 */
static tb_void_t g2_gl_path_add_split_circle_func(g2_soft_split_circle_t* split, g2_point_t const* pt)
{
	// data
	tb_handle_t* data = (tb_handle_t*)split->data;
	tb_assert_return(data && data[0]);

	// line-to?
	if (!data[1]) g2_path_line_to(data[0], pt);
	// move-to?
	else 
	{
		g2_path_move_to(data[0], pt);
		data[1] = TB_NULL;
	}
}
static tb_void_t g2_gl_path_add_split_ellipse_func(g2_soft_split_ellipse_t* split, g2_point_t const* pt)
{
	// data
	tb_handle_t* data = (tb_handle_t*)split->data;
	tb_assert_return(data && data[0]);

	// line-to?
	if (!data[1]) g2_path_line_to(data[0], pt);
	// move-to?
	else 
	{
		g2_path_move_to(data[0], pt);
		data[1] = TB_NULL;
	}
}

/* ///////////////////////////////////////////////////////////////////////
 * maker
 */
tb_void_t g2_gl_path_make_like(g2_gl_path_t* path)
{
	// check
	tb_assert_and_check_return(path);

	// has like?
	tb_check_return(path->like == G2_GL_PATH_LIKE_NONE);

	// has data?
	tb_check_return(tb_vector_size(path->code) && tb_vector_size(path->data));

	// only moveto?
	tb_check_return(path->flag & (G2_GL_PATH_FLAG_LINE | G2_GL_PATH_FLAG_QUAD | G2_GL_PATH_FLAG_CUBE));

	// data && size
	tb_size_t 			size = tb_vector_size(path->data);
	tb_float_t const* 	data = tb_vector_data(path->data);
	tb_assert_and_check_return(data && size);

	// only has lineto?
	if (!(path->flag & (G2_GL_PATH_FLAG_QUAD | G2_GL_PATH_FLAG_CUBE)))
	{
		// check
		tb_check_return(path->rect.x1 < path->rect.x2 && path->rect.y1 < path->rect.y2);

		// like for only one segment
		if (tb_vector_size(path->size) == 1)
		{
			// like line?
			if (size == 2)
			{
				if (data[0] != data[2] || data[1] != data[3]) 
				{
					path->like = G2_GL_PATH_LIKE_LINE;
					path->line.p0.x = tb_float_to_g2(data[0]);
					path->line.p0.y = tb_float_to_g2(data[1]);
					path->line.p1.x = tb_float_to_g2(data[2]);
					path->line.p1.y = tb_float_to_g2(data[3]);
					tb_trace_impl("like: line");
				}
			}
			// like triangle?
			else if (size == 3 || (size == 4 && data[0] == data[6] && data[1] == data[7]))
			{
				// p0 != p1 != p2, triangle or line
				if ((data[0] != data[2] || data[1] != data[3])
				&&	(data[0] != data[4] || data[1] != data[5])
				&&	(data[4] != data[2] || data[5] != data[3])) 
				{
					path->like = G2_GL_PATH_LIKE_TRIG;
					path->trig.p0.x = tb_float_to_g2(data[0]);
					path->trig.p0.y = tb_float_to_g2(data[1]);
					path->trig.p1.x = tb_float_to_g2(data[2]);
					path->trig.p1.y = tb_float_to_g2(data[3]);
					path->trig.p2.x = tb_float_to_g2(data[4]);
					path->trig.p2.y = tb_float_to_g2(data[5]);
					tb_trace_impl("like: triangle");
				}
			}
			// like rect?
			else if (size == 4 || (size == 5 && data[0] == data[8] && data[1] == data[9]))
			{
				if (( 	data[0] == data[2] 
					&& 	data[3] == data[5]
					&& 	data[4] == data[6]
					&& 	data[7] == data[1])
				|| ( 	data[1] == data[3] 
					&& 	data[2] == data[4] 
					&& 	data[5] == data[7]
					&& 	data[6] == data[0]))
				{
					path->like = G2_GL_PATH_LIKE_RECT;
					tb_trace_impl("like: rect");
				}
			}
		}
	}

	// has like?
	tb_check_return(path->like == G2_GL_PATH_LIKE_NONE);

	// like convex polygon?
	if (tb_vector_size(path->size) == 1 && size > 3)
	{
		tb_float_t 			a = 0;
		tb_float_t 			b = 0;
		tb_float_t const* 	p = data;
		tb_float_t const* 	e = data + (size << 1);
		tb_float_t 			x0 = 0;
		tb_float_t 			y0 = 0;
		tb_float_t 			x1 = 0;
		tb_float_t 			y1 = 0;
		tb_float_t 			x2 = 0;
		tb_float_t 			y2 = 0;
		for (; p < e; p += 2, a = b)
		{
			if (p + 4 < e)
			{
				x0 = p[0];
				y0 = p[1];
				x1 = p[2];
				y1 = p[3];
				x2 = p[4];
				y2 = p[5];
			}
			else if (p + 2 < e)
			{
				x0 = p[0];
				y0 = p[1];
				x1 = p[2];
				y1 = p[3];
				x2 = data[0];
				y2 = data[1];
			}
			else
			{
				x0 = p[0];
				y0 = p[1];
				x1 = data[0];
				y1 = data[1];
				x2 = data[2];
				y2 = data[3];
			}
			b = (x0 - x2) * (y1 - y2) - (y0 - y2) * (x1 - x2);
			if (p != data && a * b < 0) break;
		}
		if (p == e)
		{
			path->like = G2_GL_PATH_LIKE_CONX;
			tb_trace_impl("like: convex");
		}
	}
}
tb_bool_t g2_gl_path_make_fill(g2_gl_path_t* path)
{
	// check
	tb_assert_and_check_return_val(path, TB_FALSE);

	// already been maked?
	tb_check_return_val(!path->fill.size || !tb_vector_size(path->fill.size), TB_TRUE);

	// has data?
	tb_check_return_val(tb_vector_size(path->code) && tb_vector_size(path->data), TB_FALSE);

	// only moveto?
	tb_check_return_val(path->flag & (G2_GL_PATH_FLAG_LINE | G2_GL_PATH_FLAG_QUAD | G2_GL_PATH_FLAG_CUBE), TB_FALSE);

	// bounds
	path->fill.rect = path->rect;

	// only has lineto?
	if (!(path->flag & (G2_GL_PATH_FLAG_QUAD | G2_GL_PATH_FLAG_CUBE)))
	{
		// check
		tb_check_return_val(path->rect.x1 < path->rect.x2 && path->rect.y1 < path->rect.y2, TB_FALSE);

		// use the raw data directly
		if (path->fill.data != path->data) tb_vector_exit(path->fill.data);
		if (path->fill.size != path->size) tb_vector_exit(path->fill.size);
		path->fill.data = path->data;
		path->fill.size = path->size;
		return TB_TRUE;
	}
	else 
	{
		// detach the previous reference
		if (path->fill.data == path->data) path->fill.data = TB_NULL;
		if (path->fill.size == path->size) path->fill.size = TB_NULL;
	}

	// init itor
	tb_byte_t const* 	code = tb_vector_data(path->code);
	tb_float_t const* 	data = tb_vector_data(path->data);
	tb_byte_t const* 	cail = code + tb_vector_size(path->code);
	tb_float_t const* 	dail = data + (tb_vector_size(path->data) << 1);
	tb_float_t const* 	head = TB_NULL;
	tb_float_t const* 	last = TB_NULL;
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

	// init splitter
	g2_soft_split_quad_t quad;
	g2_soft_split_cube_t cube;
	g2_soft_split_quad_init(&quad, g2_gl_path_fill_split_quad_func, path);
	g2_soft_split_cube_init(&cube, g2_gl_path_fill_split_cube_func, path);

	// walk
	for (; code < cail && data < dail; code++)
	{
		// done
		switch (*code)
		{
		case G2_PATH_CODE_MOVE:
			{
				// head
				head = data;

				// move
				tb_trace_impl("move: %f %f", data[0], data[1]);
				tb_vector_insert_tail(path->fill.data, data);
				tb_vector_insert_tail(path->fill.size, 1);

				// last
				last = data;

				// next
				data += 2;
			}
			break;
		case G2_PATH_CODE_LINE:
			{
				// line
				tb_trace_impl("line: %f %f", data[0], data[1]);
				tb_vector_insert_tail(path->fill.data, data);
				tb_vector_replace_last(path->fill.size, tb_vector_last(path->fill.size) + 1);

				// last
				last = data;

				// next
				data += 2;
			}
			break;
		case G2_PATH_CODE_QUAD:
			{
				// quad
				tb_trace_impl("quad: %f %f %f %f", data[0], data[1], data[2], data[3]);

				// split
				tb_assert(last);
				g2_point_t pb, cp, pe;
				pb.x = last? tb_float_to_g2(last[0]) : 0;
				pb.y = last? tb_float_to_g2(last[1]) : 0;
				cp.x = tb_float_to_g2(data[0]);
				cp.y = tb_float_to_g2(data[1]);
				pe.x = tb_float_to_g2(data[2]);
				pe.y = tb_float_to_g2(data[3]);
				g2_soft_split_quad_done(&quad, &pb, &cp, &pe);

				// last
				last = &data[2];

				// next
				data += 4;
			}
			break;
		case G2_PATH_CODE_CUBE:
			{
				// cube
				tb_trace_impl("cube: %f %f %f %f %f %f", data[0], data[1], data[2], data[3], data[4], data[5]);

				// split
				tb_assert(last);
				g2_point_t pb, cpb, cpe, pe;
				pb.x = last? tb_float_to_g2(last[0]) : 0;
				pb.y = last? tb_float_to_g2(last[1]) : 0;
				cpb.x = tb_float_to_g2(data[0]);
				cpb.y = tb_float_to_g2(data[1]);
				cpe.x = tb_float_to_g2(data[2]);
				cpe.y = tb_float_to_g2(data[3]);
				pe.x = tb_float_to_g2(data[4]);
				pe.y = tb_float_to_g2(data[5]);
				g2_soft_split_cube_done(&cube, &pb, &cpb, &cpe, &pe);

				// last
				last = &data[4];

				// next
				data += 6;
			}
			break;
		case G2_PATH_CODE_CLOS:
			{
				// close
				tb_trace_impl("close");

				// close it
				if (head)
				{
					tb_vector_insert_tail(path->fill.data, head);
					tb_vector_replace_last(path->fill.size, tb_vector_last(path->fill.size) + 1);
				}

				// last
				last = head;
			}
			break;
		default:
			break;
		}
	}

	// bounds
	tb_trace_impl("rect: %f %f %f %f", path->fill.rect.x1, path->fill.rect.y1, path->fill.rect.x2, path->fill.rect.y2);

	// ok
	return TB_TRUE;
}
tb_bool_t g2_gl_path_make_stok(g2_gl_path_t* path)
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
	g2_gl_path_t* path = tb_malloc0(sizeof(g2_gl_path_t));
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
	path->flag = G2_GL_PATH_FLAG_NONE;

	// init like
	path->like = G2_GL_PATH_LIKE_NONE;

	// ok
	return path;

fail:
	if (path) g2_path_exit(path);
	return TB_NULL;
}
tb_void_t g2_path_exit(tb_handle_t path)
{
	g2_gl_path_t* gpath = (g2_gl_path_t*)path;
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
	g2_gl_path_t* gpath = (g2_gl_path_t*)path;
	tb_assert_and_check_return(gpath);

	// clear flag
	gpath->flag = G2_GL_PATH_FLAG_NONE;

	// clear like
	gpath->like = G2_GL_PATH_LIKE_NONE;

	// clear code
	if (gpath->code) tb_vector_clear(gpath->code);

	// clear data
	if (gpath->data) tb_vector_clear(gpath->data);

	// clear size
	if (gpath->size) tb_vector_clear(gpath->size);

	// clear rect
	tb_memset(&gpath->rect, 0, sizeof(g2_gl_rect_t));

	// clear fill 
	g2_gl_path_fill_clear(gpath);
}
tb_void_t g2_path_close(tb_handle_t path)
{
	g2_gl_path_t* gpath = (g2_gl_path_t*)path;
	tb_assert_and_check_return(gpath && gpath->code);

	// close it, no double closed
	if (!tb_vector_size(gpath->code) || (tb_byte_t)tb_vector_last(gpath->code) != G2_PATH_CODE_CLOS) 
		tb_vector_insert_tail(gpath->code, G2_PATH_CODE_CLOS);

	// close it
	gpath->flag &= ~G2_GL_PATH_FLAG_OPEN;

	// clear like
	gpath->like = G2_GL_PATH_LIKE_NONE;

	// clear fill
	g2_gl_path_fill_clear(gpath);
}
tb_bool_t g2_path_null(tb_handle_t path)
{
	g2_gl_path_t* gpath = (g2_gl_path_t*)path;
	tb_assert_and_check_return_val(gpath && gpath->data, TB_TRUE);

	return tb_vector_size(gpath->data)? TB_FALSE : TB_TRUE;
}
tb_bool_t g2_path_itor_init(tb_handle_t path)
{
	g2_gl_path_t* gpath = (g2_gl_path_t*)path;
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
	g2_gl_path_t* gpath = (g2_gl_path_t*)path;
	tb_assert_and_check_return_val(gpath && gpath->code && gpath->data && pt, G2_PATH_CODE_NONE);

	// tail?
	tb_check_return_val(gpath->itor.code != tb_iterator_tail(gpath->code), G2_PATH_CODE_NONE);

	// code
	tb_size_t code = (tb_size_t)tb_iterator_item(gpath->code, gpath->itor.code);

	// step
	tb_size_t step = g2_gl_path_code_step(code);

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
	g2_gl_path_t* gpath = (g2_gl_path_t*)path;
	tb_assert_and_check_return(gpath);

	gpath->itor.code = tb_iterator_tail(gpath->code);
	gpath->itor.data = tb_iterator_tail(gpath->data);
}
tb_bool_t g2_path_last_pt(tb_handle_t path, g2_point_t* pt)
{
	g2_gl_path_t* gpath = (g2_gl_path_t*)path;
	tb_assert_and_check_return_val(gpath && gpath->data && pt, TB_FALSE);

	// last
	tb_float_t const* last = tb_vector_last(gpath->data);
	if (last) 
	{
		pt->x = tb_float_to_g2(last[0]);
		pt->y = tb_float_to_g2(last[1]);
	}

	// ok?
	return last? TB_TRUE : TB_FALSE;
}
tb_void_t g2_path_move_to(tb_handle_t path, g2_point_t const* pt)
{
	g2_gl_path_t* gpath = (g2_gl_path_t*)path;
	tb_assert_and_check_return(gpath && gpath->code && gpath->data && gpath->size && pt);

	// data
	tb_float_t data[2];
	data[0] = g2_float_to_tb(pt->x);
	data[1] = g2_float_to_tb(pt->y);

	// bounds
	if (!tb_vector_size(gpath->code)) g2_gl_rect_init(&gpath->rect, data[0], data[1]);
	else g2_gl_rect_done(&gpath->rect, data[0], data[1]);

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
	gpath->flag |= G2_GL_PATH_FLAG_OPEN | G2_GL_PATH_FLAG_MOVE;

	// clear like
	gpath->like = G2_GL_PATH_LIKE_NONE;

	// clear fill
	g2_gl_path_fill_clear(gpath);
}
tb_void_t g2_path_line_to(tb_handle_t path, g2_point_t const* pt)
{
	g2_gl_path_t* gpath = (g2_gl_path_t*)path;
	tb_assert_and_check_return(gpath && gpath->code && gpath->data && gpath->size && pt);

	// data
	tb_float_t data[2];
	data[0] = g2_float_to_tb(pt->x);
	data[1] = g2_float_to_tb(pt->y);

	// bounds
	g2_gl_rect_done(&gpath->rect, data[0], data[1]);

	// patch move-to
	if (!(gpath->flag & G2_GL_PATH_FLAG_OPEN)) 
	{
		// the last
		tb_float_t 			null[2] = {0};
		tb_float_t const* 	last = TB_NULL;
		if (tb_vector_size(gpath->data)) last = tb_vector_last(gpath->data);

		// move to the last
		g2_path_move_to(path, last? last : null);
	}

	// line to
	gpath->flag |= G2_GL_PATH_FLAG_LINE;
	tb_vector_insert_tail(gpath->code, G2_PATH_CODE_LINE);
	tb_vector_insert_tail(gpath->data, data);
	tb_vector_replace_last(gpath->size, tb_vector_last(gpath->size) + 1);

	// clear like
	gpath->like = G2_GL_PATH_LIKE_NONE;

	// clear fill
	g2_gl_path_fill_clear(gpath);
}
tb_void_t g2_path_quad_to(tb_handle_t path, g2_point_t const* cp, g2_point_t const* pt)
{
	g2_gl_path_t* gpath = (g2_gl_path_t*)path;
	tb_assert_and_check_return(gpath && gpath->code && gpath->data && gpath->size && cp && pt);

	// data
	tb_float_t data[4];
	data[0] = g2_float_to_tb(cp->x);
	data[1] = g2_float_to_tb(cp->y);
	data[2] = g2_float_to_tb(pt->x);
	data[3] = g2_float_to_tb(pt->y);

	// bounds
	g2_gl_rect_done(&gpath->rect, data[0], data[1]);
	g2_gl_rect_done(&gpath->rect, data[2], data[3]);

	// patch move-to
	if (!(gpath->flag & G2_GL_PATH_FLAG_OPEN)) 
	{
		// the last
		tb_float_t 			null[2] = {0};
		tb_float_t const* 	last = TB_NULL;
		if (tb_vector_size(gpath->data)) last = tb_vector_last(gpath->data);

		// move to the last
		g2_path_move_to(path, last? last : null);
	}

	// quad to
	gpath->flag |= G2_GL_PATH_FLAG_QUAD;
	tb_vector_insert_tail(gpath->code, G2_PATH_CODE_QUAD);
	tb_vector_insert_tail(gpath->data, &data[0]);
	tb_vector_insert_tail(gpath->data, &data[2]);
	tb_vector_replace_last(gpath->size, tb_vector_last(gpath->size) + 1);

	// clear like
	gpath->like = G2_GL_PATH_LIKE_NONE;

	// clear fill
	g2_gl_path_fill_clear(gpath);
}
tb_void_t g2_path_cube_to(tb_handle_t path, g2_point_t const* c0, g2_point_t const* c1, g2_point_t const* pt)
{
	g2_gl_path_t* gpath = (g2_gl_path_t*)path;
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
	g2_gl_rect_done(&gpath->rect, data[0], data[1]);
	g2_gl_rect_done(&gpath->rect, data[2], data[3]);
	g2_gl_rect_done(&gpath->rect, data[4], data[5]);

	// patch move-to
	if (!(gpath->flag & G2_GL_PATH_FLAG_OPEN)) 
	{
		// the last
		tb_float_t 			null[2] = {0};
		tb_float_t const* 	last = TB_NULL;
		if (tb_vector_size(gpath->data)) last = tb_vector_last(gpath->data);

		// move to the last
		g2_path_move_to(path, last? last : null);
	}

	// cube to
	gpath->flag |= G2_GL_PATH_FLAG_CUBE;
	tb_vector_insert_tail(gpath->code, G2_PATH_CODE_CUBE);
	tb_vector_insert_tail(gpath->data, &data[0]);
	tb_vector_insert_tail(gpath->data, &data[2]);
	tb_vector_insert_tail(gpath->data, &data[4]);
	tb_vector_replace_last(gpath->size, tb_vector_last(gpath->size) + 1);

	// clear like
	gpath->like = G2_GL_PATH_LIKE_NONE;

	// clear fill
	g2_gl_path_fill_clear(gpath);
}
tb_void_t g2_path_arc_to(tb_handle_t path, g2_arc_t const* arc)
{
	tb_trace_noimpl();
}
tb_void_t g2_path_add_path(tb_handle_t path, tb_handle_t path2)
{
	tb_assert_and_check_return(path && path2);

	// path
	if (g2_path_itor_init(path))
	{
		// walk
		g2_point_t 	pt[3];
		tb_size_t 	co = G2_PATH_CODE_NONE;
		while (co = g2_path_itor_next(path, pt))
		{
			switch (co)
			{
			case G2_PATH_CODE_MOVE:
				g2_path_move_to(path2, &pt[0]);
				break;
			case G2_PATH_CODE_LINE:
				g2_path_line_to(path2, &pt[0]);
				break;
			case G2_PATH_CODE_QUAD:
				g2_path_quad_to(path2, &pt[0], &pt[1]);
				break;
			case G2_PATH_CODE_CUBE:
				g2_path_cube_to(path2, &pt[0], &pt[1], &pt[2]);
				break;
			case G2_PATH_CODE_CLOS:
				g2_path_close(path2);
				break;
			default:
				break;
			}
		}
		g2_path_itor_exit(path);
	}
}
tb_void_t g2_path_add_line(tb_handle_t path, g2_line_t const* line)
{
	tb_assert_and_check_return(path && line);
	
	g2_path_move_to(path, &line->p0);
	g2_path_line_to(path, &line->p1);
}
tb_void_t g2_path_add_arc(tb_handle_t path, g2_arc_t const* arc)
{
	tb_trace_noimpl();
}
tb_void_t g2_path_add_triangle(tb_handle_t path, g2_triangle_t const* triangle)
{
	tb_assert_and_check_return(path && triangle);
	
	g2_path_move_to(path, &triangle->p0);
	g2_path_line_to(path, &triangle->p1);
	g2_path_line_to(path, &triangle->p2);
	g2_path_close(path);
}
tb_void_t g2_path_add_rect(tb_handle_t path, g2_rect_t const* rect)
{
	tb_assert_and_check_return(path && rect);
	
	g2_path_move2_to(path, rect->x, rect->y);
	g2_path_line2_to(path, rect->x + rect->w - G2_ONE, rect->y);
	g2_path_line2_to(path, rect->x + rect->w - G2_ONE, rect->y + rect->h - G2_ONE);
	g2_path_line2_to(path, rect->x, rect->y + rect->h - G2_ONE);
	g2_path_close(path);
}
tb_void_t g2_path_add_circle(tb_handle_t path, g2_circle_t const* circle)
{
	g2_gl_path_t* gpath = (g2_gl_path_t*)path;
	tb_assert_and_check_return(path && circle);

	// init
	tb_handle_t data[2] = {path, path};

	// split
	g2_soft_split_circle_t split;
	g2_soft_split_circle_init(&split, g2_gl_path_add_split_circle_func, data);
	g2_soft_split_circle_done(&split, circle);

	// close
	g2_path_close(path);

	// like: convex
	if (!g2_path_null(path)) gpath->like = G2_GL_PATH_LIKE_CONX;
}
tb_void_t g2_path_add_ellipse(tb_handle_t path, g2_ellipse_t const* ellipse)
{
	g2_gl_path_t* gpath = (g2_gl_path_t*)path;
	tb_assert_and_check_return(path && ellipse);

	// init
	tb_handle_t data[2] = {path, path};

	// split
	g2_soft_split_ellipse_t split;
	g2_soft_split_ellipse_init(&split, g2_gl_path_add_split_ellipse_func, data);
	g2_soft_split_ellipse_done(&split, ellipse);

	// close
	g2_path_close(path);
	
	// like: convex
	if (!g2_path_null(path)) gpath->like = G2_GL_PATH_LIKE_CONX;
}
