#include "GameEngine.h"

GameEngine::GameEngine() {
    isRunning = false;
    isGameActive = true;
    window.create(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Vejapjoves simuliatorius");
}

void GameEngine::initialize() {
    window.setFramerateLimit(FRAMERATE_LIMIT);
    level.generateMap();
    isRunning = true;
}

void GameEngine::run() {
    while (isRunning) {
        processInput();
        if (isGameActive) {
            updateGame();
        }
        render();
    }
}

void GameEngine::shutdown() {
    isRunning = false;
}

void GameEngine::processInput() {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            shutdown();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
            resetGame();
        }
    }
}

void GameEngine::resetGame() {
    level.generateMap();
    player.reset();
    isGameActive = true;
}

void GameEngine::updateGame() {
    if (player.fuel < 1) {
        isGameActive = false;
        return;
    }

    sf::Time gameTime = clock.getElapsedTime();
    float sec = gameTime.asSeconds();

    player.action();
    level.ageCheck();
    level.levelUpdate();

    if (level.level[player.titlePos] == 0 || level.level[player.titlePos] == 2) {
        if (level.level[player.titlePos] == 0 && player.tool == 0) {
            level.level[player.titlePos] = 1;
            level.levelAge[player.titlePos] = level.ageTimer[1];
            player.score += 2;
        }
        if (level.level[player.titlePos] == 2 && player.tool == 1) {
            level.level[player.titlePos] = 4; 
            level.levelAge[player.titlePos] = level.ageTimer[4];
            player.score += 1;
        }
    }

    if (level.fuelArr[player.titlePos] == 1) {
        player.addFuel();
        level.fuelArr[player.titlePos] = 0;
    }
}

void GameEngine::render() {
    window.clear();
    window.draw(level.map);
    window.draw(level.fMap);
    window.draw(player.sprite);
    menu.draw(window, player.tool, player.fuel, player.score, isGameActive, player.titlePos);
    window.display();
}