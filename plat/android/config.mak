###############################################################################
# media
# #

# demo
G2_CONFIG_DEMO 						= y
G2_CONFIG_DEMO_LIBS 				= glut GLU GL z m dl pthread

# type
G2_CONFIG_DEMO_TYPE 				= apk

# neon
G2_CONFIG_ARM_NEON 					= n

# core
G2_CONFIG_CORE_SOFT 				= n
G2_CONFIG_CORE_SKIA 				= n
G2_CONFIG_CORE_GLES 				= y

###############################################################################
# tbox
# #

# include tbox
include 		$(PLAT_DIR)/tbox.mak


