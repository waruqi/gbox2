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
	g_mode = G2_STYLE_MODE_FILL_STOK;

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
#if 0
	if (g_bm) g2_draw2i_rect(g_painter, -100, -100, 200, 200);
	else g2_draw2i_rect(g_painter, g_x0 - g_dx, g_y0 - g_dy, g_dx << 1, g_dy << 1);
#else
	g2_save(g_painter, G2_SAVE_MODE_MATRIX);
	g2_matrix_t matrix = *g2_matrix(g_painter);

	g2_draw2i_rect(g_painter, g_x0 - 100, g_y0 - 100, 200, 200);
	g2_matrix_translate(&matrix, -g2_long_to_float(g_x0 - 100), -g2_long_to_float(g_y0 - 100));
	g2_matrix_rotatep(&matrix, g2_long_to_float(45), g2_long_to_float(g_x0 - 100), g2_long_to_float(g_y0 - 100));
	g2_matrix_scalep(&matrix, tb_float_to_g2(0.5f), tb_float_to_g2(0.5f), g2_long_to_float(g_x0 - 100), g2_long_to_float(g_y0 - 100));

	/*
	g2_matrix_translate(&matrix, g2_long_to_float(g_x0 - 100), g2_long_to_float(g_y0 - 100));
	g2_matrix_rotate(&matrix, g2_long_to_float(45));
	g2_matrix_translate(&matrix, -g2_long_to_float(g_x0 - 100), -g2_long_to_float(g_y0 - 100));*/
//	g2_matrix_rotatep(&matrix, g2_long_to_float(45), g2_long_to_float(g_x0 - 100), g2_long_to_float(g_y0 - 100));
//	g2_matrix_scale(&matrix, g2_long_to_float(2), g2_long_to_float(2));
//	g2_matrix_scalep(&matrix, g2_long_to_float(2), g2_long_to_float(2), g2_long_to_float(g_x0 - 100), g2_long_to_float(g_y0 - 100));
	g2_matrix_set(g_painter, &matrix);
	g2_draw2i_rect(g_painter, g_x0 - 100, g_y0 - 100, 200, 200);
	g2_load(g_painter);
#endif
}
