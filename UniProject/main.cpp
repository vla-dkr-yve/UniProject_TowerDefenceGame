#include <SFML/Graphics.hpp>
#include <iostream>
#include "BackGround.h"
#include "EnemyManager.h"
#include "GUI.h"
#include "MouseSprite.h"
#include "Map.h"
//	Plans:
// All code in main connected with enemies put into EnemyManager +
//Inside EnemyManager make a timer which would "spawn" random enemy 
// (using enum for enumarating enemies and rand for random generation)(after 100 spawned enemies spawn boss) +
//Implement working tower places, only then towers (?)
//Start implementing towers? -Probably +
//Make a common class for towers (build time, cost, etc) +
//From common tower divide them into two: military and civil
// ! While creating millitary tower I must pass the position(place on the map) !
int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1024), "");
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
		mouseSprite.Update(deltaTime, gui, mousePosition, map, event,map.GetTowers());
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
