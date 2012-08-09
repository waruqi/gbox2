# sub-makefile
include $(PRO_DIR)/prefix.mak

NAMES 					= \
						shape/arc \
						shape/line \
						shape/rect \
						shape/path \
						shape/clip \
						shape/point \
						shape/circle \
						shape/ellipse \
						shape/triangle \
						svg/svg \
						svg/dump

ifeq ($(TB_CONFIG_PLAT),linux_x86)
demo_LIBS 				= glut GLU z m dl pthread
endif

ifeq ($(TB_CONFIG_PLAT),linux_x64)
demo_LIBS 				= glut GLU z m dl pthread
endif

ifeq ($(TB_CONFIG_PLAT),mingw_x86)
demo_LIBS 				= glut gl gdi usp10 ole ws2_32
endif

ifeq ($(TB_CONFIG_PLAT),mac_x64)
demo_LIBS 				= z m dl pthread
demo_LDFLAGS 			= -framework GLUT -framework OpenGL -framework Cocoa -framework CoreFoundation \
						  -framework VideoDecodeAcceleration -framework QuartzCore
endif

define MAKE_MODULES
$(1)_TYPE 				= BIN
$(1)_C_FILES 			+= $(1) $(demo_C_FILES)
$(1)_OBJ_FILES 			+= $(demo_OBJ_FILES)
$(1)_LIBS 				+= gbox2 tbox $(demo_LIBS)
$(1)_LIB_DIR 			+= ../.. $(demo_LIB_DIR)
$(1)_INC_DIR 			+= ../.. $(demo_INC_DIR)
$(1)_CPPFLAGS 			+= -DTB_PRINT_TAG=\"gbox2\" $(demo_CPPFLAGS)
$(1)_CPPFLAGS-$(DEBUG) 	+= -DTB_TRACE_ENABLE -DTB_ASSERT_ENABLE $(demo_CPPFLAGS-y)
$(1)_LDFLAGS 			+= $(demo_LDFLAGS)
endef
$(foreach name, $(NAMES), $(eval $(call MAKE_MODULES,$(name))))

include $(PRO_DIR)/suffix.mak

