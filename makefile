UNAME := $(shell uname -s)


ifeq ($(UNAME), Linux)
	REST = -lGL -lGLU
endif

ifeq ($(UNAME), Darwin)
	REST = -framework OpenGL
endif

all:
	g++ -o test *.cpp `sdl-config --cflags --libs` $(REST)
