LOCAL_PATH:= $(call my-dir) # Get the local path of the project.

LOCAL_MODULE := cutils
LOCAL_SRC_FILES := libcutils.so
LOCAL_EXPORT_C_INCLUDES := ./include/
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := lhw
LOCAL_SRC_FILES := libhardware.so
LOCAL_SHARED_LIBRARIES := cutils
LOCAL_EXPORT_C_INCLUDES := ./include/libhardware
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:= test-hal
# LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../include
LOCAL_SRC_FILES:= hello.cpp
LOCAL_SHARED_LIBRARIES := lhw cutils
LOCAL_LDLIBS:= -llog
include $(BUILD_EXECUTABLE)

# # Test binary
# include $(CLEAR_VARS) # Clear all the variables with a prefix "LOCAL_"
# #LOCAL_SHARED_LIBRARIES:= ../libs/x86/liboboe.so
# LOCAL_SRC_FILES:=hello.cpp $(LOCAL_PATH)/../libs/x86/liboboe.so # Indicate the source code.
# LOCAL_EXPORT_C_INCLUDES := $(LOCAL_OBOE_PATH)/include $(LOCAL_OBOE_PATH)/src
# LOCAL_MODULE:= hello # The name of the binary.
# include $(BUILD_EXECUTABLE) # Tell ndk-build that we want to build a native executable.