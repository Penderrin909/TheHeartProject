
#include "Player.hpp"

Player::Player()
{
    Xsize = 1, Ysize = 1;
    Xspeed = .1, Yspeed = -.1;

    health = 100;
}

Player::~Player()
{
    
}

void Player::getStartPos(double x, double y)
{
    Xpos = x;
    Ypos = y;
}