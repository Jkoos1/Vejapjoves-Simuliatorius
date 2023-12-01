#include "GameEngine.h"

GameEngine::GameEngine()
    : window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Game Title"),
    player(GRID_SIZE),
    level(GRID_SIZE),
    menu() {
    isRunning = false;
    isGameActive = true;
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
    gameOver();

    sf::Time gameTime = clock.getElapsedTime();
    float sec = gameTime.asSeconds();

    player.action();
    level.ageCheck();
    level.levelUpdate();
    player.interactWithLevel(level);
}

void GameEngine::render() {
    window.clear();
    window.draw(level.titleMap);
    window.draw(level.fMap);
    window.draw(player.sprite);
    menu.draw(window, player.tool, player.fuel, player.score, isGameActive, player.titlePos);
    window.display();
}


void GameEngine::gameOver(){
    if (player.fuel < 1) {
        isGameActive = false;
        return;
    }
}