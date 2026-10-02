.PHONY: clean

PROJECT_NAME ?= game
OBJS = $(shell find src -name '*.cpp')

CXX ?= g++
CXXFLAGS += -Wall -std=c++23 -O1
BUILD_DIR = build


RAYLIB_FLAGS = $(shell pkg-config --cflags --libs raylib)

$(BUILD_DIR)/$(PROJECT_NAME): $(OBJS) | $(BUILD_DIR)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(RAYLIB_FLAGS)

$(BUILD_DIR): 
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

