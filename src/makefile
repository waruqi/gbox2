# sub-makefile
include $(PRO_DIR)/prefix.mak

# module name
NAMES 					= gbox2

# module type
gbox2_TYPE 				= LIB

# basic files
gbox2_C_FILES 			+= \
						gbox2 \
						svg/style \
						svg/reader \
						svg/writer \
						svg/element \
						svg/g \
						svg/svg \
						svg/use \
						svg/data \
						svg/path \
						svg/rect \
						svg/text \
						svg/line \
						svg/stop \
						svg/image \
						svg/circle \
						svg/ellipse \
						svg/polygon \
						svg/polyline \
						svg/gradient \
						svg/clippath \
						svg/textpath \
						prefix/color \
						core/path \
						core/pixmap \
						core/bitmap \
						core/shader \
						core/matrix \
						core/painter \
						core/image/decoder/bmp \
						core/image/decoder/jpg \
						core/image/decoder/png \
						core/image/decoder/gif \
						core/image/decoder/decoder

gbox2_C_FILES-$(G2_CONFIG_CORE_GL10) += \
						core/soft/style \
						core/soft/shader \
						core/soft/bitmap \
						core/soft/split/quad \
						core/soft/split/cube \
						core/soft/split/circle \
						core/soft/split/ellipse \
						core/gl10/path \
						core/gl10/fill \
						core/gl10/context \
						core/gl10/painter


gbox2_CPP_FILES-$(G2_CONFIG_CORE_SKIA) += \
						core/skia/path \
						core/skia/style \
						core/skia/shader \
						core/skia/bitmap \
						core/skia/context \
						core/skia/painter 

gbox2_C_FILES-$(G2_CONFIG_CORE_SOFT) += \
						core/soft/path \
						core/soft/style \
						core/soft/shader \
						core/soft/bitmap \
						core/soft/split/quad \
						core/soft/split/cube

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
						prefix/bits.h \
						prefix/type.h \
						prefix/float.h \
						prefix/color.h \
						prefix/pixfmt.h \
						prefix/version.h \
						svg/prefix.h \
						svg/svg.h \
						svg/style.h \
						svg/reader.h \
						svg/writer.h \
						svg/element.h \
						core/prefix.h \
						core/path.h \
						core/core.h \
						core/style.h \
						core/bitmap.h \
						core/painter.h
	
	
# freetype files
freetype_C_FILES 		= \
						base/ftinit \
						base/ftadvanc \
						base/ftcalc \
						base/ftgloadr \
						base/ftobjs \
						base/ftoutln \
						base/ftrfork \
						base/ftsnames \
						base/ftstream \
						base/fttrigon \
						base/ftutil \
						base/ftlcdfil \
						base/ftfstype \
						base/ftxf86 \
						base/fttype1 \
						base/ftbitmap \
						base/ftapi \
						base/ftsystem \
						truetype/ttdriver \
						truetype/ttgload \
						truetype/ttgxvar \
						truetype/ttinterp \
						truetype/ttobjs \
						truetype/ttpload \
						autofit/afangles \
						autofit/afcjk \
						autofit/afdummy \
						autofit/afglobal \
						autofit/afhints \
						autofit/afindic \
						autofit/aflatin \
						autofit/afloader \
						autofit/afmodule \
						cache/ftcbasic \
						cache/ftccache \
						cache/ftccmap \
						cache/ftcglyph \
						cache/ftcimage \
						cache/ftcmanag \
						cache/ftcmru \
						cache/ftcsbits \
						sfnt/ttload \
						sfnt/ttmtx \
						sfnt/ttcmap \
						sfnt/ttsbit \
						sfnt/ttpost \
						sfnt/ttkern \
						sfnt/ttbdf \
						sfnt/sfobjs \
						sfnt/sfdriver \
						smooth/ftgrays \
						smooth/ftsmooth

freetype_INC_DIR 		:= third/freetype/include
freetype_CFLAGS 		:= -DFT2_BUILD_LIBRARY
freetype_C_FILES 		:= $(addprefix third/freetype/,$(freetype_C_FILES))
gbox2_C_FILES-$(G2_CONFIG_CORE_SKIA) 	+= $(freetype_C_FILES)
gbox2_CFLAGS-$(G2_CONFIG_CORE_SKIA) 	+= $(freetype_CFLAGS)
gbox2_INC_DIR-$(G2_CONFIG_CORE_SKIA) 	+= $(freetype_INC_DIR)
	
