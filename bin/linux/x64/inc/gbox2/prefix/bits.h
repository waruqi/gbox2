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
 * @file		bits.h
 *
 */
#ifndef G2_PREFIX_BITS_H
#define G2_PREFIX_BITS_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "config.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */
#ifdef TB_WORDS_BIGENDIAN
// 16-bits
# 	define g2_bits_get_u16_le(p) 		tb_bits_get_u16_le_impl(((tb_byte_t const*)(p)))
# 	define g2_bits_get_s16_le(p) 		tb_bits_get_s16_le_impl(((tb_byte_t const*)(p)))
# 	define g2_bits_get_u16_be(p) 		tb_bits_get_u16_ne_impl(((tb_byte_t const*)(p)))
# 	define g2_bits_get_s16_be(p) 		tb_bits_get_s16_ne_impl(((tb_byte_t const*)(p)))

# 	define g2_bits_set_u16_le(p, x) 	tb_bits_set_u16_le_impl(((tb_byte_t*)(p)), x)
# 	define g2_bits_set_s16_le(p, x) 	tb_bits_set_s16_le_impl(((tb_byte_t*)(p)), x)
# 	define g2_bits_set_u16_be(p, x) 	tb_bits_set_u16_ne_impl(((tb_byte_t*)(p)), x)
# 	define g2_bits_set_s16_be(p, x) 	tb_bits_set_s16_ne_impl(((tb_byte_t*)(p)), x)

// 24-bits
# 	define g2_bits_get_u24_le(p) 		tb_bits_get_u24_le_impl(((tb_byte_t const*)(p)))
# 	define g2_bits_get_s24_le(p) 		tb_bits_get_s24_le_impl(((tb_byte_t const*)(p)))
# 	define g2_bits_get_u24_be(p) 		tb_bits_get_u24_ne_impl(((tb_byte_t const*)(p)))
# 	define g2_bits_get_s24_be(p) 		tb_bits_get_s24_ne_impl(((tb_byte_t const*)(p)))

# 	define g2_bits_set_u24_le(p, x) 	tb_bits_set_u24_le_impl(((tb_byte_t*)(p)), x)
# 	define g2_bits_set_s24_le(p, x) 	tb_bits_set_s24_le_impl(((tb_byte_t*)(p)), x)
# 	define g2_bits_set_u24_be(p, x) 	tb_bits_set_u24_ne_impl(((tb_byte_t*)(p)), x)
# 	define g2_bits_set_s24_be(p, x) 	tb_bits_set_s24_ne_impl(((tb_byte_t*)(p)), x)

// 32-bits
# 	define g2_bits_get_u32_le(p) 		tb_bits_get_u32_le_impl(((tb_byte_t const*)(p)))
# 	define g2_bits_get_s32_le(p) 		tb_bits_get_s32_le_impl(((tb_byte_t const*)(p)))
# 	define g2_bits_get_u32_be(p) 		tb_bits_get_u32_ne_impl(((tb_byte_t const*)(p)))
# 	define g2_bits_get_s32_be(p) 		tb_bits_get_s32_ne_impl(((tb_byte_t const*)(p)))

# 	define g2_bits_set_u32_le(p, x) 	tb_bits_set_u32_le_impl(((tb_byte_t*)(p)), x)
# 	define g2_bits_set_s32_le(p, x) 	tb_bits_set_u32_le_impl(((tb_byte_t*)(p)), x)
# 	define g2_bits_set_u32_be(p, x) 	tb_bits_set_u32_ne_impl(((tb_byte_t*)(p)), x)
# 	define g2_bits_set_s32_be(p, x) 	tb_bits_set_s32_ne_impl(((tb_byte_t*)(p)), x)

// 64-bits
# 	define g2_bits_get_u64_le(p) 		tb_bits_get_u64_le_impl(((tb_byte_t const*)(p)))
# 	define g2_bits_get_s64_le(p) 		tb_bits_get_s64_le_impl(((tb_byte_t const*)(p)))
# 	define g2_bits_get_u64_be(p) 		tb_bits_get_u64_ne_impl(((tb_byte_t const*)(p)))
# 	define g2_bits_get_s64_be(p) 		tb_bits_get_s64_ne_impl(((tb_byte_t const*)(p)))

# 	define g2_bits_set_u64_le(p, x) 	tb_bits_set_u64_le_impl(((tb_byte_t*)(p)), x)
# 	define g2_bits_set_s64_le(p, x) 	tb_bits_set_u64_le_impl(((tb_byte_t*)(p)), x)
# 	define g2_bits_set_u64_be(p, x) 	tb_bits_set_u64_ne_impl(((tb_byte_t*)(p)), x)
# 	define g2_bits_set_s64_be(p, x) 	tb_bits_set_s64_ne_impl(((tb_byte_t*)(p)), x)

