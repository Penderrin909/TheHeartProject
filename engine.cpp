
#include "engine.hpp"

engine::engine()
{
    Surf_Display = NULL;
    textSurf = NULL;
    running = true;
}

engine::~engine()
{
    
}

void engine::init()
{
    SDL_Init(SDL_INIT_EVERYTHING/*|SDL_INIT_NOPARACHUTE*/);
    
    Surf_Display = SDL_SetVideoMode( screenSize[0], screenSize[1], 32, SDL_OPENGL );
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    //angleX = 0.0, angleY = 0.0;
    //Gy = 1.0f;
    g = .012, jumpA = 0;
    
    //SDL_WM_GrabInput(SDL_GRAB_ON);
    
    getNewMap();
    
    for(int j = 0; j<xMAX; j++)
    {
        for(int i = 0; i<yMAX; i++)
        {
            if(mapVCorrect[i][j]== 2)
            {
                playerStartX = j;
                playerStartY = i;
                player.getStartPos(playerStartX,playerStartY);
                
                Cam.getXCamPos(player.Xpos);
                Cam.getYCamPos(player.Ypos);
                
                //std::cout<<Cam.XCamPos<<" "<<Cam.YCamPos<<"\n"<<player.Xpos<<" "<<player.Ypos<<"\n";
            }
        }
    }
    
    delayTime = 0, nextA = 0, nextB = 0;
    
    loadTexture("tex1_alt.png", firstBlock);
    loadTexture("tex2_right.png", player.texMoveRight);
    loadTexture("tex2_left.png", player.texMoveLeft);
    
    SDL_FreeSurface(textSurf);
}

void engine::getNewMap()
{
    //read in value for 1st map
    readMap("maps/3.map");
    
    //get MAX x and y coordinate of map file
    Cam.setXCamMAX(xMAX);
    Cam.setYCamMAX(yMAX);
}

void engine::render()
{
    //get Camera positions
    
    
    //clears the screen's color and depth (default is black but can change with glClearColor(...))
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //drawing to an area starting at the bottom left, 640 wide, 480 high.
    glViewport(0,0,screenSize[0],screenSize[1]);
    //OpenGL is a state machine. tell it that future commands changing the matrix are to change OpenGL's projection matrix
    glMatrixMode(GL_PROJECTION);
    //Reset the projection matrix
    glLoadIdentity();
    //Multiply a perspective projection matrix into opengls projection matrix
    gluPerspective(45.0, (double)(screenSize[0])/(double)(screenSize[1]), 0.1f, 100.0f);
    //tell it that future commands changing the matric are to change the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    
    //reset the modelview matrix
    glLoadIdentity();
    //multiply opengls modelview matrix with a transform matric that simulates a camera at (0,0,-1) looking towards the location (0,0,0) with up defined to be (0,1,0)
    //gluLookAt(Cam.XCamPos, Cam.YCamPos, 10,Cam.XCamPos, Cam.YCamPos, 0, 0, 1, 0);
    gluLookAt(Cam.XCamPos, Cam.YCamPos, 10,Cam.XCamPos, Cam.YCamPos, 0, 0, 1, 0); //DEFAULT
    //gluLookAt(0, 5, 10,Cam.XCamPos, Cam.YCamPos, 0, 0, 1, 0);
    //x,y,z
    
    //load texture for boxes..
    glBindTexture(GL_TEXTURE_2D, firstBlock); //select which texture
    glEnable(GL_TEXTURE_2D); //tell opengl to use the texture
    for(int i = 0; i<yMAX; i++)
    {
        for(int j = 0; j<xMAX; j++)
        {
            if(mapVCorrect[i][j] >= 10)
            {
                drawSquare(j,i); //check if block in vector should be drawn
            }
        }
    }
    
    glDisable(GL_TEXTURE_2D);
    
    determineLeftOrRight(player);
    
    glEnable(GL_TEXTURE_2D);
    
    
    glTranslatef(player.Xpos,player.Ypos,0);
    
    // DRAW PLAYER
    drawPlayer();
    
    glDisable(GL_TEXTURE_2D);
    
    //double buffered
    SDL_GL_SwapBuffers();
    
}

void engine::determineLeftOrRight(Character &mover)
{
    if(mover.Xspeed > 0)
    {
        mover.right = true;
        mover.lastRight = true;
        glBindTexture(GL_TEXTURE_2D, player.texMoveRight);
    }
    else if(mover.Xspeed < 0)
    {
        mover.right = false;
        mover.lastRight = false;
        glBindTexture(GL_TEXTURE_2D, player.texMoveLeft);
    }
    else if(mover.Xspeed == 0)
    {
        if(mover.lastRight == true) glBindTexture(GL_TEXTURE_2D, player.texMoveRight);
        else if(mover.lastRight == false) glBindTexture(GL_TEXTURE_2D, player.texMoveLeft);
    }
}

