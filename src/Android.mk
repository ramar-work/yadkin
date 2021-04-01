LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main 

# Includes have to be referenced absolutely
# $TOP/platforms/android-project/app/jni/src
LOCAL_C_INCLUDES := /home/ramar/prj/app/screentest_c/include

# Add your application source files here...
LOCAL_SRC_FILES := main.c 

# Reference any static/shared libraries
LOCAL_SHARED_LIBRARIES := SDL2

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

LOCAL_CFLAGS += \
	-Wall -Wextra \

include $(BUILD_SHARED_LIBRARY)
