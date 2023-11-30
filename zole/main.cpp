#include "GameEngine.h"

int main() {
	GameEngine gameEngine;

	gameEngine.initialize();
	gameEngine.run();
	gameEngine.shutdown();

	return 0;
} 