void engine::event()
{//SDL_WM_GrabInput
    
    SDL_PumpEvents();
    
    Uint8 *keyboard_state = SDL_GetKeyState(NULL);
    //SDL_GetMouseState(&Xpos,&Ypos);
    //SDL_GetRelativeMouseState(&xrel,&yrel);
    
    if(keyboard_state[SDLK_q] || keyboard_state[SDLK_ESCAPE])
    {
        running = false;
    }
    
    if((keyboard_state[SDLK_d]||keyboard_state[SDLK_RIGHT]))
    {
        player.Xspeed = .1; //player.Xspeed = .1
    }
    else if((keyboard_state[SDLK_a]||keyboard_state[SDLK_LEFT]))
    {
        player.Xspeed = -.1;
    }
    else player.Xspeed = 0;
    
    
    collisionDetect(player);
    
    //Check collisions of player and more objects if needed
    
    /*
    if(keyboard_state[SDLK_w]||keyboard_state[SDLK_UP])
    {
        player.Yspeed = .1;
    }
    else if(keyboard_state[SDLK_s]||keyboard_state[SDLK_DOWN])
    {
        player.Yspeed = -.1;
    }
    else player.Yspeed = 0;
     */
    
    if(keyboard_state[SDLK_SPACE]&&(player.Yspeed == 0)) //Gravity for player
    {
        jumpA = .25;
    }
    else
    {
        jumpA = 0;
    }
    
    //std::cout<<player.Xspeed<<" XSPEED"<<" "<<player.Yspeed<<" YSPEED\n";
    
    
    //Checks
    /*std::cout<<"X = "<<player.Xpos<<"|||| Y = "<<player.Ypos<<std::endl;
    if(player.Xpos<-.5||player.Xpos>10.5)
    {
        std::cout<<"X OUT\n";
    }
    if(player.Ypos<1||player.Ypos>9)
    {
        std::cout<<"Y OUT\n";
    }*/
    
    move(player);
}

void engine::readMap(string mapFile) // takes the map file and reads it into the vector mapV
{
    /*
     3 4 sample map file 3 = xMAX 4 = yMAX
     xxx
     xxx
     xxx
     xxx
     */
    
    int rowNum = 0; //used to track the multiplier for y^2-rowNum*y
    vector<int> row;
    
    ifstream map;
    map.open(mapFile.c_str());
    int c;
    mapV.clear();
    
    map >> xMAX;
    map >> yMAX;
    
    while(!map.eof())
    {
        for(int yCount = 0; yCount<yMAX; yCount++)
        {
            
             for(int xCount = 0; xCount<xMAX; xCount++)
             {
                 map >> c; //puts an element into int c
                 row.push_back(c); // c is then put into a temporary 1 dimensional vector
             }
            mapV.push_back(row); //the whole temporary vector is then placed into mapV as a whole row
            mapVCorrect.push_back(row); // go ahead and make the corrected vector same length
            row.clear(); // clears row to be used again
             
        }
    
    }
    
    //rotates array upside down to correct for X and Y differences between array and space
    for(int k = 0; k<yMAX; k++)
    {
        for(int l = 0; l<xMAX; l++)
        {
            mapVCorrect[yMAX-k-1][l] = mapV[k][l];
     
        }
    }
    
    //check vector components
    /*mapVCorrect.begin();
    for(int i = 0; i<yMAX;i++)
    {
        for(int j = 0;j<xMAX;j++)
        {
            std::cout<<mapVCorrect[i][j]<<" ";
        }
    }*/
    //x and y are switched in the vectors... not sure how to fix..
    
    map.close();
    
}

//draws a cube starting from the upper left hand corner
void engine::drawSquare(float startx, float starty)
{
    glBegin(GL_POLYGON);
    //glColor3f(1.0f,1.0f,1.0f); // red + green + blue
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(startx,starty,0.0f);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(startx+1,starty,0.0f);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(startx+1,starty-1,0.0f);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(startx,starty-1,0.0f);
    glEnd();

    /*glBegin(GL_LINE_LOOP);
    glColor3f(1.0f,1.0f,1.0f); // red + green + blue
    glVertex3f(startx,starty,0.0f);
    glVertex3f(startx+1,starty,0.0f);
    glVertex3f(startx+1,starty-1,0.0f);
    glVertex3f(startx,starty-1,0.0f);
    glEnd();*/
}

