/* ////////////////////////////////////////////////////////////////////////
 * globals
 */
// style
static tb_handle_t 	g_style 	= TB_NULL;
static tb_size_t 	g_mode 		= G2_STYLE_MODE_NONE;
static tb_size_t 	g_penw 		= 1;
static tb_size_t 	g_capi 		= 0;
static tb_size_t 	g_joini 	= 0;
static tb_size_t 	g_shaderi 	= 0;
static tb_handle_t 	g_bitmap 	= TB_NULL;
static tb_size_t 	g_cap[] 	= {G2_STYLE_CAP_BUTT, G2_STYLE_CAP_SQUARE, G2_STYLE_CAP_ROUND};
static tb_size_t 	g_join[] 	= {G2_STYLE_JOIN_MITER, G2_STYLE_JOIN_BEVEL, G2_STYLE_JOIN_ROUND};
static tb_handle_t 	g_shader[5] = {TB_NULL};
static tb_handle_t 	g_mhader[5] = {TB_NULL};

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
	g_shaderi = (g_shaderi + 1) % (g_bitmap? 5 : 4);
}
static tb_void_t g2_demo_lclickup(tb_int_t x, tb_int_t y)
{
}
static tb_void_t g2_demo_rclickdown(tb_int_t x, tb_int_t y)
{
	g_capi = (g_capi + 1) % 3;
	g_joini = (g_joini + 1) % 3;
}
static tb_void_t g2_demo_rclickup(tb_int_t x, tb_int_t y)
{
}
static tb_void_t g2_demo_key(tb_int_t key)
{
	switch (key)
	{
	case 'w':
		{
			if (g_penw > 1000) g_penw = 1000;
			else g_penw++;
		}
		break;
	default:
		break;
	}

	g2_demo_shape_key(key);
}

/* ////////////////////////////////////////////////////////////////////////
 * implemention
 */
static tb_bool_t g2_demo_init(tb_int_t argc, tb_char_t** argv)
{
	// init style
	g_style = g2_style(g_painter);
	tb_assert_and_check_return_val(g_style, TB_FALSE);

	// init bitmap
	if (argv[1]) g_bitmap = g2_bitmap_init_url(G2_DEMO_PIXFMT, argv[1]);

	// init gradient
	g2_color_t 		color[3] = {G2_COLOR_RED, G2_COLOR_GREEN, G2_COLOR_BLUE};
	g2_gradient_t 	grad = {color, TB_NULL, 3};

	// init shader
	g_shader[1]	= g2_shader_init2i_linear(g_context, g_x0 - 100, g_y0 - 100, g_x0 + 100, g_y0 + 100, &grad, G2_SHADER_WRAP_CLAMP);
	g_mhader[1]	= g2_shader_init2i_linear(g_context, -50, -50, 50, 50, &grad, G2_SHADER_WRAP_CLAMP);

	g_shader[2]	= g2_shader_init2i_radial(g_context, g_x0, g_y0, 100, &grad, G2_SHADER_WRAP_CLAMP);
	g_mhader[2]	= g2_shader_init2i_radial(g_context, 0, 0, 50, &grad, G2_SHADER_WRAP_CLAMP);

	g_shader[3]	= g2_shader_init2i_radial2(g_context, g_x0, g_y0, 100, g_x0, g_y0, 200, &grad, G2_SHADER_WRAP_CLAMP);
	g_mhader[3]	= g2_shader_init2i_radial2(g_context, 0, 0, 50, 0, 0, 100, &grad, G2_SHADER_WRAP_CLAMP);

	if (g_bitmap)
	{
		g_shader[4]	= g2_shader_init_bitmap(g_context, g_bitmap, G2_SHADER_WRAP_CLAMP);
		g_mhader[4]	= g2_shader_init_bitmap(g_context, g_bitmap, G2_SHADER_WRAP_CLAMP);
	}

	// ok
	return g2_demo_shape_init(argc, argv);
}
static tb_void_t g2_demo_exit()
{
	// exit shape
	g2_demo_shape_exit();

	// exit shader
	tb_size_t i = 0;
	for (i = 0; i < 5; i++)
	{
		if (g_shader[i]) g2_shader_exit(g_shader[i]);
		if (g_mhader[i]) g2_shader_exit(g_mhader[i]);
	}

	// exit bitmap
	if (g_bitmap) g2_bitmap_exit(g_bitmap);
}
static tb_void_t g2_demo_size(tb_int_t w, tb_int_t h)
{
}
static tb_void_t g2_demo_render()
{
	// render 
	if (g_mode & G2_STYLE_MODE_FILL)
	{
		g2_style_clear(g_style);
		g2_style_mode_set(g_style, G2_STYLE_MODE_FILL);
		g2_style_color_set(g_style, G2_COLOR_RED);
		g2_style_shader_set(g_style, g_bm? g_mhader[g_shaderi] : g_shader[g_shaderi]);
		if (g_shaderi == 4) 
		{
			g2_matrix_t mx;
			tb_size_t bw 	= g2_bitmap_width(g_bitmap);
			tb_size_t bh 	= g2_bitmap_height(g_bitmap);
			tb_size_t cw 	= g2_bitmap_width(g_surface);
			tb_size_t ch 	= g2_bitmap_height(g_surface);
			if (g_bm)
			{
				g2_matrix_init_translate(&mx, -g2_long_to_float(100), -g2_long_to_float(100));
				g2_matrix_scale(&mx, g2_long_to_float(200) / bw, g2_long_to_float(200) / bh);
				g2_shader_matrix_set(g_mhader[g_shaderi], &mx);
			}
			else
			{
				g2_matrix_init_translate(&mx, 0, 0);
				g2_matrix_scale(&mx, g2_long_to_float(cw) / bw, g2_long_to_float(ch) / bh);
				g2_shader_matrix_set(g_shader[g_shaderi], &mx);
			}
		}

		// render
		g2_demo_shape_render();
	}

	if (g_mode & G2_STYLE_MODE_STOK)
	{
		g2_style_clear(g_style);
		g2_style_mode_set(g_style, G2_STYLE_MODE_STOK);
		g2_style_color_set(g_style, G2_COLOR_BLUE);

		g2_style_width_set(g_style, g2_long_to_float(g_penw));
		g2_style_cap_set(g_style, g_cap[g_capi]);
		g2_style_join_set(g_style, g_join[g_joini]);

		// render
		g2_demo_shape_render();
	}
}
