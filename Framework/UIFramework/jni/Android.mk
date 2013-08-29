LOCAL_PATH:= $(call my-dir)/
LOCAL_PATH:=$(subst jni/../jni/,jni/,$(LOCAL_PATH))

#编译参数设置
#MYCOMPILE_FLAG:= -g -D ANDROID  -fpermissive -DNOEXCEPTION
MYCOMPILE_FLAG:= -g -D ANDROID  -fpermissive -fexceptions
MY_DEFLIB:= -llog -ldl

##################################################ndbg##################################################
include $(CLEAR_VARS)
LOCAL_PATH_TEMP = $(LOCAL_PATH)
#======================= 头文件设置 =======================
#头文件目录
INC_DIR:=../

# 需要排除的目录,要以'%'打头,中间用空格分隔
EXCLUDE_INC_DIRS := %C3/IOS %C3/Win 

#取得头文件的目录及子目录
INC_DIRTREE := $(shell find $(LOCAL_PATH)$(INC_DIR) -maxdepth 99 -type d)
INC_DIRTREE := $(filter-out $(EXCLUDE_INC_DIRS),$(INC_DIRTREE))


#======================= 源码文件设置 =======================
#源码根目录
SRC_DIR:=../

# 需要排除的目录,要以'%'打头,中间用空格分隔
EXCLUDE_SRC_DIRS := %.svn %prop-base %props %text-base %tmp %../../Android %../../Env %../../Env/ani %../../Env/data %../../Env/fonts %../../Env/ini %../../Env/sound %../../IOSProject %../../IOSProject/build %../../IOSProject/NDBG.xcodeproj %../../IOSProject/Resources %../../XPProject/Debug %../../XPProject/res 
EXCLUDE_SRCINC_DIRS := %.svn %prop-base %props %text-base %tmp %../../Android %../../Env %../../Env/ani %../../Env/data %../../Env/fonts %../../Env/ini %../../Env/sound %../../IOSProject %../../IOSProject/build %../../IOSProject/NDBG.xcodeproj %../../IOSProject/Resources %../../XPProject/Debug %../../XPProject/res 

# 需要排除的文件,要以'%'打头,中间用空格分隔
EXCLUDE_SRC_FILES := %.svn %prop-base %props %text-base %tmp %.proto

# 取得源码文件的目录及子目录
SRCINC_DIRTREE := $(shell find $(LOCAL_PATH)$(SRC_DIR) -maxdepth 99 -type d)
SRCINC_DIRTREE := $(filter-out $(EXCLUDE_SRCINC_DIRS),$(SRCINC_DIRTREE))

SRCDIRTREE := $(shell find $(LOCAL_PATH)$(SRC_DIR) -maxdepth 99 -type d)
SRCDIRTREE := $(filter-out $(EXCLUDE_SRC_DIRS),$(SRCDIRTREE))

#生成编译的源文件
SRC_FILES       := $(foreach sdir,$(SRCDIRTREE),$(wildcard $(sdir)/*.cpp))
SRC_FILES       += $(foreach sdir,$(SRCDIRTREE),$(wildcard $(sdir)/*.c))
SRC_FILES:= $(subst $(LOCAL_PATH),,$(SRC_FILES))

#过滤掉某些不能编译进去的cpp
LOCAL_SRC_FILES := $(filter-out $(EXCLUDE_SRC_FILES), $(SRC_FILES))


#======================= 生成 UIFramework 库 =======================

LOCAL_C_INCLUDES:=$(INC_DIRTREE)
LOCAL_C_INCLUDES+=$(SRCINC_DIRTREE)
LOCAL_MODULE:=uiframework_static
LOCAL_LDLIBS := $(MY_DEFLIB)
LOCAL_CFLAGS := $(MYCOMPILE_FLAG)
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)
LOCAL_EXPORT_CFLAGS := $(LOCAL_CFLAGS)
LOCAL_EXPORT_LDLIBS := $(LOCAL_LDLIBS)

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static basecode_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions) \
$(call import-module,BaseCode/jni)