void engine::collisionDetect(Character &player)
{ // x and y are player position
    
    
    //std::cout<<player.Yspeed<<"\n";
    //check in negative X direction on player
    if((player.Xspeed < 0)&&((mapVCorrect[(int)(trunc(player.Ypos+1))][(int)(trunc(player.Xpos-.01))] >= 10)||(mapVCorrect[(int)(trunc(player.Ypos+2))][(int)(trunc(player.Xpos-.01))] >= 10))) //add .001 to help with bad truncation
     {
         player.Xpos -= player.Xspeed;
     }
    
    //check in positive X direction on player
     if((player.Xspeed > 0)&&((mapVCorrect[(int)(trunc(player.Ypos+1))][(int)trunc((player.Xpos+1.01))] >= 10)||(mapVCorrect[(int)(trunc(player.Ypos+2))][(int)trunc((player.Xpos+1.01))] >= 10))) //add .001 to help with bad truncation
     {
         player.Xpos -= player.Xspeed;
         
     }
    
    //check in negative Y direction of player
    if((player.Yspeed < 0)&&((mapVCorrect[(int)(trunc(player.Ypos+.999+player.Yspeed))][(int)(trunc(player.Xpos+.001))] >= 10)||(mapVCorrect[(int)(trunc(player.Ypos+.999+player.Yspeed))][(int)(trunc(player.Xpos+.999))] >= 10))) //add .001 to help with bad truncation
    {
        player.Yspeed -= player.Yspeed;
    }
    
    //check in Y positive direction
    if((player.Yspeed > 0)&&((mapVCorrect[(int)(trunc(player.Ypos+2))][(int)(trunc(player.Xpos+.001))] >= 10)||(mapVCorrect[(int)(trunc(player.Ypos+2))][(int)(trunc(player.Xpos+.999))] >= 10))) //add .001 to help with bad truncation //1.001
    {
        player.Ypos -= player.Yspeed;
        player.Yspeed = -.001;
        jumpA = 0;
    }
    
    
    //std::cout<<"___"<<player.Yspeed<<"____\n";
    //std::cout<<" X: "<<trunc(player.Xpos+0.0)<<" Y: "<<trunc(player.Ypos+1.0)<<" MapV: "<<mapVCorrect[(int)(trunc(player.Ypos+1))][(int)trunc((player.Xpos))]<<"\n";
    //std::cout<<" Xreal: "<<(player.Xpos)<<" Yreal: "<<(player.Ypos)<<"\n";
    
}


//moves objects about the origin
void engine::move(Character &player)
{
    player.Xpos += player.Xspeed;
    player.Ypos += player.Yspeed;
    player.Yspeed -= g-jumpA;
    
    Cam.getXCamPos(player.Xpos);
    Cam.getYCamPos(player.Ypos);
}

//Draws the player (currently a square...) perhaps move this to the player class DUH
void engine::drawPlayer()
{
    glTranslatef(0,0,0);
    
    glBegin(GL_POLYGON);
    //glColor3f(1.0f,0.0f,1.0f); // red + green + blue
    glTexCoord2f(1.0f,1.0f); // (1,1)
    glVertex3f(0.0f,0.0f,0.0f);
    glTexCoord2f(0.0f,1.0f); // (0,1)
    glVertex3f(1.0f,0.0f,0.0f);
    glTexCoord2f(0.0f,0.0f); // (0,0)
    glVertex3f(1.0f,1.0f,0.0f);
    glTexCoord2f(1.0f,0.0f); // (1,0)
    glVertex3f(0.0f,1.0f,0.0f);
    glEnd();
    
    /*
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f,0.0f,1.0f); // red + green + blue
    glVertex3f(0.0,0.0,0.0f);
    glVertex3f(1.0,0.0,0.0f);
    glVertex3f(1.0,1.0,0.0f);
    glVertex3f(0.0,1.0,0.0f);
    glEnd();
    */
    
}

void engine::loadTexture(const string textureName, GLuint &texN)
{
    string image = "textures/"+textureName;
    
    std::cout<<image<<"\n";
    
    textSurf = IMG_Load(image.c_str());
    if(textSurf==NULL)
	{
        std::cout<<"Error: no "<<textureName<<" found!\n";
		running = false;
	}
    
    glGenTextures(1,&texN);
    glBindTexture(GL_TEXTURE_2D, texN);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textSurf->w, textSurf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textSurf->pixels);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
}

void engine::checkFrames()
{
    //nextA, nextB to track FPS
    nextB = SDL_GetTicks();
    if((nextB-nextA) < ((1/float(MAXfps))*1000))
    {
        //std::cout<<nextB-nextA<<"\n";
        SDL_Delay(((1/float(MAXfps))*1000)-(nextB-nextA));
    }
    nextA = nextB;
    
    
    //std::cout<<player.Yspeed<<"\n";
}

void engine::quit()
{
    
}
