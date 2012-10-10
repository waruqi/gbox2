/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "demo.h"

/* ////////////////////////////////////////////////////////////////////////
 * macros
 */

// pixfmt
#define G2_DEMO_PIXFMT 			(G2_PIXFMT_ARGB8888 | G2_PIXFMT_NENDIAN)
//#define G2_DEMO_PIXFMT 			(G2_PIXFMT_RGB565 | G2_PIXFMT_NENDIAN)

/* ////////////////////////////////////////////////////////////////////////
 * globals
 */

// context
static tb_handle_t 	g_context 	= TB_NULL;

// surface
static tb_handle_t 	g_surface 	= TB_NULL;

// painter
static tb_handle_t 	g_painter 	= TB_NULL;

// library
static tb_handle_t 	g_library 	= TB_NULL;

// clock
static tb_hong_t 	g_bt 		= 0;
static tb_hong_t 	g_fp 		= 0;
static tb_hong_t 	g_rt 		= 0;
static tb_hong_t 	g_fps 		= 0;

// position
static tb_long_t 	g_x0 		= 0;
static tb_long_t 	g_y0 		= 0;
static tb_long_t 	g_dx 		= 0;
static tb_long_t 	g_dy 		= 0;
static tb_long_t 	g_x 		= 0;
static tb_long_t 	g_y 		= 0;
static tb_float_t 	g_an 		= 0.;
static tb_bool_t 	g_bm 		= TB_FALSE;
static g2_matrix_t 	g_mx;

/* ////////////////////////////////////////////////////////////////////////
 * demo 
 */
//#include "../../../svg.c"
//#include "../../../arc.c"
//#include "../../../line.c"
//#include "../../../rect.c"
#include "../../../path.c"
//#include "../../../clip.c"
//#include "../../../point.c"
//#include "../../../circle.c"
//#include "../../../ellipse.c"
//#include "../../../triangle.c"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */

