//
//  Player.cpp
//  The Elder Scrolls 2D
//
//  Created by Ramy Fawaz on 7/31/15.
//  Copyright (c) 2015 Ramy Fawaz. All rights reserved.
//

#include "Player.h"


Player::Player() 
: posX(100), posY(100), velX(0), velY(0)
{}

Player::Player(Texture* playerTexture) 
: posX(100), posY(100), velX(0), velY(0)
{
    setTexture(playerTexture);
}

void Player::setTexture(Texture *playerTexture)
{
    texture = playerTexture;
}

void Player::setPos(int xPos, int yPos)
{
	posX = xPos;
	posY = yPos;
}

void Player::handleEvent(SDL_Event& e)
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_LEFT: velX -= velocity; break;
            case SDLK_RIGHT: velX += velocity; break;
            case SDLK_a: velX -= velocity; break;
            case SDLK_d: velX += velocity; break;

            case SDLK_UP: velY -= velocity; break;
            case SDLK_DOWN: velY += velocity; break;
            case SDLK_w: velY -= velocity; break;
            case SDLK_s: velY += velocity; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )         {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_LEFT: velX += velocity; break;
            case SDLK_RIGHT: velX -= velocity; break;
            case SDLK_a: velX += velocity; break;
            case SDLK_d: velX -= velocity; break;

            case SDLK_UP: velY += velocity; break;
            case SDLK_DOWN: velY -= velocity; break;
            case SDLK_w: velY += velocity; break;
            case SDLK_s: velY -= velocity; break;
        }
    }
}

void Player::move()
{
    posX += velX;
    posY += velY;
}

void Player::render()
{
    SDL_Rect* test_Rectangle = new SDL_Rect;
    test_Rectangle->x = 0;
    test_Rectangle->y = 0;
    test_Rectangle->w = width;
    test_Rectangle->h = height;
    
    texture->render(posX, posY, test_Rectangle);
}
