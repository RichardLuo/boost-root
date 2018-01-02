##################################################################
# author: Richard Luo                      
# date:   2013-03-20 15:22:08
#                                                                
##################################################################

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
include $(call get-mod-path, boost)/common.mk
include $(call get-mod-path, x-live)/paths.mk
include $(call get-mod-path, libjingle)/android_common.mk

LOCAL_MODULE := atomic_simple_test

LOCAL_CXX11_ENABLED := yes

LOCAL_SRC_FILES := atomic_simple_test.cpp

LOCAL_CFLAGS := \
	$(BOOST_CFLAGS) \

LOCAL_C_INCLUDES := \
	$(BOOST_INCLUDES)

LOCAL_SHARED_LIBRARIES := \
	libBoostAtomic

LOCAL_LDLIBS += -ldl -lrt -lpthread

LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_TAGS := eng

ifneq ($(TARGET_SIMULATOR),true)
LOCAL_C_INCLUDES += bionic		# very important!
LOCAL_C_INCLUDES += external/stlport/stlport 
LOCAL_SHARED_LIBRARIES += libstlport libdl
endif

include $(BUILD_EXECUTABLE)
