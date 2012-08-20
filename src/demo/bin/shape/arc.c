/* ////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "demo.h"

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
}
static tb_void_t g2_demo_lclickup(tb_int_t x, tb_int_t y)
{
}
static tb_void_t g2_demo_rclickdown(tb_int_t x, tb_int_t y)
{
}
static tb_void_t g2_demo_rclickup(tb_int_t x, tb_int_t y)
{
}
static tb_void_t g2_demo_key(tb_int_t key)
{
}

/* ////////////////////////////////////////////////////////////////////////
 * implemention
 */
static tb_bool_t g2_demo_init(tb_int_t argc, tb_char_t** argv)
{
	// init mode
	g_mode = G2_STYLE_MODE_STOK;

	// ok
	return TB_TRUE;
}
static tb_void_t g2_demo_exit()
{
}
static tb_void_t g2_demo_size(tb_int_t w, tb_int_t h)
{
}
static tb_void_t g2_demo_render()
{
	if (g_bm) g2_draw2i_arc(g_painter, 0, 0, 200, 100, 0, 270);
	else g2_draw2i_arc(g_painter, g_x0, g_y0, g_dx, g_dy, 0, 270);
}
