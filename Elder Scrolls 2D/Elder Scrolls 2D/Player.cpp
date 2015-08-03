//
//  Player.cpp
//  The Elder Scrolls 2D
//
//  Created by Ramy Fawaz on 7/31/15.
//  Copyright (c) 2015 Ramy Fawaz. All rights reserved.
//

#include "Player.h"
#include "GameManager.h"
#include <iostream>


Player::Player() 
: posX(100), posY(100), velX(0), velY(0), movementCounter(1)
{}

Player::Player(Texture* playerTexture) 
: posX(100), posY(100), velX(0), velY(0), movementCounter(1)
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

void Player::setAnimation(a_PlayerMovement animation, int frame)
{
    setTexture(GameManager::getGameManager()->movementAnimations[animation][movementCounter]);
    currentAnimation = animation;
}

void Player::handleEvent(SDL_Event& e)
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_a:
                velX -= velocity;
                if (isStationary()){setAnimation(a_PlayerMovement::LEFT_SIDE);}
                if (!time_movement.isStarted()){time_movement.start();}
                direction[a_Directions::LEFT] = true;
                break;
            case SDLK_d:
                velX += velocity;
                if (isStationary()){setAnimation(a_PlayerMovement::RIGHT_SIDE);}
                if (!time_movement.isStarted()){time_movement.start();}
                direction[a_Directions::RIGHT] = true;
                break;
            case SDLK_w:
                velY -= velocity;
                if (isStationary()){setAnimation(a_PlayerMovement::FORWARD);}
                if (!time_movement.isStarted()){time_movement.start();}
                direction[a_Directions::UP] = true;
                break;
            case SDLK_s:
                velY += velocity;
                if (isStationary()){setAnimation(a_PlayerMovement::BACKWARDS);}
                if (!time_movement.isStarted()){time_movement.start();}
                direction[a_Directions::DOWN] = true;
                break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )         {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_a:
                velX += velocity;
                direction[a_Directions::LEFT] = false;
                if (isStationary()){time_movement.stop();}
                changeDirection();
                break;
            case SDLK_d:
                velX -= velocity;
                direction[a_Directions::RIGHT] = false;
                if (isStationary()){time_movement.stop();}
                changeDirection();
                break;
            case SDLK_w:
                velY += velocity;
                direction[a_Directions::UP] = false;
                if (isStationary()){time_movement.stop();}
                changeDirection();
                break;
            case SDLK_s:
                velY -= velocity;
                direction[a_Directions::DOWN] = false;
                if (isStationary()){time_movement.stop();}
                changeDirection();
                break;
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
    
    

    if (!isStationary() && (time_movement.getTicks() > walkingAnimationDelta)
        && (currentAnimation == a_PlayerMovement::BACKWARDS || currentAnimation == a_PlayerMovement::RIGHT_SIDE))
    {
        movementCounter++;
        if (movementCounter > 6) {movementCounter = 1;}
        setAnimation(currentAnimation, movementCounter);
        time_movement.start();
    }
    
    texture->render(posX, posY, test_Rectangle);

}

void Player::changeDirection()
{
    if (direction[a_Directions::UP])
    {
        setAnimation(a_PlayerMovement::FORWARD);
    }
    else if (direction[a_Directions::DOWN])
    {
        setAnimation(a_PlayerMovement::BACKWARDS);
    }
    else if (direction[a_Directions::LEFT])
    {
        setAnimation(a_PlayerMovement::LEFT_SIDE);
    }
    else if (direction[a_Directions::RIGHT])
    {
        setAnimation(a_PlayerMovement::RIGHT_SIDE);
    }
}

bool Player::isStationary()
{
    return (!direction[a_Directions::UP] &&
            !direction[a_Directions::DOWN] &&
            !direction[a_Directions::RIGHT] &&
            !direction[a_Directions::LEFT]);
}
