/* ////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "core/cutter/cutter.h"

/* ////////////////////////////////////////////////////////////////////////
 * globals
 */
static tb_handle_t 	g_path 		= tb_null;
static tb_handle_t 	g_fill 		= tb_null;
static tb_handle_t 	g_temp 		= tb_null;
static tb_bool_t 	g_move 		= tb_true;

/* ////////////////////////////////////////////////////////////////////////
 * interfaces
 */
static tb_void_t g2_demo_shape_key(tb_int_t key);
static tb_bool_t g2_demo_shape_init(tb_int_t argc, tb_char_t** argv);
static tb_void_t g2_demo_shape_exit();
static tb_void_t g2_demo_shape_render();

/* ////////////////////////////////////////////////////////////////////////
 * events
 */
static tb_void_t g2_demo_move(tb_int_t x, tb_int_t y)
{
}
static tb_void_t g2_demo_drag(tb_int_t x, tb_int_t y)
{
}
static tb_void_t g2_demo_wheeldown(tb_int_t x, tb_int_t y)
{	
}
static tb_void_t g2_demo_wheelup(tb_int_t x, tb_int_t y)
{
}
static tb_void_t g2_demo_lclickdown(tb_int_t x, tb_int_t y)
{	
	if (g_move)
	{
		g2_path_move2i_to(g_path, x, y);
		g_move = tb_false;
	}
	else g2_path_line2i_to(g_path, x, y);
}
static tb_void_t g2_demo_lclickup(tb_int_t x, tb_int_t y)
{
}
static tb_void_t g2_demo_rclickdown(tb_int_t x, tb_int_t y)
{
	// close path
	g2_path_close(g_path);
	g_move = tb_true;

	// clear temp
	g2_path_clear(g_temp);

	// clear fill
	g2_path_clear(g_fill);

	// cutter path
	g2_cutter_path_t cp;
	g2_cutter_path_init(&cp, g2_cutter_func_path_append, g_temp);
	g2_cutter_path_done(&cp, g_path);
	g2_cutter_path_exit(&cp);

	// cutter fill
	g2_cutter_fill_t cf;
	g2_cutter_fill_init(&cf, G2_STYLE_RULE_EVENODD, g2_cutter_func_path_append, g_fill);
//	g2_cutter_fill_init(&cf, G2_STYLE_RULE_NONZERO, g2_cutter_func_path_append, g_fill);
	g2_cutter_fill_done(&cf, g_temp);
	g2_cutter_fill_exit(&cf);
}
static tb_void_t g2_demo_rclickup(tb_int_t x, tb_int_t y)
{
}
static tb_void_t g2_demo_key(tb_int_t key)
{
	switch (key)
	{
	case 'c':
		if (g_path) g2_path_clear(g_path);
		if (g_fill) g2_path_clear(g_fill);
		break;
	default:
		break;
	}
}

/* ////////////////////////////////////////////////////////////////////////
 * implemention
 */
static tb_bool_t g2_demo_init(tb_int_t argc, tb_char_t const** argv)
{
	// init path
	g_path = g2_path_init();
	tb_assert_and_check_return_val(g_path, tb_false);

	// init temp
	g_temp = g2_path_init();
	tb_assert_and_check_return_val(g_temp, tb_false);

	// init fill
	g_fill = g2_path_init();
	tb_assert_and_check_return_val(g_fill, tb_false);

	// ok
	return tb_true;
}
static tb_void_t g2_demo_exit()
{
	// exit path
	if (g_path) g2_path_exit(g_path);
	if (g_fill) g2_path_exit(g_fill);
	if (g_temp) g2_path_exit(g_temp);
	g_path = tb_null;
	g_fill = tb_null;
	g_temp = tb_null;
}
static tb_void_t g2_demo_size(tb_int_t w, tb_int_t h)
{
}
static tb_void_t g2_demo_render()
{
	g2_mode(g_painter, G2_STYLE_MODE_FILL);
	g2_color(g_painter, G2_COLOR_RED);
	g2_draw_path(g_painter, g_path);

	g2_mode(g_painter, G2_STYLE_MODE_STOK);
	g2_color(g_painter, G2_COLOR_BLUE);
	g2_draw_path(g_painter, g_fill);
}
