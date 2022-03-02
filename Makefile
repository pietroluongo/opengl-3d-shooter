.DEFAULT_GOAL := dev

ifndef $(RENDERER)
RENDERER = GLFW
endif

GIT_HASH = `git rev-parse HEAD`
# GIT_HASH = ""
COMPILE_TIME=`date +'%Y-%m-%d %H:%M:%S GMT+3'`

# the compiler: gcc for C program, define as g++ for C++
CC = gcc

ifeq ($(ARCH), WIN)
CXX = x86_64-w64-mingw32-g++
else
CXX = g++
endif

BUILD_DIR = build
IMGUI_DIR = libs/imgui
TINYXML_DIR = libs/tinyxml2

COMPILE_VARS = -DGIT_HASH="\"$(GIT_HASH)\"" -DCOMPILE_TIME="\"$(COMPILE_TIME)\""

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -std=c++11 -g -Wall $(COMPILE_VARS) $(LINKING)

ifeq ($(ARCH), WIN)
ifeq ($(RENDERER), GLUT)
LINKING=-static -lfreeglut -lopengl32 -Wl,--subsystem,windows -Ilibs/win/freeglut/include -Llibs/win/freeglut/lib/x64
else
LINKING=-static -lglfw3 -lopengl32 -lgdi32 -Wl,--subsystem,windows -Ilibs/win/glfw/include -Llibs/win/glfw/lib/
endif
else
ifeq ($(RENDERER), GLUT)
LINKING = -lglut -lGL -lGLU
else
LINKING = -lglfw -lGL -lGLU
endif
endif

ifeq ($(RENDERER), GLFW)
CFLAGS := $(CFLAGS) -DUSE_GLFW
else
CFLAGS := $(CFLAGS) -DUSE_GLUT
endif

IMGUI_SOURCES_DIRTY := $(wildcard $(IMGUI_DIR)/*.cpp)
IMGUI_SOURCES_NO_PREFIX := $(subst $(IMGUI_DIR)/,,$(IMGUI_SOURCES_DIRTY))
IMGUI_SOURCES := $(IMGUI_SOURCES_NO_PREFIX:.cpp=)
IMGUI_OBJS := $(IMGUI_SOURCES:%=$(BUILD_DIR)/imgui/%.o)

ifeq ($(RENDERER), GLUT)
IMGUI_OBJS := $(IMGUI_OBJS) $(BUILD_DIR)/imgui/imgui_impl_glut.o
else
IMGUI_OBJS := $(IMGUI_OBJS) $(BUILD_DIR)/imgui/imgui_impl_glfw.o
endif

TINYXML_SOURCES_DIRTY := $(wildcard $(TINYXML_DIR)/*.cpp)
TINYXML_SOURCES_NO_PREFIX := $(subst $(TINYXML_DIR)/,,$(TINYXML_SOURCES_DIRTY))
TINYXML_SOURCES := $(TINYXML_SOURCES_NO_PREFIX:.cpp=)
TINYXML_OBJS := $(TINYXML_SOURCES:%=$(BUILD_DIR)/tinyxml/%.o)

all: trabalhocg

dev: trabalhocg
	./trabalhocg.exe /home/pietroluongo/ufes/arena_teste.svg

slow: remake dev

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

$(BUILD_DIR)/imgui/%.o: $(IMGUI_DIR)/glut/%.cpp | build_imgui
	$(CXX) $(CFLAGS) -o $@ -c $< 

$(BUILD_DIR)/imgui/%.o: $(IMGUI_DIR)/glfw/%.cpp | build_imgui
	$(CXX) $(CFLAGS) -o $@ -c $< 

build_imgui: build
	mkdir build/imgui -p

build_tinyxml: build
	mkdir build/tinyxml -p

build:
	mkdir build -p

clean: clean-full

clean-partial:
	$(RM) $(BUILD_DIR)/*.o trabalhocg -rf

clean-full:
	$(RM) $(BUILD_DIR) trabalhocg trabalhocg.exe -rf

remake: clean all

# Domain classes

CALLBACK_DEPS = ""

ifeq ($(RENDERER), GLUT)
	CALLBACK_DEPS = $(BUILD_DIR)/glutCallbacks.o
else
	CALLBACK_DEPS = $(BUILD_DIR)/glfwCallbacks.o
endif

trabalhocgDeps: \
	$(BUILD_DIR)/main.o \
	$(BUILD_DIR)/globalctx.o \
	$(BUILD_DIR)/game.o \
	$(BUILD_DIR)/player.o \
	$(BUILD_DIR)/debug.o \
	$(BUILD_DIR)/platform.o \
	$(BUILD_DIR)/camera.o \
	$(BUILD_DIR)/object.o \
	$(BUILD_DIR)/map.o \
	$(BUILD_DIR)/enemy.o \
	$(BUILD_DIR)/collider.o \
	$(BUILD_DIR)/projectile.o \
	$(BUILD_DIR)/character.o \
	$(BUILD_DIR)/solidUtils.o \
	$(CALLBACK_DEPS)


$(BUILD_DIR)/globalctx.o: src/globalCtx.cpp include/globalCtx.h include/constants.h | build
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/game.o: src/game.cpp include/game.h include/constants.h | build
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/player.o: src/player.cpp include/player.h include/constants.h | build
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/main.o: src/main.cpp src/_main.h include/constants.h | build
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/debug.o: src/debug.cpp include/debug.h include/constants.h | build
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/platform.o: src/platform.cpp include/platform.h include/constants.h | build
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/glutCallbacks.o: src/glutCallbacks.cpp include/constants.h | build
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/camera.o: src/camera.cpp include/camera.h include/constants.h | build
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/object.o: src/object.cpp include/object.h include/constants.h | build
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/map.o: src/map.cpp include/map.h include/constants.h | build
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/enemy.o: src/enemy.cpp include/enemy.h include/constants.h | build
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/collider.o: src/collider.cpp include/collider.h include/constants.h | build
	$(CXX) $(CFLAGS) -o $@ -c $<
	
$(BUILD_DIR)/projectile.o: src/projectile.cpp include/projectile.h include/constants.h | build
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/character.o: src/character.cpp include/character.h include/constants.h | build
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/glfwCallbacks.o: src/glfwCallbacks.cpp include/glfwCallbacks.h include/constants.h | build
	$(CXX) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/solidUtils.o: src/solidUtils.cpp include/solidUtils.h include/constants.h | build
	$(CXX) $(CFLAGS) -o $@ -c $<