# jpeg files
jpeg_C_FILES 			= \
						jcapimin \
						jcapistd \
						jccoefct \
						jccolor \
						jcdctmgr \
						jchuff \
						jcinit \
						jcmainct \
						jcmarker \
						jcmaster \
						jcomapi \
						jcparam \
						jcphuff \
						jcprepct \
						jcsample \
						jctrans \
						jdapimin \
						jdapistd \
						jdatadst \
						jdatasrc \
						jdcoefct \
						jdcolor \
						jddctmgr \
						jdhuff \
						jdinput \
						jdmainct \
						jdmarker \
						jdmaster \
						jdmerge \
						jdphuff \
						jdpostct \
						jdsample \
						jdtrans \
						jerror \
						jfdctflt \
						jfdctfst \
						jfdctint \
						jidctflt \
						jidctfst \
						jidctint \
						jidctred \
						jquant1 \
						jquant2 \
						jutils \
						jmemansi \
						jmemmgr
		
jpeg_C_FILES 			:= $(addprefix third/jpeg/,$(jpeg_C_FILES))
gbox2_C_FILES			+= $(jpeg_C_FILES)
		
# png files
png_C_FILES 			= \
						png \
						pngerror \
						pngget \
						pngmem \
						pngpread \
						pngread \
						pngrio \
						pngrtran \
						pngrutil \
						pngset \
						pngtrans \
						pngwio \
						pngwrite \
						pngwtran \
						pngwutil
	
png_C_FILES 			:= $(addprefix third/png/,$(png_C_FILES))
gbox2_C_FILES			+= $(png_C_FILES)
	
# skia files
skia_CPP_FILES 			= \
						core/Sk64 \
						core/SkAAClip \
						core/SkAdvancedTypefaceMetrics \
						core/SkAlphaRuns \
						core/SkBitmap \
						core/SkBitmapProcShader \
						core/SkBitmapProcState \
						core/SkBitmapProcState_matrixProcs \
						core/SkBitmapSampler \
						core/SkBitmap_scroll \
						core/SkBlitMask_D32 \
						core/SkBlitRow_D16 \
						core/SkBlitRow_D32 \
						core/SkBlitRow_D4444 \
						core/SkBlitter \
						core/SkBlitter_4444 \
						core/SkBlitter_A1 \
						core/SkBlitter_A8 \
						core/SkBlitter_ARGB32 \
						core/SkBlitter_RGB16 \
						core/SkBlitter_Sprite \
						core/SkBuffer \
						core/SkCanvas \
						core/SkChunkAlloc \
						core/SkClipStack \
						core/SkColor \
						core/SkColorFilter \
						core/SkColorTable \
						core/SkComposeShader \
						core/SkConcaveToTriangles \
						core/SkConfig8888 \
						core/SkCordic \
						core/SkCubicClipper \
						core/SkData \
						core/SkDebug \
						core/SkDeque \
						core/SkDevice \
						core/SkDeviceProfile \
						core/SkDither \
						core/SkDraw \
						core/SkEdgeBuilder \
						core/SkEdgeClipper \
						core/SkEdge \
						core/SkFilterProc \
						core/SkFlattenable \
						core/SkFloat \
						core/SkFloatBits \
						core/SkFontHost \
						core/SkGeometry \
						core/SkGlyphCache \
						core/SkGraphics \
						core/SkLineClipper \
						core/SkMallocPixelRef \
						core/SkMask \
						core/SkMaskFilter \
						core/SkMath \
						core/SkMatrix \
						core/SkMemory_stdlib \
						core/SkMetaData \
						core/SkOrderedReadBuffer \
						core/SkOrderedWriteBuffer \
						core/SkPackBits \
						core/SkPaint \
						core/SkPath \
						core/SkPathEffect \
						core/SkPathHeap \
						core/SkPathMeasure \
						core/SkPicture \
						core/SkPictureFlat \
						core/SkPicturePlayback \
						core/SkPictureRecord \
						core/SkPixelRef \
						core/SkPoint \
						core/SkPtrRecorder \
						core/SkQuadClipper \
						core/SkRasterClip \
						core/SkRasterizer \
						core/SkRect \
						core/SkRefCnt \
						core/SkRefDict \
						core/SkRegion \
						core/SkRegion_path \
						core/SkScalar \
						core/SkScalerContext \
						core/SkScan \
						core/SkScan_AntiPath \
						core/SkScan_Antihair \
						core/SkScan_Hairline \
						core/SkScan_Path \
						core/SkShader \
						core/SkShape \
						core/SkSpriteBlitter_ARGB32 \
						core/SkSpriteBlitter_RGB16 \
						core/SkStream \
						core/SkString \
						core/SkStroke \
						core/SkStrokerPriv \
						core/SkTLS \
						core/SkTSearch \
						core/SkTypeface \
						core/SkTypefaceCache \
						core/SkUnPreMultiply \
						core/SkUtils \
						core/SkWriter32 \
						core/SkXfermode \
						effects/SkGradientShader \
						effects/SkBitmapCache \
						effects/SkClampRange \
						ports/SkDebug_stdio \
						ports/SkFontHost_sandbox_none \
						ports/SkFontHost_gamma_none \
						ports/SkFontHost_linux \
						ports/SkFontHost_tables \
						ports/SkFontDescriptor \
						ports/SkMemory_malloc \
						ports/SkOSFile_stdio \
						ports/SkTime_Unix \
						ports/SkXMLParser_empty \
						utils/SkOSFile

