UNAME := $(shell uname -s)


ifeq ($(UNAME), Linux)
	REST = -I/usr/include/freetype2 -lGL -lGLU -lSDL_image
endif

ifeq ($(UNAME), Darwin)
	REST = -I/usr/local/include/freetype2 -framework OpenGL -framework SDL_image
endif

all:
	g++ -o TheHeartProject *.cpp `sdl-config --cflags --libs` $(REST)

clean:
	rm -f TheHeartProject
