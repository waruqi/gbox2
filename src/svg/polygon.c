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
 * @file		polygon.c
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
#include "painter/painter.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static tb_void_t g2_svg_element_polygon_writ(g2_svg_element_t const* element, tb_gstream_t* gst)
{
	g2_svg_element_polygon_t const* polygon = (g2_svg_element_polygon_t const*)element;
	tb_assert_and_check_return(polygon);

	// id
	if (tb_pstring_size(&polygon->base.id))
		tb_gstream_printf(gst, " id=\"%s\"", tb_pstring_cstr(&polygon->base.id));

	// polygon
	if (polygon->path && g2_path_itor_init(polygon->path))
	{
		// init points
		tb_gstream_printf(gst, " points=\"");

		// walk
		g2_point_t 	pt[4];
		tb_size_t 	co = G2_PATH_CODE_NONE;
		while (co = g2_path_itor_next(polygon->path, pt))
		{
			switch (co)
			{
			case G2_PATH_CODE_MOVE:
				tb_gstream_printf(gst, "%f,%f ", g2_float_to_tb(pt[0].x), g2_float_to_tb(pt[0].y));
				break;
			case G2_PATH_CODE_LINE:
				tb_gstream_printf(gst, "%f,%f ", g2_float_to_tb(pt[1].x), g2_float_to_tb(pt[1].y));
				break;
			case G2_PATH_CODE_CLOSE:
				break;
			default:
				tb_assert(0);
				break;
			}
		}
		g2_path_itor_exit(polygon->path);

		// exit points
		tb_gstream_printf(gst, "\"");
	}

	// style 
	g2_svg_writer_style(gst, &polygon->style); 

	// transform 
	g2_svg_writer_transform(gst, &polygon->transform); 
}
static tb_void_t g2_svg_element_polygon_draw(g2_svg_element_t const* element, g2_svg_painter_t* painter)
{
	g2_svg_element_polygon_t const* polygon = (g2_svg_element_polygon_t const*)element;
	tb_assert_and_check_return(polygon && painter && painter->painter);

	// draw
	if (polygon->path) g2_draw_path(painter->painter, polygon->path);
}
static tb_void_t g2_svg_element_polygon_exit(g2_svg_element_t* element)
{
	g2_svg_element_polygon_t* polygon = (g2_svg_element_polygon_t*)element;
	if (polygon)
	{
		// exit style
		g2_svg_style_exit(&polygon->style);
	
		// exit path
		if (polygon->path) g2_path_exit(polygon->path);
		polygon->path = TB_NULL;
	}
}
static tb_char_t const* g2_svg_element_polygon_point(g2_svg_element_polygon_t* element, tb_char_t const* data, tb_size_t* size)
{
	// init
	tb_char_t const* p = data;

	// x
	g2_float_t x = 0; p = g2_svg_parser_float(p, &x); p = g2_svg_parser_separator_skip(p);

	// y
	g2_float_t y = 0; p = g2_svg_parser_float(p, &y); p = g2_svg_parser_separator_skip(p);

	// trace
	tb_trace_impl("polygon: point: %f, %f", g2_float_to_tb(x), g2_float_to_tb(y));

	// init path
	if (!element->path) element->path = g2_path_init();
	
	// done path
	if (element->path)
	{
		// move to
		if (!*size) g2_path_move2_to(element->path, x, y);
		// line to
		else g2_path_line2_to(element->path, x, y);
	}

	// size++
	(*size)++;

	// ok
	return p;
}
static tb_void_t g2_svg_element_polygon_points(g2_svg_element_polygon_t* element, tb_char_t const* data)
{
	// init
	tb_char_t const* p = data;
	tb_assert_and_check_return(p);

	// size
	tb_size_t size = 0;

	// trace
	tb_trace_impl("polygon: points");
	while (*p)
	{
		if (!tb_isspace(*p) && tb_isdigit(*p))
			p = g2_svg_element_polygon_point(element, p, &size);
		else p++;
	}

	// close path
	if (element->path) g2_path_close(element->path);
}
/* ///////////////////////////////////////////////////////////////////////
 * initializer
 */
g2_svg_element_t* g2_svg_element_init_polygon(tb_handle_t reader)
{
	// alloc 
	g2_svg_element_polygon_t* element = tb_malloc0(sizeof(g2_svg_element_polygon_t));
	tb_assert_and_check_return_val(element, TB_NULL);

	// init
	element->base.exit 		= g2_svg_element_polygon_exit;
	element->base.writ 		= g2_svg_element_polygon_writ;
	element->base.fill 		= g2_svg_element_polygon_draw;
	element->base.stok 		= g2_svg_element_polygon_draw;
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
		else if (!tb_pstring_cstricmp(&attr->name, "points"))
			g2_svg_element_polygon_points(element, p);
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
		else if (!tb_pstring_cstricmp(&attr->name, "clip-path"))
			g2_svg_parser_style_clippath(p, &element->style);
		else if (!tb_pstring_cstricmp(&attr->name, "transform"))
			g2_svg_parser_transform(p, &element->transform);
	}

	// ok
	return element;
}

