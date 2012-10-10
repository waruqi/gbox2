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
 * macros
 */
#define G2_DEMO_PIXFMT			G2_VIEW_PIXFMT

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
static tb_bool_t g2_demo_init(tb_int_t argc, tb_char_t const** argv);
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
tb_bool_t g2_demo_gbox2_init(tb_int_t argc, tb_char_t const** argv, tb_byte_t version)
{
	// init width & height
	tb_size_t width = [[UIScreen mainScreen] bounds].size.width;
	tb_size_t height = [[UIScreen mainScreen] bounds].size.height;
	
	// init context
#if defined(G2_CONFIG_CORE_GL) || defined(G2_CONFIG_CORE_GLES)
	g_context = g2_context_init_gl(G2_VIEW_PIXFMT, width, height, version);
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
 * interface
 */
@interface G2ViewController ()
{
	// the thread
	tb_handle_t				thread;
	
	// the timer	
	NSTimer*				timer;
	
	// the info
	UILabel*				info;
	
	// the key
	UIButton*				qKey;
	UIButton*				mKey;
	UIButton*				pKey;
	UIButton*				wKey;
	UIButton*				fKey;
	UIButton*				sKey;
	
	// the orientaion
	UIInterfaceOrientation	orientaion;
}

// the render
@property (strong, atomic)	G2View*		render;

// is stoped?
@property (atomic)			tb_size_t	stoped;

// recognizer
- (void)onMove:(UIPanGestureRecognizer *)recognizer;
- (void)onSingle:(UITapGestureRecognizer *)recognizer;
- (void)onDouble:(UITapGestureRecognizer *)recognizer;

// key
- (void)onKey:(id)sender;

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
	
	// init pool
	pool = [[NSAutoreleasePool alloc] init];
	tb_assert_and_check_goto(pool, end);
	
	// init args
	tb_char_t const* argv[] =
	{
		TB_NULL
	,	[[[NSBundle mainBundle] pathForResource:@"logo" ofType:@"jpg"] UTF8String]
//	,	[[[NSBundle mainBundle] pathForResource:@"tiger" ofType:@"svg"] UTF8String]
//	,	[[[NSBundle mainBundle] pathForResource:@"tiger2" ofType:@"svg"] UTF8String]
//	,	[[[NSBundle mainBundle] pathForResource:@"lineargradient1" ofType:@"svg"] UTF8String]
	};
	tb_int_t argc = tb_arrayn(argv);
	
	// bind render
	tb_trace_impl("render: init");
	tb_byte_t version = [cl.render bind];
	tb_assert_and_check_goto(version, end);
	
	// init gbox2
	if (!g2_demo_gbox2_init(argc, argv, version)) goto end;
	
	// init demo
	if (!g2_demo_init(argc, argv)) goto end;
		
	// loop
	while (!cl.stoped)
	{
		// lock render
		if (![cl.render lock]) goto end;
		
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
		
		// draw render
		[cl.render draw];
	}

	// end
end:
	// exit demo
	g2_demo_exit();
	
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

- (void)dealloc
{
	// exit info
	[info release];
	
	// exit key
	[qKey release];
	[mKey release];
	[wKey release];
	[pKey release];
	[fKey release];
	[sKey release];
	
	// exit render
	[self.render release];
	
	// free it
    [super dealloc];
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self)
	{
		// screen bounds
		CGRect screenBounds = [[UIScreen mainScreen] bounds];
		
        // init the render
		self.render = [[G2View alloc] initWithFrame:screenBounds];
		tb_assert_and_check_return_val(self.render, nil);
		[self.view addSubview:self.render];
		
		// init single tap
		UITapGestureRecognizer* singleTap = [[UITapGestureRecognizer alloc] initWithTarget: self action: @selector(onSingle:)];
		singleTap.numberOfTouchesRequired = 1;
		singleTap.numberOfTapsRequired = 1;
		[self.view addGestureRecognizer:singleTap];
		[singleTap release];
		
		// init double tap
		UITapGestureRecognizer* doubleTap = [[UITapGestureRecognizer alloc] initWithTarget: self action: @selector(onDouble:)];
		doubleTap.numberOfTouchesRequired = 1;
		doubleTap.numberOfTapsRequired = 2;
		[self.view addGestureRecognizer:doubleTap];
		[singleTap requireGestureRecognizerToFail: doubleTap];
		[doubleTap release];
		
		// init move pan
		UIPanGestureRecognizer* movePan = [[UIPanGestureRecognizer alloc] initWithTarget:self action: @selector(onMove:)];
		[movePan setMinimumNumberOfTouches:1];
		[movePan setMaximumNumberOfTouches:1];
		[self.view addGestureRecognizer:movePan];
		[movePan release];
		
		// init info
		CGRect infoBounds = CGRectMake(screenBounds.origin.x + 30, screenBounds.origin.y + 30, 200, 30);
		info = [[UILabel alloc] initWithFrame:infoBounds];
		[info setTextColor:[UIColor blueColor]];
		[info setBackgroundColor:[UIColor yellowColor]];
		[self.view addSubview:info];
		
		// init key
		CGRect qKeyBounds = CGRectMake(screenBounds.origin.x + 30, screenBounds.origin.y + screenBounds.size.height - 40, 30, 30);
		qKey = [[UIButton alloc] initWithFrame:qKeyBounds];
		[qKey setTitle:@"q" forState:UIControlStateNormal];
		[qKey setTitleColor:[UIColor blueColor] forState:UIControlStateNormal];
		[qKey setBackgroundColor:[UIColor yellowColor]];
		[qKey addTarget:self action:@selector(onKey:) forControlEvents:UIControlEventTouchDown];
		[self.view addSubview:qKey];
		
		CGRect mKeyBounds = CGRectMake(qKeyBounds.origin.x + qKeyBounds.size.width + 10, qKeyBounds.origin.y, 30, 30);
		mKey = [[UIButton alloc] initWithFrame:mKeyBounds];
		[mKey setTitle:@"m" forState:UIControlStateNormal];
		[mKey setTitleColor:[UIColor blueColor] forState:UIControlStateNormal];
		[mKey setBackgroundColor:[UIColor yellowColor]];
		[mKey addTarget:self action:@selector(onKey:) forControlEvents:UIControlEventTouchDown];
		[self.view addSubview:mKey];
		
		CGRect wKeyBounds = CGRectMake(mKeyBounds.origin.x + mKeyBounds.size.width + 10, mKeyBounds.origin.y, 30, 30);
		wKey = [[UIButton alloc] initWithFrame:wKeyBounds];
		[wKey setTitle:@"w" forState:UIControlStateNormal];
		[wKey setTitleColor:[UIColor blueColor] forState:UIControlStateNormal];
		[wKey setBackgroundColor:[UIColor yellowColor]];
		[wKey addTarget:self action:@selector(onKey:) forControlEvents:UIControlEventTouchDown];
		[self.view addSubview:wKey];
		
		CGRect pKeyBounds = CGRectMake(wKeyBounds.origin.x + wKeyBounds.size.width + 10, wKeyBounds.origin.y, 30, 30);
		pKey = [[UIButton alloc] initWithFrame:pKeyBounds];
		[pKey setTitle:@"p" forState:UIControlStateNormal];
		[pKey setTitleColor:[UIColor blueColor] forState:UIControlStateNormal];
		[pKey setBackgroundColor:[UIColor yellowColor]];
		[pKey addTarget:self action:@selector(onKey:) forControlEvents:UIControlEventTouchDown];
		[self.view addSubview:pKey];
		
		CGRect fKeyBounds = CGRectMake(pKeyBounds.origin.x + pKeyBounds.size.width + 10, pKeyBounds.origin.y, 30, 30);
		fKey = [[UIButton alloc] initWithFrame:fKeyBounds];
		[fKey setTitle:@"f" forState:UIControlStateNormal];
		[fKey setTitleColor:[UIColor blueColor] forState:UIControlStateNormal];
		[fKey setBackgroundColor:[UIColor yellowColor]];
		[fKey addTarget:self action:@selector(onKey:) forControlEvents:UIControlEventTouchDown];
		[self.view addSubview:fKey];
		
		CGRect sKeyBounds = CGRectMake(fKeyBounds.origin.x + fKeyBounds.size.width + 10, fKeyBounds.origin.y, 30, 30);
		sKey = [[UIButton alloc] initWithFrame:sKeyBounds];
		[sKey setTitle:@"s" forState:UIControlStateNormal];
		[sKey setTitleColor:[UIColor blueColor] forState:UIControlStateNormal];
		[sKey setBackgroundColor:[UIColor yellowColor]];
		[sKey addTarget:self action:@selector(onKey:) forControlEvents:UIControlEventTouchDown];
		[self.view addSubview:sKey];
    }
    return self;
}

