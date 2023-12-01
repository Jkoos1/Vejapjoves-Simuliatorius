#include "Menu.h"

Menu::Menu() : translationUtils("translation.json") {
    if (!font.loadFromFile("fonts/Magic Dreams.ttf")) {
        std::cout << MSG_ERROR_FILE_NOT_FOUND << std::endl;
    }

    for (int i = 0; i < 8; i++) {
        if (!fuelBarTextures[i].loadFromFile("sprites/fuelbar/" + std::to_string(i) + ".png")) {
            std::cout << MSG_ERROR_FILE_NOT_FOUND << std::endl;
        }
    }

    setMenuItem(menu[0], 16, 480 - 16, sf::Color::Red);
    setMenuItem(menu[1], 250, 480 - 16, sf::Color::Red);
    setMenuItem(menu[2], 30, 200, sf::Color::Red, translationUtils.getTranslation("gameEndMessage", currentLanguage));

    updateFuelBarSprite(7);
}

void Menu::setMenuItem(sf::Text& menuItem, float x, float y, sf::Color color, const std::string& text) {
    menuItem.setFont(font);
    menuItem.setFillColor(color);
    menuItem.setPosition(x, y);
    if (!text.empty()) menuItem.setString(text);
}

void Menu::updateFuelBarSprite(int index) {
    fuelBarSprite.setTexture(fuelBarTextures[index]);
    fuelBarSprite.setPosition(400, 480 - 16);
}

void Menu::draw(sf::RenderWindow& window, int toolType, int fuelLevel, int score, int gState, int pTitle) {
    int fuelIndex = std::max(0, fuelLevel / 20);
    updateFuelBarSprite(fuelIndex);

    std::string toolTemp;
    switch (toolType) {
    case 0: toolTemp = translationUtils.getTranslation("lawnmower", currentLanguage); break;
    default: toolTemp = translationUtils.getTranslation("tractor", currentLanguage);
    }
    if (pTitle == 0) toolTemp = translationUtils.getTranslation("space", currentLanguage) + toolTemp;
    menu[0].setString(toolTemp);

    menu[1].setString(translationUtils.getTranslation("score", currentLanguage) + std::to_string(score));

    window.draw(menu[0]);
    window.draw(menu[1]);
    if (gState == 0) window.draw(menu[2]);
    window.draw(fuelBarSprite);
}
