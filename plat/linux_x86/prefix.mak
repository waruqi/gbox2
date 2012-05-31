# architecture makefile configure

# prefix & suffix
BIN_PREFIX 			= 
BIN_SUFFIX 			= .b

OBJ_PREFIX 			= 
OBJ_SUFFIX 			= .o

LIB_PREFIX 			= lib
LIB_SUFFIX 			= .a

DLL_PREFIX 			= lib
DLL_SUFFIX 			= .so

ASM_SUFFIX 			= .asm

# tool
PRE 				= 
CC 					= $(PRE)gcc
AR 					= $(PRE)ar
STRIP 				= $(PRE)strip
RANLIB 				= $(PRE)ranlib
LD 					= $(PRE)g++
AS					= yasm 
RM 					= rm -f
RMDIR 				= rm -rf
CP 					= cp
CPDIR 				= cp -r
MKDIR 				= mkdir -p
MAKE 				= make
PWD 				= pwd

# cppflags: c/c++ files
CPPFLAGS_RELEASE 	= \
					-DNDEBUG -O3 
					

CPPFLAGS_DEBUG 		= -g
CPPFLAGS 			= \
					-c -Wall \
					-march=i686 -fomit-frame-pointer -mssse3

CPPFLAGS-I 			= -I
CPPFLAGS-o 			= -o

# cflags: c files
CFLAGS_RELEASE 		= 
CFLAGS_DEBUG 		= 
CFLAGS 				= \
					-std=gnu99 

# cxxflags: c++ files
CXXFLAGS_RELEASE 	= -fno-rtti
CXXFLAGS_DEBUG 		= 
CXXFLAGS 			= 

# ldflags
LDFLAGS_RELEASE 	= 
LDFLAGS_DEBUG 		= 
LDFLAGS 			= 
LDFLAGS-L 			= -L
LDFLAGS-l 			= -l
LDFLAGS-o 			= -o

# asflags
ASFLAGS_RELEASE 	= -O2
ASFLAGS_DEBUG 		= 
ASFLAGS 			= -f elf 
ASFLAGS-I 			= -I
ASFLAGS-o 			= -o

# arflags
ARFLAGS 			= -cr

# share ldflags
SHFLAGS 			= 

# include sub-config
include 			$(PLAT_DIR)/config.mak


