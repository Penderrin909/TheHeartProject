/*
Creates a class to hold values to edit the OPENGL
 lookat function in engine::render()
*/

#ifndef ____Camera__
#define ____Camera__

class Camera
{
public:
    Camera();
    ~Camera();
    
    double XCamPos;
    double YCamPos;
    double lookAtX;
    double lookAtY;
    
    void setXCamMAX(int val);
    void setYCamMAX(int val);
    void getXCamPos(double playerX);
    void getYCamPos(double playerY);
    
private:
    
    int XCamMAX;
    int YCamMAX;
    
};

#endif /* defined(____Camera__) */
