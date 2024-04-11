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

RAW_NAME = metro_short_path
BINARY_EXTENSION = .bin
PROGRAM_NAME = "$(RAW_NAME)$(BINARY_EXTENSION)"

OBJS = main.o       \
	   jsonparser.o \
	   graph.o

all: prepare build link

# preparing prerequisites before building project
prepare:
	@[ ! -d "$(BUILD_DIR)" ] && mkdir "$(BUILD_DIR)" || true

build: $(OBJS)

link: build
	cd "$(BUILD_DIR)" && $(CC) $(OBJS) $(CXXLDFLAGS) -o $(PROGRAM_NAME)

main.o: $(SRC_DIR)/main.cpp
	$(CC) $(SRC_DIR)/main.cpp -c $(CXXFLAGS) -o $(BUILD_DIR)/main.o

jsonparser.o: $(SRC_DIR)/jsonparser.cpp  $(INC_DIR)/jsonparser.h
	$(CC) $(SRC_DIR)/jsonparser.cpp -c $(CXXFLAGS) -o $(BUILD_DIR)/jsonparser.o

graph.o: $(SRC_DIR)/graph.cpp $(INC_DIR)/graph.h
	$(CC) $(SRC_DIR)/graph.cpp -c $(CXXFLAGS) -o $(BUILD_DIR)/graph.o

clean:
	@/bin/rm -rfv $(BUILD_DIR)/*

.PHONY: all prepare build link clean