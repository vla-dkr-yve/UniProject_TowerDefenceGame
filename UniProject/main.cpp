#include <SFML/Graphics.hpp>
#include <iostream>
#include "BackGround.h"
#include "EnemyManager.h"
#include "GUI.h"
#include "MouseSprite.h"
#include "Map.h"
//	Plans:
//From common tower divide them into two: military and civil
//Make Update civil tower function
//


int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1024), "");
	window.setFramerateLimit(60);
	Map map;
	EnemyManager enemyManager;
	GUI gui;
	MouseSprite mouseSprite;
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
			if (event.type == event.MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
					if (!gui.IsOnTheGui(mousePosition) && mouseSprite.IsActive() && map.IsOnThePlace(mousePosition.x / 64, mousePosition.y / 64))
					{
						map.AddTower(mouseSprite.GetTowerType(), sf::Vector2f(mousePosition.x, mousePosition.y), mousePosition.x / 64, mousePosition.y / 64);
					}
				}
			}
		}
		sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
		mouseSprite.Update(deltaTime, gui, mousePosition, map, event,map.GetMilitaryTowers());
		enemyManager.Update(deltaTime);
		map.Update(deltaTime, enemyManager.GetEnemyVector());


		window.clear(sf::Color::Black);

		map.Draw(window);
		enemyManager.Draw(window);
		gui.Draw(window);
		mouseSprite.Draw(window);
		window.display();
	}
}
