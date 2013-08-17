/* ///////////////////////////////////////////////////////////////////////
 * includes
 */ 
#include "gbox2.h"
#include <stdlib.h>

/* ///////////////////////////////////////////////////////////////////////
 * main
 */ 
tb_int_t main(tb_int_t argc, tb_char_t** argv)
{
	// init tbox
	if (!tb_init(malloc(10 * 1024 * 1024), 10 * 1024 * 1024)) return 0;

	// init stream
	tb_gstream_t* ist = tb_gstream_init_from_url(argv[1]);
	tb_gstream_t* ost = tb_gstream_init_from_url(argv[2]);
	if (ost) tb_gstream_ctrl(ost, TB_FSTREAM_CTRL_SET_MODE, TB_FILE_MODE_WO | TB_FILE_MODE_CREAT | TB_FILE_MODE_TRUNC);
	if (ist && ost && tb_gstream_bopen(ist) && tb_gstream_bopen(ost))
	{
		// init reader & writer
		tb_handle_t reader = g2_svg_reader_init(ist);
		tb_handle_t writer = g2_svg_writer_init(ost, tb_true);
		if (reader && writer)
		{
			// load svg
			g2_svg_element_t* svg = g2_svg_reader_load(reader);
			if (svg)
			{
				// save svg
				g2_svg_writer_save(writer, svg);

				// exit svg
				g2_svg_element_exit(svg);
			}
			
			// exit reader
			g2_svg_reader_exit(reader);

			// exit writer
			g2_svg_writer_exit(writer);
		}
	
		// exit stream
		tb_gstream_exit(ist);
		tb_gstream_exit(ost);
	}
	
	// exit tbox
	tb_exit();
	return 0;
}

