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
	tb_gstream_t* gst = tb_gstream_init_from_url(argv[1]);
	if (gst && tb_gstream_bopen(gst))
	{
		// init reader
		tb_handle_t reader = g2_svg_reader_init(gst);
		if (reader)
		{
			// load
			g2_svg_element_dump(g2_svg_reader_load(reader));

			// exit reader
			g2_svg_reader_exit(reader);
		}
	
		// exit stream
		tb_gstream_exit(gst);
	}
	
	// exit tbox
	tb_exit();
	return 0;
}

