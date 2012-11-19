# sub-makefile
include $(PRO_DIR)/prefix.mak

NAMES 					= \
						arc \
						svg \
						dump \
						rect \
						line \
						clip \
						path \
						point \
						circle \
						ellipse \
						triangle


ifeq ($(TB_CONFIG_PLAT),mac_x64)
demo_LIBS 				= z m dl pthread
demo_LDFLAGS 			= -framework GLUT -framework OpenGL -framework Cocoa -framework CoreFoundation \
						  -framework VideoDecodeAcceleration -framework QuartzCore
endif

define MAKE_MODULES
$(1)_TYPE 				= BIN
$(1)_C_FILES 			+= $(1) $(demo_C_FILES)
$(1)_OBJ_FILES 			+= $(demo_OBJ_FILES)
$(1)_LIBS 				+= gbox2 tbox $(G2_CONFIG_DEMO_LIBS)
$(1)_LIB_DIR 			+= ../.. $(demo_LIB_DIR)
$(1)_INC_DIR 			+= ../.. $(demo_INC_DIR)
$(1)_CXFLAGS 			+= -DTB_PRINT_TAG=\"gbox2\" $(demo_CXFLAGS)
$(1)_CXFLAGS-$(DEBUG) 	+= -DTB_TRACE_ENABLE -DTB_ASSERT_ENABLE $(demo_CXFLAGS-y)
$(1)_LDFLAGS 			+= $(demo_LDFLAGS)
endef
$(foreach name, $(NAMES), $(eval $(call MAKE_MODULES,$(name))))

include $(PRO_DIR)/suffix.mak

