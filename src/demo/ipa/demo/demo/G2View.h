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
 * @file		G2View.h
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */

#import <UIKit/UIKit.h>
#include "gbox2/gbox2.h"

/* //////////////////////////////////////////////////////////////////////////
 * macros
 */

// pixfmt
#define G2_VIEW_PIXFMT 			(G2_PIXFMT_ARGB8888 | G2_PIXFMT_NENDIAN)
//#define G2_VIEW_PIXFMT 			(G2_PIXFMT_RGB565 | G2_PIXFMT_NENDIAN)

// version
#define G2_VIEW_GL_VERSION		(0x19)

/* ///////////////////////////////////////////////////////////////////////
 * interface
 */

@interface G2View : UIView

- (tb_byte_t)	bind;
- (tb_bool_t)	lock;
- (tb_void_t)	draw;

@end
