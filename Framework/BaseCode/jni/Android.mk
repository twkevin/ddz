LOCAL_PATH:= $(call my-dir)/
LOCAL_PATH:=$(subst jni/../jni/,jni/,$(LOCAL_PATH))

#�����������
#MYCOMPILE_FLAG:= -g -D ANDROID  -fpermissive -DNOEXCEPTION
MYCOMPILE_FLAG:= -g -D ANDROID  -fpermissive -fexceptions
MY_DEFLIB:= -llog -ldl

##################################################BaseCode##################################################
include $(CLEAR_VARS)
LOCAL_PATH_TEMP = $(LOCAL_PATH)
#======================= ͷ�ļ����� =======================
#ͷ�ļ�Ŀ¼
INC_DIR:=../

# ��Ҫ�ų���Ŀ¼,Ҫ��'%'��ͷ,�м��ÿո�ָ�
EXCLUDE_INC_DIRS := %C3/IOS %C3/Win 

#ȡ��ͷ�ļ���Ŀ¼����Ŀ¼
INC_DIRTREE := $(shell find $(LOCAL_PATH)$(INC_DIR) -maxdepth 99 -type d)
INC_DIRTREE := $(filter-out $(EXCLUDE_INC_DIRS),$(INC_DIRTREE))


#======================= Դ���ļ����� =======================
#Դ���Ŀ¼
SRC_DIR:=../

# ��Ҫ�ų���Ŀ¼,Ҫ��'%'��ͷ,�м��ÿո�ָ�
EXCLUDE_SRC_DIRS := %.svn %prop-base %props %text-base %tmp %../../Android %../../Env %../../Env/ani %../../Env/data %../../Env/fonts %../../Env/ini %../../Env/sound %../../IOSProject %../../IOSProject/build %../../IOSProject/NDBG.xcodeproj %../../IOSProject/Resources %../../XPProject/Debug %../../XPProject/res 
EXCLUDE_SRCINC_DIRS := %.svn %prop-base %props %text-base %tmp %../../Android %../../Env %../../Env/ani %../../Env/data %../../Env/fonts %../../Env/ini %../../Env/sound %../../IOSProject %../../IOSProject/build %../../IOSProject/NDBG.xcodeproj %../../IOSProject/Resources %../../XPProject/Debug %../../XPProject/res 

# ��Ҫ�ų����ļ�,Ҫ��'%'��ͷ,�м��ÿո�ָ�
EXCLUDE_SRC_FILES := %.svn %prop-base %props %text-base %tmp %.proto

# ȡ��Դ���ļ���Ŀ¼����Ŀ¼
SRCINC_DIRTREE := $(shell find $(LOCAL_PATH)$(SRC_DIR) -maxdepth 99 -type d)
SRCINC_DIRTREE := $(filter-out $(EXCLUDE_SRCINC_DIRS),$(SRCINC_DIRTREE))

SRCDIRTREE := $(shell find $(LOCAL_PATH)$(SRC_DIR) -maxdepth 99 -type d)
SRCDIRTREE := $(filter-out $(EXCLUDE_SRC_DIRS),$(SRCDIRTREE))

#���ɱ����Դ�ļ�
SRC_FILES       := $(foreach sdir,$(SRCDIRTREE),$(wildcard $(sdir)/*.cpp))
SRC_FILES       += $(foreach sdir,$(SRCDIRTREE),$(wildcard $(sdir)/*.c))
SRC_FILES:= $(subst $(LOCAL_PATH),,$(SRC_FILES))

#���˵�ĳЩ���ܱ����ȥ��cpp
LOCAL_SRC_FILES := $(filter-out $(EXCLUDE_SRC_FILES), $(SRC_FILES))


#======================= ���� BaseCode �� =======================

LOCAL_C_INCLUDES:=$(INC_DIRTREE)
LOCAL_C_INCLUDES+=$(SRCINC_DIRTREE)
LOCAL_MODULE:=basecode_static
LOCAL_LDLIBS := $(MY_DEFLIB)
LOCAL_CFLAGS := $(MYCOMPILE_FLAG)
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)
LOCAL_EXPORT_CFLAGS := $(LOCAL_CFLAGS)
LOCAL_EXPORT_LDLIBS := $(LOCAL_LDLIBS)
LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static  
include $(BUILD_STATIC_LIBRARY)

$(call import-module,cocos2dx)
