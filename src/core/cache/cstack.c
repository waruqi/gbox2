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
 * @file		cstack.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "cstack.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the cstack type
typedef struct __g2_cstack_t
{
	// the object
	tb_handle_t 				object;

	// the stack
	tb_stack_t* 				stack;

	// the cache
	tb_stack_t* 				cache;

	// the cache size
	tb_size_t 					csize;

	// the func
	g2_cstack_func_t 			func;

}g2_cstack_t;

/* ///////////////////////////////////////////////////////////////////////
 * helper
 */
static tb_bool_t g2_cstack_item_free(tb_stack_t* stack, tb_pointer_t* item, tb_bool_t* bdel, tb_pointer_t data)
{
	tb_assert_and_check_return_val(stack && bdel && data, tb_false);

	// free object item
	if (item) 
	{
		tb_handle_t object = (tb_handle_t)*item;
		if (object) ((g2_cstack_t*)data)->func.exit(object);
		*item = tb_null;
	}

	// ok
	return tb_true;
}

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */

tb_handle_t g2_cstack_init(tb_size_t csize, g2_cstack_func_t const* ofunc)
{
	// check
	tb_assert_and_check_return_val(csize && ofunc && ofunc->init && ofunc->exit, tb_null);

	// alloc
	g2_cstack_t* cstack = tb_malloc0(sizeof(g2_cstack_t));
	tb_assert_and_check_return_val(cstack, tb_null);

	// init
	cstack->func = *ofunc;
	cstack->csize = csize;

	// init object
	cstack->object = ofunc->init();
	tb_assert_and_check_goto(cstack->object, fail);

	// init cache
	cstack->cache = tb_stack_init(csize, tb_item_func_ptr(tb_null, tb_null));
	tb_assert_and_check_goto(cstack->cache, fail);
	while (csize--)
	{
		// init
		tb_handle_t object = ofunc->init();
		tb_assert_and_check_goto(object, fail);

		// put
		tb_stack_put(cstack->cache, object);
	}

	// init stack
	cstack->stack = tb_stack_init(cstack->csize << 2, tb_item_func_ptr(tb_null, tb_null));
	tb_assert_and_check_goto(cstack->stack, fail);

	// ok
	return cstack;
fail:
	if (cstack) g2_cstack_exit(cstack);
	return tb_null;
}
tb_void_t g2_cstack_exit(tb_handle_t cstack)
{
	g2_cstack_t* gcstack = (g2_cstack_t*)cstack;
	if (gcstack)
	{
		// exit object
		if (gcstack->object) gcstack->func.exit(gcstack->object);
		gcstack->object = tb_null;

		// exit stack
		if (gcstack->stack) 
		{
			tb_stack_walk(gcstack->stack, g2_cstack_item_free, gcstack);
			tb_stack_exit(gcstack->stack);
		}
		gcstack->stack = tb_null;

		// exit object cache
		if (gcstack->cache) 
		{
			tb_stack_walk(gcstack->cache, g2_cstack_item_free, gcstack);
			tb_stack_exit(gcstack->cache);
		}
		gcstack->cache = tb_null;
				
		// exit it
		tb_free(gcstack);
	}
}
tb_handle_t g2_cstack_object(tb_handle_t cstack)
{
	g2_cstack_t* gcstack = (g2_cstack_t*)cstack;
	tb_assert_and_check_return_val(gcstack, tb_null);

	return gcstack->object;
}
tb_handle_t g2_cstack_save(tb_handle_t cstack)
{
	g2_cstack_t* gcstack = (g2_cstack_t*)cstack;
	tb_assert_and_check_return_val(gcstack && gcstack->cache && gcstack->stack, tb_null);

	// init a new object from cache first
	tb_handle_t object = tb_null;
	if (tb_stack_size(gcstack->cache))
	{
		// get
		object = (tb_handle_t)tb_stack_top(gcstack->cache);
		tb_assert_and_check_return_val(gcstack->cache, tb_null);

		// pop
		tb_stack_pop(gcstack->cache);
	}
	// init a new object
	else object = gcstack->func.init();
	tb_assert_and_check_return_val(object, tb_null);

	// save the old object
	tb_stack_put(gcstack->stack, gcstack->object);

	// copy the new object
	if (gcstack->func.copy) gcstack->func.copy(object, gcstack->object);
	gcstack->object = object;

	// ok
	return gcstack->object;
}
tb_void_t g2_cstack_load(tb_handle_t cstack)
{
	g2_cstack_t* gcstack = (g2_cstack_t*)cstack;
	tb_assert_and_check_return(gcstack && gcstack->cache && gcstack->stack);

	// load the top object
	tb_handle_t object = (tb_handle_t)tb_stack_top(gcstack->stack);
	tb_assert_and_check_return(object);
	tb_stack_pop(gcstack->stack);

	// free object to cache first
	if (gcstack->object && tb_stack_size(gcstack->cache) < gcstack->csize)
		tb_stack_put(gcstack->cache, gcstack->object);
	// free object
	else gcstack->func.exit(gcstack->object);

	// copy the top object
	gcstack->object = object;
}
