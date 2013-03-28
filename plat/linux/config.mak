###############################################################################
# media
# #

# demo
G2_CONFIG_DEMO 						= y
G2_CONFIG_DEMO_LIBS 				= glut GLU GL z m dl pthread

# demo
G2_CONFIG_DEMO_TYPE 				= bin

# core
G2_CONFIG_CORE_GL 					= n
G2_CONFIG_CORE_SKIA 				= y
G2_CONFIG_CORE_SOFT 				= n

###############################################################################
# tbox
# #

# include tbox
include 		$(PLAT_DIR)/tbox.mak


