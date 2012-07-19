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
 * @file		reader.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "reader.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the svg reader type
typedef struct __g2_svg_reader_t
{
	// the reader
	tb_handle_t 			reader;

}g2_svg_reader_t;

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */

tb_handle_t g2_svg_reader_init(tb_gstream_t* gst)
{
	// check
	tb_assert_and_check_return_val(gst, TB_NULL);

	// alloc
	g2_svg_reader_t* reader = tb_malloc0(sizeof(g2_svg_reader_t));
	tb_assert_and_check_return_val(reader, TB_NULL);

	// init
	reader->reader = tb_xml_reader_init(gst);
	tb_assert_and_check_goto(reader->reader, fail);

	// ok
	return reader;

fail:
	if (reader) g2_svg_reader_exit(reader);
	return TB_NULL;
}
tb_void_t g2_svg_reader_exit(tb_handle_t reader)
{
	g2_svg_reader_t* sreader = (g2_svg_reader_t*)reader;
	if (sreader)
	{
		// exit reader
		if (sreader->reader) tb_xml_reader_exit(sreader->reader);
	
		// free it
		tb_free(sreader);
	}
}
g2_svg_element_t* g2_svg_reader_load(tb_handle_t reader)
{
	g2_svg_reader_t* sreader = (g2_svg_reader_t*)reader;
	tb_assert_and_check_return_val(sreader && sreader->reader, TB_NULL);

	// walk
	tb_size_t e = TB_XML_READER_EVENT_NONE;
	while (e = tb_xml_reader_next(sreader->reader))
	{
		switch (e)
		{
		case TB_XML_READER_EVENT_DOCUMENT:
		case TB_XML_READER_EVENT_DOCUMENT_TYPE:
			break;
		case TB_XML_READER_EVENT_ELEMENT_EMPTY: 
			{
			}
			break;
		case TB_XML_READER_EVENT_ELEMENT_BEG: 
			{
			}
			break;
		case TB_XML_READER_EVENT_ELEMENT_END: 
			{
			}
			break;
		case TB_XML_READER_EVENT_TEXT: 
			{
			}
			break;
		case TB_XML_READER_EVENT_CDATA: 
			{
			}
			break;
		case TB_XML_READER_EVENT_COMMENT: 
			{
			}
			break;
		default:
			break;
		}
	}

	// ok
	return TB_NULL;
}
