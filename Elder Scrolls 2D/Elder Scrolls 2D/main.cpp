//
//  main.cpp
//  Space Invaders
//
//  Created by Ramy Fawaz on 5/17/15.
//  Copyright (c) 2015 Ramy Fawaz. All rights reserved.
//

#include "GameManager.h"
#include <iostream>
#include "Timer.h"
#include <string> 
#include <sstream>

const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

bool init();                        //Starts up SDL and creates window
bool loadMedia();                   //Loads media

void close();                       //Frees media and shuts down SDL

GameManager* GameManager::gameManager = nullptr;
GameManager* mainGame;


int main( int argc, char* args[] )
{
    mainGame = GameManager::getGameManager();
    
    if( !mainGame->init() )
    {printf( "Initialization did not work properly\n" );}
    else
    {
        bool quit = false;
        SDL_Event e;
        
        //The frames per second timer
        Timer fpsTimer;
        
        //The frames per second cap timer
        Timer capTimer;
        
        //Start counting frames per second
        int countedFrames = 0;
        fpsTimer.start();
            
        while( !quit )
        {
            //Start cap timer
            capTimer.start();
            
            while( SDL_PollEvent( &e ) != 0 )
            {
                if( e.type == SDL_QUIT )
                { quit = true; }
                
                else if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN )
                {
 
                }
                    
                mainGame->handleEvent(e);
            }
            
            //Calculate and correct fps
            float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
            if( avgFPS > 2000000 )
            {
                avgFPS = 0;
            }
            
            
            //mainGame->checkCollisions();
            
            mainGame->updatePosition();

            mainGame->clearScreen();
                
            mainGame->renderObjects();
                
            mainGame->updateScreen();
            ++countedFrames;
            
            //If frame finished early
            int frameTicks = capTimer.getTicks();
            if( frameTicks < SCREEN_TICK_PER_FRAME )
            {
                //Wait remaining time
                SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
            }
        }
        
    }
    mainGame->close();
    
    return 0;
}
