CONFIG_PATH := $(dir $(lastword $(MAKEFILE_LIST)))

PROJECT_ROOT := $(CONFIG_PATH)/..

CC := g++

DEBUG_FLAGS := -g
FLAGS := -O2 -std=c++20 -Wall -Werror

LIBS := -L$(PROJECT_ROOT)/bin
INCLUDES :=
