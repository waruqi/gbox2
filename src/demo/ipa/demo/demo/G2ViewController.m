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
 * @file		G2ViewController.m
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * trace
 */
#define TB_TRACE_IMPL_TAG 		"demo"

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#import "G2ViewController.h"
#import "G2View.h"

/* ///////////////////////////////////////////////////////////////////////
 * globals
 */

// context
static tb_handle_t 	g_context 	= TB_NULL;

// surface
static tb_handle_t 	g_surface 	= TB_NULL;

// painter
static tb_handle_t 	g_painter 	= TB_NULL;

// clock
static tb_hong_t 	g_bt 		= 0;
static tb_hong_t 	g_fp 		= 0;
static tb_hong_t 	g_rt 		= 0;
static tb_hong_t 	g_fps 		= 0;
static tb_bool_t 	g_pt 		= TB_TRUE;//TB_FALSE;

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
 * callbacks
 */
static tb_bool_t g2_demo_init(tb_int_t argc, tb_char_t** argv);
static tb_void_t g2_demo_exit();
static tb_void_t g2_demo_size(tb_int_t w, tb_int_t h);
static tb_void_t g2_demo_render();
static tb_void_t g2_demo_move(tb_int_t x, tb_int_t y);
static tb_void_t g2_demo_drag(tb_int_t x, tb_int_t y);
static tb_void_t g2_demo_wheeldown(tb_int_t x, tb_int_t y);
static tb_void_t g2_demo_wheelup(tb_int_t x, tb_int_t y);
static tb_void_t g2_demo_lclickdown(tb_int_t x, tb_int_t y);
static tb_void_t g2_demo_lclickup(tb_int_t x, tb_int_t y);
static tb_void_t g2_demo_rclickdown(tb_int_t x, tb_int_t y);
static tb_void_t g2_demo_rclickup(tb_int_t x, tb_int_t y);
static tb_void_t g2_demo_key(tb_int_t key);

/* ////////////////////////////////////////////////////////////////////////
 * gbox2
 */
tb_bool_t g2_demo_gbox2_init(tb_int_t argc, tb_char_t** argv)
{
	// init width & height
	tb_size_t width = [[UIScreen mainScreen] bounds].size.width;
	tb_size_t height = [[UIScreen mainScreen] bounds].size.height;
	
	// init context
#if defined(G2_CONFIG_CORE_GL)
	g_context = g2_context_init_gl(G2_DEMO_PIXFMT, width, height);
	tb_assert_and_check_return_val(g_context, TB_FALSE);
#elif defined(G2_CONFIG_CORE_SKIA)
	g_context = g2_context_init_skia(G2_DEMO_PIXFMT, TB_NULL, width, height, 0);
	tb_assert_and_check_return_val(g_context, TB_FALSE);
#else
	g_context = g2_context_init_soft(G2_DEMO_PIXFMT, TB_NULL, width, height, 0);
	tb_assert_and_check_return_val(g_context, TB_FALSE);
#endif
	
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
	
	// ok
	return TB_TRUE;
}
tb_void_t g2_demo_gbox2_exit()
{
	// exit painter
	if (g_painter) g2_exit(g_painter);
	
	// exit context
	if (g_context) g2_context_exit(g_context);
}

/* ///////////////////////////////////////////////////////////////////////
 * demo
 */
//#include "../../../arc.c"
//#include "../../../line.c"
#include "../../../rect.c"
//#include "../../../path.c"
//#include "../../../clip.c"
//#include "../../../point.c"
//#include "../../../circle.c"
//#include "../../../ellipse.c"
//#include "../../../triangle.c"

/* ///////////////////////////////////////////////////////////////////////
 * interface
 */
@interface G2ViewController ()
{
	// the thread
	tb_handle_t		thread;
	
}

// the render
@property (strong, atomic)	G2View*		render;

// is stoped?
@property (atomic)			tb_size_t	bstop;

@end

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static tb_pointer_t onRender(tb_pointer_t data)
{
	// init
	G2ViewController*	cl = TB_NULL;
	NSAutoreleasePool*	pool = TB_NULL;
	
	// init controller
	cl = (G2ViewController*)data;
	tb_assert_and_check_goto(cl, end);
	
	// init gbox2
	if (!g2_demo_gbox2_init(1, TB_NULL)) goto end;
	
	// init pool
	pool = [[NSAutoreleasePool alloc] init];
	tb_assert_and_check_goto(pool, end);
	
	// bind render
	tb_trace_impl("render: init");
	if (![cl.render bind]) goto end;

	// loop
	while (!cl.bstop)
	{
		// lock render
		if (![cl.render lock]) goto end;
		
		//glClear(GL_COLOR_BUFFER_BIT);
		
		// clear
		g2_clear(g_painter, G2_COLOR_GREEN);
		
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
		
		// draw
#if defined(G2_CONFIG_CORE_SKIA) || defined(G2_CONFIG_CORE_SOFT)
		// ...
#endif
		// render fps & rpt
		g_fp++;
		if (!g_bt) g_bt = tb_uclock();
		if ((tb_uclock() - g_bt) > 1000000)
		{
			g_fps = (1000000 * g_fp) / (tb_uclock() - g_bt);
			g_fp = 0;
			g_bt = 0;
			
			if (g_pt) tb_trace_impl("fps: %lld, rpt: %lld us", g_fps, g_rt);
		}
		
		// draw render
		[cl.render draw];

		// wait some time
		//tb_msleep(100);
	}

	// end
end:
	// exit gbox2
	g2_demo_gbox2_exit();
	
	// exit pool
	if (pool) [pool release];
	
	// exit thread
	tb_trace_impl("render: exit");
	tb_thread_return(TB_NULL);
	return TB_NULL;
}

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
@implementation G2ViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self)
	{
        // init the render
		self.render = [[G2View alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
		[self.view addSubview:self.render];
    }
    return self;
}

- (void)viewDidLoad
{
	// load view
    [super viewDidLoad];
	
	// init the thread
	self.bstop = 0;
	thread = tb_thread_init(TB_NULL, onRender, self, 0);
}

- (void)viewDidUnload
{
	// exit view
    [super viewDidUnload];
	
	// exit the thread
	self.bstop = 1;
	if (thread)
	{
		// wait
		if (!tb_thread_wait(thread, 5000))
			tb_thread_kill(thread);
		
		// exit it
		tb_thread_exit(thread);
		thread = TB_NULL;
	}
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

@end
