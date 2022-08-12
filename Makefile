CXX=g++
CC=gcc
PREFIX?="./"
CXXFLAGS:=-Iinclude -std=gnu++17 -Wall -Wextra -O2 # This is for the C++ compiler
CPPFLAGS:=-D__PREFIX=$(PREFIX) # This is for the C PreProcessor
DBGFLAGS:=-D__PREFIX="./" -D_DBG -g # For the C PreProcessor when debugging
LDFLAGS:=-lglfw -lstdc++ -lGL -lGLEW -lm -lIL
# libs, in order of appearance: GLFW, GNU C++ Runtime, OpenGL, GLEW, Math, DevIL

.PHONY: all install clean
.SUFFIXES: .o .cpp .dvo
# .o is for standard object files, .cpp is for C++ source files,
# .dvo is for developer/debug object files (practically the same as normal objects, just different file extension)

OBJS=\
src/rendering/obj/tinyObjLoader.o \
src/rendering/obj/texture.o \
src/rendering/obj/objwrapper.o \
src/rendering/va.o \
src/rendering/triangle.o \
src/rendering/shaders.o \
src/rendering/camera.o \
src/proc.o \
src/main.o \

all: jord

jord: $(OBJS)
	$(CC) -o bin/$@ $(OBJS) $(LDFLAGS)

jord-dev: $(OBJS:.o=.dvo)
	$(CC) -o bin/$(@:-dev=) $(OBJS:.o=.dvo) $(LDFLAGS)

.cpp.o:
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(CPPFLAGS)

.cpp.dvo:
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(DBGFLAGS)

install: jord

clean:
	rm -f $(OBJS) $(OBJS:.o=.dvo) bin/jord
