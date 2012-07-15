/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "demo.h"

/* ////////////////////////////////////////////////////////////////////////
 * macros
 */
#define G2_DEMO_WIDTH 			(640)
#define G2_DEMO_HEIGHT 			(480)

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the demo type
typedef g2_demo_t
{
	// the context
	tb_handle_t 	context;

	// the surface
	tb_handle_t 	surface;

	// the painter
	tb_handle_t 	painter;

	// the style
	tb_handle_t 	style;

	// the pixfmt
	tb_size_t 		pixfmt;

	// the pen width
	tb_size_t 		penw;

}g2_demo_t;

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */

tb_handle_t g2_demo_init()
{
	return (tb_handle_t)tb_malloc0(sizeof(g2_demo_t));
}
tb_void_t g2_demo_exit(tb_handle_t hdemo)
{
	g2_demo_t* demo = hdemo;
	if (demo)
	{
	
		// free it
		tb_free(demo);
	}
}
tb_void_t g2_demo_draw(tb_handle_t hdemo)
{
}
tb_void_t g2_demo_size(tb_handle_t hdemo, tb_size_t width, tb_size_t height)
{
	g2_demo_t* demo = hdemo;
	tb_assert_and_check_return(demo);

	if (!demo->context)
	{
		// init context
#ifdef G2_CONFIG_CORE_GL10
		demo->context = g2_context_init_gl10(demo->pixfmt, G2_DEMO_WIDTH, G2_DEMO_HEIGHT);
		tb_assert_and_check_return_val(demo->context, TB_FALSE);
#else
		demo->context = g2_context_init_skia(demo->pixfmt, TB_NULL, G2_DEMO_WIDTH, G2_DEMO_HEIGHT, 0);
		tb_assert_and_check_return_val(demo->context, TB_FALSE);
#endif

		// init surface
		demo->surface = g2_context_surface(demo->context);
		tb_assert_and_check_return_val(demo->surface, TB_FALSE);

		// init painter
		demo->painter = g2_init(demo->context);
		tb_assert_and_check_return_val(demo->painter, TB_FALSE);

		// init style
		demo->style = g2_style(demo->painter);
		tb_assert_and_check_return_val(demo->style, TB_FALSE);
	}
	else
	{
	
	}
}
tb_void_t g2_demo_move(tb_handle_t hdemo, tb_londemo->t x, tb_londemo->t y)
{
}
