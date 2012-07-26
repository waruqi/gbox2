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
static tb_char_t const* g2_svg_element_path_d_m(g2_svg_element_path_t const* element, tb_char_t const* data)
{
	tb_trace_noimpl();
	return data + 1;
}
static tb_char_t const* g2_svg_element_path_d_l(g2_svg_element_path_t const* element, tb_char_t const* data)
{
	tb_trace_noimpl();
	return data + 1;
}
static tb_char_t const* g2_svg_element_path_d_c(g2_svg_element_path_t const* element, tb_char_t const* data)
{
	tb_trace_noimpl();
	return data + 1;
}
static tb_char_t const* g2_svg_element_path_d_h(g2_svg_element_path_t const* element, tb_char_t const* data)
{
	tb_trace_noimpl();
	return data + 1;
}
static tb_char_t const* g2_svg_element_path_d_v(g2_svg_element_path_t const* element, tb_char_t const* data)
{
	tb_trace_noimpl();
	return data + 1;
}
static tb_char_t const* g2_svg_element_path_d_s(g2_svg_element_path_t const* element, tb_char_t const* data)
{
	tb_trace_noimpl();
	return data + 1;
}
static tb_char_t const* g2_svg_element_path_d_q(g2_svg_element_path_t const* element, tb_char_t const* data)
{
	tb_trace_noimpl();
	return data + 1;
}
static tb_char_t const* g2_svg_element_path_d_t(g2_svg_element_path_t const* element, tb_char_t const* data)
{
	tb_trace_noimpl();
	return data + 1;
}
static tb_char_t const* g2_svg_element_path_d_a(g2_svg_element_path_t const* element, tb_char_t const* data)
{
	tb_trace_noimpl();
	return data + 1;
}
static tb_char_t const* g2_svg_element_path_d_z(g2_svg_element_path_t const* element, tb_char_t const* data)
{
	tb_trace_noimpl();
	return data + 1;
}
static tb_void_t g2_svg_element_path_d(g2_svg_element_path_t const* element, tb_char_t const* data)
{
	// init
	tb_char_t const* p = data;
	tb_assert_and_check_return(p);

	while (*p)
	{
		switch (*p)
		{
		case 'M':
		case 'm':
			p = g2_svg_element_path_d_m(element, p);
			break;
		case 'L':
		case 'l':
			p = g2_svg_element_path_d_l(element, p);
			break;
		case 'C':
		case 'c':
			p = g2_svg_element_path_d_c(element, p);
			break;
		case 'H':
		case 'h':
			p = g2_svg_element_path_d_h(element, p);
			break;
		case 'V':
		case 'v':
			p = g2_svg_element_path_d_v(element, p);
			break;
		case 'S':
		case 's':
			p = g2_svg_element_path_d_s(element, p);
			break;
		case 'Q':
		case 'q':
			p = g2_svg_element_path_d_q(element, p);
			break;
		case 'T':
		case 't':
			p = g2_svg_element_path_d_t(element, p);
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

