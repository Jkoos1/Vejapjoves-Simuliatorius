#include "Level.h"

Level::Level(int gridSize) : gridSize(gridSize) {
	level = new int[gridSize];
	levelAge = new int[gridSize];
	fuelArr = new int[gridSize];

	for (int i = 0; i < gridSize; i++) {
		level[i] = 0;
		levelAge[i] = 0;
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

Level::~Level() {
	delete[] level;
	delete[] levelAge;
	delete[] fuelArr;
}

void Level::generateMap() {
    std::srand((unsigned)time(NULL));

    for (int i = 1; i < gridSize - 32; i++) {
        levelAge[i] = rand() % 300;
        fuelArr[i] = 0;
        level[i] = 2;
        if (levelAge[i] > ageTimer[2]) level[i] = 0;
        if (levelAge[i] > ageTimer[0]) level[i] = 1;
    }

    level[toolTitle] = 3;
    for (int i = gridSize - 32; i < gridSize; i++) {
        if (i < gridSize - 16) level[i] = 6;
        else level[i] = 5;
    }
}

void Level::levelUpdate() {
	if (!titleMap.load("sprites/tiles.png", sf::Vector2u(32, 32), level, 16, 16))
		std::cout << "update grid...";
	if (!fMap.load("sprites/fuel.png", sf::Vector2u(32, 32), fuelArr, 16, 16))
		std::cout << "update fuel...";
}

void Level::ageCheck() {
    sf::Time timo = ageClock.getElapsedTime();
    sf::Time fuelTime = fuelClock.getElapsedTime();

    if (fuelTime.asSeconds() > fuelSpawnRate) {
        int prc = rand() % (gridSize - 32);
        if (fuelArr[prc] != 1 && prc != 0) {
            fuelArr[prc] = 1;
        }
        sf::Time elapsed = fuelClock.restart();
    }

    if (timo.asSeconds() > 1) {
        sf::Time elapsed = ageClock.restart();
        for (int i = 1; i < gridSize - 32; i++) {
            if (levelAge[i] > 0) levelAge[i] -= 1;
            if (levelAge[i] == ageTimer[1]) level[i] = 1;
            if (levelAge[i] == ageTimer[0]) level[i] = 0;
            if (levelAge[i] == ageTimer[2]) level[i] = 2;
        }
    }
}