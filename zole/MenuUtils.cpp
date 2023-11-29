#include "menu.h"
#include <iostream>
#include <string>
#include "Messages.h"

Menu::Menu() : translator("translation.json") {
	if (!font.loadFromFile("fonts/Magic Dreams.ttf")) {
		std::cout << MSG_ERROR_FILE_NOT_FOUND << std::endl;
	}

	if (!fuelBarTexture.loadFromFile("sprites/fuelbar/7.png")) {
		std::cout << MSG_ERROR_FILE_NOT_FOUND << std::endl;
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

void Menu::draw(sf::RenderWindow& window, int toolType, int fuelLevel, int score, int gameState, int pTitle) {
    std::string currentLanguage = "en";
    // Simplify fuel level check with a loop
    for (int level = 140, img = 7; level > 0; level -= 20, img--) {
        if (fuelLevel < level) {
            std::string filePath = "sprites/fuelbar/" + std::to_string(img) + ".png";
            if (!fuelBarTexture.loadFromFile(filePath)) {
                std::cout << MSG_ERROR_FILE_NOT_FOUND << std::endl;
            }
            fuelBarSprite.setTexture(fuelBarTexture);
            break;
        }
    }

    // Simplify tool type string setting
    std::string toolTemp = (toolType == 0) ? translator.getTranslation("lawnmower", currentLanguage) : translator.getTranslation("tractor", currentLanguage);
    if (pTitle == 0) toolTemp = translator.getTranslation("space", currentLanguage) + " " + toolTemp;
    menu[0].setString(toolTemp);

    // Set score string
    menu[1].setString("Taskai: " + std::to_string(score));

    // Draw menu items
    window.draw(menu[0]);
    window.draw(menu[1]);
    if (gameState == 0) window.draw(menu[2]);
    window.draw(fuelBarSprite);
}
