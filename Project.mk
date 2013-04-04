#################################################################################
# Project: AngryGL project
# Author: Ilija Djukic
#################################################################################

PROJECT_NAME := AngryGL_Test

EXTERNAL_FILES := \
	source/external/iniparser/dictionary.c \
	source/external/iniparser/iniparser.c

FRAMEWORKS_FILES := \
	source/frameworks/app/AppClient.cpp \
	source/frameworks/app/AppServer.cpp \
	source/frameworks/common/Color.cpp \
	source/frameworks/common/common.cpp \
	source/frameworks/common/matrix4.cpp \
	source/frameworks/common/mymath.cpp \
	source/frameworks/common/quat.cpp

PROJECT_FILES := \
	$(EXTERNAL_FILES) \
	$(FRAMEWORKS_FILES) \
	source/game/GameClient.cpp \
	source/game/GameMain.cpp

PROJECT_PATHS := \
	-Iprebuilt/glfw/include \
	-Isource/external \
	-Isource/frameworks

PROJECT_LIBRARIES := \
	prebuilt/glfw/lib-mingw/libglfw.a
