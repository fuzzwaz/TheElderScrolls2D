//
//  GameManager.h
//  Space Invaders
//
//  Created by Ramy Fawaz on 6/2/15.
//  Copyright (c) 2015 Ramy Fawaz. All rights reserved.
//

#ifndef Space_Invaders_GameManager_h
#define Space_Invaders_GameManager_h

#include "Texture.h"
#include "CEvent.h"
#include "vector"

class Player;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 750;

class GameManager
{
public:
    
    bool init();
    bool loadMedia();
    
    void loadLevelOne();
    void handleEvent(SDL_Event e);
    void handleCEvent(CEvent e, int = -1);
    void updatePosition();
    void renderObjects();
    void clearScreen();
    void updateScreen();
    void close();
    void checkCollisions();
    
    SDL_Renderer* getRenderer();
    static GameManager* getGameManager();
    
    Texture* movementAnimations[4];
    
private:
    
    GameManager();
    
    SDL_Window* gWindow = NULL;         //Main Window
    SDL_Renderer* gRenderer = NULL;     //Window Renderer
    Texture* t_front_player = NULL;
    Player* player;

    static GameManager* gameManager;

};
#endif
