#include "Player.h"

Player::Player(int GRID_SIZE) : level(GRID_SIZE) {
	changeSpriteDirection(0);
    reset();
}

void Player::changeSpriteDirection(int input) {
	if (tool == 0) {
		if (input == 0 && !texture.loadFromFile("sprites/playerRight.png")) {
			std::cout << MSG_ERROR_FILE_NOT_FOUND << std::endl;
		}

		if (input == 1 && !texture.loadFromFile("sprites/playerLeft.png")) {
			std::cout << MSG_ERROR_FILE_NOT_FOUND << std::endl;
		}
	}
	else {
		if (input == 0 && !texture.loadFromFile("sprites/seedRight.png")) {
			std::cout << MSG_ERROR_FILE_NOT_FOUND << std::endl;
		}

		if (input == 1 && !texture.loadFromFile("sprites/seedLeft.png")) {
			std::cout << MSG_ERROR_FILE_NOT_FOUND << std::endl;
		}
	}


	sprite.setTexture(texture);
}

void Player::consumeFuel() {
    if (fuelClock.getElapsedTime().asSeconds() > fuelConsumptionTime) {
        fuel -= fuelConsumption;
        fuelClock.restart();
    }
}

void Player::addFuel() {
	fuel += fuelAmount;
}

void Player::movePlayer() {
    sf::Vector2f newPosition(0.f, 0.f);
    bool moved = false;

    if (moveClock.getElapsedTime().asMilliseconds() > inputDelayMovement) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && position.x < MAX_X) {
            newPosition.x = speed;
            moved = true;
            changeSpriteDirection(0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && position.x > MIN_X) {
            newPosition.x = -speed;
            moved = true;
            changeSpriteDirection(1);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && position.y > MIN_Y) {
            newPosition.y = -speed;
            moved = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && position.y < MAX_Y) {
            newPosition.y = speed;
            moved = true;
        }

        if (moved) {
            sprite.move(newPosition);
            moveClock.restart();
        }
    }
}

void Player::performAction() {
    if (actionClock.getElapsedTime().asMilliseconds() > inputDelayAction) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && titlePos == level.toolTitle) {
            tool = (tool == 0) ? 1 : 0;
            actionClock.restart();
        }
    }
}

void Player::updateTitlePos() {
    int tempx = position.x / TILE_SIZE;
    int tempy = position.y / TILE_SIZE;
    titlePos = tempx + tempy * TILES_X;
}

void Player::action() {
    consumeFuel();
    position = sprite.getPosition();
    movePlayer();
    performAction();
    updateTitlePos();
}

void Player::reset() {
	fuel = 140;
	score = 0;
	sprite.setPosition(0, 0);
}

void Player::interactWithLevel(Level& level) {
    if (level.level[titlePos] == 0 || level.level[titlePos] == 2) {
        if (level.level[titlePos] == 0 && tool == 0) {
            level.level[titlePos] = 1;
            level.levelAge[titlePos] = level.ageTimer[1];
            score += 2;
        }
        if (level.level[titlePos] == 2 && tool == 1) {
            level.level[titlePos] = 4;
            level.levelAge[titlePos] = level.ageTimer[4];
            score += 1;
        }
    }

    if (level.fuelArr[titlePos] == 1) {
        addFuel();
        level.fuelArr[titlePos] = 0;
    }
}
