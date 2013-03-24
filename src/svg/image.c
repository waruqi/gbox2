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
 * @file		image.c
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
static tb_void_t g2_svg_element_image_writ(g2_svg_element_t const* element, tb_gstream_t* gst)
{
	g2_svg_element_image_t const* image = (g2_svg_element_image_t const*)element;
	tb_assert_and_check_return(image);

	// id
	if (tb_pstring_size(&image->base.id))
		tb_gstream_printf(gst, " id=\"%s\"", tb_pstring_cstr(&image->base.id));

	// href
	if (tb_pstring_size(&image->href))
		tb_gstream_printf(gst, " xlink:href=\"%s\"", tb_pstring_cstr(&image->href));

	// rect
	if (g2_nz(image->rect.x) || g2_nz(image->rect.y))
		tb_gstream_printf(gst, " x=\"%f\" y=\"%f\"", g2_float_to_tb(image->rect.x), g2_float_to_tb(image->rect.y));
	if (g2_nz(image->rect.w) || g2_nz(image->rect.h))
		tb_gstream_printf(gst, " width=\"%f\" height=\"%f\"", g2_float_to_tb(image->rect.w), g2_float_to_tb(image->rect.h));

	// style 
	g2_svg_writer_style(gst, &image->style); 

	// transform 
	g2_svg_writer_transform(gst, &image->transform); 
}
static tb_void_t g2_svg_element_image_load(g2_svg_element_t* element, g2_svg_painter_t* painter)
{
	g2_svg_element_image_t* image = (g2_svg_element_image_t*)element;
	tb_assert_and_check_return(image && painter && painter->painter);

	if (!image->bitmap && tb_pstring_size(&image->href)) 
	{
		// load bitmap
		image->bitmap = g2_bitmap_init_url(g2_pixfmt(painter->painter), tb_pstring_cstr(&image->href));

		// init style
		image->style.mode |= G2_SVG_STYLE_MODE_IMAGE;
		image->style.image.bitmap = image->bitmap;
		image->style.image.bounds = &image->rect;
	}
}
static tb_void_t g2_svg_element_image_draw(g2_svg_element_t const* element, g2_svg_painter_t* painter)
{
	g2_svg_element_image_t const* image = (g2_svg_element_image_t const*)element;
	tb_assert_and_check_return(image && painter && painter->painter);

	// draw
	g2_draw_rect(painter->painter, &image->rect);
}
static tb_void_t g2_svg_element_image_exit(g2_svg_element_t* element)
{
	g2_svg_element_image_t* image = (g2_svg_element_image_t*)element;
	if (image)
	{
		// exit href
		tb_pstring_exit(&image->href);

		// exit bitmap
		if (image->bitmap) g2_bitmap_exit(image->bitmap);
		image->bitmap = tb_null;

		// exit style
		g2_svg_style_exit(&image->style);
	}
}
/* ///////////////////////////////////////////////////////////////////////
 * initializer
 */
g2_svg_element_t* g2_svg_element_init_image(tb_handle_t reader)
{
	// alloc 
	g2_svg_element_image_t* element = tb_malloc0(sizeof(g2_svg_element_image_t));
	tb_assert_and_check_return_val(element, tb_null);

	// init
	element->base.exit 		= g2_svg_element_image_exit;
	element->base.writ 		= g2_svg_element_image_writ;
	element->base.load 		= g2_svg_element_image_load;
	element->base.fill 		= g2_svg_element_image_draw;
	element->base.style 	= &element->style;
	element->base.transform = &element->transform;

	// init href
	tb_pstring_init(&element->href);

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
		else if (!tb_pstring_cstricmp(&attr->name, "x"))
			g2_svg_parser_float(p, &element->rect.x);
		else if (!tb_pstring_cstricmp(&attr->name, "y"))
			g2_svg_parser_float(p, &element->rect.y);
		else if (!tb_pstring_cstricmp(&attr->name, "width"))
			g2_svg_parser_float(p, &element->rect.w);
		else if (!tb_pstring_cstricmp(&attr->name, "height"))
			g2_svg_parser_float(p, &element->rect.h);
		else if (!tb_pstring_cstricmp(&attr->name, "opacity"))
			g2_svg_parser_style_opacity(p, &element->style);
		else if (!tb_pstring_cstricmp(&attr->name, "clip-path"))
			g2_svg_parser_style_clippath(p, &element->style);
		else if (!tb_pstring_cstricmp(&attr->name, "transform"))
			g2_svg_parser_transform(p, &element->transform);
		else if (!tb_pstring_cstricmp(&attr->name, "xlink:href"))
			tb_pstring_strcpy(&element->href, &attr->data);
	}

	// ok
	return element;
}

