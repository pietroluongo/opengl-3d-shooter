.DEFAULT_GOAL := dev

GIT_HASH = `git rev-parse HEAD`
COMPILE_TIME=`date +'%Y-%m-%d %H:%M:%S GMT+3'`

# the compiler: gcc for C program, define as g++ for C++
CC = gcc
CXX = g++

BUILD_DIR = build
IMGUI_DIR = libs/imgui
TINYXML_DIR = libs/tinyxml2

COMPILE_VARS = -DGIT_HASH="\"$(GIT_HASH)\"" -DCOMPILE_TIME="\"$(COMPILE_TIME)\""

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall -std=c++11 $(COMPILE_VARS)
LINKING = -lglut -lGL -lGLU

IMGUI_SOURCES_DIRTY := $(wildcard $(IMGUI_DIR)/*.cpp)
IMGUI_SOURCES_NO_PREFIX := $(subst $(IMGUI_DIR)/,,$(IMGUI_SOURCES_DIRTY))
IMGUI_SOURCES := $(IMGUI_SOURCES_NO_PREFIX:.cpp=)
IMGUI_OBJS := $(IMGUI_SOURCES:%=$(BUILD_DIR)/imgui/%.o)

TINYXML_SOURCES_DIRTY := $(wildcard $(TINYXML_DIR)/*.cpp)
TINYXML_SOURCES_NO_PREFIX := $(subst $(TINYXML_DIR)/,,$(TINYXML_SOURCES_DIRTY))
TINYXML_SOURCES := $(TINYXML_SOURCES_NO_PREFIX:.cpp=)
TINYXML_OBJS := $(TINYXML_SOURCES:%=$(BUILD_DIR)/tinyxml/%.o)

all: trabalhocg

dev: trabalhocg
	./trabalhocg /home/pietroluongo/ufes/arena_teste.svg

slow: remake dev

collisionTest: trabalhocg
	./trabalhocg /home/pietroluongo/ufes/collisionTest.svg

leakTest: trabalhocg
	valgrind ./trabalhocg /home/pietroluongo/ufes/arena_teste.svg

trabalhocg: trabalhocgDeps imgui tinyxml
	$(CXX) $(CFLAGS) -o $@ $(BUILD_DIR)/*.o $(BUILD_DIR)/imgui/*.o $(BUILD_DIR)/tinyxml/*.o $(LINKING)

run: trabalhocg
	./trabalhocg

imgui: $(IMGUI_OBJS)

tinyxml: $(TINYXML_OBJS)

$(BUILD_DIR)/tinyxml/%.o: $(TINYXML_DIR)/%.cpp | build_tinyxml
	$(CXX) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/imgui/%.o: $(IMGUI_DIR)/%.cpp | build_imgui
	$(CXX) $(CFLAGS) -o $@ -c $< 

build_imgui: build
	mkdir build/imgui -p

build_tinyxml: build
	mkdir build/tinyxml -p

build:
	mkdir build -p

clean:
	$(RM) $(BUILD_DIR)/*.o trabalhocg -rf

clean-full:
	$(RM) $(BUILD_DIR) trabalhocg -rf

remake: clean all

# Domain classes

trabalhocgDeps: \
	$(BUILD_DIR)/main.o \
	$(BUILD_DIR)/globalctx.o \
	$(BUILD_DIR)/game.o \
	$(BUILD_DIR)/player.o \
	$(BUILD_DIR)/debug.o \
	$(BUILD_DIR)/platform.o \
	$(BUILD_DIR)/glutCallbacks.o \
	$(BUILD_DIR)/camera.o \
	$(BUILD_DIR)/object.o \
	$(BUILD_DIR)/map.o \
	$(BUILD_DIR)/enemy.o \
	$(BUILD_DIR)/collider.o \
	$(BUILD_DIR)/projectile.o \
	$(BUILD_DIR)/character.o
	
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

$(BUILD_DIR)/platform.o: src/platform.cpp | build
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/glutCallbacks.o: src/glutCallbacks.cpp | build
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/camera.o: src/camera.cpp | build
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/object.o: src/object.cpp | build
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/map.o: src/map.cpp | build
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/enemy.o: src/enemy.cpp | build
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/collider.o: src/collider.cpp | build
	$(CXX) $(CFLAGS) -o $@ -c $<
	
$(BUILD_DIR)/projectile.o: src/projectile.cpp | build
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/character.o: src/character.cpp | build
	$(CXX) $(CFLAGS) -o $@ -c $<
