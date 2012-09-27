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
	
	// init pool
	pool = [[NSAutoreleasePool alloc] init];
	tb_assert_and_check_goto(pool, end);
	
	// bind render
	tb_trace_impl("render: init");
	if (![cl.render bind]) goto end;
	
	glClearColor(1.0, 0.0, 0.0, 1.0);
	

	tb_size_t i = 0;
	while (!cl.bstop)
	{
		// lock render
		if (![cl.render lock]) goto end;
		glClear(GL_COLOR_BUFFER_BIT);
		
		// draw render
		[cl.render draw];

		tb_trace_impl("render: draw: %lu", i++);
		tb_msleep(1000);
	}

	// end
end:
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
