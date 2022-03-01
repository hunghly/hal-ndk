LOCAL_PATH:= $(call my-dir)

LOCAL_MODULE := cutils
LOCAL_SRC_FILES := ./libcutils.so
# LOCAL_EXPORT_C_INCLUDES := ./include/
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:= hal-ndk
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../include
LOCAL_SRC_FILES:= hal-ndk.cpp hardware.c audio_hw.c
# LOCAL_SHARED_LIBRARIES := cutils
LOCAL_LDLIBS:= -llog
LOCAL_LDFLAGS:= -Wl,-rpath,/system/lib/,--enable-new-dtags # might not be needed
# LOCAL_LDFLAGS:= -Wl,-rpath,/system/lib64/,--enable-new-dtags # might not be needed

include $(BUILD_EXECUTABLE)