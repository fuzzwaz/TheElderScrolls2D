//
//  GameManager.cpp
//  Space Invaders
//
//  Created by Ramy Fawaz on 6/2/15.
//  Copyright (c) 2015 Ramy Fawaz. All rights reserved.
//


#include "GameManager.h"
#include "Player.h"
#include "Animation_Player.h"
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
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF ); //Background color of renderer
                
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
                t_front_player = new Texture();
                t_front_player->setRenderer(gRenderer);
                
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 7; ++j)
                    {
                        movementAnimations[i][j] = new Texture();
                        movementAnimations[i][j]->setRenderer(gRenderer);
                    }
                }

                player->setTexture(movementAnimations[a_PlayerMovement::BACKWARDS][0]);
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
    
    if( !movementAnimations[a_PlayerMovement::FORWARD][0]->loadFromFile( "Textures/Player/Front.png" ) )
    {
        printf( "Failed to load player texture!\n" );
        success = false;
    }
    
    if( !movementAnimations[a_PlayerMovement::BACKWARDS][0]->loadFromFile( "Textures/Player/Back.png" ) )
    {
        printf( "Failed to load player texture!\n" );
        success = false;
    }
    
    if( !movementAnimations[a_PlayerMovement::RIGHT_SIDE][0]->loadFromFile( "Textures/Player/Side1.png" ) )
    {
        printf( "Failed to load player texture!\n" );
        success = false;
    }
    
    if( !movementAnimations[a_PlayerMovement::LEFT_SIDE][0]->loadFromFile( "Textures/Player/Side2.png" ) )
    {
        printf( "Failed to load player texture!\n" );
        success = false;
    }

    if( !movementAnimations[a_PlayerMovement::BACKWARDS][1]->loadFromFile( "Textures/Player/Walking/Back_Walk_1.png" ) )
    {
        printf( "Failed to load player texture!\n" );
        success = false;
    }

    if( !movementAnimations[a_PlayerMovement::BACKWARDS][2]->loadFromFile( "Textures/Player/Walking/Back_Walk_2.png" ) )
    {
        printf( "Failed to load player texture!\n" );
        success = false;
    }

    if( !movementAnimations[a_PlayerMovement::BACKWARDS][3]->loadFromFile( "Textures/Player/Walking/Back_Walk_3.png" ) )
    {
        printf( "Failed to load player texture!\n" );
        success = false;
    }

    if( !movementAnimations[a_PlayerMovement::BACKWARDS][4]->loadFromFile( "Textures/Player/Walking/Back_Walk_4.png" ) )
    {
        printf( "Failed to load player texture!\n" );
        success = false;
    }

    if( !movementAnimations[a_PlayerMovement::BACKWARDS][5]->loadFromFile( "Textures/Player/Walking/Back_Walk_5.png" ) )
    {
        printf( "Failed to load player texture!\n" );
        success = false;
    }

    if( !movementAnimations[a_PlayerMovement::BACKWARDS][6]->loadFromFile( "Textures/Player/Walking/Back_Walk_6.png" ) )
    {
        printf( "Failed to load player texture!\n" );
        success = false;
    }
    
    if( !movementAnimations[a_PlayerMovement::RIGHT_SIDE][1]->loadFromFile( "Textures/Player/Walking/Right_Walk_1.png" ) )
    {
        printf( "Failed to load player texture!\n" );
        success = false;
    }
    
    if( !movementAnimations[a_PlayerMovement::RIGHT_SIDE][2]->loadFromFile( "Textures/Player/Walking/Right_Walk_2.png" ) )
    {
        printf( "Failed to load player texture!\n" );
        success = false;
    }
    
    if( !movementAnimations[a_PlayerMovement::RIGHT_SIDE][3]->loadFromFile( "Textures/Player/Walking/Right_Walk_3.png" ) )
    {
        printf( "Failed to load player texture!\n" );
        success = false;
    }
    
    if( !movementAnimations[a_PlayerMovement::RIGHT_SIDE][4]->loadFromFile( "Textures/Player/Walking/Right_Walk_4.png" ) )
    {
        printf( "Failed to load player texture!\n" );
        success = false;
    }
    
    if( !movementAnimations[a_PlayerMovement::RIGHT_SIDE][5]->loadFromFile( "Textures/Player/Walking/Right_Walk_5.png" ) )
    {
        printf( "Failed to load player texture!\n" );
        success = false;
    }
    
    if( !movementAnimations[a_PlayerMovement::RIGHT_SIDE][6]->loadFromFile( "Textures/Player/Walking/Right_Walk_6.png" ) )
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
