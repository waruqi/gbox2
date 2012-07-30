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
//#define TB_TRACE_IMPL_TAG 		"svg"

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "element.h"
#include "parser/parser.h"
#include "writer/writer.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static tb_void_t g2_svg_element_path_writ(g2_svg_element_t const* element, tb_gstream_t* gst)
{
	g2_svg_element_path_t const* path = (g2_svg_element_path_t const*)element;
	tb_assert_and_check_return(path);

	// id
	if (tb_pstring_size(&path->base.id))
		tb_gstream_printf(gst, " id=\"%s\"", tb_pstring_cstr(&path->base.id));

	// path
	if (path->path && g2_path_itor_init(path->path))
	{
		// init d
		tb_gstream_printf(gst, " d=\"");

		// walk
		g2_point_t 	pt[4];
		tb_size_t 	co = G2_PATH_CODE_NONE;
		while (co = g2_path_itor_next(path->path, pt))
		{
			switch (co)
			{
			case G2_PATH_CODE_MOVE:
				tb_gstream_printf(gst, "M %f,%f ", g2_float_to_tb(pt[0].x), g2_float_to_tb(pt[0].y));
				break;
			case G2_PATH_CODE_LINE:
				tb_gstream_printf(gst, "L %f,%f ", g2_float_to_tb(pt[1].x), g2_float_to_tb(pt[1].y));
				break;
			case G2_PATH_CODE_QUAD:
				tb_gstream_printf(gst, "Q %f,%f %f,%f ", g2_float_to_tb(pt[1].x), g2_float_to_tb(pt[1].y), g2_float_to_tb(pt[2].x), g2_float_to_tb(pt[2].y));
				break;
			case G2_PATH_CODE_CUBIC:
				tb_gstream_printf(gst, "C %f,%f %f,%f %f,%f ", g2_float_to_tb(pt[1].x), g2_float_to_tb(pt[1].y), g2_float_to_tb(pt[2].x), g2_float_to_tb(pt[2].y), g2_float_to_tb(pt[3].x), g2_float_to_tb(pt[3].y));
				break;
			case G2_PATH_CODE_CLOSE:
				tb_gstream_printf(gst, "Z");
				break;
			}
		}
		g2_path_itor_exit(path->path);

		// exit d
		tb_gstream_printf(gst, "\"");
	}

	// style 
	g2_svg_writer_style(gst, &path->style); 

	// transform 
	g2_svg_writer_transform(gst, &path->matrix); 

	// exit
	g2_path_itor_exit(path->path);
}
static tb_void_t g2_svg_element_path_exit(g2_svg_element_t* element)
{
	g2_svg_element_path_t* path = (g2_svg_element_path_t*)element;
	if (path)
	{
		// exit style
		g2_svg_style_exit(&path->style);
		
		// exit path
		if (path->path) g2_path_exit(path->path);
		path->path = TB_NULL;
	}
}
static tb_char_t const* g2_svg_element_path_d_xoy(g2_svg_element_path_t* element, tb_char_t const* data)
{
	// init 
	tb_char_t const* p = data;

	// mode
	tb_char_t mode = *p++;

	// xoy
	g2_float_t xoy = 0; p = g2_svg_parser_float(p, &xoy); p = g2_svg_parser_separator_skip(p);

	// trace
	tb_trace_impl("path: d: %c: %f", mode, g2_float_to_tb(xoy));

	// done path
	if (element->path)
	{
		// last point
		g2_point_t pt = {0};
		g2_path_last_pt(element->path, &pt);

		// done
		switch (mode)
		{
			case 'H':
				g2_path_line2_to(element->path, xoy, pt.y);
				break;
			case 'h':
				g2_path_line2_to(element->path, pt.x + xoy, pt.y);
				break;
			case 'V':
				g2_path_line2_to(element->path, pt.x, xoy);
				break;
			case 'v':
				g2_path_line2_to(element->path, pt.x, pt.y + xoy);
				break;
			default:
				tb_trace_noimpl();
				break;
		}
	}

	// ok
	return p;
}
static tb_char_t const* g2_svg_element_path_d_xy1(g2_svg_element_path_t* element, tb_char_t const* data)
{
	// init 
	tb_char_t const* p = data;

	// mode
	tb_char_t mode = *p++;

	// x1
	g2_float_t x1 = 0; p = g2_svg_parser_float(p, &x1); p = g2_svg_parser_separator_skip(p);

	// y1
	g2_float_t y1 = 0; p = g2_svg_parser_float(p, &y1); p = g2_svg_parser_separator_skip(p);

	// trace
	tb_trace_impl("path: d: %c: %f, %f", mode, g2_float_to_tb(x1), g2_float_to_tb(y1));

	// init path
	if (!element->path) element->path = g2_path_init();

	// done path
	if (element->path)
	{
		// last point
		g2_point_t pt = {0};
		g2_path_last_pt(element->path, &pt);

		// done
		switch (mode)
		{
			case 'M':
				g2_path_move2_to(element->path, x1, y1);
				break;
			case 'm':
				g2_path_move2_to(element->path, pt.x + x1, pt.y + y1);
				break;
			case 'L':
				g2_path_line2_to(element->path, x1, y1);
				break;
			case 'l':
				g2_path_line2_to(element->path, pt.x + x1, pt.y + y1);
				break;
			default:
				tb_trace_noimpl();
				break;
		}
	}

	// ok
	return p;
}
static tb_char_t const* g2_svg_element_path_d_xy2(g2_svg_element_path_t* element, tb_char_t const* data)
{
	// init 
	tb_char_t const* p = data;

	// mode
	tb_char_t mode = *p++;

	// x1
	g2_float_t x1 = 0; p = g2_svg_parser_float(p, &x1); p = g2_svg_parser_separator_skip(p);

	// y1
	g2_float_t y1 = 0; p = g2_svg_parser_float(p, &y1); p = g2_svg_parser_separator_skip(p);

	// x2
	g2_float_t x2 = 0; p = g2_svg_parser_float(p, &x2); p = g2_svg_parser_separator_skip(p);

	// y2
	g2_float_t y2 = 0; p = g2_svg_parser_float(p, &y2); p = g2_svg_parser_separator_skip(p);

	// trace
	tb_trace_impl("path: d: %c: %f, %f, %f, %f", mode, g2_float_to_tb(x1), g2_float_to_tb(y1), g2_float_to_tb(x2), g2_float_to_tb(y2));

	// init path
	if (!element->path) element->path = g2_path_init();

	// done path
	if (element->path)
	{
		// last point
		g2_point_t pt = {0};
		g2_path_last_pt(element->path, &pt);

		// done
		switch (mode)
		{
			case 'Q':
				g2_path_quad2_to(element->path, x2, y2, x1, y1);
				break;
			case 'q':
				g2_path_quad2_to(element->path, pt.x + x2, pt.y + y2, pt.x + x1, pt.y + y1);
				break;
			default:
				tb_trace_noimpl();
				break;
		}
	}

	// ok
	return p;
}
static tb_char_t const* g2_svg_element_path_d_xy3(g2_svg_element_path_t* element, tb_char_t const* data)
{
	// init 
	tb_char_t const* p = data;

	// mode
	tb_char_t mode = *p++;

	// x1
	g2_float_t x1 = 0; p = g2_svg_parser_float(p, &x1); p = g2_svg_parser_separator_skip(p);

	// y1
	g2_float_t y1 = 0; p = g2_svg_parser_float(p, &y1); p = g2_svg_parser_separator_skip(p);

	// x2
	g2_float_t x2 = 0; p = g2_svg_parser_float(p, &x2); p = g2_svg_parser_separator_skip(p);

	// y2
	g2_float_t y2 = 0; p = g2_svg_parser_float(p, &y2); p = g2_svg_parser_separator_skip(p);

	// x3
	g2_float_t x3 = 0; p = g2_svg_parser_float(p, &x3); p = g2_svg_parser_separator_skip(p);

	// y3
	g2_float_t y3 = 0; p = g2_svg_parser_float(p, &y3); p = g2_svg_parser_separator_skip(p);

	// trace
	tb_trace_impl("path: d: %c: %f, %f, %f, %f, %f, %f", mode, g2_float_to_tb(x1), g2_float_to_tb(y1), g2_float_to_tb(x2), g2_float_to_tb(y2), g2_float_to_tb(x3), g2_float_to_tb(y3));

	// init path
	if (!element->path) element->path = g2_path_init();

	// done path
	if (element->path)
	{
		// last point
		g2_point_t pt = {0};
		g2_path_last_pt(element->path, &pt);

		// done
		switch (mode)
		{
			case 'C':
				g2_path_cube2_to(element->path, x3, y3, x1, y1, x2, y2);
				break;
			case 'c':
				g2_path_cube2_to(element->path, pt.x + x3, pt.y + y3, pt.x + x1, pt.y + y1, pt.x + x2, pt.y + y2);
				break;
			default:
				tb_trace_noimpl();
				break;
		}
	}

	// ok
	return p;
}
static tb_char_t const* g2_svg_element_path_d_a(g2_svg_element_path_t* element, tb_char_t const* data)
{
	// init 
	tb_char_t const* p = data;

	// mode
	tb_char_t mode = *p++;

	// rx
	g2_float_t rx = 0; p = g2_svg_parser_float(p, &rx); p = g2_svg_parser_separator_skip(p);

	// ry
	g2_float_t ry = 0; p = g2_svg_parser_float(p, &ry); p = g2_svg_parser_separator_skip(p);

	// x-axis-rotation
	g2_float_t xr = 0; p = g2_svg_parser_float(p, &xr); p = g2_svg_parser_separator_skip(p);

	// large-arc-flag
	g2_float_t af = 0; p = g2_svg_parser_float(p, &af); p = g2_svg_parser_separator_skip(p);

	// sweep-flag
	g2_float_t sf = 0; p = g2_svg_parser_float(p, &sf); p = g2_svg_parser_separator_skip(p);

	// x
	g2_float_t x = 0; p = g2_svg_parser_float(p, &x); p = g2_svg_parser_separator_skip(p);

	// y
	g2_float_t y = 0; p = g2_svg_parser_float(p, &y); p = g2_svg_parser_separator_skip(p);

	// trace
	tb_trace_impl("path: a: %c: %f, %f, %f, %f, %f, %f, %f", mode, g2_float_to_tb(rx), g2_float_to_tb(ry), g2_float_to_tb(xr), g2_float_to_tb(af), g2_float_to_tb(sf), g2_float_to_tb(x), g2_float_to_tb(y));

	// no impl
	tb_trace_noimpl();

	// ok
	return p;
}
static tb_char_t const* g2_svg_element_path_d_z(g2_svg_element_path_t* element, tb_char_t const* data)
{
	// trace
	tb_trace_impl("path: d: z");

	// close path
	if (element->path) g2_path_close(element->path);

	// ok
	return data + 1;
}
static tb_void_t g2_svg_element_path_d(g2_svg_element_path_t* element, tb_char_t const* data)
{
	// init
	tb_char_t const* p = data;
	tb_assert_and_check_return(p);

	// trace
	tb_trace_impl("path: d");
	while (*p)
	{
		switch (*p)
		{
		case 'M':
		case 'm':
		case 'L':
		case 'l':
		case 'T':
		case 't':
			p = g2_svg_element_path_d_xy1(element, p);
			break;
		case 'H':
		case 'h':
		case 'V':
		case 'v':
			p = g2_svg_element_path_d_xoy(element, p);
			break;
		case 'S':
		case 's':
		case 'Q':
		case 'q':
			p = g2_svg_element_path_d_xy2(element, p);
			break;
		case 'C':
		case 'c':
			p = g2_svg_element_path_d_xy3(element, p);
			break;
		case 'A':
		case 'a':
			p = g2_svg_element_path_d_a(element, p);
			break;
		case 'Z':
		case 'z':
			p = g2_svg_element_path_d_z(element, p);
			break;
		default:
			p++;
			break;
		}
	}
}

