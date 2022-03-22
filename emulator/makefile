LOCAL_PATH := $(dir $(lastword $(MAKEFILE_LIST)))

include $(LOCAL_PATH)/../config/common.mk

TARGET=libchip8.so

SOURCES := Processor.cpp

OUTPUT := $(PROJECT_ROOT)/bin/$(TARGET)

FLAGS += -shared

all: debug release

debug:
	$(CC) $(DEBUG_FLAGS) $(INCLUDES) $(FLAGS) $(SOURCES) -o $(OUTPUT) $(LIBS)

release:
	$(CC) $(FLAGS) $(INCLUDES) $(SOURCES) -o $(OUTPUT) $(LIBS)
