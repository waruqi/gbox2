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
 * @file		stop.c
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
#include "parser/parser.h"
#include "writer/writer.h"

/* ///////////////////////////////////////////////////////////////////////
 * stop
 */
static tb_void_t g2_svg_element_stop_writ(g2_svg_element_t const* element, tb_gstream_t* gst)
{
	g2_svg_element_stop_t const* stop = (g2_svg_element_stop_t const*)element;
	tb_assert_and_check_return(stop);

	// offset
	tb_gstream_printf(gst, " offset=\"%f\"", g2_float_to_tb(stop->offset));

	// style 
	g2_pixel_t pixel = g2_color_pixel(stop->color);
	tb_gstream_printf(gst, " stop-color=\"#%06x\"", stop->color.a != 0xff? pixel : (pixel & 0x00ffffff));
}
/* ///////////////////////////////////////////////////////////////////////
 * initializer
 */
g2_svg_element_t* g2_svg_element_init_stop(tb_handle_t reader)
{
	// alloc 
	g2_svg_element_stop_t* element = tb_malloc0(sizeof(g2_svg_element_stop_t));
	tb_assert_and_check_return_val(element, TB_NULL);

	// init
	element->base.writ = g2_svg_element_stop_writ;

	// attributes
	tb_xml_node_t const* attr = tb_xml_reader_attributes(reader);
	for (; attr; attr = attr->next)
	{
		tb_char_t const* p = tb_pstring_cstr(&attr->data);
		if (!tb_pstring_cstricmp(&attr->name, "offset"))
			g2_svg_parser_float(p, &element->offset);
		else if (!tb_pstring_cstricmp(&attr->name, "style"))
			g2_svg_parser_style_stop(p, &element->color);
		else if (!tb_pstring_cstricmp(&attr->name, "stop-color"))
			g2_svg_parser_style_stop_color(p, &element->color);
		else if (!tb_pstring_cstricmp(&attr->name, "stop-opacity"))
			g2_svg_parser_style_stop_opacity(p, &element->color);
	}

	// ok
	return element;
}

