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
 * @file		region.h
 *
 */
#ifndef G2_CORE_REGION_H
#define G2_CORE_REGION_H

// c plus plus
#ifdef __cplusplus
extern "C" {
#endif

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */
// the region op type
typedef enum __g2_region_op_t
{
	G2_REGION_OP_NONE 			= 0
,	G2_REGION_OP_SUBTRACT 		= 1
,	G2_REGION_OP_INTERSECT 		= 2
,	G2_REGION_OP_UNION 			= 3

}g2_region_op_t;

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

// init & exit
tb_handle_t 	g2_region_init();
tb_void_t 		g2_region_exit(tb_handle_t region);

// clear
tb_void_t 		g2_region_clear(tb_handle_t region);

// set
tb_bool_t 		g2_region_set_rect(tb_handle_t region, g2_rect_t const* rect);

// c plus plus
#ifdef __cplusplus
}
#endif

#endif
