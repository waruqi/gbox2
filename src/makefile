# sub-makefile
include $(PRO_DIR)/prefix.mak

# module name
NAMES 					= gbox2

# module type
gbox2_TYPE 				= LIB

# basic files
gbox2_C_FILES 			+= \
						gbox2 

gbox2_CPP_FILES-$(G2_CONFIG_CORE_SKIA) += \
						core/skia/path \
						core/skia/style \
						core/skia/bitmap \
						core/skia/painter \
						core/skia/clipper 

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
						prefix/version.h \
						core/prefix.h \
						core/path.h \
						core/style.h \
						core/bitmap.h \
						core/clipper.h \
						core/painter.h
	
	
# freetype files
freetype_C_FILES 		= \
						base/ftadvanc \
						base/ftcalc \
						base/ftdbgmem \
						base/ftgloadr \
						base/ftobjs \
						base/ftoutln \
						base/ftrfork \
						base/ftsnames \
						base/ftstream \
						base/fttrigon \
						base/ftutil \
						truetype/ttdriver \
						truetype/ttgload \
						truetype/ttgxvar \
						truetype/ttinterp \
						truetype/ttobjs \
						truetype/ttpic \
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
						autofit/afpic \
						autofit/afwarp \
						cache/ftcbasic \
						cache/ftccache \
						cache/ftccmap \
						cache/ftcglyph \
						cache/ftcimage \
						cache/ftcmanag \
						cache/ftcmru \
						cache/ftcsbits

freetype_INC_DIR 		:= libs/freetype/include
freetype_CFLAGS 		:= -DFT2_BUILD_LIBRARY
freetype_C_FILES 		:= $(addprefix libs/freetype/,$(freetype_C_FILES))
gbox2_C_FILES-$(G2_CONFIG_CORE_SKIA) 	+= $(freetype_C_FILES)
gbox2_CFLAGS-$(G2_CONFIG_CORE_SKIA) 	+= $(freetype_CFLAGS)
gbox2_INC_DIR-$(G2_CONFIG_CORE_SKIA) 	+= $(freetype_INC_DIR)
	
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
						core/SkMetaData \
						core/SkMMapStream \
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
						core/SkProcSpriteBlitter \
						core/SkPtrRecorder \
						core/SkQuadClipper \
						core/SkRasterClip \
						core/SkRasterizer \
						core/SkRect \
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
						core/SkXfermode 
	
skia_CPP_FILES 			:= $(addprefix libs/skia/,$(skia_CPP_FILES))
gbox2_CPP_FILES-$(G2_CONFIG_CORE_SKIA) += $(skia_CPP_FILES)
	
# demo
ifeq ($(G2_CONFIG_DEMO),y)
SUB_PROS 				= demo
endif

include $(PRO_DIR)/suffix.mak

