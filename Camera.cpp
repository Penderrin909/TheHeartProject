//changes the values of the opengl lookat function in render()
#include "Camera.hpp"

Camera::Camera()
{
    
}

//get max x value for the current map
void Camera::setXCamMAX(int val)
{
    XCamMAX = val;
}

//get max y value for the current map
void Camera::setYCamMAX(int val)
{
    YCamMAX = val;
}

//playerX is the players position so
// return playerX if player is not half a screen away
// from the left most or right most side
// if he is return the last value that he was
double Camera::getXCamPos(double playerX)
{
    if((playerX+5.5)>=XCamMAX)
    {
        
    }
    else if((playerX-5.5)<=0)
    {
        
    }
    else
    {
        XCamPos = playerX;
    }
}

//X and y are dealt with the same way.
double Camera::getYCamPos(double playerY)
{
    if((playerY+5.5)>=YCamMAX)
    {
        
    }
    else if((playerY-4.5)<=0)
    {
        
    }
    else
    {
        YCamPos = playerY;
    }
}


Camera::~Camera()
{
    
}