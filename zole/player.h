#ifndef PLAYER_H
#define PLAYER_H

#pragma once
#include "SFML/Graphics.hpp"
#include "Level.h"
#include "Menu.h"
#include "Messages.h"
#include <iostream>
#include <string>

class Player : public sf::Transformable {
public:
    Player(int GRID_SIZE);

    void changeSpriteDirection(int input);
    void action();
    void reset();
    void consumeFuel();
    void addFuel();
    void movePlayer();
    void performAction();
    void updateTitlePos();
    void interactWithLevel(Level& level);

    const int MAX_X = 480;
    const int MIN_X = 0;
    const int MAX_Y = 480;
    const int MIN_Y = 0;
    const int TILE_SIZE = 32; 
    const int TILES_X = 16;

    const float inputDelayMovement = 180.0f; 
    const float inputDelayAction = 400.0f;

    const float speed = 32.0f;
    const int fuelConsumptionTime = 3;
    const int fuelConsumption = 10;
    const int fuelAmount = 20;

    int titlePos;
    int score;
    int fuel;
    int tool;

    Level level;
    Menu menu;

    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;

    sf::Clock moveClock;
    sf::Clock actionClock;
    sf::Clock fuelClock;

private:
};

#endif // PLAYER_H