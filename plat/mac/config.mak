###############################################################################
# media
# #

# demo
G2_CONFIG_DEMO_LIBS 				= z m dl pthread
G2_CONFIG_DEMO_LDFLAGS 				= -framework GLUT -framework OpenGL


# demo
G2_CONFIG_DEMO_TYPE 				= bin

###############################################################################
# tbox
# #

# include tbox
include 		$(PLAT_DIR)/tbox.mak


