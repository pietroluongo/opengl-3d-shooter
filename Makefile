.DEFAULT_GOAL := all
# the compiler: gcc for C program, define as g++ for C++
CC = gcc
CXX = g++

BUILD_DIR = build
IMGUI_DIR = libs/imgui

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall -std=c++11
LINKING = -lglut -lGL -lGLU

IMGUI_SOURCES_DIRTY := $(wildcard $(IMGUI_DIR)/*.cpp)
IMGUI_SOURCES_NO_PREFIX := $(subst $(IMGUI_DIR)/,,$(IMGUI_SOURCES_DIRTY))
IMGUI_SOURCES := $(IMGUI_SOURCES_NO_PREFIX:.cpp=)
IMGUI_OBJS := $(IMGUI_SOURCES:%=$(BUILD_DIR)/imgui/%.o)

trabalhocg: trabalhocgDeps imgui
	$(CXX) $(CFLAGS) -o $@ $(BUILD_DIR)/*.o $(BUILD_DIR)/imgui/*.o $(LINKING)

run: trabalhocg
	./trabalhocg

all: trabalhocg

imgui: $(IMGUI_OBJS)

$(BUILD_DIR)/imgui/%.o: $(IMGUI_DIR)/%.cpp | build_imgui
	$(CXX) $(CFLAGS) -o $@ -c $< 

build_imgui: build
	mkdir build/imgui -p

build:
	mkdir build -p

clean:
	$(RM) $(BUILD_DIR)/*.o trabalhocg -rf

clean-full:
	$(RM) $(BUILD_DIR) trabalhocg -rf

trabalhocgDeps: $(BUILD_DIR)/main.o $(BUILD_DIR)/globalctx.o $(BUILD_DIR)/game.o $(BUILD_DIR)/player.o $(BUILD_DIR)/debug.o

$(BUILD_DIR)/globalctx.o: src/globalCtx.cpp | build
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/game.o: src/game.cpp | build
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/player.o: src/player.cpp | build
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/main.o: src/main.cpp | build
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/debug.o: src/debug.cpp | build
	$(CXX) $(CFLAGS) -o $@ -c $<