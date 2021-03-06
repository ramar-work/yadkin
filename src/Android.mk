LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main 

SDL_PATH := ../SDL/

SDL_TTF_PATH := ../SDL_ttf/

# Includes have to be referenced absolutely
# $TOP/platforms/android-project/app/jni/src
LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/$(SDL_TTF_PATH)/include

# Add your application source files here...
LOCAL_SRC_FILES := main.c 

# Reference any static/shared libraries
LOCAL_SHARED_LIBRARIES := SDL2 SDL2_ttf

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
