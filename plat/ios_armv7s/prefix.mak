# architecture makefile configure

# prefix & suffix
BIN_PREFIX 		= 
BIN_SUFFIX 		= .b

OBJ_PREFIX 		= 
OBJ_SUFFIX 		= .o

LIB_PREFIX 		= lib
LIB_SUFFIX 		= .a

DLL_PREFIX 		= lib
DLL_SUFFIX 		= .so

ASM_SUFFIX 		= .S

ifeq ($(BIN),)
BIN 			= /Developer/Platforms/iPhoneOS.platform/Developer/usr/bin
endif

ifeq ($(SDK),)
SDK 			= /Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS6.0.sdk
endif

CC 				= $(BIN)/gcc 
AR 				= $(BIN)/ar
STRIP 			= $(BIN)/strip
RANLIB 			= $(BIN)/ranlib
LD 				= $(BIN)/gcc
AS				= $(PLAT_DIR)/gas-preprocessor.pl $(BIN)/gcc
RM 				= rm -f
RMDIR 			= rm -rf
CP 				= cp
CPDIR 			= cp -r
MKDIR 			= mkdir -p
MAKE 			= make
PWD 			= pwd

# cppflags: c/c++ files
CXFLAGS_RELEASE 	= \
	-O3 -DNDEBUG \
	-fomit-frame-pointer -freg-struct-return -fno-bounds-check \
	-fvisibility=hidden

CXFLAGS_DEBUG 	= -g 
CXFLAGS 		= -arch armv7s -c -Wall  \
				  -mthumb -mcpu=cortex-a8 -miphoneos-version-min=6.0 \
				  -fmessage-length=0  -Wreturn-type -Wunused-variable \
				  -pipe -Wno-trigraphs -fpascal-strings \
				  --sysroot=$(SDK)
CXFLAGS-I 		= -I
CXFLAGS-o 		= -o

# cflags: c files
CFLAGS_RELEASE 	= 
CFLAGS_DEBUG 	= 
CFLAGS 			= -std=gnu99

# cxxflags: c++ files
CCFLAGS_RELEASE = -fno-rtti
CCFLAGS_DEBUG 	= 
CCFLAGS 		= 

# ldflags
LDFLAGS_RELEASE =
LDFLAGS_DEBUG 	= 
LDFLAGS 		= -arch armv7s -isysroot $(SDK) --sysroot=$(SDK)
LDFLAGS-L 		= -L
LDFLAGS-l 		= -l
LDFLAGS-o 		= -o

# asflags
ASFLAGS_RELEASE = 
ASFLAGS_DEBUG 	= 
ASFLAGS 		= -arch armv7s -c -fPIC
ASFLAGS-I 		= -I
ASFLAGS-o 		= -o

# arflags
ARFLAGS 		= -cr

# share ldflags
SHFLAGS 		= -dynamiclib -Wl,-single_module

# include sub-config
include 		$(PLAT_DIR)/config.mak

