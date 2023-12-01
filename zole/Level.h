#ifndef LEVEL_H
#define LEVEL_H

#pragma once
#include <stdlib.h>
#include <iostream>
#include <map>
#include "TileMap.h"
#include "Messages.h"

class Level {
public:
    Level(int gridSize);
    ~Level();

    void generateMap();
    void levelUpdate();
    void ageCheck();

    TileMap titleMap;
    TileMap fMap;

    int* level;    
    int* levelAge; 
    int toolTitle = 0;

    int* fuelArr;  
    int fuelSpawnRate = 6;

    std::map<int, int> ageTimer;

private:
    sf::Sprite fuelSprite;
    sf::Texture fuelTexture;
    sf::Clock ageClock;
    sf::Clock fuelClock;
    int gridSize; 
};

#endif // LEVEL_H
