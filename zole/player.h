#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include "MapUtils.h"
#include "menu.h"

class Player : public sf::Transformable {
public:

	float speed = 32.0f; // playerio greitis 32 = 1 langelis
	int titlePos = 0; // playerio langelis
	int score = 0; // playerio taskai

	int fuel = 140;
	int fuelConsumptionTime = 3; //default 2
	int fuelConsumption = 10; //default 10
	int fuelAmount = 20;

	int tool = 0; // 0 - zoliapjove, 1 - seklos

	float inputDelayMovement = 180.0f; // spam preventionas
	float inputDelayAction = 400.0f;

	MapUtils map;
	Menu menu;

	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f position;

	sf::Clock moveClock;
	sf::Clock actionClock;
	sf::Clock fuelClock;

	Player() {
		playerSprite(0);
	}

	Player operator+=(const Player& b) {
		Player p;
		p.fuel = this->fuel += b.fuelAmount;
		return p;
	}

	void playerSprite(int input) {
		// 0 - rigth, 1 - left :: player sprites
		if (tool == 0) {
			if (input == 0 && !texture.loadFromFile("sprites/playerRight.png")) {
				std::cout << "kazkas neveikia" << std::endl;
			}

			if (input == 1 && !texture.loadFromFile("sprites/playerLeft.png")) {
				std::cout << "kazkas neveikia" << std::endl;
			}
		}
		else {
			if (input == 0 && !texture.loadFromFile("sprites/seedRight.png")) {
				std::cout << "kazkas neveikia" << std::endl;
			}

			if (input == 1 && !texture.loadFromFile("sprites/seedLeft.png")) {
				std::cout << "kazkas neveikia" << std::endl;
			}
		}
		

		sprite.setTexture(texture);
	}

	void playerAction() { // playerio inputs ir pozicijos sekimas

		sf::Time moveTime = moveClock.getElapsedTime(); // laiku dalykai
		sf::Time actionTime = actionClock.getElapsedTime();
		sf::Time fuelTime = fuelClock.getElapsedTime();
		float fTime = fuelTime.asSeconds();
		float sec1 = moveTime.asMilliseconds();
		float sec2 = actionTime.asMilliseconds();

		if (fTime > fuelConsumptionTime) { // mazina kura
			fuel -= fuelConsumption;
			sf::Time elapsed = fuelClock.restart();
		}

		position = sprite.getPosition();

		if (sec1 > inputDelayMovement) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && position.x < 480)
			{
				sprite.move(sf::Vector2f(speed, 0));
				sf::Time elapsed = moveClock.restart();
				playerSprite(0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && position.x > 0)
			{
				sprite.move(sf::Vector2f(-speed, 0));
				sf::Time elapsed = moveClock.restart();
				playerSprite(1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && position.y > 0)
			{
				sprite.move(sf::Vector2f(0, -speed));
				sf::Time elapsed = moveClock.restart();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && position.y < 416)
			{
				sprite.move(sf::Vector2f(0, speed));
				sf::Time elapsed = moveClock.restart();
			}
		}

		if (sec2 > inputDelayAction) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) // tool change
			{
				if (titlePos == map.toolTitle) {
					if (tool == 0) tool = 1; // vejas, seklos
					else tool = 0;
					std::cout << "change";
					sf::Time elapsed = actionClock.restart();
				}
			}
		}

		// playerio langelis
		int tempx = 0, tempy = 0;
		if (position.x != 0) tempx = position.x / 32; else tempx = 0;
		if (position.y != 0) tempy = position.y / 32; else tempy = 0;
		titlePos = tempx + tempy * 16;


	}


};