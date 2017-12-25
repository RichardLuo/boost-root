##################################################################
# author: Richard Luo                      
# date:   2013-03-20 15:22:08
#                                                                
##################################################################

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
include $(call get-mod-path, x-live)/paths.mk
include $(call get-mod-path, libjingle)/android_common.mk

LOCAL_MODULE := libBoostAtomic

LOCAL_CXX11_ENABLED := yes

LOCAL_SRC_FILES := lockpool.cpp

LOCAL_CFLAGS := \
	-D_STLP_USE_DYNAMIC_LIB=1 \
	-DBOOST_ATOMIC_STATIC_LINK=1 \

LOCAL_C_INCLUDES := \
	external/boost-root/boost_1_66_0

# LOCAL_SHARED_LIBRARIES := $(common_LOCAL_SHARED_LIBRARIES)

LOCAL_LDLIBS += -ldl -lrt -lpthread

LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_TAGS := eng

ifneq ($(TARGET_SIMULATOR),true)
LOCAL_C_INCLUDES += bionic		# very important!
LOCAL_C_INCLUDES += external/stlport/stlport 
LOCAL_SHARED_LIBRARIES += libstlport libdl
endif

include $(BUILD_SHARED_LIBRARY)