tb_bool_t g2_demo_gl_init(tb_byte_t version)
{
	// load interfaces for common
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
#ifndef G2_CONFIG_CORE_GLES
	G2_GL_INTERFACE_LOAD_S(glTexImage1D);
#endif
	G2_GL_INTERFACE_LOAD_S(glTexImage2D);
	G2_GL_INTERFACE_LOAD_S(glTexParameterf);
	G2_GL_INTERFACE_LOAD_S(glTexParameteri);
	G2_GL_INTERFACE_LOAD_S(glViewport);

	// load interfaces for gl 1.x
	G2_GL_INTERFACE_LOAD_S(glColor4f);
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
#if !G2_CONFIG_GL_VERSION || G2_CONFIG_GL_VERSION >= 0x20
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
	G2_GL_INTERFACE_LOAD_S(glUniformMatrix4fv);
	G2_GL_INTERFACE_LOAD_S(glUseProgram);
	G2_GL_INTERFACE_LOAD_S(glVertexAttrib4f);
	G2_GL_INTERFACE_LOAD_S(glVertexAttribPointer);
#endif

	// init width & height
	tb_size_t width = 0;
	tb_size_t height = 0;
	
	// init context
	g_context = g2_context_init_gl(G2_DEMO_PIXFMT, width, height, version);
	tb_assert_and_check_return_val(g_context, TB_FALSE);
	
	// init surface
	g_surface = g2_context_surface(g_context);
	tb_assert_and_check_return_val(g_surface, TB_FALSE);
	
	// init painter
	g_painter = g2_init(g_context);
	tb_assert_and_check_return_val(g_painter, TB_FALSE);
	
	// init position
	g_x0 		= width >> 1;
	g_y0 		= height >> 1;
	g_dx 		= width >> 2;
	g_dy 		= height >> 2;
	g_x 		= g_dx;
	g_y 		= g_dy;
	
	// init matrix
	g2_matrix_init_translate(&g_mx, g2_long_to_float(g_x0), g2_long_to_float(g_y0));	
			
	// init args
	tb_char_t const* argv[] =
	{
		TB_NULL
	,	"/mnt/sdcard/logo.jpg"
//	,	"/mnt/sdcard/tiger.svg"
//	,	"/mnt/sdcard/tiger2.svg"
	};
	tb_int_t argc = tb_arrayn(argv);
	
	// init demo
	return g2_demo_init(argc, argv);
}
tb_void_t g2_demo_gl_exit()
{	
	// exit demo
	g2_demo_exit();

	// exit painter
	if (g_painter) g2_exit(g_painter);
	
	// exit context
	if (g_context) g2_context_exit(g_context);
}
tb_void_t g2_demo_gl_draw()
{	
	// clear
	g2_clear(g_painter, G2_COLOR_BLACK);
	
	// matrix
	if (g_bm)
	{
		g2_save(g_painter, G2_SAVE_MODE_MATRIX);
		g2_matrix_set(g_painter, &g_mx);
	}
	
	// start clock
	g_rt = tb_uclock();

	// render
	g2_demo_render();
	
	// stop clock
	g_rt = tb_uclock() - g_rt;
	
	// load
	if (g_bm) g2_load(g_painter);
	
	// render fps & rpt
	g_fp++;
	if (!g_bt) g_bt = tb_uclock();
	if ((tb_uclock() - g_bt) > 1000000)
	{
		g_fps = (1000000 * g_fp) / (tb_uclock() - g_bt);
		g_fp = 0;
		g_bt = 0;
	}
}
tb_void_t g2_demo_gl_size(tb_size_t width, tb_size_t height)
{

}
tb_void_t g2_demo_gl_move(tb_long_t x, tb_long_t y)
{
	g_x = x;
	g_y = y;
	
	g_dx = x > g_x0? (x - g_x0) << 1 : (g_x0 - x) << 1;
	g_dy = y > g_y0? (y - g_y0) << 1 : (g_y0 - y) << 1;
	
	g2_float_t x0 = g2_long_to_float(g_x0);
	g2_float_t y0 = g2_long_to_float(g_y0);
	g2_float_t dx = g2_long_to_float(g_dx);
	g2_float_t dy = g2_long_to_float(g_dy);
	g2_float_t dw = g2_long_to_float(g2_bitmap_width(g_surface));
	g2_float_t dh = g2_long_to_float(g2_bitmap_height(g_surface));
	
	g2_float_t an = 0;
	if (y == g_y0) an = 0;
	else if (x == g_x0) an = g2_long_to_float(90);
	else an = g2_div(g2_atan(g2_div(dy, dx)) * 180, G2_PI);
	if (y < g_y0 && x < g_x0) an = g2_long_to_float(180) - an;
	if (y > g_y0 && x < g_x0) an += g2_long_to_float(180);
	if (y > g_y0 && x > g_x0) an = g2_long_to_float(360) - an;
	g_an = -an;
	
	dx = g2_lsh(dx, 2);
	dy = g2_lsh(dy, 2);
	
	g2_matrix_init_translate(&g_mx, x0, y0);
	g2_matrix_scale(&g_mx, g2_div(dx, dw), g2_div(dy, dh));
	g2_matrix_rotate(&g_mx, g_an);

	g2_demo_move(x, y);
}
tb_size_t g2_demo_gl_tfps()
{
	return (tb_size_t)g_fps;
}
tb_size_t g2_demo_gl_trpt()
{
	return (tb_size_t)g_rt;
}
tb_void_t g2_demo_gl_tkey(tb_size_t key)
{
	tb_trace_impl("key: %c", key);
	switch (key)
	{
		case 'q':
			g2_quality_set((g2_quality() + 1) % 3);
			break;
		case 'm':
			g_bm = g_bm? TB_FALSE : TB_TRUE;
			break;
		default:
			break;
	}
	
	g2_demo_key(key);
}

