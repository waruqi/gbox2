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
 * @file		line.c
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
#include "painter/painter.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static tb_void_t g2_svg_element_line_writ(g2_svg_element_t const* element, tb_gstream_t* gst)
{
	g2_svg_element_line_t const* line = (g2_svg_element_line_t const*)element;
	tb_assert_and_check_return(line);

	// id
	if (tb_pstring_size(&line->base.id))
		tb_gstream_printf(gst, " id=\"%s\"", tb_pstring_cstr(&line->base.id));

	// line
	tb_gstream_printf(gst, " x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\"", g2_float_to_tb(line->line.p0.x), g2_float_to_tb(line->line.p0.y), g2_float_to_tb(line->line.p1.x), g2_float_to_tb(line->line.p1.y));

	// style 
	g2_svg_writer_style(gst, &line->style); 

	// transform 
	g2_svg_writer_transform(gst, &line->transform); 
}
static tb_void_t g2_svg_element_line_draw(g2_svg_element_t const* element, g2_svg_painter_t* painter)
{
	g2_svg_element_line_t const* line = (g2_svg_element_line_t const*)element;
	tb_assert_and_check_return(line && painter && painter->painter);

	// draw
	g2_draw_line(painter->painter, &line->line);
}
static tb_void_t g2_svg_element_line_exit(g2_svg_element_t* element)
{
	g2_svg_element_line_t* line = (g2_svg_element_line_t*)element;
	if (line)
	{
		// exit style
		g2_svg_style_exit(&line->style);
	}
}
/* ///////////////////////////////////////////////////////////////////////
 * initializer
 */
g2_svg_element_t* g2_svg_element_init_line(tb_handle_t reader)
{
	// alloc 
	g2_svg_element_line_t* element = tb_malloc0(sizeof(g2_svg_element_line_t));
	tb_assert_and_check_return_val(element, TB_NULL);

	// init
	element->base.exit 		= g2_svg_element_line_exit;
	element->base.writ 		= g2_svg_element_line_writ;
	element->base.stok 		= g2_svg_element_line_draw;
	element->base.style 	= &element->style;
	element->base.transform = &element->transform;

	// init style
	g2_svg_style_init(&element->style);

	// init transform
	g2_matrix_clear(&element->transform);

	// attributes
	tb_xml_node_t const* attr = tb_xml_reader_attributes(reader);
	for (; attr; attr = attr->next)
	{
		tb_char_t const* p = tb_pstring_cstr(&attr->data);
		if (!tb_pstring_cstricmp(&attr->name, "id"))
			tb_pstring_strcpy(&element->base.id, &attr->data);
		else if (!tb_pstring_cstricmp(&attr->name, "x1"))
			g2_svg_parser_float(p, &element->line.p0.x);
		else if (!tb_pstring_cstricmp(&attr->name, "y1"))
			g2_svg_parser_float(p, &element->line.p0.y);
		else if (!tb_pstring_cstricmp(&attr->name, "x2"))
			g2_svg_parser_float(p, &element->line.p1.x);
		else if (!tb_pstring_cstricmp(&attr->name, "y2"))
			g2_svg_parser_float(p, &element->line.p1.y);
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
		else if (!tb_pstring_cstricmp(&attr->name, "clip-path"))
			g2_svg_parser_style_clippath(p, &element->style);
		else if (!tb_pstring_cstricmp(&attr->name, "transform"))
			g2_svg_parser_transform(p, &element->transform);

	}

	// ok
	return element;
}

