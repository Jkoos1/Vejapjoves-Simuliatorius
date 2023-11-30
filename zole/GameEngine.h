#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#pragma once
#include "SFML/Graphics.hpp"
#include "Menu.h"
#include "TileMap.h"
#include "Player.h"
#include "Level.h"

class GameEngine {
public:
    GameEngine();         

    void initialize(); 
    void run();        
    void shutdown();   
    void resetGame();

private:
    bool isRunning;    
    bool isGameActive;    

    const int WINDOW_SIZE = 512;
    const int FRAMERATE_LIMIT = 60;

    sf::RenderWindow window;
    sf::Clock clock;
    Player player;
    Level level;
    Menu menu;

    void processInput();   
    void updateGame();     
    void render();         
};

#endif // GAMEENGINE_H