#include <SFML/Graphics.hpp>
#include <iostream>
#include "BackGround.h"
#include "EnemyManager.h"


//	Plans:
// All code in main connected with enemies put into EnemyManager +
//Inside EnemyManager make a timer which would "spawn" random enemy (using enum for enumarating enemies and rand for random generation)(after 100 spawned enemies spawn boss) +
//Implement working tower places, only then towers
//Start implementing towers? -Probably
//Make a common class for towers (build time, cost, etc)
//From common tower divide them into two: military and civil
int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1024), "");
	BackGround backGround;
	EnemyManager enemyManager;
	sf::Clock clock;
	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		enemyManager.Update(deltaTime);
		window.clear(sf::Color::Black);

		backGround.Draw(window);
		enemyManager.Draw(window);
		window.display();
	}
}
