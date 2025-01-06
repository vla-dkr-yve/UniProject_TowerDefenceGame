#include "GameplayState.h"
//void GameplayState::Play()
//{
//}

GameplayState::GameplayState(StateManager& manager, sf::RenderWindow& window): stateManager(manager)
{
	//sf::RenderWindow window(sf::VideoMode(1920, 1024), "");
	/*window.create(sf::VideoMode(1920, 1024), "");*/
	//window.setFramerateLimit(60);
	gui = new GUI(player.GetMoney(), player.GetResearchPoints(), player.GetLives(), player.GetScore());

	pause = new Pause(window);
}

void GameplayState::HandleEvents(sf::RenderWindow& window)
{
	sf::Event event;

	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		if (event.type == event.MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left && hero.IsActive())
			{
				hero.Attack();
			}
		}
		if (event.type == event.MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (mouseSprite.IsActive() && map.IsOnThePlace(mousePosition.x / 64, mousePosition.y / 64) && !pause->IsPaused())
				{
					map.AddTower(mouseSprite.GetTowerType(), mousePosition.x / 64, mousePosition.y / 64, player);
				}
				if (mouseSprite.IsShovelActive() && map.IsOnThePlace(mousePosition.x / 64, mousePosition.y / 64) && !pause->IsPaused())
				{
					map.DeleteTower(mousePosition.x / 64, mousePosition.y / 64);
				}
			}
		}


		if (event.type == event.KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				pause->ChangeState();
			}
			if (event.key.code == sf::Keyboard::LAlt)
			{
				reseacrhTree.ChangeViewState();
			}
		}
	}
}

void GameplayState::Update(sf::RenderWindow& window)
{
	float deltaTime = clock.restart().asSeconds();

	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
	if (!reseacrhTree.IsResearchTreeActive())
	{
		mouseSprite.Update(deltaTime, *gui, mousePosition, map, map.GetMilitaryTowers(), map.GetCivilTowers());
	}

	if (!pause->IsPaused() && !reseacrhTree.IsResearchTreeActive())
	{
		player.Update(deltaTime);
		enemyManager.Update(deltaTime, player);
		hero.Update(deltaTime);
		gui->UpdateTextValues(player.GetMoney(), player.GetResearchPoints(), player.GetLives(), player.GetScore());
		map.Update(deltaTime, enemyManager.GetEnemyVector(), player);
	}

	reseacrhTree.Update(mousePosition);
}

void GameplayState::Draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);
	map.Draw(window);
	pause->Draw(window);
	hero.Draw(window);
	enemyManager.Draw(window);
	reseacrhTree.Draw(window);
	gui->Draw(window);
	mouseSprite.Draw(window);
	window.display();
}
