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
 * @file		ellipse.c
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
 * implementation
 */
static tb_void_t g2_svg_element_ellipse_writ(g2_svg_element_t const* element, tb_gstream_t* gst)
{
	g2_svg_element_ellipse_t const* ellipse = (g2_svg_element_ellipse_t const*)element;
	tb_assert_and_check_return(ellipse);

	// id
	if (tb_pstring_size(&ellipse->base.id))
		tb_gstream_printf(gst, " id=\"%s\"", tb_pstring_cstr(&ellipse->base.id));

	// ellipse
	if (g2_nz(ellipse->ellipse.c0.x)) tb_gstream_printf(gst, " cx=\"%f\"", g2_float_to_tb(ellipse->ellipse.c0.x));
	if (g2_nz(ellipse->ellipse.c0.y)) tb_gstream_printf(gst, " cy=\"%f\"", g2_float_to_tb(ellipse->ellipse.c0.y));
	if (g2_nz(ellipse->ellipse.rx)) tb_gstream_printf(gst, " rx=\"%f\"", g2_float_to_tb(ellipse->ellipse.rx));
	if (g2_nz(ellipse->ellipse.ry)) tb_gstream_printf(gst, " ry=\"%f\"", g2_float_to_tb(ellipse->ellipse.ry));

	// style 
	g2_svg_writer_style(gst, &ellipse->style); 

	// transform 
	g2_svg_writer_transform(gst, &ellipse->transform); 
}
static tb_void_t g2_svg_element_ellipse_draw(g2_svg_element_t const* element, g2_svg_painter_t* painter)
{
	g2_svg_element_ellipse_t const* ellipse = (g2_svg_element_ellipse_t const*)element;
	tb_assert_and_check_return(ellipse && painter && painter->painter);

	// draw
	g2_draw_ellipse(painter->painter, &ellipse->ellipse);
}
static tb_void_t g2_svg_element_ellipse_exit(g2_svg_element_t* element)
{
	g2_svg_element_ellipse_t* ellipse = (g2_svg_element_ellipse_t*)element;
	if (ellipse)
	{
		// exit style
		g2_svg_style_exit(&ellipse->style);
	}
}
/* ///////////////////////////////////////////////////////////////////////
 * initializer
 */
g2_svg_element_t* g2_svg_element_init_ellipse(tb_handle_t reader)
{
	// alloc 
	g2_svg_element_ellipse_t* element = tb_malloc0(sizeof(g2_svg_element_ellipse_t));
	tb_assert_and_check_return_val(element, TB_NULL);

	// init
	element->base.exit 		= g2_svg_element_ellipse_exit;
	element->base.writ 		= g2_svg_element_ellipse_writ;
	element->base.fill 		= g2_svg_element_ellipse_draw;
	element->base.stok 		= g2_svg_element_ellipse_draw;
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
		else if (!tb_pstring_cstricmp(&attr->name, "cx"))
			g2_svg_parser_float(p, &element->ellipse.c0.x);
		else if (!tb_pstring_cstricmp(&attr->name, "cy"))
			g2_svg_parser_float(p, &element->ellipse.c0.y);
		else if (!tb_pstring_cstricmp(&attr->name, "rx"))
			g2_svg_parser_float(p, &element->ellipse.rx);
		else if (!tb_pstring_cstricmp(&attr->name, "ry"))
			g2_svg_parser_float(p, &element->ellipse.ry);
		else if (!tb_pstring_cstricmp(&attr->name, "fill"))
			g2_svg_parser_style_fill(p, &element->style);
		else if (!tb_pstring_cstricmp(&attr->name, "stroke"))
			g2_svg_parser_style_stok(p, &element->style);
		else if (!tb_pstring_cstricmp(&attr->name, "stroke-width"))
			g2_svg_parser_style_stok_width(p, &element->style);
		else if (!tb_pstring_cstricmp(&attr->name, "stroke-linejoin"))
			g2_svg_parser_style_stok_linejoin(p, &element->style);
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

