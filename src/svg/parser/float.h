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
 * @file		float.h
 *
 */
#ifndef G2_SVG_PARSER_FLOAT_H
#define G2_SVG_PARSER_FLOAT_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * inlines
 */

// e.g. -3.1415926in
static __tb_inline__ tb_char_t const* g2_svg_parser_float(tb_char_t const* p, g2_float_t* value)
{
	// skip space
	while (tb_isspace(*p)) p++;

	// has sign?
	tb_long_t sign = 0;
	if (*p == '-') 
	{
		sign = 1;
		p++;
	}

	// skip '0'
	while (*p == '0') p++;

	// compute double: lhs.rhs
	tb_float_t 	res = 0;
	tb_long_t 	dec = 0;
	tb_uint32_t lhs = 0;
	tb_float_t 	rhs = 0.;
	tb_long_t 	zeros = 0;
	tb_int8_t 	decimals[256];
	tb_int8_t* 	d = decimals;
	tb_int8_t* 	e = decimals + 256;
	while (*p)
	{
		tb_char_t ch = *p;

		// is the part of decimal?
		if (ch == '.')
		{
			if (!dec) 
			{
				dec = 1;
				p++;
				continue ;
			}
			else break;
		}

		// parse integer & decimal
		if (tb_isdigit10(ch))
		{
			// save decimals
			if (dec) 
			{
				if (d < e)
				{
					if (ch != '0')
					{
						// fill '0'
						while (zeros--) *d++ = 0;
						zeros = 0;

						// save decimal
						*d++ = ch - '0';
					}
					else zeros++;
				}
			}
			else lhs = lhs * 10 + (ch - '0');
		}
		else break;
	
		p++;
	}

	tb_assert(d <= decimals + 256);

	// compute decimal
	while (d-- > decimals) rhs = (rhs + *d) / 10;

	// merge 
	res = (sign? ((tb_float_t)lhs + rhs) * -1. : ((tb_float_t)lhs + rhs));

	/* unit
	 *
	 * "1pt" equals "1.25px"
	 * "1pc" equals "15px"
	 * "1mm" would be "3.543307px"
	 * "1cm" equals "35.43307px"
	 * "1in" equals "90px"
	 */
	if (p[0] == 'p' && p[1] == 't')
	{
		res *= 1.25f;
		p += 2;
	}
	else if (p[0] == 'p' && p[1] == 'c')
	{
		res *= 15;	
		p += 2;
	}
	else if (p[0] == 'm' && p[1] == 'm')
	{
		res *= 3.543307f;
		p += 2;
	}
	else if (p[0] == 'c' && p[1] == 'm')
	{
		res *= 35.43307f;
		p += 2;
	}
	else if (p[0] == 'i' && p[1] == 'n')
	{
		res *= 90;
		p += 2;
	}
	else if (p[0] == 'p' && p[1] == 'x')
		p += 2;

	// value
	if (value) *value = tb_float_to_g2(res);

	// ok
	return p;
}
static __tb_inline__ tb_char_t const* g2_svg_parser_float_skip(tb_char_t const* p)
{
	// skip sign
	if (*p == '-') p++;

	// skip '0'
	while (*p == '0') p++;
	
	// skip float
	tb_size_t bdecimal = 0;
	while (*p)
	{
		// is decimal?
		if (*p == '.')
		{
			if (!bdecimal) 
			{
				bdecimal = 1;
				p++;
				continue ;
			}
			else break;
		}

		// skip digit
		if (!tb_isdigit(*p)) break;

		// next
		p++;
	}

	// ok
	return p;
}


#endif


