#include "Menu.h"

const std::string FONT_PATH = "fonts/Magic Dreams.ttf";
const std::string FUEL_BAR_SPRITE_PATH = "sprites/fuelbar/";
const std::string FILE_NOT_FOUND_MSG = "File not found: ";

Menu::Menu()
    : translator("translation.json"),
    fuelBarSprite(),
    font() {
    if (!font.loadFromFile(FONT_PATH)) {
        std::cerr << FILE_NOT_FOUND_MSG << FONT_PATH << std::endl;
    }

    initializeMenuItems();
    loadFuelBarSprite(7); 
}

void Menu::initializeMenuItems() {
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; ++i) {
        menu[i].setFont(font);
        menu[i].setFillColor(sf::Color::Red);
    }

    menu[0].setPosition(16, 480 - 16);
    menu[1].setPosition(250, 480 - 16);
    menu[2].setPosition(30, 200);
    menu[2].setString("Zaidimo pabaiga. Ar norite testi?y/n");
}

void Menu::loadFuelBarSprite(int index) {
    std::string filePath = FUEL_BAR_SPRITE_PATH + std::to_string(index) + ".png";
    if (!fuelBarTexture.loadFromFile(filePath)) {
        std::cerr << FILE_NOT_FOUND_MSG << filePath << std::endl;
    }
    fuelBarSprite.setTexture(fuelBarTexture);
    fuelBarSprite.setPosition(400, 480 - 16);
}

void Menu::draw(sf::RenderWindow& window, int toolType, int fuelLevel, int score, int gameState, int pTitle) {
    std::string currentLanguage = "en";

    int level = 140, img = 7;
    while (level > 0) {
        if (fuelLevel < level) {
            loadFuelBarSprite(img);
            break;
        }
        level -= 20;
        img--;
    }

    std::string toolTemp = (toolType == 0) ? translator.getTranslation("lawnmower", currentLanguage)
        : translator.getTranslation("tractor", currentLanguage);
    if (pTitle == 0) {
        toolTemp = translator.getTranslation("space", currentLanguage) + " " + toolTemp;
    }
    menu[0].setString(toolTemp);
    menu[1].setString("Taskai: " + std::to_string(score));

    window.draw(menu[0]);
    window.draw(menu[1]);
    if (gameState == 0) {
        window.draw(menu[2]);
    }
    window.draw(fuelBarSprite);
}
