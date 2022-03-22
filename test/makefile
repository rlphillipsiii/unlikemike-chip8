LOCAL_PATH := $(dir $(lastword $(MAKEFILE_LIST)))

include $(LOCAL_PATH)/../config/common.mk

TARGET=chip8test

SOURCES := Chip8Test.cpp

OUTPUT := $(PROJECT_ROOT)/bin/$(TARGET)

LIBS += -lgtest_main
LIBS += -lgtest
LIBS += -lchip8

INCLUDES += -I$(PROJECT_ROOT)/emulator

all: debug release

debug:
	$(CC) $(DEBUG_FLAGS) $(INCLUDES) $(FLAGS) $(SOURCES) -o $(OUTPUT) $(LIBS)

release:
	$(CC) $(FLAGS) $(INCLUDES) $(SOURCES) -o $(OUTPUT) $(LIBS)
