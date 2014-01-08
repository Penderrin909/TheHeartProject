UNAME := $(shell uname -s)


ifeq ($(UNAME), Linux)
	REST = -I/usr/include/freetype2 -lGL -lGLU
endif

ifeq ($(UNAME), Darwin)
	REST = -I/usr/local/include/freetype2 -framework OpenGL
endif

all:
	g++ -o test *.cpp `sdl-config --cflags --libs` $(REST)
