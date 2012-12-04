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
 * @file		cstack.h
 *
 */
#ifndef G2_CORE_CSTACK_H
#define G2_CORE_CSTACK_H

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

// the cstack func type
typedef struct __g2_cstack_func_t
{
	// init
	tb_handle_t (*init)();

	// exit
	tb_void_t 	(*exit)(tb_handle_t object);

	// copy
	tb_void_t 	(*copy)(tb_handle_t object, tb_handle_t copy);

}g2_cstack_func_t;

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

// init
tb_handle_t 				g2_cstack_init(tb_size_t csize, g2_cstack_func_t const* ofunc);

// exit
tb_void_t 					g2_cstack_exit(tb_handle_t cstack);

// save
tb_handle_t 				g2_cstack_save(tb_handle_t cstack);

// load
tb_void_t 					g2_cstack_load(tb_handle_t cstack);

// object
tb_handle_t 				g2_cstack_object(tb_handle_t cstack);

// c plus plus
#ifdef __cplusplus
}
#endif

#endif
