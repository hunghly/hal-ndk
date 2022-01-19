# Oboe Shared Library
# LOCAL_PATH:= $(call my-dir) # Get the local path of the project.
# include $(CLEAR_VARS) # Clear all the variables with a prefix "LOCAL_"
# LOCAL_MODULE:= oboe
# LOCAL_OBOE_PATH:= $(LOCAL_PATH)/oboe
# LOCAL_C_INCLUDES:=$(LOCAL_OBOE_PATH)/include $(LOCAL_OBOE_PATH)/src
# AAUDIO_FILE_LIST := $(wildcard $(LOCAL_PATH)/oboe/src/aaudio/*.cpp)
# COMMON_FILE_LIST := $(wildcard $(LOCAL_PATH)/oboe/src/common/*.cpp)
# FIFO_FILE_LIST := $(wildcard $(LOCAL_PATH)/oboe/src/fifo/*.cpp)
# RESAMPLER_FILE_LIST := $(wildcard $(LOCAL_PATH)/oboe/src/flowgraph/resampler/*.cpp)
# FLOWGRAPH_FILE_LIST := $(wildcard $(LOCAL_PATH)/oboe/src/flowgraph/*.cpp)
# OPENSLES_FILE_LIST := $(wildcard $(LOCAL_PATH)/oboe/src/opensles/*.cpp)
# LOCAL_SRC_FILES := $(AAUDIO_FILE_LIST:$(LOCAL_PATH)/%=%) \
# $(COMMON_FILE_LIST:$(LOCAL_PATH)/%=%) \
# $(FIFO_FILE_LIST:$(LOCAL_PATH)/%=%) \
# $(RESAMPLER_FILE_LIST:$(LOCAL_PATH)/%=%) \
# $(FLOWGRAPH_FILE_LIST:$(LOCAL_PATH)/%=%) \
# $(OPENSLES_FILE_LIST:$(LOCAL_PATH)/%=%)
# LOCAL_LDLIBS:= -llog -lOpenSLES -laaudio
# include $(BUILD_SHARED_LIBRARY)

# Test binary
LOCAL_PATH := $(call my-dir) # Get the local path of the project.
include $(CLEAR_VARS) # Clear all the variables with a prefix "LOCAL_"
#LOCAL_SHARED_LIBRARIES:= $(LOCAL_PATH)/../../libs/x86/liboboe
LOCAL_SRC_FILES:=hello.cpp  # Indicate the source code.
LOCAL_MODULE:= hello # The name of the binary.
include $(BUILD_EXECUTABLE) # Tell ndk-build that we want to build a native executable.