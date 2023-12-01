#ifndef MENU_H
#define MENU_H

#pragma once
#include "SFML/Graphics.hpp"
#include "TranslationUtils.h"
#include "Messages.h"
#include <iostream>
#include <string>

#define MAX_NUMBER_OF_ITEMS 3
#define MAX_FUEL_LEVELS 8

class Menu {
public:
    Menu();

    void draw(sf::RenderWindow& window, int toolType, int fuelLevel, int score, int gState, int pTitle);

private:
    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
    sf::Sprite fuelBarSprite;
    sf::Texture fuelBarTextures[MAX_FUEL_LEVELS];
    TranslationUtils translationUtils;
    std::string currentLanguage = "en";

    void setMenuItem(sf::Text& menuItem, float x, float y, sf::Color color, const std::string& text = "");
    void updateFuelBarSprite(int index);
};

#endif // MENU_H