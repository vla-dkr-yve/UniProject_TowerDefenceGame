#include <SFML/Graphics.hpp>
#include <iostream>
#include "BackGround.h"
#include "EnemyManager.h"
#include "GUI.h"
#include "MouseSprite.h"
#include "Map.h"
#include "Player.h"
//	Plans:
//From common tower divide them into two: military and civil +
//Make Update civil tower function +-
//Add a timer over civil towers that shows their Action %+
// 
// Rewrite mousesprite description to look more normal +-
// Add research tab
// 
// Separate most of the code tha currently in main
// Rewrite code to replace most of uneccesary shit with pointers etc. 
//

int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1024), "");
	window.setFramerateLimit(60);
	Map map;
	EnemyManager enemyManager;
	Player player;
	GUI gui(player.GetMoney(), player.GetResearchPoints(), player.GetLives());
	MouseSprite mouseSprite;
	sf::Clock clock;

	bool bIsPaused = false;
	sf::RectangleShape pauseRect;
	sf::Text pauseText;
	sf::Font font;
	font.loadFromFile("Assets/Fonts/Arial.TTF");
	pauseText.setFont(font);
	pauseText.setString("Game is paused");
	pauseRect.setSize(sf::Vector2f(300, 100));
	pauseRect.setPosition(sf::Vector2f(window.getSize().x / 2 - pauseRect.getSize().x / 2, window.getSize().y / 2 - pauseRect.getSize().y / 2));
	pauseRect.setFillColor(sf::Color(0,0,0,64));
	pauseText.setPosition(sf::Vector2f(pauseRect.getPosition().x + 25, pauseRect.getPosition().y + 25));

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
					if (mouseSprite.IsActive() && map.IsOnThePlace(mousePosition.x / 64, mousePosition.y / 64) && !bIsPaused)
					{
						map.AddTower(mouseSprite.GetTowerType(), mousePosition.x / 64, mousePosition.y / 64, player);
					}
					if (mouseSprite.IsShovelActive() && map.IsOnThePlace(mousePosition.x / 64, mousePosition.y / 64) && !bIsPaused)
					{
						map.DeleteTower(mousePosition.x / 64, mousePosition.y / 64);
					}
				}
			}
			if (event.type == event.KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					bIsPaused = !bIsPaused;
				}
			}
		}
		sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
		mouseSprite.Update(deltaTime, gui, mousePosition, map, event,map.GetMilitaryTowers(), map.GetCivilTowers());
		if (!bIsPaused)
		{
			player.Update(deltaTime);
			enemyManager.Update(deltaTime, player);
			gui.UpdateTextValues(player.GetMoney(), player.GetResearchPoints(), player.GetLives());
			map.Update(deltaTime, enemyManager.GetEnemyVector(), player);
		}


		window.clear(sf::Color::Black);
		map.Draw(window);
		if (bIsPaused)
		{
			window.draw(pauseRect);
			window.draw(pauseText);
		}
		enemyManager.Draw(window);
		gui.Draw(window);
		mouseSprite.Draw(window);
		window.display();
	}
}
