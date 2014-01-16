
#ifndef ____Character__
#define ____Character__

#ifdef __linux__
#include <GL/gl.h>
#include <GL/glu.h>
#elif __APPLE__
#include <OpenGL/GL.h> //MAC OS STUFF
#include <OpenGL/GLU.h>
#endif

class Character
{
public:
    
    Character();
    ~Character();
    
    void init();
    void draw();
    
    double Xpos, Ypos;
    double Xsize, Ysize, Xspeed, Yspeed;
    
    int health;
    
    bool lastRight;
    bool right;
    
    GLuint texMoveRight;
    GLuint texMoveLeft;
};


#endif /* defined(____Character__) */