#else

// 16-bits
# 	define g2_bits_get_u16_le(p) 		tb_bits_get_u16_ne_impl(((tb_byte_t const*)(p)))
# 	define g2_bits_get_s16_le(p) 		tb_bits_get_s16_ne_impl(((tb_byte_t const*)(p)))
# 	define g2_bits_get_u16_be(p) 		tb_bits_get_u16_be_impl(((tb_byte_t const*)(p)))
# 	define g2_bits_get_s16_be(p) 		tb_bits_get_s16_be_impl(((tb_byte_t const*)(p)))

# 	define g2_bits_set_u16_le(p, x) 	tb_bits_set_u16_ne_impl(((tb_byte_t*)(p)), x)
# 	define g2_bits_set_s16_le(p, x) 	tb_bits_set_s16_ne_impl(((tb_byte_t*)(p)), x)
# 	define g2_bits_set_u16_be(p, x) 	tb_bits_set_u16_be_impl(((tb_byte_t*)(p)), x)
# 	define g2_bits_set_s16_be(p, x) 	tb_bits_set_s16_be_impl(((tb_byte_t*)(p)), x)

// 24-bits
# 	define g2_bits_get_u24_le(p) 		tb_bits_get_u24_ne_impl(((tb_byte_t const*)(p)))
# 	define g2_bits_get_s24_le(p) 		tb_bits_get_s24_ne_impl(((tb_byte_t const*)(p)))
# 	define g2_bits_get_u24_be(p) 		tb_bits_get_u24_be_impl(((tb_byte_t const*)(p)))
# 	define g2_bits_get_s24_be(p) 		tb_bits_get_s24_be_impl(((tb_byte_t const*)(p)))

# 	define g2_bits_set_u24_le(p, x) 	tb_bits_set_u24_ne_impl(((tb_byte_t*)(p)), x)
# 	define g2_bits_set_s24_le(p, x) 	tb_bits_set_s24_ne_impl(((tb_byte_t*)(p)), x)
# 	define g2_bits_set_u24_be(p, x) 	tb_bits_set_u24_be_impl(((tb_byte_t*)(p)), x)
# 	define g2_bits_set_s24_be(p, x) 	tb_bits_set_s24_be_impl(((tb_byte_t*)(p)), x)

// 32-bits
# 	define g2_bits_get_u32_le(p) 		tb_bits_get_u32_ne_impl(((tb_byte_t const*)(p)))
# 	define g2_bits_get_s32_le(p) 		tb_bits_get_s32_ne_impl(((tb_byte_t const*)(p)))
# 	define g2_bits_get_u32_be(p) 		tb_bits_get_u32_be_impl(((tb_byte_t const*)(p)))
# 	define g2_bits_get_s32_be(p) 		tb_bits_get_s32_be_impl(((tb_byte_t const*)(p)))

# 	define g2_bits_set_u32_le(p, x) 	tb_bits_set_u32_le_impl(((tb_byte_t*)(p)), x)
# 	define g2_bits_set_s32_le(p, x) 	tb_bits_set_u32_le_impl(((tb_byte_t*)(p)), x)
# 	define g2_bits_set_u32_be(p, x) 	tb_bits_set_u32_be_impl(((tb_byte_t*)(p)), x)
# 	define g2_bits_set_s32_be(p, x) 	tb_bits_set_s32_be_impl(((tb_byte_t*)(p)), x)

// 64-bits
# 	define g2_bits_get_u64_le(p) 		tb_bits_get_u64_ne_impl(((tb_byte_t const*)(p)))
# 	define g2_bits_get_s64_le(p) 		tb_bits_get_s64_ne_impl(((tb_byte_t const*)(p)))
# 	define g2_bits_get_u64_be(p) 		tb_bits_get_u64_be_impl(((tb_byte_t const*)(p)))
# 	define g2_bits_get_s64_be(p) 		tb_bits_get_s64_be_impl(((tb_byte_t const*)(p)))

# 	define g2_bits_set_u64_le(p, x) 	tb_bits_set_u64_le_impl(((tb_byte_t*)(p)), x)
# 	define g2_bits_set_s64_le(p, x) 	tb_bits_set_u64_le_impl(((tb_byte_t*)(p)), x)
# 	define g2_bits_set_u64_be(p, x) 	tb_bits_set_u64_be_impl(((tb_byte_t*)(p)), x)
# 	define g2_bits_set_s64_be(p, x) 	tb_bits_set_s64_be_impl(((tb_byte_t*)(p)), x)

#endif /* TB_WORDS_BIGENDIAN */

#endif


