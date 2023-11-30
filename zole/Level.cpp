#include "Level.h"

Level::Level () {
	for (int i = 0; i < 256; i++) {
		fuelArr[i] = 0;
	}

	ageTimer[0] = 200;
	ageTimer[1] = 300;
	ageTimer[2] = 100;
	ageTimer[4] = 400;

	if (!fuelTexture.loadFromFile("sprites/fuel.png")) {
		std::cout << MSG_ERROR_FILE_NOT_FOUND << std::endl;
	}
	fuelSprite.setTexture(fuelTexture);
}

void Level::generateMap() {
	std::srand((unsigned)time(NULL));

	for (int i = 1; i < 256 - 32; i++) {
		levelAge[i] = rand() % 300;

		fuelArr[i] = 0;

		level[i] = 2;
		if (levelAge[i] > ageTimer[2]) level[i] = 0;
		if (levelAge[i] > ageTimer[0]) level[i] = 1;
	}

	level[toolTitle] = 3;
	for (int i = 256 - 32; i < 256; i++) {
		if (i < 256 - 16) level[i] = 6;
		else level[i] = 5;
	}
}

void Level::levelUpdate() {
	if (!map.load("sprites/tiles.png", sf::Vector2u(32, 32), level, 16, 16))
		std::cout << "update grid...";
	if (!fMap.load("sprites/fuel.png", sf::Vector2u(32, 32), fuelArr, 16, 16))
		std::cout << "update fuel...";
}

void Level::ageCheck() {
	sf::Time timo = ageClock.getElapsedTime();
	sf::Time fuelTime = fuelClock.getElapsedTime();

	if (fuelTime.asSeconds() > fuelSpawnRate) {
		int prc = rand() % 256 - 32;
		if (fuelArr[prc] != 1 && prc != 0) {
			fuelArr[prc] = 1;
		}
		sf::Time elapsed = fuelClock.restart();
	}

	if (timo.asSeconds() > 1) {
		sf::Time elapsed = ageClock.restart();
		for (int i = 1; i < 256 - 32; i++) {
			if (levelAge[i] > 0) levelAge[i] -= 1;
			if (levelAge[i] == ageTimer[1]) level[i] = 1;
			if (levelAge[i] == ageTimer[0]) level[i] = 0;
			if (levelAge[i] == ageTimer[2]) level[i] = 2;

		}
	}
}
