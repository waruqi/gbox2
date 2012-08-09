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
 * @file		color.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "color.h"

/* ///////////////////////////////////////////////////////////////////////
 * globals
 */
// the colors
static g2_named_color_t 	g_named_colors[] = 
{
 	G2_COLOR_INIT_BLACK
,	G2_COLOR_INIT_BLUE 
,	G2_COLOR_INIT_BROWN
,	G2_COLOR_INIT_DARKBLUE
,	G2_COLOR_INIT_GOLD 
,	G2_COLOR_INIT_GRAY
,	G2_COLOR_INIT_GREY
,	G2_COLOR_INIT_GREEN
,	G2_COLOR_INIT_LIGHTBLUE
,	G2_COLOR_INIT_LIGHTGRAY
,	G2_COLOR_INIT_LIGHTGREY
,	G2_COLOR_INIT_LIGHTPINK
,	G2_COLOR_INIT_LIGHTYELLOW
,	G2_COLOR_INIT_NAVY
,	G2_COLOR_INIT_ORANGE
,	G2_COLOR_INIT_PINK
,	G2_COLOR_INIT_PURPLE
,	G2_COLOR_INIT_RED
,	G2_COLOR_INIT_SNOW
,	G2_COLOR_INIT_TOMATO
,	G2_COLOR_INIT_YELLOW
,	G2_COLOR_INIT_WHEAT
,	G2_COLOR_INIT_WHITE

};

/* ///////////////////////////////////////////////////////////////////////
 * comparator
 */
static tb_long_t g2_named_color_comp(tb_iterator_t* iterator, tb_cpointer_t item, tb_cpointer_t name)
{
	// check
	tb_assert_return_val(item && name, 0);

	// comp
	return tb_strnicmp(((g2_named_color_t const*)item)->name, name, tb_strlen(((g2_named_color_t const*)item)->name));
}

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */

g2_named_color_t const* g2_color_from_name(tb_char_t const* name)
{
	tb_assert_and_check_return_val(name, TB_NULL);

	// init iterator
	tb_iterator_t 	iterator = tb_iterator_mem(g_named_colors, tb_arrayn(g_named_colors), sizeof(g2_named_color_t));
	iterator.comp = g2_named_color_comp;

	// find it by the binary search
	tb_size_t 		itor = tb_binary_find_all(&iterator, name);

	// ok?
	return (itor != tb_iterator_tail(&iterator))? (g2_named_color_t const*)tb_iterator_item(&iterator, itor) : TB_NULL;
}
g2_named_color_t const* g2_color_from_index(tb_size_t index)
{
	tb_assert_and_check_return_val(index < tb_arrayn(g_named_colors), TB_NULL);
	return g_named_colors + index;
}

