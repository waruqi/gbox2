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
 * @file		painter.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * trace
 */
#define TB_TRACE_IMPL_TAG 		"svg"

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "painter.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */
#ifdef TB_CONFIG_MEMORY_MODE_SMALL
# 	define G2_SVG_PAINTER_HASH_MAXN 			(32)
#else
# 	define G2_SVG_PAINTER_HASH_MAXN 			(64)
#endif

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static tb_void_t g2_svg_painter_load_element(g2_svg_painter_t* spainter, g2_svg_element_t const* element)
{
	// has id?
	if (tb_pstring_size(&element->id))
	{
		// init pool
		if (!spainter->pool) spainter->pool = tb_spool_init(TB_SPOOL_GROW_SMALL, 0);

		// init hash
		if (!spainter->hash) spainter->hash = tb_hash_init(G2_SVG_PAINTER_HASH_MAXN, tb_item_func_str(TB_TRUE, spainter->pool), tb_item_func_ptr());
	
		// set id => element
		if (spainter->hash) tb_hash_set(spainter->hash, tb_pstring_cstr(&element->id), element);
	}

	// walk
	if (element->head)
	{
		g2_svg_element_t* next = element->head;
		while (next)
		{
			// load
			g2_svg_painter_load_element(spainter, element);

			// next
			next = next->next;
		}
	}
}
static tb_void_t g2_svg_painter_draw_element(g2_svg_painter_t* spainter, g2_svg_element_t const* element)
{
	// draw
	if (element->draw) element->draw(element, spainter);

	// walk
	if (element->head)
	{
		g2_svg_element_t* next = element->head;
		while (next)
		{
			// load
			g2_svg_painter_draw_element(spainter, element);

			// next
			next = next->next;
		}
	}
}
static tb_bool_t g2_svg_painter_init(g2_svg_painter_t* spainter, tb_handle_t painter, g2_svg_element_t const* element)
{
	// init
	spainter->element 	= element;
	spainter->painter 	= painter;
	spainter->style 	= g2_style(painter);
	spainter->pool 		= TB_NULL;
	spainter->hash 		= TB_NULL;
	tb_assert_and_check_return_val(spainter->style, TB_FALSE);

	// load
	g2_svg_painter_load_element(spainter, element);

	// ok
	return TB_TRUE;
}
static tb_void_t g2_svg_painter_exit(g2_svg_painter_t* spainter)
{
	if (spainter)
	{
		// exit hash
		if (spainter->hash) tb_hash_exit(spainter->hash);
		spainter->hash = TB_NULL;

		// exit pool
		if (spainter->pool) tb_spool_exit(spainter->pool);
		spainter->pool = TB_NULL;
	}
}
static tb_void_t g2_svg_painter_draw(g2_svg_painter_t* spainter)
{
	g2_svg_painter_draw_element(spainter, spainter->element);
}
/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */
tb_void_t g2_draw_svg(tb_handle_t painter, g2_svg_element_t const* element)
{
	tb_assert_and_check_return(painter && element);

	// init
	g2_svg_painter_t spainter;
	if (g2_svg_painter_init(&spainter, painter, element))
	{
		// draw
		g2_svg_painter_draw(&spainter);

		// exit
		g2_svg_painter_exit(&spainter);
	}
}

