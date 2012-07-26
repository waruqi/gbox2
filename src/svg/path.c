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
#define TB_TRACE_IMPL_TAG 		"svg"

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "element.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
#ifdef G2_DEBUG
static tb_void_t g2_svg_element_path_dump(g2_svg_element_t const* element, tb_pstring_t* attr)
{
	g2_svg_element_path_t const* path = (g2_svg_element_path_t const*)element;
	tb_assert_and_check_return(path);

	// clear
	tb_pstring_clear(attr);
}
#endif
static tb_char_t const* g2_svg_element_path_d_xoy(g2_svg_element_path_t const* element, tb_char_t const* data)
{
	// init 
	tb_char_t const* p = data;

	// mode
	tb_char_t mode = *p++;

	// xoy
	g2_float_t xoy = tb_float_to_g2(tb_stof(p));
	p = g2_svg_skip_float(p); p = g2_svg_skip_separator(p);

	// trace
	tb_trace_impl("path: d: %c: %f", mode, g2_float_to_tb(xoy));

	// ok
	return p;
}
static tb_char_t const* g2_svg_element_path_d_xy1(g2_svg_element_path_t const* element, tb_char_t const* data)
{
	// init 
	tb_char_t const* p = data;

	// mode
	tb_char_t mode = *p++;

	// x1
	g2_float_t x1 = tb_float_to_g2(tb_stof(p));
	p = g2_svg_skip_float(p); p = g2_svg_skip_separator(p);

	// y1
	g2_float_t y1 = tb_float_to_g2(tb_stof(p));
	p = g2_svg_skip_float(p); p = g2_svg_skip_separator(p);

	// trace
	tb_trace_impl("path: d: %c: %f, %f", mode, g2_float_to_tb(x1), g2_float_to_tb(y1));

	// ok
	return p;
}
static tb_char_t const* g2_svg_element_path_d_xy2(g2_svg_element_path_t const* element, tb_char_t const* data)
{
	// init 
	tb_char_t const* p = data;

	// mode
	tb_char_t mode = *p++;

	// x1
	g2_float_t x1 = tb_float_to_g2(tb_stof(p));
	p = g2_svg_skip_float(p); p = g2_svg_skip_separator(p);

	// y1
	g2_float_t y1 = tb_float_to_g2(tb_stof(p));
	p = g2_svg_skip_float(p); p = g2_svg_skip_separator(p);

	// x2
	g2_float_t x2 = tb_float_to_g2(tb_stof(p));
	p = g2_svg_skip_float(p); p = g2_svg_skip_separator(p);

	// y2
	g2_float_t y2 = tb_float_to_g2(tb_stof(p));
	p = g2_svg_skip_float(p); p = g2_svg_skip_separator(p);

	// trace
	tb_trace_impl("path: d: %c: %f, %f, %f, %f", mode, g2_float_to_tb(x1), g2_float_to_tb(y1), g2_float_to_tb(x2), g2_float_to_tb(y2));

	// ok
	return p;
}
static tb_char_t const* g2_svg_element_path_d_xy3(g2_svg_element_path_t const* element, tb_char_t const* data)
{
	// init 
	tb_char_t const* p = data;

	// mode
	tb_char_t mode = *p++;

	// x1
	g2_float_t x1 = tb_float_to_g2(tb_stof(p));
	p = g2_svg_skip_float(p); p = g2_svg_skip_separator(p);

	// y1
	g2_float_t y1 = tb_float_to_g2(tb_stof(p));
	p = g2_svg_skip_float(p); p = g2_svg_skip_separator(p);

	// x2
	g2_float_t x2 = tb_float_to_g2(tb_stof(p));
	p = g2_svg_skip_float(p); p = g2_svg_skip_separator(p);

	// y2
	g2_float_t y2 = tb_float_to_g2(tb_stof(p));
	p = g2_svg_skip_float(p); p = g2_svg_skip_separator(p);

	// x3
	g2_float_t x3 = tb_float_to_g2(tb_stof(p));
	p = g2_svg_skip_float(p); p = g2_svg_skip_separator(p);

	// y3
	g2_float_t y3 = tb_float_to_g2(tb_stof(p));
	p = g2_svg_skip_float(p); p = g2_svg_skip_separator(p);

	// trace
	tb_trace_impl("path: d: %c: %f, %f, %f, %f, %f, %f", mode, g2_float_to_tb(x1), g2_float_to_tb(y1), g2_float_to_tb(x2), g2_float_to_tb(y2), g2_float_to_tb(x3), g2_float_to_tb(y3));

	// ok
	return p;
}
static tb_char_t const* g2_svg_element_path_d_a(g2_svg_element_path_t const* element, tb_char_t const* data)
{
	// init 
	tb_char_t const* p = data;

	// mode
	tb_char_t mode = *p++;

	// rx
	g2_float_t rx = tb_float_to_g2(tb_stof(p));
	p = g2_svg_skip_float(p); p = g2_svg_skip_separator(p);

	// ry
	g2_float_t ry = tb_float_to_g2(tb_stof(p));
	p = g2_svg_skip_float(p); p = g2_svg_skip_separator(p);

	// x-axis-rotation
	g2_float_t xr = tb_float_to_g2(tb_stof(p));
	p = g2_svg_skip_float(p); p = g2_svg_skip_separator(p);

	// large-arc-flag
	g2_float_t af = tb_float_to_g2(tb_stof(p));
	p = g2_svg_skip_float(p); p = g2_svg_skip_separator(p);

	// sweep-flag
	g2_float_t sf = tb_float_to_g2(tb_stof(p));
	p = g2_svg_skip_float(p); p = g2_svg_skip_separator(p);

	// x
	g2_float_t x = tb_float_to_g2(tb_stof(p));
	p = g2_svg_skip_float(p); p = g2_svg_skip_separator(p);

	// y
	g2_float_t y = tb_float_to_g2(tb_stof(p));
	p = g2_svg_skip_float(p); p = g2_svg_skip_separator(p);

	// trace
	tb_trace_impl("path: a: %c: %f, %f, %f, %f, %f, %f, %f", mode, g2_float_to_tb(rx), g2_float_to_tb(ry), g2_float_to_tb(xr), g2_float_to_tb(af), g2_float_to_tb(sf), g2_float_to_tb(x), g2_float_to_tb(y));

	// ok
	return p;
}
static tb_char_t const* g2_svg_element_path_d_z(g2_svg_element_path_t const* element, tb_char_t const* data)
{
	// trace
	tb_trace_impl("path: d: z");

	// ok
	return data + 1;
}
static tb_void_t g2_svg_element_path_d(g2_svg_element_path_t const* element, tb_char_t const* data)
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
#ifdef G2_DEBUG
	element->base.dump = g2_svg_element_path_dump;
#endif

	// attributes
	tb_xml_node_t const* attr = tb_xml_reader_attributes(reader);
	for (; attr; attr = attr->next)
	{
		if (!tb_pstring_cstricmp(&attr->name, "p"))
			g2_svg_element_path_d(element, tb_pstring_cstr(&attr->data));
	}

	// ok
	return element;
}

