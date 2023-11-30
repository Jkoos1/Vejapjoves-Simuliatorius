#ifndef MENU_H
#define MENU_H

#pragma once
#include "SFML/Graphics.hpp"
#include "TranslationUtils.h"
#include "Messages.h"
#include <iostream>
#include <string>

#define MAX_NUMBER_OF_ITEMS 3

class Menu {
public:
    Menu();
    void draw(sf::RenderWindow& window, int toolType, int fuelLevel, int score, int gameState, int pTitle);
    void loadFuelBarSprite(int index);
    void initializeMenuItems();

private:
    TranslationUtils translator;
    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
    sf::Sprite fuelBarSprite;
    sf::Texture fuelBarTexture;
};

#endif // MENU_H