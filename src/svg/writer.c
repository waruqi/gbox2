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
 * @file		writer.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * trace
 */
#define TB_TRACE_IMPL_TAG 		"svg"

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "writer.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the svg writer type
typedef struct __g2_svg_writer_t
{
	// stream
	tb_gstream_t* 			wstream;

	// is format?
	tb_bool_t 				bformat;

}g2_svg_writer_t;

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */

tb_handle_t g2_svg_writer_init(tb_gstream_t* gst, tb_bool_t bformat)
{
	// check
	tb_assert_and_check_return_val(gst, TB_NULL);

	// alloc
	g2_svg_writer_t* writer = tb_malloc0(sizeof(g2_svg_writer_t));
	tb_assert_and_check_return_val(writer, TB_NULL);

	// init
	writer->wstream = gst;
	writer->bformat = bformat;

	// ok
	return writer;
}
tb_void_t g2_svg_writer_exit(tb_handle_t writer)
{
	if (writer) tb_free(writer);
}
tb_void_t g2_svg_writer_save(tb_handle_t writer, g2_svg_element_t* element)
{
	g2_svg_writer_t* gwriter = (g2_svg_writer_t*)writer;
	tb_assert_and_check_return(gwriter && gwriter->wstream && element);

	// the element name
	tb_char_t const* name = g2_svg_element_name(element);

	// the element level
	tb_size_t 			level = 0;
	g2_svg_element_t* 	parent = element->parent;
	for (; parent; parent = parent->parent) level++;

	// the element attributes
	tb_pstring_t 		attrs;
	tb_pstring_init(&attrs);
	if (element->dump) element->dump(element, &attrs);

	// format
	tb_size_t 			ntabs = level;
	if (gwriter->bformat) while (ntabs--) tb_gstream_printf(gwriter->wstream, "\t");

	// walk
	if (element->head)
	{
		// enter element
		tb_gstream_printf(gwriter->wstream, "<%s%s>", name, tb_pstring_cstr(&attrs)? tb_pstring_cstr(&attrs) : "");
		if (gwriter->bformat) tb_gstream_printf(gwriter->wstream, "\n");

		// dump childs
		g2_svg_element_t* next = element->head;
		while (next)
		{
			// dump
			g2_svg_element_dump(next);

			// next
			next = next->next;
		}

		// format
		ntabs = level;
		if (gwriter->bformat) while (ntabs--) tb_gstream_printf(gwriter->wstream, "\t");

		// leave element
		tb_gstream_printf(gwriter->wstream, "</%s>", name);
		if (gwriter->bformat) tb_gstream_printf(gwriter->wstream, "\n");
	}
	// empty element
	else 
	{
		tb_gstream_printf(gwriter->wstream, "<%s%s/>", name, tb_pstring_cstr(&attrs)? tb_pstring_cstr(&attrs) : "");
		if (gwriter->bformat) tb_gstream_printf(gwriter->wstream, "\n");
	}

	// exit attrs
	tb_pstring_exit(&attrs);
}

