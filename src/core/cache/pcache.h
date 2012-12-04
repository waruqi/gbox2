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
 * @file		pcache.h
 *
 */
#ifndef G2_CORE_PCACHE_H
#define G2_CORE_PCACHE_H

// c plus plus
#ifdef __cplusplus
extern "C" {
#endif

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

// init
tb_handle_t 				g2_pcache_init(tb_size_t maxn);

// exit
tb_void_t 					g2_pcache_exit(tb_handle_t pcache);

// clear
tb_void_t 					g2_pcache_clear(tb_handle_t pcache);

// get
tb_handle_t 				g2_pcache_get(tb_handle_t pcache, g2_shape_t const* shape);

// add
tb_handle_t 				g2_pcache_add(tb_handle_t pcache, g2_shape_t const* shape);

// c plus plus
#ifdef __cplusplus
}
#endif

#endif
