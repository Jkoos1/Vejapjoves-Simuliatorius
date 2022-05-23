#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <stdlib.h>

#include "menu.h"
#include "titleMap.h"
#include "player.h"
#include "mapGenerator.h"


int main() {

	Player player;
	Gen world;
	Menu menu;


	bool gameState = true;

	sf::RenderWindow window(sf::VideoMode(512, 512), "Vejapjoves simuliatorius");
	window.setFramerateLimit(60);


	sf::Clock clock;

	world.levelGen(); 

	while (window.isOpen()) { 

		while (gameState == true) {

			if (player.fuel < 1) gameState = false;

			sf::Time gameTime = clock.getElapsedTime();
			float sec = gameTime.asSeconds();

			player.playerAction(); 
			world.ageCheck();
			world.levelUpdate();

			if (world.level[player.titlePos] == 0 || world.level[player.titlePos] == 2) { // action 
				if (world.level[player.titlePos] == 0 && player.tool == 0) {
					world.level[player.titlePos] = 1; // nupjauta
					world.levelAge[player.titlePos] = world.ageTimer[1];
					player.score += 2;
				}
				if (world.level[player.titlePos] == 2 && player.tool == 1) {
					world.level[player.titlePos] = 4; // paseta
					world.levelAge[player.titlePos] = world.ageTimer[4];
					player.score += 1;
				}
			}

			Player p2;

			if (world.fuelArr[player.titlePos] == 1) {
				player += p2;
				world.fuelArr[player.titlePos] = 0;
			}
		
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape) // exit
					window.close();
				if (event.key.code == sf::Keyboard::R) { // reset zaidima
					world.levelGen();
					player.fuel = 140;
					player.score = 0;
					player.sprite.setPosition(0, 0);
					//world.levelUpdate();
				}

			}

			window.clear(); // piesia dalykus
			window.draw(world.map);
			window.draw(world.fMap);
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
				world.levelGen();
				gameState = 1;
				player.fuel = 140;
				player.score = 0;
				player.sprite.setPosition(0, 0);
				//world.levelUpdate();
			}

		}
		

	}

	return 0;
}