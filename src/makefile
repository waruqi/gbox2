# sub-makefile
include $(PRO_DIR)/prefix.mak

# module name
NAMES 					= gbox2

# module type
gbox2_TYPE 				= LIB

# basic files
gbox2_C_FILES 			+= \
						gbox2 

# flags
gbox2_CPPFLAGS 			+= -DTB_PRINT_TAG=\"gbox2\"
gbox2_CPPFLAGS-$(DEBUG) += -DTB_TRACE_ENABLE -DTB_ASSERT_ENABLE


# header files
INC_FILES 				= \
						gbox2.h \
						config.h \
						prefix.h \
						prefix/config.h \
						prefix/prefix.h \
						prefix/type.h \
						prefix/version.h

# demo
ifeq ($(GB2_CONFIG_DEMO),y)
SUB_PROS 				= demo
endif

include $(PRO_DIR)/suffix.mak

