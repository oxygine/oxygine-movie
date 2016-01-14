LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := main

#SDK_ROOT points to folder with SDL and oxygine-framework
LOCAL_SRC_FILES := ../../../../../..//SDL/src/main/android/SDL_android_main.c


SRC := ../../../src
LOCAL_SRC_FILES += \
	$(SRC)/entry_point.cpp \
	$(SRC)/example.cpp \
	$(SRC)/Test.cpp 


LOCAL_STATIC_LIBRARIES := oxygine-framework_static oxygine-sound_static oxygine-movie_static
LOCAL_SHARED_LIBRARIES := SDL2

include $(BUILD_SHARED_LIBRARY)


#import from NDK_MODULE_PATH defined in build.cmd
$(call import-module, oxygine-framework)
$(call import-module, oxygine-movie)
$(call import-module, oxygine-sound)
