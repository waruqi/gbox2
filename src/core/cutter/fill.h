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
 * @file		fill.h
 *
 */
#ifndef G2_CORE_CUTTER_FILL_H
#define G2_CORE_CUTTER_FILL_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the cutter fill type
typedef struct __g2_cutter_fill_t
{
	// the base
	g2_cutter_t 			base;
	
	// the rule
	tb_size_t 				rule;

	// the path
	tb_handle_t 			path;

}g2_cutter_fill_t;

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

// init
tb_void_t g2_cutter_fill_init(g2_cutter_fill_t* cutter, tb_size_t rule, g2_cutter_func_t func, tb_pointer_t data);

// done
tb_void_t g2_cutter_fill_done(g2_cutter_fill_t* cutter, tb_handle_t path);

// exit
tb_void_t g2_cutter_fill_exit(g2_cutter_fill_t* cutter);

#endif


