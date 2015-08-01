//
//  GameManager.cpp
//  Space Invaders
//
//  Created by Ramy Fawaz on 6/2/15.
//  Copyright (c) 2015 Ramy Fawaz. All rights reserved.
//


#include "GameManager.h"
#include "Player.h"
#include <iostream>

GameManager::GameManager()
{
    player = new Player();
}

bool GameManager::init()
{
    //Initialization flag
    bool success = true;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) //Setting to 1 is for linear filtering of textures
        {
            printf( "Linear Filtering failed to be enabled" );
        }
        
        //Create window function    *window name*     *x position*             *y position*             *width*       *height*       *window flags*
        gWindow = SDL_CreateWindow( "The Elder Scrolls 2D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window    *window*  *which renderer*   *use hardware for speed*   *sync monitor with frames*
            gRenderer = SDL_CreateRenderer( gWindow,      -1           , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF ); //Background color of renderer
                
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
                t_front_player = new Texture();
                t_front_player->setRenderer(gRenderer);
                player->setTexture(t_front_player);
                
                for (int i = 0; i < 4; i++)
                {
                    movementAnimations[i] = new Texture();
                    movementAnimations[i]->setRenderer(gRenderer);
                }
            }
        }
    }
    
    if (success) {
        if (loadMedia())
        {
            loadLevelOne();
            return true;
        }
        else
        {
            return false;
        }
        
    }
    
    
    return success;
}

bool GameManager::loadMedia()
{
    //Loading success flag
    bool success = true;
    
   if( !t_front_player->loadFromFile( "Textures/Player/Front.png" ) )
   {
       printf( "Failed to load player texture!\n" );
       success = false;
   }
    
    if( !movementAnimations[0]->loadFromFile( "Textures/Player/Front.png" ) )
    {
        printf( "Failed to load player texture!\n" );
        success = false;
    }
    
    if( !movementAnimations[1]->loadFromFile( "Textures/Player/Back.png" ) )
    {
        printf( "Failed to load player texture!\n" );
        success = false;
    }
    
    if( !movementAnimations[2]->loadFromFile( "Textures/Player/Side1.png" ) )
    {
        printf( "Failed to load player texture!\n" );
        success = false;
    }
    
    if( !movementAnimations[3]->loadFromFile( "Textures/Player/Side2.png" ) )
    {
        printf( "Failed to load player texture!\n" );
        success = false;
    }

    return success;
}

void GameManager::handleEvent(SDL_Event e)
{
    player->handleEvent(e);
}

void GameManager::handleCEvent(CEvent e, int information)
{

}

void GameManager::updatePosition()
{
   player->move();
}

void GameManager::renderObjects()
{
   player->render();
}

void GameManager::clearScreen()
{
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear( gRenderer );
}

void GameManager::updateScreen()
{
    SDL_RenderPresent( gRenderer );
}

void GameManager::loadLevelOne()
{
   player->setPos(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
}

void GameManager::checkCollisions()
{

}

void GameManager::close()
{
    //Free loaded images
    //shipTexture.free();
    
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}


SDL_Renderer* GameManager::getRenderer()
{
    return gRenderer;
}

GameManager* GameManager::getGameManager()
{
    if (gameManager == nullptr) {
        gameManager = new GameManager();
    }
    return gameManager;
}
