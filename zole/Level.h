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
    Level();

    void generateMap();
    void levelUpdate();
    void ageCheck();

    TileMap map;
    TileMap fMap;

    int level[256] = {};
    int levelAge[256] = {};  
    int toolTitle = 0;

    int fuelArr[256] = {};
    int fuelSpawnRate = 6;

    std::map<int, int> ageTimer;

private:
    sf::Sprite fuelSprite;
    sf::Texture fuelTexture;
    sf::Clock ageClock;
    sf::Clock fuelClock;
};

#endif // LEVEL_H
