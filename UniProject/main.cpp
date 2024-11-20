#include <SFML/Graphics.hpp>
#include <iostream>
#include "BackGround.h"
#include "FastEnemy.h"
#include "SlowEnemy.h"
#include <vector>
int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1024), "");
	BackGround backGround;
	FastEnemy fastEnemy;
	SlowEnemy SlowEnemy;
	sf::Vector2f direction = sf::Vector2f(0, 1);
	sf::Clock clock;
	std::vector <Enemy*> enemies;
	enemies.push_back(&fastEnemy);
	enemies.push_back(&SlowEnemy);
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
		for (auto it = enemies.begin(); it != enemies.end();)
		{
			if ((*it)->IsDead())
			{
				enemies.erase(it);
			}
			else {
				(*it)->Update(deltaTime);
				it++;
			}
		}
		window.clear(sf::Color::Black);

		backGround.Draw(window);
		for (auto enemy : enemies)
		{
			enemy->Draw(window);
		}
		window.display();
	}
}



