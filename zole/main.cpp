#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <stdlib.h>

#include "menu.h"
#include "titleMap.h"
#include "player.h"
#include "MapUtils.h"

const int WINDOW_SIZE = 512;
const int FRAMERATE_LIMIT = 60;
const int INITIAL_FUEL = 140;

int main() {

	Player player;
	MapUtils map;
	Menu menu;
	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Vejapjoves simuliatorius");
	bool gameState = true;

	window.setFramerateLimit(FRAMERATE_LIMIT);
	map.generateMap(); 

	while (window.isOpen()) { 
		while (gameState == true) {
			if (player.fuel < 1) gameState = false;

			sf::Time gameTime = clock.getElapsedTime();
			float sec = gameTime.asSeconds();

			player.playerAction(); 
			map.ageCheck();
			map.levelUpdate();

			if (map.level[player.titlePos] == 0 || map.level[player.titlePos] == 2) { // action 
				if (map.level[player.titlePos] == 0 && player.tool == 0) {
					map.level[player.titlePos] = 1; // nupjauta
					map.levelAge[player.titlePos] = map.ageTimer[1];
					player.score += 2;
				}
				if (map.level[player.titlePos] == 2 && player.tool == 1) {
					map.level[player.titlePos] = 4; // paseta
					map.levelAge[player.titlePos] = map.ageTimer[4];
					player.score += 1;
				}
			}

			Player player2;

			if (map.fuelArr[player.titlePos] == 1) {
				player += player2;
				map.fuelArr[player.titlePos] = 0;
			}
		
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape) // exit
					window.close();
				if (event.key.code == sf::Keyboard::R) { // reset zaidima
					map.generateMap();
					player.fuel = INITIAL_FUEL;
					player.score = 0;
					player.sprite.setPosition(0, 0);
					//world.levelUpdate();
				}
			}

			window.clear(); // piesia dalykus
			window.draw(map.map);
			window.draw(map.fMap);
			window.draw(player.sprite);
			menu.draw(window, player.tool, player.fuel, player.score, gameState, player.titlePos);
			window.display();
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::N || event.key.code == sf::Keyboard::Escape) // exit
				window.close();
			if (event.key.code == sf::Keyboard::Y) { // reset zaidima
				map.generateMap();
				gameState = 1;
				player.fuel = INITIAL_FUEL;
				player.score = 0;
				player.sprite.setPosition(0, 0);
			}
		}
	}
	return 0;
}