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
 * @file		pcache.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "pcache.h"
#include "../path.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the pcache type
typedef struct __g2_pcache_t
{
	// the path maxn
	tb_size_t 		maxn;

	// the hash: shape => path
	tb_hash_t* 		hash;

	// the path cache
	tb_stack_t* 	cache;

}g2_pcache_t;

/* ///////////////////////////////////////////////////////////////////////
 * helper
 */
static tb_void_t g2_pcache_hash_item_free(tb_item_func_t* func, tb_pointer_t item)
{
	tb_assert_and_check_return(func && item);

	// pcache
	g2_pcache_t* pcache = (g2_pcache_t*)func->priv;
	tb_assert_and_check_return(pcache && pcache->cache);

	// path
	tb_handle_t path = *((tb_handle_t const*)item);
	if (path)
	{
		// check
		tb_assert_and_check_return(tb_stack_size(pcache->cache) < pcache->maxn);

		// free path to cache
		tb_stack_put(pcache->cache, path);
	
		// clear path
		g2_path_clear(path);

		// clear
		*((tb_handle_t*)item) = tb_null;
	}
}
static tb_bool_t g2_pcache_stack_item_free(tb_stack_t* stack, tb_pointer_t* item, tb_bool_t* bdel, tb_pointer_t data)
{
	tb_assert_and_check_return_val(stack && bdel, tb_false);

	// free path item
	if (item) 
	{
		tb_handle_t path = (tb_handle_t)*item;
		if (path) g2_path_exit(path);
		*item = tb_null;
	}

	// ok
	return tb_true;
}
/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */

tb_handle_t g2_pcache_init(tb_size_t maxn)
{
	// check
	tb_assert_and_check_return_val(maxn, tb_null);

	// alloc
	g2_pcache_t* pcache = tb_malloc0(sizeof(g2_pcache_t));
	tb_assert_and_check_return_val(pcache, tb_null);

	// init func
	tb_item_func_t func = tb_item_func_ptr();
	func.free = g2_pcache_hash_item_free;
	func.priv = pcache;

	// init path cache
	pcache->maxn = maxn;
	pcache->cache = tb_stack_init(maxn, tb_item_func_ptr());
	tb_assert_and_check_goto(pcache->cache, fail);
	while (maxn--)
	{
		// init
		tb_handle_t path = g2_path_init();
		tb_assert_and_check_goto(path, fail);

		// put
		tb_stack_put(pcache->cache, path);
	}

	// init path hash
	pcache->hash = tb_hash_init(tb_isqrti(pcache->maxn), tb_item_func_ifm(sizeof(g2_shape_t), tb_null, tb_null), func);
	tb_assert_and_check_goto(pcache->hash, fail);

	// ok
	return pcache;
fail:
	if (pcache) g2_pcache_exit(pcache);
	return tb_null;
}
tb_void_t g2_pcache_exit(tb_handle_t pcache)
{
	g2_pcache_t* gpcache = (g2_pcache_t*)pcache;
	if (gpcache)
	{
		// exit hash
		if (gpcache->hash) tb_hash_exit(gpcache->hash);
		gpcache->hash = tb_null;

		// exit cache
		if (gpcache->cache) 
		{
			tb_stack_walk(gpcache->cache, g2_pcache_stack_item_free, tb_null);
			tb_stack_exit(gpcache->cache);
		}
		gpcache->cache = tb_null;
		
		// exit it
		tb_free(gpcache);
	}
}
tb_void_t g2_pcache_clear(tb_handle_t pcache)
{
	g2_pcache_t* gpcache = (g2_pcache_t*)pcache;
	tb_assert_and_check_return(gpcache);

	if (gpcache->hash) tb_hash_clear(gpcache->hash);
}
tb_handle_t g2_pcache_get(tb_handle_t pcache, g2_shape_t const* shape)
{
	g2_pcache_t* gpcache = (g2_pcache_t*)pcache;
	tb_assert_and_check_return_val(gpcache && gpcache->hash && gpcache->cache && shape, tb_null);

	return tb_hash_get(gpcache->hash, shape);
}

tb_handle_t g2_pcache_add(tb_handle_t pcache, g2_shape_t const* shape)
{
	g2_pcache_t* gpcache = (g2_pcache_t*)pcache;
	tb_assert_and_check_return_val(gpcache && gpcache->hash && gpcache->cache && shape, tb_null);

	// clear hash if full
	if (tb_hash_size(gpcache->hash) >= gpcache->maxn)
		tb_hash_clear(gpcache->hash);

	// init path from cache
	tb_handle_t path = (tb_handle_t)tb_stack_top(gpcache->cache);
	tb_assert_and_check_return_val(path, tb_null);

	// pop path from cache
	tb_stack_pop(gpcache->cache);

	// add path to hash
	tb_hash_set(gpcache->hash, shape, path);

	// ok
	return path;
}

