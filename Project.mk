#################################################################################
# Project: AngryGL project
# Author: Ilija Djukic
#################################################################################

PROJECT_NAME := Test

EXTERNAL_FILES := \
	source/external/iniparser/dictionary.c \
	source/external/iniparser/iniparser.c

FRAMEWORKS_FILES := \
	source/frameworks/app/AppClient.cpp \
	source/frameworks/app/AppServer.cpp \
	source/frameworks/common/common.cpp \
	source/frameworks/common/matrix4.cpp \
	source/frameworks/common/mymath.cpp \
	source/frameworks/common/quat.cpp \
	source/frameworks/game/GameObject.cpp \
	source/frameworks/game/GameScene.cpp \
	source/frameworks/glplus/GLCamera.cpp \
	source/frameworks/glplus/GLColor.cpp \
	source/frameworks/glplus/GLFont.cpp \
	source/frameworks/glplus/GLTerrain.cpp \
	source/frameworks/glplus/GLTexture.cpp \
	source/frameworks/glplus/GLView.cpp \
	source/frameworks/utils/BMFont.cpp \
	source/frameworks/utils/stb_image.c

GAME_FILES := \
	source/game/GameClient.cpp \
	source/game/GameMain.cpp

PROJECT_FILES := \
	$(EXTERNAL_FILES) \
	$(FRAMEWORKS_FILES) \
	$(GAME_FILES)

PROJECT_PATHS := \
	-Iprebuilt/glfw/include \
	-Isource/external \
	-Isource/frameworks

PROJECT_LIBRARIES := \
	prebuilt/glfw/lib-mingw/libglfw.a

