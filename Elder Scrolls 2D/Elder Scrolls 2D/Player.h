//
//  Player.h
//  The Elder Scrolls 2D
//
//  Created by Ramy Fawaz on 7/31/15.
//  Copyright (c) 2015 Ramy Fawaz. All rights reserved.
//

#ifndef __The_Elder_Scrolls_2D__Player__
#define __The_Elder_Scrolls_2D__Player__

#include "Texture.h"
#include "Timer.h"
#include "CEvent.h"
#include "Animation_Player.h"

class Player
{

public:
	Player();
	Player(Texture* playerTexture);

	void setTexture (Texture* playerTexture);
    void handleEvent( SDL_Event& e );
    void setPos(int xPos, int yPos);
    void setAnimation(a_PlayerMovement animation, int frame = 0);
    void move();
    void render();

    int getWidth()	const {return width;};
    int getHeight()	const {return height;};
    int getPosX()	const {return posX;};
    int getPosY()	const {return posY;};

private:
    void changeDirection();
    
    bool isStationary();

    bool direction[4] = {0,0,0,0};

	const int width = 65; //50
    const int height = 165;//165
    const int velocity = 3;
    const int walkingAnimationDelta = 200;

    int posX, posY;
    int velX, velY;
    int movementCounter;

    a_PlayerMovement currentAnimation;

    Timer time_movement;

    Texture* texture;
};


#endif /* defined(__The_Elder_Scrolls_2D__Player__) */
