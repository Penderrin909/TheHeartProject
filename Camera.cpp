//changes the values of the opengl lookat function in render()
#include "Camera.hpp"

Camera::Camera()
{
    XCamPos = 5.5;
    YCamPos = 4.5;
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
void Camera::getXCamPos(double playerX)
{
    if(((playerX+5.5)>=XCamMAX)&&((playerX-5.5)<=0))
    {
        XCamPos = playerX;
    }
    else if((playerX+5.5)>=XCamMAX)
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
void Camera::getYCamPos(double playerY)
{
    if(((playerY+5.5)>=YCamMAX)&&((playerY-4.5)<=0))
    {
        XCamPos = playerY;
    }
    else if((playerY+5.5)>=YCamMAX)
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