- (void)viewDidLoad
{
	// load view
    [super viewDidLoad];
	
	// load render
	if (self.render)
	{
		// init the thread
		self.stoped = 0;
		thread = tb_thread_init(TB_NULL, onRender, self, 0);
	
		// init timer
		timer = [NSTimer scheduledTimerWithTimeInterval:(NSTimeInterval)1 target:self selector:@selector(onInfo) userInfo:nil repeats:TRUE];
	}
}

- (void)viewDidUnload
{
	// exit timer
	if (timer) [timer invalidate];
	timer = nil;
	
	// exit the thread
	self.stoped = 1;
	if (thread)
	{
		// wait
		if (!tb_thread_wait(thread, 5000))
			tb_thread_kill(thread);
		
		// exit it
		tb_thread_exit(thread);
		thread = TB_NULL;
	}
	
	// exit view
    [super viewDidUnload];
}
- (void)onMove:(UIPanGestureRecognizer *)recognizer
{
	CGPoint pt = [recognizer locationInView:self.view];
//	tb_trace_impl("move: %f %f", pt.x, pt.y);
	tb_check_return(!tb_isnanf(pt.x) && !tb_isnanf(pt.y));
	
	if (	orientaion == UIInterfaceOrientationLandscapeRight
		||	orientaion == UIInterfaceOrientationLandscapeLeft)
	{
		CGRect screenBounds = [[UIScreen mainScreen] bounds];
		pt.x *= screenBounds.size.width / screenBounds.size.height;
		pt.y *= screenBounds.size.height / screenBounds.size.width;
	}
	
	tb_int_t x = pt.x;
	tb_int_t y = pt.y;
	
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
- (void)onSingle:(UITapGestureRecognizer *)recognizer
{
	CGPoint pt = [recognizer locationInView:self.view];
	tb_trace_impl("single: %f %f", pt.x, pt.y);
}
- (void)onDouble:(UITapGestureRecognizer *)recognizer
{
	CGPoint pt = [recognizer locationInView:self.view];
	tb_trace_impl("double: %f %f", pt.x, pt.y);
	
	info.hidden = !info.hidden;
	qKey.hidden = !qKey.hidden;
	mKey.hidden = !mKey.hidden;
	pKey.hidden = !pKey.hidden;
	wKey.hidden = !wKey.hidden;
	fKey.hidden = !fKey.hidden;
	sKey.hidden = !sKey.hidden;
}
- (void)onKey:(id)sender
{
	UIButton* btn = (UIButton*)sender;
	tb_assert_and_check_return(btn);
	
	tb_char_t key = [[btn titleForState:UIControlEventTouchDown] UTF8String][0];
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

- (void)onInfo
{
	if (!info.hidden)
		[info setText:[NSString stringWithFormat:@"   fps: %lld, rpt: %lld us", g_fps, g_rt]];
}
- (void) willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
	if (	toInterfaceOrientation == UIInterfaceOrientationLandscapeRight
		||	toInterfaceOrientation == UIInterfaceOrientationLandscapeLeft)
	{
		CGRect screenBounds = [[UIScreen mainScreen] bounds];
		CGRect viewBounds = CGRectMake(screenBounds.origin.y, screenBounds.origin.x, screenBounds.size.height, screenBounds.size.width);
		CGRect infoBounds = CGRectMake(screenBounds.origin.y + 30, screenBounds.origin.x + 30, 200, 30);
		CGRect qKeyBounds = CGRectMake(screenBounds.origin.y + 30, screenBounds.origin.x + screenBounds.size.width - 40, 30, 30);
		CGRect mKeyBounds = CGRectMake(qKeyBounds.origin.x + qKeyBounds.size.width + 10, qKeyBounds.origin.y, 30, 30);
		CGRect wKeyBounds = CGRectMake(mKeyBounds.origin.x + mKeyBounds.size.width + 10, mKeyBounds.origin.y, 30, 30);
		CGRect pKeyBounds = CGRectMake(wKeyBounds.origin.x + wKeyBounds.size.width + 10, wKeyBounds.origin.y, 30, 30);
		CGRect fKeyBounds = CGRectMake(pKeyBounds.origin.x + pKeyBounds.size.width + 10, pKeyBounds.origin.y, 30, 30);
		CGRect sKeyBounds = CGRectMake(fKeyBounds.origin.x + fKeyBounds.size.width + 10, fKeyBounds.origin.y, 30, 30);
		self.view.frame = viewBounds;
		self.render.frame = viewBounds;
		info.frame = infoBounds;
		qKey.frame = qKeyBounds;
		mKey.frame = mKeyBounds;
		wKey.frame = wKeyBounds;
		pKey.frame = pKeyBounds;
		fKey.frame = fKeyBounds;
		sKey.frame = sKeyBounds;
	}
	else 
	{
		CGRect screenBounds = [[UIScreen mainScreen] bounds];
		CGRect viewBounds = screenBounds;
		CGRect infoBounds = CGRectMake(screenBounds.origin.x + 30, screenBounds.origin.y + 30, 200, 30);
		CGRect qKeyBounds = CGRectMake(screenBounds.origin.x + 30, screenBounds.origin.y + screenBounds.size.height - 40, 30, 30);
		CGRect mKeyBounds = CGRectMake(qKeyBounds.origin.x + qKeyBounds.size.width + 10, qKeyBounds.origin.y, 30, 30);
		CGRect wKeyBounds = CGRectMake(mKeyBounds.origin.x + mKeyBounds.size.width + 10, mKeyBounds.origin.y, 30, 30);
		CGRect pKeyBounds = CGRectMake(wKeyBounds.origin.x + wKeyBounds.size.width + 10, wKeyBounds.origin.y, 30, 30);
		CGRect fKeyBounds = CGRectMake(pKeyBounds.origin.x + pKeyBounds.size.width + 10, pKeyBounds.origin.y, 30, 30);
		CGRect sKeyBounds = CGRectMake(fKeyBounds.origin.x + fKeyBounds.size.width + 10, fKeyBounds.origin.y, 30, 30);
		self.view.frame = viewBounds;
		self.render.frame = viewBounds;
		info.frame = infoBounds;
		qKey.frame = qKeyBounds;
		mKey.frame = mKeyBounds;
		wKey.frame = wKeyBounds;
		pKey.frame = pKeyBounds;
		fKey.frame = fKeyBounds;
		sKey.frame = sKeyBounds;
	}
	
	orientaion = toInterfaceOrientation;
}
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
	if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) 
		return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
	else return YES;
}
@end
