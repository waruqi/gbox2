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
 * trace
 */
#define TB_TRACE_IMPL_TAG 		"svg"

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "reader.h"
#include "element.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the svg reader type
typedef struct __g2_svg_reader_t
{
	// the reader
	tb_handle_t 			reader;

}g2_svg_reader_t;

// the svg reader element type
typedef struct __g2_svg_reader_element_t
{
	// the element type
	tb_size_t 				type;

	// the element name
	tb_char_t const* 		name;

}g2_svg_reader_element_t;

/* ///////////////////////////////////////////////////////////////////////
 * globals
 */

// the element names
static g2_svg_reader_element_t* 	g_svg_elements[] = 
{
	{G2_SVG_ELEMENT_TYPE_NONE, 				TB_NULL 			}
,	{G2_SVG_ELEMENT_TYPE_CIRClE, 			"circle" 			}
,	{G2_SVG_ELEMENT_TYPE_CLIPPATH, 			"clipPath" 			}
,	{G2_SVG_ELEMENT_TYPE_DEFS, 				"defs" 				}
,	{G2_SVG_ELEMENT_TYPE_ELLIPSE, 			"ellipse" 			}
,	{G2_SVG_ELEMENT_TYPE_FECOLORMATRIX, 	"feColorMatrix" 	}
,	{G2_SVG_ELEMENT_TYPE_FILTER, 			"filter" 			}
,	{G2_SVG_ELEMENT_TYPE_G, 				"g" 				}
,	{G2_SVG_ELEMENT_TYPE_IMAGE, 			"image" 			}
,	{G2_SVG_ELEMENT_TYPE_LINE, 				"line" 				}
,	{G2_SVG_ELEMENT_TYPE_LINEARGRADIENT, 	"linearGradient" 	}
,	{G2_SVG_ELEMENT_TYPE_MASK, 				"mask" 				}
,	{G2_SVG_ELEMENT_TYPE_METADATA, 			"metadata" 			}
,	{G2_SVG_ELEMENT_TYPE_PATH, 				"path" 				}
,	{G2_SVG_ELEMENT_TYPE_POLYGON, 			"polygon" 			}
,	{G2_SVG_ELEMENT_TYPE_POLYLINE, 			"polyline" 			}
,	{G2_SVG_ELEMENT_TYPE_RADIALGRADIENT, 	"radialGradient" 	}
,	{G2_SVG_ELEMENT_TYPE_RECT, 				"rect" 				}
,	{G2_SVG_ELEMENT_TYPE_SVG, 				"svg" 				}
,	{G2_SVG_ELEMENT_TYPE_STOP, 				"circle" 			}
,	{G2_SVG_ELEMENT_TYPE_SYMBOL, 			"stop" 				}
,	{G2_SVG_ELEMENT_TYPE_TEXT, 				"text" 				}
,	{G2_SVG_ELEMENT_TYPE_TSPAN, 			"tspan" 			}
,	{G2_SVG_ELEMENT_TYPE_USE, 				"use" 				}
};

/* ///////////////////////////////////////////////////////////////////////
 * parser
 */

static tb_size_t g2_svg_reader_type(tb_char_t const* name)
{

	return 0;
}

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

	// init 
	tb_bool_t bsvg = TB_FALSE;

	// walk
	tb_size_t e = TB_XML_READER_EVENT_NONE;
	while (e = tb_xml_reader_next(sreader->reader))
	{
		switch (e)
		{
		case TB_XML_READER_EVENT_ELEMENT_EMPTY: 
			{
				// check
				tb_assert_and_check_goto(bsvg, fail);
			}
			break;
		case TB_XML_READER_EVENT_ELEMENT_BEG: 
			{
				// init
				tb_char_t const* name = tb_xml_reader_element(sreader->reader);
				tb_assert_and_check_goto(name, fail);

				// is svg?
				if (!bsvg)
				{
					if (!tb_stricmp(name, "svg")) bsvg = TB_TRUE;
					else goto fail;
				}
				

				tb_print("%s", name);

			}
			break;
		case TB_XML_READER_EVENT_ELEMENT_END: 
			{
				// check
				tb_assert_and_check_goto(bsvg, fail);
			}
			break;
		case TB_XML_READER_EVENT_TEXT: 
			{
				// check
				tb_assert_and_check_goto(bsvg, fail);
			}
			break;
		case TB_XML_READER_EVENT_CDATA: 
			{
				// check
				tb_assert_and_check_goto(bsvg, fail);
			}
			break;
		case TB_XML_READER_EVENT_COMMENT: 
			{
				// check
				tb_assert_and_check_goto(bsvg, fail);
			}
			break;
		default:
			break;
		}
	}

	// ok
	return TB_NULL;

fail:
	return TB_NULL;
}
