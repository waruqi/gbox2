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
	if (g_bm) g2_draw2i_line(g_painter, -100, -100, 100, 100);
	else 
	{
		tb_long_t dx = (g_x - g_x0) << 1;
		tb_long_t dy = (g_y - g_y0) << 1;
		g2_draw2i_line(g_painter, g_x0 - dx, g_y0 - dy, g_x0 + dx, g_y0 + dy);
	}
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
