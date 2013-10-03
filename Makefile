#################################################################################
# Project: AngryGL project
# Author: Ilija Djukic
#
# Input variables:
#    TARGET
#    BUILD
#    PACKAGE
#################################################################################

TARGET := mingw
BUILD := debug

#################################################################################
# Tools
#################################################################################

CC := gcc
CPP := g++
RMDIR := rm -rf
MKDIR := mkdir -p

#################################################################################
# Compiler settings
#################################################################################

SRCS :=
INC_PATHS :=
LIB_PATHS :=
LIBS :=
SRC_RES :=

ifeq ($(BUILD),debug)
	OPT := -g -DDEBUG
else
	OPT := -Wall -O2
endif

#################################################################################
# Project
#################################################################################

include Project.mk

OUT_DIR := bin
OBJ_DIR := $(OUT_DIR)/obj/$(BUILD)
ONAME := $(OUT_DIR)/$(PROJECT_NAME)_$(BUILD)

SRCS += $(PROJECT_FILES)
INC_PATHS += $(PROJECT_PATHS)
LIBS += $(PROJECT_LIBRARIES)
SRC_RES += $(PROJECT_RESOURCES)

#################################################################################
# Target settings
#################################################################################

ifeq ($(TARGET),linux)
	LIBS += -lm -ldl -lGL -lGLU -lXrandr
endif

ifeq ($(TARGET),mingw)
	LIBS += -lgdi32 -lglu32 -lopengl32
	INC_PATHS += -I/usr/local/include
	LIB_PATHS += -L/usr/local/lib
endif

#################################################################################
# Build rules
#################################################################################

CFLAGS := $(OPT) $(INC_PATHS) $(LIB_PATHS)
OBJS := $(foreach file, $(SRCS), $(OBJ_DIR)/$(strip $(basename $(file))).o)
RES := $(foreach file, $(SRC_RES), $(OBJ_DIR)/$(strip $(basename $(file))).res)

$(OBJ_DIR)/%.res: %.rc
	@echo Win32 Resource
	@-$(MKDIR) "$(@D)"
	@windres.exe -i $< -J rc -o $@ -O coff

$(OBJ_DIR)/%.o: %.cpp
	@echo Compiling $<
	@-$(MKDIR) "$(@D)"
	@$(CPP) -c $(CFLAGS) $(DEFINES) -o $@ $<

$(OBJ_DIR)/%.o: %.cc
	@echo Compiling $<
	@-$(MKDIR) "$(@D)"
	@$(CPP) -c $(CFLAGS) $(DEFINES) -o $@ $<

$(OBJ_DIR)/%.o:  %.c
	@echo Compiling $<
	@-$(MKDIR) "$(@D)"
	@$(CC) -c $(CFLAGS) $(DEFINES) -o $@ $<

#################################################################################
# Build rules
#################################################################################

all: build

info:
	@echo ' ======================='
	@echo '  OUTPUT=$(ONAME)'
	@echo '  TARGET=$(TARGET)'
	@echo '  BUILD=$(BUILD)'
	@echo ' ======================='

build: info $(OBJS) $(RES)
	@$(CPP) $(CFLAGS) -o $(ONAME) $(OBJS) $(RES) $(LIBS)
	@echo 'Finished building target: $(ONAME)'

clean: info
	-$(RMDIR) $(OUT_DIR)
	@echo 'Intermediate files removed'

run: build
	./$(ONAME)

help:
	@echo " "
	@echo " -----------------------------------------------------------------------------"
	@echo " Usage:"
	@echo " "
	@echo " make <rule> TARGET=<target> BUILD=<build>"
	@echo "   <rule>       :  all, build, clean, help"
	@echo "   <target>     :  linux, mingw"
	@echo "   <build>      :  release, debug"
	@echo " -----------------------------------------------------------------------------"
	@echo " "
