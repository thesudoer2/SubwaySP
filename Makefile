CC = gcc
CXXVER = -std=c++17
CXXDEBUG = -ggdb3
CXXLDFLAGS = -lstdc++
CXXINCLUDE = -I.
CXXWARNING = -Wall

# Get value of "BUILD_TYPE" from environment
BUILD_TYPE_VALUE := $(shell echo $$BUILD_TYPE)

ifeq ($(BUILD_TYPE_VALUE), Debug)
	CXXOPTIMIZE := -O0
	CXXFLAGS := $(CXXVER) $(CXXINCLUDE) $(CXXOPTIMIZE) $(CXXWARNING) $(CXXDEBUG)
else
	CXXOPTIMIZE := -O3
	CXXFLAGS := $(CXXVER) $(CXXINCLUDE) $(CXXOPTIMIZE) $(CXXWARNING)
endif

BUILD_DIR = build
SRC_DIR = src
INC_DIR = include
RES_DIR = res

RAW_NAME = subwaysp
BINARY_EXTENSION =
PROGRAM_NAME = $(RAW_NAME)$(BINARY_EXTENSION)

# Installation related variables and target
INSTALL = cp -pPR
INSTALL_DIR := /usr/local/bin

OBJS = $(BUILD_DIR)/main.o       \
	   $(BUILD_DIR)/jsonparser.o \
	   $(BUILD_DIR)/graph.o      \
	   $(BUILD_DIR)/stations.o

all: prepare build $(BUILD_DIR)/$(PROGRAM_NAME)

# preparing prerequisites before building project
prepare:
	@[ ! -d "$(BUILD_DIR)" ] && mkdir "$(BUILD_DIR)" || true

build: $(OBJS)

$(BUILD_DIR)/$(PROGRAM_NAME): build
	$(CC) $(OBJS) $(CXXLDFLAGS) -o $(BUILD_DIR)/$(PROGRAM_NAME)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CC) $(SRC_DIR)/main.cpp -c $(CXXFLAGS) -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/jsonparser.o: $(SRC_DIR)/jsonparser.cpp  $(INC_DIR)/jsonparser.h
	$(CC) $(SRC_DIR)/jsonparser.cpp -c $(CXXFLAGS) -o $(BUILD_DIR)/jsonparser.o

$(BUILD_DIR)/graph.o: $(SRC_DIR)/graph.cpp $(INC_DIR)/graph.h
	$(CC) $(SRC_DIR)/graph.cpp -c $(CXXFLAGS) -o $(BUILD_DIR)/graph.o

$(BUILD_DIR)/stations.o: $(SRC_DIR)/stations.cpp
	$(CC) $(SRC_DIR)/stations.cpp -c $(CXXFLAGS) -o $(BUILD_DIR)/stations.o

install: all
	mkdir -vp $(INSTALL_DIR)
	$(INSTALL) $(BUILD_DIR)/$(PROGRAM_NAME) $(INSTALL_DIR)

uninstall:
	@/bin/rm -rfv "$(INSTALL_DIR)/$(PROGRAM_NAME)"

clean:
	@/bin/rm -rfv $(BUILD_DIR)/*

.PHONY: all prepare build $(BUILD_DIR)/$(PROGRAM_NAME) clean install uninstall