ifeq ($(TB_CONFIG_PLAT),mingw_x86)
skia_CPP_FILES 			+= ports/SkFontHost_win
skia_CPP_FILES 			+= ports/SkThread_win
skia_CPP_FILES 			+= utils/SkBase64
skia_CPP_FILES 			+= sfnt/SkOTUtils
else
skia_CPP_FILES 			+= core/SkMMapStream
skia_CPP_FILES 			+= ports/SkFontHost_FreeType
skia_CPP_FILES 			+= ports/SkThread_pthread
endif

ifeq ($(TB_CONFIG_PLAT),mingw_x86)
skia_CPP_FILES 			+= \
						opts/SkBitmapProcState_opts_none \
						opts/SkBlitRow_opts_none \
						opts/SkUtils_opts_none
else
ifeq ($(TB_CONFIG_ARCH),x86)
skia_CPP_FILES 			+= \
						opts/opts_check_SSE2 \
						opts/SkBitmapProcState_opts_SSE2 \
						opts/SkBitmapProcState_opts_SSSE3 \
						opts/SkBlitRow_opts_SSE2 \
						opts/SkBlitRect_opts_SSE2 \
						opts/SkUtils_opts_SSE2
endif
	
ifeq ($(TB_CONFIG_ARCH),x64)
skia_CPP_FILES 			+= \
						opts/opts_check_SSE2 \
						opts/SkBitmapProcState_opts_SSE2 \
						opts/SkBitmapProcState_opts_SSSE3 \
						opts/SkBlitRow_opts_SSE2 \
						opts/SkBlitRect_opts_SSE2 \
						opts/SkUtils_opts_SSE2
endif
	
ifeq ($(TB_CONFIG_ARCH),arm)
skia_CPP_FILES 			+= \
						opts/opts_check_arm \
						opts/SkBitmapProcState_opts_arm \
						opts/SkBlitRow_opts_arm

ifeq ($(G2_CONFIG_ARM_NEON),y)
skia_ASM_FILES 			+= opts/memset16_neon
skia_ASM_FILES 			+= opts/memset32_neon
else
skia_ASM_FILES 			+= opts/memset.arm
endif
endif
endif

skia_CPP_FILES 			:= $(addprefix third/skia/,$(skia_CPP_FILES))
skia_ASM_FILES 			:= $(addprefix third/skia/,$(skia_ASM_FILES))
gbox2_CPP_FILES-$(G2_CONFIG_CORE_SKIA) += $(skia_CPP_FILES)
gbox2_ASM_FILES-$(G2_CONFIG_CORE_SKIA) += $(skia_ASM_FILES)
	
# demo
ifeq ($(G2_CONFIG_DEMO),y)
SUB_PROS 				= demo/$(G2_CONFIG_DEMO_TYPE)
endif

include $(PRO_DIR)/suffix.mak

