###############################################################################
# media
# #

# demo
G2_CONFIG_DEMO_LIBS 				= glut GLU GL z m dl pthread

# type
G2_CONFIG_DEMO_TYPE 				= apk

# arm
G2_CONFIG_ARM 						= y
G2_CONFIG_ARM_NEON 					= n

###############################################################################
# tbox
# #

# include tbox
include 		$(PLAT_DIR)/tbox.mak


