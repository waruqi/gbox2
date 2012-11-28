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
 * @file		clipper.h
 *
 */
#ifndef G2_CORE_CLIPPER_H
#define G2_CORE_CLIPPER_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the clipper mode enum
typedef enum __g2_clipper_mode_e
{
	G2_CLIPPER_MODE_NONE 		= 0x0000
,	G2_CLIPPER_MODE_SUBTRACT 	= 0x0001
,	G2_CLIPPER_MODE_INTERSECT 	= 0x0002
,	G2_CLIPPER_MODE_UNION 		= 0x0003
,	G2_CLIPPER_MODE_REPLACE 	= 0x0004
,	G2_CLIPPER_MODE_MASK 		= 0x00ff

,	G2_CLIPPER_FLAG_ANTI_ALIAS 	= 0x0100
,	G2_CLIPPER_FLAG_MASK 		= 0xff00

}g2_clipper_mode_e;

// the clipper item enum
typedef enum __g2_clipper_item_e
{
	G2_CLIPPER_ITEM_RECT 		= 0
, 	G2_CLIPPER_ITEM_PATH 		= 1

}g2_clipper_item_e;

// the clipper item type
typedef struct __g2_clipper_item_t
{
	// the clip mode
	tb_size_t 			mode 	: 16;

	// the clip type
	tb_size_t 			type 	: 16;

	// the clip item
	union 
	{
		// rect
		g2_rect_t 		rect;
		
		// path
		tb_handle_t 	path;

	}u;

}g2_clipper_item_t;

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

// init & exit
tb_handle_t 		g2_clipper_init();
tb_void_t 			g2_clipper_exit(tb_handle_t clipper);

// clear
tb_void_t 			g2_clipper_clear(tb_handle_t clipper);

// path
tb_void_t 			g2_clipper_path(tb_handle_t clipper, 	tb_size_t mode, tb_handle_t path);

// rect
tb_void_t 			g2_clipper_rect(tb_handle_t clipper, 	tb_size_t mode, g2_rect_t const* rect);
tb_void_t 			g2_clipper_rect2(tb_handle_t clipper, 	tb_size_t mode, g2_float_t x, g2_float_t y, g2_float_t w, g2_float_t h);

// irect
tb_void_t 			g2_clipper_irect(tb_handle_t clipper, 	tb_size_t mode, g2_irect_t const* rect);
tb_void_t 			g2_clipper_irect2(tb_handle_t clipper, 	tb_size_t mode, tb_long_t x, tb_long_t y, tb_size_t w, tb_size_t h);

#endif
