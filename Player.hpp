//Player class inherits from Character

#ifndef ____player__
#define ____player__

#include "Character.hpp"

class Player: public Character
{
public:
    
    Player();
    ~Player();
    
    void getStartPos(double x, double y);
    
};

#endif /* defined(____player__) */
