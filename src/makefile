# sub-makefile
include $(PRO_DIR)/prefix.mak

# module name
NAMES 						= gbox2

# module type
gbox2_TYPE 					= LIB

# basic files
gbox2_C_FILES 				+= \
							gbox2 \
							svg/style \
							svg/reader \
							svg/writer \
							svg/element \
							svg/g \
							svg/svg \
							svg/use \
							svg/data \
							svg/path \
							svg/rect \
							svg/text \
							svg/line \
							svg/stop \
							svg/image \
							svg/circle \
							svg/ellipse \
							svg/polygon \
							svg/polyline \
							svg/gradient \
							svg/clippath \
							svg/textpath \
							prefix/color \
							core/path \
							core/pixmap \
							core/bitmap \
							core/shader \
							core/matrix \
							core/clipper \
							core/painter \
							core/cache/pcache \
							core/cache/cstack \
							core/cutter/arc \
							core/cutter/func \
							core/cutter/fill \
							core/cutter/path \
							core/cutter/quad \
							core/cutter/cube \
							core/cutter/circle \
							core/cutter/ellipse \
							core/image/decoder/bmp \
							core/image/decoder/gif \
							core/image/decoder/decoder

# gl files
gbox2_C_FILES-$(GL) 		+= \
							core/gbox/style \
							core/gbox/bitmap \
							core/gl/path \
							core/gl/draw \
							core/gl/fill \
							core/gl/stok \
							core/gl/shader \
							core/gl/context \
							core/gl/painter \
							core/gl/program \
							core/gl/program/color \
							core/gl/program/bitmap \
							core/gl/interface 

# png files
gbox2_C_FILES-$(PNG) 		+= core/image/decoder/png

# jpg files
gbox2_C_FILES-$(JPG) 		+= core/image/decoder/jpg

# skia files
gbox2_CPP_FILES-$(SKIA) 	+= \
							core/skia/path \
							core/skia/style \
							core/skia/shader \
							core/skia/bitmap \
							core/skia/context \
							core/skia/painter 

# other files
ifneq ($(GL),y)
ifneq ($(SKIA),y)
gbox2_C_FILES 				+= \
							core/gbox/path \
							core/gbox/style \
							core/gbox/shader \
							core/gbox/bitmap \
							core/gbox/context \
							core/gbox/painter 
endif
endif

# flags
gbox2_CXFLAGS 				+= -DTB_PRINT_TAG=\"gbox2\"
gbox2_CXFLAGS-$(DEBUG) 		+= -DTB_TRACE_ENABLE -DTB_ASSERT_ENABLE
gbox2_CXFLAGS-$(GL) 		+= -DTB_CONFIG_GL
gbox2_CXFLAGS-$(PNG) 		+= -DTB_CONFIG_PNG
gbox2_CXFLAGS-$(JPG) 		+= -DTB_CONFIG_JPG
gbox2_CXFLAGS-$(SKIA) 		+= -DTB_CONFIG_SKIA
gbox2_CXFLAGS-$(FREETYPE) 	+= -DTB_CONFIG_FREETYPE

# header files
INC_FILES 					= \
							gbox2.h \
							config.h \
							prefix.h \
							prefix/config.h \
							prefix/prefix.h \
							prefix/bits.h \
							prefix/type.h \
							prefix/float.h \
							prefix/color.h \
							prefix/pixfmt.h \
							prefix/version.h \
							svg/prefix.h \
							svg/svg.h \
							svg/style.h \
							svg/reader.h \
							svg/writer.h \
							svg/element.h \
							core/prefix.h \
							core/path.h \
							core/core.h \
							core/style.h \
							core/shader.h \
							core/bitmap.h \
							core/matrix.h \
							core/context.h \
							core/painter.h \
							core/clipper.h \
							core/gl/interface.h

# tbox
gbox2_INC_DIR 			+= $(PRO_DIR)/../tbox/pre/inc/$(PLAT)/$(ARCH)
gbox2_LIB_DIR 			+= $(PRO_DIR)/../tbox/pre/lib/$(PLAT)/$(ARCH)

# demo
ifeq ($(DEMO),y)
SUB_PROS 				= demo/$(G2_CONFIG_DEMO_TYPE)
endif

include $(PRO_DIR)/suffix.mak

