#ifndef ENGINE_HPP
#define ENGINE_HPP


#ifdef __linux__
#include <GL/gl.h>
#include <GL/glu.h>
#elif __APPLE__
#include <OpenGL/GL.h> //MAC OS STUFF
#include <OpenGL/GLU.h>
#endif


#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>

#include <cmath>

/*#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>*/

//#include <FTGL/ftgl.h>

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Player.hpp"
#include "Camera.hpp"

using std::vector;
using std::string;
using std::ifstream;


const int screenSize[2] = {640, 480};
const float pi = 3.14159265359;
const int MAXfps = 35;

class engine
{
public:
    
    engine();
    ~engine();
    
    void init();
    void render();
    void event();
    void quit();
    void getNewMap();
    void readMap(string mapFile);
    void drawSquare(float startx, float starty);
    void drawPlayer();
    void loadTexture(const string textureName,GLuint &texN);
    
    void move(Character &);
    void collisionDetect(Character &);
    
    void checkFrames();
    
    Player player;
    Camera Cam;
    
    SDL_Surface *textSurf;
    SDL_Surface *Surf_Display;
    bool running;
    
    SDL_Event events;
    
private:
    
    //double angleX, angleY;
    //int xrel, yrel;
    //float Gy; //Ground position in relation to player
    double g, jumpA;
    
    double playerStartX, playerStartY;
    
    int xMAX, yMAX;
    vector<vector <int> > mapV;
    vector<vector <int> > mapVCorrect;
    
    //Frame check
    int delayTime,nextA, nextB;
    
    //textures
    GLuint firstBlock;
    GLuint playerTex;
    
};


#endif /* ENGINE_HPP */
