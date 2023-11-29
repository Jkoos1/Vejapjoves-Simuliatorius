#pragma once
#include <stdlib.h>
#include <iostream>
#include <map>
#include "titleMap.h"
#include "messages.h"


class MapUtils {
public:
	TileMap map;
	TileMap fMap;

	int level[256];
	int levelAge[256];
	int toolTitle = 0;

	int fuelArr[256];
	int fuelSpawnRate = 6; // mazesnis resikia greiciau

	std::map<int, int> ageTimer;

	sf::Sprite fuelSprite;
	sf::Texture fuelTexture;
	sf::Clock ageClock;
	sf::Clock fuelClock;

	MapUtils() {
		for (int i = 0; i < 256; i++) {
			fuelArr[i] = 0;
		}

		ageTimer[0] = 200; // pilna zole
		ageTimer[1] = 300; // nupjauta
		ageTimer[2] = 100; // tuscias
		ageTimer[4] = 400; // paseta

		if (!fuelTexture.loadFromFile("sprites/fuel.png")) {
			std::cout << MSG_ERROR_FILE_NOT_FOUND << std::endl;
		}
		fuelSprite.setTexture(fuelTexture);

	}

	void generateMap() {
		std::srand((unsigned)time(NULL));

		for (int i = 1; i < 256 - 32; i++) {
			levelAge[i] = rand() % 300; // title amzius

			fuelArr[i] = 0;

			level[i] = 2; // title stadiju checks
			if (levelAge[i] > ageTimer[2]) level[i] = 0;
			if (levelAge[i] > ageTimer[0]) level[i] = 1;
			//if (levelAge[i] > ageTimer[1]) level[i] = 4; // paseti laukai

		}

		level[toolTitle] = 3; // zaidimo pradzios laukas
		for (int i = 256 - 32; i < 256; i++) {
			if(i < 256 - 16) level[i] = 6;
			else level[i] = 5;
		}
		std::cout << "Generated!" << std::endl;

	}

	void levelUpdate() { // updatina langelius
		if (!map.load("sprites/tiles.png", sf::Vector2u(32, 32), level, 16, 16))
			std::cout << "update grid...";
		if (!fMap.load("sprites/fuel.png", sf::Vector2u(32, 32), fuelArr, 16, 16))
			std::cout << "update fuel...";
	}

	void ageCheck() { // keicia langeliu stadijas ir degalu spawn
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

	void printGird() { // debug printina grido matrica
		for (int i = 0; i < 256; i++) {
			std::cout << level[i];
			if (i % 7 == 0) std::cout << std::endl;
		}
	}
};