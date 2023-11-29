#pragma once
#include "SFML/Graphics.hpp"
#include "TranslationUtils.cpp"

#define MAX_NUMBER_OF_ITEMS 3

class Menu {
public:
	Menu();
	~Menu();

	void draw(sf::RenderWindow &window, int toolType, int fuelLevel, int score, int gState, int pTitle);

private:
	TranslationUtils translator;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Sprite fuelBarSprite;
	sf::Texture fuelBarTexture;
};