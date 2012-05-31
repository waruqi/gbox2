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
 * @file		memory.h
 *
 */
#ifndef G2_CORE_SKIA_MEMORY_H
#define G2_CORE_SKIA_MEMORY_H

/* /////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* /////////////////////////////////////////////////////////
 * inlines
 */

#ifdef TB_DEBUG
__tb_inline__ tb_pointer_t operator new(tb_uint_t size, tb_char_t const* func, tb_size_t line, tb_char_t const* file) throw () 
{
	return tb_memory_malloc0_impl(size, func, line, file);
}

__tb_inline__ tb_pointer_t operator new[](tb_uint_t size, tb_char_t const* func, tb_size_t line, tb_char_t const* file) throw () 
{ 
	return tb_memory_malloc0_impl(size, func, line, file); 
}
#else
__tb_inline__ tb_pointer_t operator new(tb_uint_t size) throw () 	
{
	return tb_malloc0(size);
}
__tb_inline__ tb_pointer_t operator new[](tb_uint_t size) throw () 
{ 
	return tb_malloc0(size); 
}
#endif

__tb_inline__ tb_void_t operator delete(tb_pointer_t data) throw() 
{
	tb_free(data); 			
}
__tb_inline__ tb_void_t operator delete[](tb_pointer_t data) throw()
{ 
	tb_free(data); 			
}

/* /////////////////////////////////////////////////////////
 * macros
 */

#ifdef TB_DEBUG
# 	define new 		new(__tb_func__, __tb_line__, __tb_file__)
#endif


#endif