/* ///////////////////////////////////////////////////////////////////////
 * initializer
 */
g2_svg_element_t* g2_svg_element_init_path(tb_handle_t reader)
{
	// alloc 
	g2_svg_element_path_t* element = tb_malloc0(sizeof(g2_svg_element_path_t));
	tb_assert_and_check_return_val(element, TB_NULL);

	// init
	element->base.exit = g2_svg_element_path_exit;
	element->base.writ = g2_svg_element_path_writ;

	// init style
	g2_svg_style_init(&element->style);

	// init matrix
	g2_matrix_clear(&element->matrix);

	// attributes
	tb_xml_node_t const* attr = tb_xml_reader_attributes(reader);
	for (; attr; attr = attr->next)
	{
		tb_char_t const* p = tb_pstring_cstr(&attr->data);
		if (!tb_pstring_cstricmp(&attr->name, "id"))
			tb_pstring_strcpy(&element->base.id, &attr->data);
		else if (!tb_pstring_cstricmp(&attr->name, "d"))
			g2_svg_element_path_d(element, p);
		else if (!tb_pstring_cstricmp(&attr->name, "fill"))
			g2_svg_parser_style_fill(p, &element->style);
		else if (!tb_pstring_cstricmp(&attr->name, "stroke"))
			g2_svg_parser_style_stroke(p, &element->style);
		else if (!tb_pstring_cstricmp(&attr->name, "stroke-width"))
			g2_svg_parser_style_stroke_width(p, &element->style);
		else if (!tb_pstring_cstricmp(&attr->name, "stroke-linecap"))
			g2_svg_parser_style_stroke_linecap(p, &element->style);
		else if (!tb_pstring_cstricmp(&attr->name, "stroke-linejoin"))
			g2_svg_parser_style_stroke_linejoin(p, &element->style);
		else if (!tb_pstring_cstricmp(&attr->name, "style"))
			g2_svg_parser_style(p, &element->style);
		else if (!tb_pstring_cstricmp(&attr->name, "transform"))
			g2_svg_parser_transform(p, &element->matrix);
	}

	// ok
	return element;
}

