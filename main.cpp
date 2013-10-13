
#include "engine.hpp"

int main(int argv, char* argc[])
{
    //initializes everything
    engine engine1;
    
    engine1.init();
    
    while(engine1.running == true)
    {
        engine1.event();
        
        engine1.render();
    }
    
    return 0;
}