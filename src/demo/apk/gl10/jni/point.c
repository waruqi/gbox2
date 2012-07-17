/* ////////////////////////////////////////////////////////////////////////
 * implemention
 */
static tb_bool_t g2_demo_init()
{
	// init mode
	g_mode = G2_STYLE_MODE_STROKE;

	// ok
	return TB_TRUE;
}
static tb_void_t g2_demo_exit()
{
}
static tb_void_t g2_demo_draw()
{
	if (g_bm) g2_draw2i_point(g_painter, 0, 0);
	else g2_draw2i_point(g_painter, g_x, g_y);
}
static tb_void_t g2_demo_move(tb_long_t x, tb_long_t y)
{
}
static tb_void_t g2_demo_size(tb_size_t width, tb_size_t height)
{
}
static tb_void_t g2_demo_tkey(tb_size_t key)
{
}
