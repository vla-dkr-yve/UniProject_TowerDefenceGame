#include <SFML/Graphics.hpp>
#include <iostream>
#include "BackGround.h"
#include "EnemyManager.h"
#include "GUI.h"
#include "MouseSprite.h"
#include "Map.h"
#include "Player.h"
#include "ResearchTree.h"
//	Plans:
// 
// Separate most of the code tha currently in main
// Rewrite code to replace most of uneccesary shit with pointers etc. 
// 
// Add main menu with 3 option play, leaderboard(load from file), exit
// Add kinda of score
// Add login system (username + password)?
// Save score into the file when lives go to 0/player finish the game closing the window (x button)
//
// Finish research tree
//

int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1024), "");
	window.setFramerateLimit(60);
	Map map;
	EnemyManager enemyManager;
	Player player;
	GUI gui(player.GetMoney(), player.GetResearchPoints(), player.GetLives());
	MouseSprite mouseSprite;

	ResearchTree reseacrhTree;
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
				if (event.key.code == sf::Keyboard::LAlt)
				{
					reseacrhTree.ChangeViewState();
				}
			}
		}
		sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));

		if (!reseacrhTree.IsResearchTreeActive())
		{
			mouseSprite.Update(deltaTime, gui, mousePosition, map, event,map.GetMilitaryTowers(), map.GetCivilTowers());
		}
		if (!bIsPaused && !reseacrhTree.IsResearchTreeActive())
		{
			player.Update(deltaTime);
			enemyManager.Update(deltaTime, player);
			gui.UpdateTextValues(player.GetMoney(), player.GetResearchPoints(), player.GetLives());
			map.Update(deltaTime, enemyManager.GetEnemyVector(), player);
		}
		reseacrhTree.Update(mousePosition);

		window.clear(sf::Color::Black);
		map.Draw(window);
		if (bIsPaused)
		{
			window.draw(pauseRect);
			window.draw(pauseText);
		}
		enemyManager.Draw(window);
		reseacrhTree.Draw(window);
		gui.Draw(window);
		mouseSprite.Draw(window);
		window.display();
	}
}
