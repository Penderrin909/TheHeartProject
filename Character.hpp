
#ifndef ____Character__
#define ____Character__

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
    
};


#endif /* defined(____Character__) */
