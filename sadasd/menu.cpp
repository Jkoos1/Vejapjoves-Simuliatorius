#include "menu.h"
#include <iostream>
#include <string>

Menu::Menu() {
	if (!font.loadFromFile("fonts/Magic Dreams.ttf")) {
		std::cout << "errors";
	}

	if (!fuelBarTexture.loadFromFile("sprites/fuelbar/7.png")) {
		std::cout << "errors";
	}

	fuelBarSprite.setTexture(fuelBarTexture);
	fuelBarSprite.setPosition(400, 480 - 16);

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setPosition(16,480 - 16);

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::Red);
	menu[1].setPosition(250, 480 - 16);

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::Red);
	menu[2].setPosition(30, 200);
	menu[2].setString("Zaidimo pabaiga. Ar norite testi?y/n");
}

Menu::~Menu() {

}

void Menu::draw(sf::RenderWindow &window, int toolType, int fuelLevel, int score, int gState, int pTitle) {

	if (fuelLevel < 140) {
		if (!fuelBarTexture.loadFromFile("sprites/fuelbar/7.png")) {
			std::cout << "errors";
		}
		fuelBarSprite.setTexture(fuelBarTexture);
	}

	if (fuelLevel < 120) {
		if (!fuelBarTexture.loadFromFile("sprites/fuelbar/6.png")) {
			std::cout << "errors";
		}
		fuelBarSprite.setTexture(fuelBarTexture);
	}

	if (fuelLevel < 100) {
		if (!fuelBarTexture.loadFromFile("sprites/fuelbar/5.png")) {
			std::cout << "errors";
		}
		fuelBarSprite.setTexture(fuelBarTexture);
	}

	if (fuelLevel < 80) {
		if (!fuelBarTexture.loadFromFile("sprites/fuelbar/4.png")) {
			std::cout << "errors";
		}
		fuelBarSprite.setTexture(fuelBarTexture);
	}

	if (fuelLevel < 60) {
		if (!fuelBarTexture.loadFromFile("sprites/fuelbar/3.png")) {
			std::cout << "errors";
		}
		fuelBarSprite.setTexture(fuelBarTexture);
	}

	if (fuelLevel < 40) {
		if (!fuelBarTexture.loadFromFile("sprites/fuelbar/2.png")) {
			std::cout << "errors";
		}
		fuelBarSprite.setTexture(fuelBarTexture);
	}

	if (fuelLevel < 20) {
		if (!fuelBarTexture.loadFromFile("sprites/fuelbar/1.png")) {
			std::cout << "errors";
		}
		fuelBarSprite.setTexture(fuelBarTexture);
	}

	if (fuelLevel < 1) {
		if (!fuelBarTexture.loadFromFile("sprites/fuelbar/0.png")) {
			std::cout << "errors";
		}
		fuelBarSprite.setTexture(fuelBarTexture);
	}

	std::string toolTemp;
	if (toolType == 0) toolTemp = "Zoliapjove";
	else toolTemp = "Seklos";
	menu[0].setString(toolTemp);
	if (pTitle == 0) menu[0].setString("Space " +  toolTemp);


	std::string temp = "Taskai: " + std::to_string(score);

	menu[1].setString(temp);

	window.draw(menu[0]);
	window.draw(menu[1]);
	if (gState == 0) window.draw(menu[2]);
	window.draw(fuelBarSprite);
}