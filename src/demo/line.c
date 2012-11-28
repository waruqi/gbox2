/* ////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "shape.c"

/* ////////////////////////////////////////////////////////////////////////
 * implemention
 */
static tb_bool_t g2_demo_shape_init(tb_int_t argc, tb_char_t** argv)
{
	// init mode
	g_mode = G2_STYLE_MODE_STOK;

	// ok
	return TB_TRUE;
}
static tb_void_t g2_demo_shape_exit()
{
}
static tb_void_t g2_demo_shape_render()
{
	if (g_bm) g2_draw_iline2(g_painter, -100, -100, 100, 100);
	else 
	{
		tb_long_t dx = (g_x - g_x0) << 1;
		tb_long_t dy = (g_y - g_y0) << 1;
		g2_draw_iline2(g_painter, g_x0 - dx, g_y0 - dy, g_x0 + dx, g_y0 + dy);
	}
}
static tb_void_t g2_demo_shape_key(tb_int_t key)
{
}
