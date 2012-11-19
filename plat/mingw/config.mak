###############################################################################
# media
# #

# demo
G2_CONFIG_DEMO 						= y
G2_CONFIG_DEMO_LIBS 				= glut gl gdi usp10 ole winmm ws2_32 gcc

# demo
G2_CONFIG_DEMO_TYPE 				= bin

# core
G2_CONFIG_CORE_GL 					= y
G2_CONFIG_CORE_SKIA 				= n
G2_CONFIG_CORE_SOFT 				= n

###############################################################################
# tbox
# #

# include tbox
include 		$(PLAT_DIR)/tbox.mak


