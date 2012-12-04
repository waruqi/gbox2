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
	g_mode = G2_STYLE_MODE_FILL_STOK;

	// ok
	return TB_TRUE;
}
static tb_void_t g2_demo_shape_exit()
{
}
static tb_void_t g2_demo_shape_render()
{
	g2_color(g_painter, G2_COLOR_GREEN);
	g2_clear_path(g_painter);	
	g2_move2i_to(g_painter, 100, 100);
	g2_line2i_to(g_painter, 200, 100);
	g2_line2i_to(g_painter, 200, 200);
	g2_line2i_to(g_painter, 100, 200);
	g2_close(g_painter);

	g2_save(g_painter);
	g2_save_path(g_painter);	
	g2_save_style(g_painter);	
	g2_color(g_painter, G2_COLOR_BLUE);
	g2_clear_path(g_painter);	
	g2_translate(g_painter, g2_long_to_float(50), 0);
	g2_move2i_to(g_painter, 200, 100);
	g2_line2i_to(g_painter, 300, 100);
	g2_line2i_to(g_painter, 300, 200);
	g2_line2i_to(g_painter, 200, 200);
	g2_close(g_painter);

	g2_save(g_painter);
	g2_save_path(g_painter);	
	g2_save_style(g_painter);	
	g2_save_clipper(g_painter);
	g2_color(g_painter, G2_COLOR_RED);
	g2_clear_path(g_painter);
	g2_translate(g_painter, g2_long_to_float(50), 0);
//	g2_clip_irect2(g_painter, G2_CLIPPER_MODE_REPLACE, 310, 110, 80, 80);	
	g2_move2i_to(g_painter, 300, 100);
	g2_line2i_to(g_painter, 400, 100);
	g2_line2i_to(g_painter, 400, 200);
	g2_line2i_to(g_painter, 300, 200);
	g2_close(g_painter);
	g2_draw(g_painter);	
	g2_load(g_painter);
	g2_load_path(g_painter);
	g2_load_style(g_painter);
	g2_load_clipper(g_painter);
	
	g2_draw(g_painter);	
	g2_load(g_painter);
	g2_load_path(g_painter);
	g2_load_style(g_painter);

	g2_draw(g_painter);	
}
static tb_void_t g2_demo_shape_key(tb_int_t key)
{
}
