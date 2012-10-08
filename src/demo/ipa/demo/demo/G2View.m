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
 * @file		G2AView.m
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#import "G2View.h"
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGLDrawable.h>
#include "gbox2/gbox2.h"

/* //////////////////////////////////////////////////////////////////////////
 * interfaces
 */
@interface G2View () 
{
	// the gl version
	tb_byte_t			glVersion;
	
	// the gl context
	EAGLContext*		glContext;
	
	// the gl frame
	GLuint				glFrame;
	
	// the gl width
	GLint				glWidth;
	
	// the gl height
	GLint				glHeight;
	
	// the gl render
	GLuint				glRender;
}

// the gl init & exit
- (tb_bool_t)	glInit;
- (tb_void_t)	glExit;

// the gl frame init & exit
- (tb_bool_t)	glFrameInit;
- (tb_void_t)	glFrameExit;

@end

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
@implementation G2View

// class
+ (Class) layerClass
{
	return [CAEAGLLayer class];
}

- (void)dealloc
{
	// exit gl
	[self glExit];
	
	// free it
    [super dealloc];
}

- (id)initWithFrame:(CGRect)frame
{
	if (self = [super initWithFrame:frame]) 
	{
		// init gl
		if (![self glInit]) return nil;
	} 
    return self;
}

// gl init & exit
- (tb_bool_t) glInit
{
	// check
	tb_check_return_val(!glContext, TB_TRUE);
	
	// init layer
	CAEAGLLayer* glLayer = (CAEAGLLayer*) self.layer;
	glLayer.opaque = YES;
	switch (G2_PIXFMT(G2_VIEW_PIXFMT))
	{
		case G2_PIXFMT_RGB565:
			glLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys: [NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGB565, kEAGLDrawablePropertyColorFormat, nil];
			break;
		case G2_PIXFMT_ARGB8888:
			glLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys: [NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
			break;
		default:
			break;
	}
	
	
	// retina?
	if ([UIScreen instancesRespondToSelector:@selector(currentMode)] && CGSizeEqualToSize(CGSizeMake(640, 960), [[UIScreen mainScreen] currentMode].size))
	{
		self.contentScaleFactor = 2.0f;
		glLayer.contentsScale = 2.0f;
	}
	
	// init gl context
	if (G2_VIEW_GL_VERSION >= 0x20 || !G2_VIEW_GL_VERSION)
	{
		glVersion = 0x20;
		glContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
	}
	if (!glContext) 
	{
		glContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
		glVersion = 0x19;
	}
	tb_assert_and_check_return_val(glContext, TB_FALSE);
	
	// bind context
    [EAGLContext setCurrentContext:glContext];
	
	// init gl frame
	if (![self glFrameInit]) return TB_FALSE;
	
	// ok
	return TB_TRUE;
}

- (tb_void_t) glExit
{
	// exit gl frame
	[self glFrameExit];
	
	// bind gl context: null
    if ([EAGLContext currentContext] == glContext)
        [EAGLContext setCurrentContext:nil];
	
	// exit gl context
	glContext = nil;
}

// gl frame init & exit
- (tb_bool_t)glFrameInit
{
	// add frame & render
	glGenFramebuffersOES(1, &glFrame);
	glGenRenderbuffersOES(1, &glRender);
	
	// bind frame & render
	glBindFramebufferOES(GL_FRAMEBUFFER_OES, glFrame);
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, glRender);
	
	// attach render to layer
	[glContext renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:(id<EAGLDrawable>)self.layer];
	glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, glRender);
	
	// get width & height
	glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &glWidth);
	glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &glHeight);
	
	// check
	tb_check_return_val(glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES) == GL_FRAMEBUFFER_COMPLETE_OES, TB_FALSE);
	
	// ok
	return TB_TRUE;
}
- (tb_void_t)glFrameExit
{
	// free frame
	if (glFrame) glDeleteFramebuffersOES(1, &glFrame);
	glFrame = 0;
	
	// free render
	if (glRender) glDeleteRenderbuffersOES(1, &glRender);
	glRender = 0;
}
- (tb_byte_t)bind
{
	// check
	tb_assert_and_check_return_val(glContext, 0);
	
	// bind context
    [EAGLContext setCurrentContext:glContext];
	
	// ok
	return glVersion;
}
- (tb_bool_t)lock
{
	// check
	tb_assert_and_check_return_val(glFrame, TB_FALSE);
	
	// bind frame
	glBindFramebufferOES(GL_FRAMEBUFFER_OES, glFrame);
	
	// ok
	return TB_TRUE;
}
- (tb_void_t)draw
{
	// bind render
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, glRender);
	
	// render
	[glContext presentRenderbuffer:GL_RENDERBUFFER_OES];
}

@end
