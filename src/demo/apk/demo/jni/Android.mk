# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
include $(LOCAL_PATH)/../../../../../config.mak
include $(LOCAL_PATH)/../../../../../prefix.mak

LOCAL_MODULE    := demo
LOCAL_SRC_FILES := com_gbox2_DemoView.c demo.c
LOCAL_CFLAGS 	:= -I$(INC_DIR) -I$(SRC_DIR) -I$(PRO_DIR)/../tbox/pre/inc/$(PLAT)/$(ARCH) -DTB_PRINT_TAG=\"gbox2\" -DTB_TRACE_ENABLE -DTB_ASSERT_ENABLE
LOCAL_LDLIBS 	:= -L$(SYSROOT)/usr/lib -L$(LOCAL_PATH) -L$(LIB_DIR) -L$(SRC_DIR) -L$(PRO_DIR)/../tbox/pre/lib/$(PLAT)/$(ARCH) -lgbox2 -ltbox -llog
LOCAL_SHARED_LIBRARIES := libGLESv1_CM

include $(BUILD_SHARED_LIBRARY)
