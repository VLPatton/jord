CXX=g++
CC=gcc
CXXFLAGS:=-Iinclude -std=gnu++17 -Wall -Wextra -O2
LDFLAGS:=-lglfw -lstdc++ -lGL -lGLEW -ldl -lm

.PHONY: all install clean
.SUFFIXES: .o .cpp

OBJS=\
src/obj/tinyObjLoader.o \
src/rendering/va.o \
src/rendering/triangle.o \
src/rendering/shaders.o \
src/rendering/camera.o \
src/proc.o \
src/main.o \

all: idea-game

idea-game: $(OBJS)
	$(CC) -o bin/$@ $(OBJS) $(LDFLAGS) -O2

.cpp.o:
	$(CXX) -c $< -o $@ $(CXXFLAGS)

install: idea-game

clean:
	rm -f $(OBJS)
