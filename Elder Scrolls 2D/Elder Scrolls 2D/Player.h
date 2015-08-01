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
#include "CEvent.h"

class Player
{

public:
	Player();
	Player(Texture* playerTexture);

	void setTexture (Texture* playerTexture);
    void handleEvent( SDL_Event& e );
    void setPos(int xPos, int yPos);
    void move();
    void render();

    int getWidth()	const {return width;};
    int getHeight()	const {return height;};
    int getPosX()	const {return posX;};
    int getPosY()	const {return posY;};

private:

	const int width = 50;
    const int height = 140;
    const int velocity = 3;

    int posX, posY;
    int velX, velY;
    Texture* texture;

};

//testing

#endif /* defined(__The_Elder_Scrolls_2D__Player__) */