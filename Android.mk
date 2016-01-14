LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := oxygine-movie_static
LOCAL_MODULE_FILENAME := liboxygine-movie

TH := deps/libtheora/lib

LOCAL_SRC_FILES := \
	$(TH)/analyze.c \
	$(TH)/apiwrapper.c \
	$(TH)/bitpack.c \
	$(TH)/cpu.c \
	$(TH)/decapiwrapper.c \
	$(TH)/decinfo.c \
	$(TH)/decode.c \
	$(TH)/dequant.c \
	$(TH)/encapiwrapper.c \
	$(TH)/encfrag.c \
	$(TH)/encinfo.c \
	$(TH)/encode.c \
	$(TH)/enquant.c \
	$(TH)/fdct.c \
	$(TH)/fragment.c \
	$(TH)/huffdec.c \
	$(TH)/huffenc.c \
	$(TH)/idct.c \
	$(TH)/info.c \
	$(TH)/internal.c \
	$(TH)/mathops.c \
	$(TH)/mcenc.c \
	$(TH)/quant.c \
	$(TH)/rate.c \
	$(TH)/state.c \
	$(TH)/tokenize.c \
	src/MovieSprite.cpp \
	src/theora/MovieSpriteTheora.cpp


OXYGINE_SRC := $(LOCAL_PATH)/../oxygine-framework/oxygine/src
OXYGINE_SOUND_SRC := $(LOCAL_PATH)/../oxygine-sound

LOCAL_C_INCLUDES := $(OXYGINE_SRC)/ \
					$(LOCAL_PATH)/src \
					$(LOCAL_PATH)/deps/libtheora/include \
					$(OXYGINE_SOUND_SRC)/dependencies/openal-android/jni/OpenAL/include \
					$(OXYGINE_SOUND_SRC)/dependencies/tremor/Tremor \
					$(OXYGINE_SOUND_SRC)/dependencies/libogg/include

LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/src
LOCAL_EXPORT_CFLAGS += $(LOCAL_CFLAGS)


include $(BUILD_STATIC_LIBRARY)

$(call import-module, SDL)
$(call import-module, oxygine-sound)