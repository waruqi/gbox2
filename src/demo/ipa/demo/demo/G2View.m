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
	
	// the gl width
	GLint				glWidth;
	
	// the gl height
	GLint				glHeight;
	
	// the gl frame
	GLuint				glFrame;
	
	// the gl color render
	GLuint				glRenderColor;
	
	// the gl stencil render
	GLuint				glRenderStencil;
	
	// the gl frame for msaa
	GLuint				glFrameMsaa;
	
	// the gl color render for msaa
	GLuint				glRenderColorMsaa;
	
	// the gl stencil render for mssa
	GLuint				glRenderStencilMssa;
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
	switch (G2_PIXFMT(G2_VIEW_PIXFMT))
	{
		case G2_PIXFMT_RGB565:
			glLayer.opaque = YES;
			glLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys: [NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGB565, kEAGLDrawablePropertyColorFormat, nil];
			break;
		case G2_PIXFMT_RGBA8888:
			glLayer.opaque = NO;
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
	
	// load interfaces for common
	G2_GL_INTERFACE_LOAD_S(glActiveTexture);
	G2_GL_INTERFACE_LOAD_S(glAlphaFunc);
	G2_GL_INTERFACE_LOAD_S(glBindTexture);
	G2_GL_INTERFACE_LOAD_S(glBlendFunc);
	G2_GL_INTERFACE_LOAD_S(glClear);
	G2_GL_INTERFACE_LOAD_S(glClearColor);
	G2_GL_INTERFACE_LOAD_S(glClearStencil);
	G2_GL_INTERFACE_LOAD_S(glColorMask);
	G2_GL_INTERFACE_LOAD_S(glDeleteTextures);
	G2_GL_INTERFACE_LOAD_S(glDisable);
	G2_GL_INTERFACE_LOAD_S(glDrawArrays);
	G2_GL_INTERFACE_LOAD_S(glEnable);
	G2_GL_INTERFACE_LOAD_S(glGenTextures);
	G2_GL_INTERFACE_LOAD_S(glGetString);
	G2_GL_INTERFACE_LOAD_S(glIsTexture);
	G2_GL_INTERFACE_LOAD_S(glPixelStorei);
	G2_GL_INTERFACE_LOAD_S(glStencilFunc);
	G2_GL_INTERFACE_LOAD_S(glStencilMask);
	G2_GL_INTERFACE_LOAD_S(glStencilOp);
	G2_GL_INTERFACE_LOAD_S(glTexImage2D);
	G2_GL_INTERFACE_LOAD_S(glTexParameterf);
	G2_GL_INTERFACE_LOAD_S(glTexParameteri);
	G2_GL_INTERFACE_LOAD_S(glViewport);

	// load interfaces for gl 1.x
	G2_GL_INTERFACE_LOAD_S(glColor4f);
	G2_GL_INTERFACE_LOAD_S(glColorPointer);
	G2_GL_INTERFACE_LOAD_S(glDisableClientState);
	G2_GL_INTERFACE_LOAD_S(glEnableClientState);
	G2_GL_INTERFACE_LOAD_S(glLoadIdentity);
	G2_GL_INTERFACE_LOAD_S(glLoadMatrixf);
	G2_GL_INTERFACE_LOAD_S(glMatrixMode);
	G2_GL_INTERFACE_LOAD_S(glMultMatrixf);
# 	ifdef G2_CONFIG_CORE_GLES
	G2_GL_INTERFACE_LOAD_S(glOrthof);
# 	else
	G2_GL_INTERFACE_LOAD_S(glOrtho);
# 	endif
	G2_GL_INTERFACE_LOAD_S(glPopMatrix);
	G2_GL_INTERFACE_LOAD_S(glPushMatrix);
	G2_GL_INTERFACE_LOAD_S(glRotatef);
	G2_GL_INTERFACE_LOAD_S(glScalef);
	G2_GL_INTERFACE_LOAD_S(glTexCoordPointer);
	G2_GL_INTERFACE_LOAD_S(glTexEnvi);
	G2_GL_INTERFACE_LOAD_S(glTranslatef);
	G2_GL_INTERFACE_LOAD_S(glVertexPointer);

	// load interfaces for gl >= 2.0
#if !G2_VIEW_GL_VERSION || G2_VIEW_GL_VERSION >= 0x20
	G2_GL_INTERFACE_LOAD_S(glAttachShader);
	G2_GL_INTERFACE_LOAD_S(glCompileShader);
	G2_GL_INTERFACE_LOAD_S(glCreateProgram);
	G2_GL_INTERFACE_LOAD_S(glCreateShader);
	G2_GL_INTERFACE_LOAD_S(glDeleteProgram);
	G2_GL_INTERFACE_LOAD_S(glDeleteShader);
	G2_GL_INTERFACE_LOAD_S(glDisableVertexAttribArray);
	G2_GL_INTERFACE_LOAD_S(glEnableVertexAttribArray);
	G2_GL_INTERFACE_LOAD_S(glGetAttribLocation);
	G2_GL_INTERFACE_LOAD_S(glGetProgramiv);
	G2_GL_INTERFACE_LOAD_S(glGetProgramInfoLog);
	G2_GL_INTERFACE_LOAD_S(glGetShaderiv);
	G2_GL_INTERFACE_LOAD_S(glGetShaderInfoLog);
	G2_GL_INTERFACE_LOAD_S(glGetUniformLocation);
	G2_GL_INTERFACE_LOAD_S(glLinkProgram);
	G2_GL_INTERFACE_LOAD_S(glShaderSource);
	G2_GL_INTERFACE_LOAD_S(glUniform1i);
	G2_GL_INTERFACE_LOAD_S(glUniformMatrix4fv);
	G2_GL_INTERFACE_LOAD_S(glUseProgram);
	G2_GL_INTERFACE_LOAD_S(glVertexAttrib4f);
	G2_GL_INTERFACE_LOAD_S(glVertexAttribPointer);
#endif

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
	// init frame
	glGenFramebuffers(1, &glFrame);
	glBindFramebuffer(GL_FRAMEBUFFER, glFrame);
	
	// add color render to frame
	glGenRenderbuffers(1, &glRenderColor);
	glBindRenderbuffer(GL_RENDERBUFFER, glRenderColor);
	[glContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:(id<EAGLDrawable>)self.layer];
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, glRenderColor);
	
	// check
	tb_assert_and_check_return_val(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, TB_FALSE);
	
	// get width & height
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &glWidth);
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &glHeight);
	
	// add stencil render to frame
	glGenRenderbuffers(1, &glRenderStencil);
	glBindRenderbuffer(GL_RENDERBUFFER, glRenderStencil);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX8, glWidth, glHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, glRenderStencil);
	
	// check
	tb_assert_and_check_return_val(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, TB_FALSE);
	
	// init mssa frame
	glGenFramebuffers(1, &glFrameMsaa);
    glBindFramebuffer(GL_FRAMEBUFFER, glFrameMsaa);
	
	// add color render to the mssa frame
    glGenRenderbuffers(1, &glRenderColorMsaa);
    glBindRenderbuffer(GL_RENDERBUFFER, glRenderColorMsaa);
    glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, 4, GL_RGBA8_OES, glWidth, glHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, glRenderColorMsaa);
	
	// check
	tb_assert_and_check_return_val(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, TB_FALSE);
	
	// add stencil render to the mssa frame
	glGenRenderbuffers(1, &glRenderStencilMssa);
	glBindRenderbuffer(GL_RENDERBUFFER, glRenderStencilMssa);
	glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, 4, GL_STENCIL_INDEX8, glWidth, glHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, glRenderStencilMssa);
	
	// check
	tb_assert_and_check_return_val(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, TB_FALSE);
	
	// ok
	return TB_TRUE;
}
- (tb_void_t)glFrameExit
{
	// free frame
	if (glFrame) glDeleteFramebuffers(1, &glFrame);
	glFrame = 0;
	
	// free color render
	if (glRenderColor) glDeleteRenderbuffers(1, &glRenderColor);
	glRenderColor = 0;
	
	// free stencil render
	if (glRenderStencil) glDeleteRenderbuffers(1, &glRenderStencil);
	glRenderStencil = 0;
	
	// free frame for mssa
	if (glFrameMsaa) glDeleteFramebuffers(1, &glFrameMsaa);
	glFrameMsaa = 0;
	
	// free color render for mssa
	if (glRenderColorMsaa) glDeleteRenderbuffers(1, &glRenderColorMsaa);
	glRenderColorMsaa = 0;
	
	// free stencil render for mssa
	if (glRenderStencilMssa) glDeleteRenderbuffers(1, &glRenderStencilMssa);
	glRenderStencilMssa = 0;
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
	if (g2_quality() > G2_QUALITY_LOW)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, glFrameMsaa);
		glBindRenderbuffer(GL_RENDERBUFFER, glRenderColorMsaa);
	}
	else glBindFramebuffer(GL_FRAMEBUFFER, glFrame);
	
	// ok
	return TB_TRUE;
}
- (tb_void_t)draw
{
	// bind render
	if (g2_quality() > G2_QUALITY_LOW)
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER_APPLE, glFrameMsaa);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER_APPLE, glFrame);
		glResolveMultisampleFramebufferAPPLE();
		glBindFramebuffer(GL_FRAMEBUFFER, glFrame);
		glBindRenderbuffer(GL_RENDERBUFFER, glRenderColor);
	}
	else glBindRenderbuffer(GL_RENDERBUFFER, glRenderColor);
	
	// render
	[glContext presentRenderbuffer:GL_RENDERBUFFER];
}

@end
