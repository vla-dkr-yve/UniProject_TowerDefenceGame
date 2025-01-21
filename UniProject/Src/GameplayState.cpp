#include "GameplayState.h"
#include "DataBase.h"
//void GameplayState::Play()
//{
//}


GameplayState::GameplayState(StateManager& manager, bool& isLogined, sf::RenderWindow& window): stateManager(manager), m_isLogined(isLogined)
{
	gui = new GUI(player.GetMoney(), player.GetResearchPoints(), player.GetLives(), player.GetScore());

	pause = new Pause(window);

	fightingManager = new FightingManager(hero);

	m_font.loadFromFile("Assets/Fonts/Arial.TTF");

	m_loseText.setFont(m_font);
	m_loseText.setString("You've lost");
	m_loseText.setCharacterSize(20);
	m_loseText.setPosition(sf::Vector2f(m_windowResolution.x / 2 - m_loseText.getGlobalBounds().getSize().x / 2,
		m_windowResolution.y / 2 - m_loseText.getGlobalBounds().getSize().y / 2) + sf::Vector2f(0, -35));

	m_loseScoreText.setFont(m_font);
	m_loseScoreText.setCharacterSize(20);

	m_continueBtn.setFont(m_font);
	m_continueBtn.setString("Continue");
	m_continueBtn.setCharacterSize(20);
	m_continueBtn.setPosition(sf::Vector2f(m_windowResolution.x / 2 - m_loseText.getGlobalBounds().getSize().x / 2,
		m_windowResolution.y / 2 - m_loseText.getGlobalBounds().getSize().y / 2) + sf::Vector2f(0, 35));
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
				if (m_haveLost && m_continueBtn.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
				{

					if (m_isLogined)
					{
						DataBase::InsertNewScore(DataBase::Username, std::to_string(player.GetScore()));
					}

					stateManager.PopState(window);
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
	if (player.GetLives() <= 0 && !m_haveLost)
	{
		m_haveLost = true;
		m_loseScoreText.setString("Your score is: " + std::to_string(player.GetScore()));
		m_loseScoreText.setPosition(sf::Vector2f(m_windowResolution.x / 2 - m_loseText.getGlobalBounds().getSize().x / 2,
			m_windowResolution.y / 2 - m_loseText.getGlobalBounds().getSize().y / 2));
	}

	float deltaTime = clock.restart().asSeconds();

	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
	if (!reseacrhTree.IsResearchTreeActive())
	{
		mouseSprite.Update(deltaTime, *gui, mousePosition, map, map.GetMilitaryTowers(), map.GetCivilTowers());
	}

	if (!pause->IsPaused() && !reseacrhTree.IsResearchTreeActive() && !m_haveLost)
	{
		player.Update(deltaTime);
		enemyManager.Update(deltaTime, player);
		hero.Update(deltaTime);
		fightingManager->Update(enemyManager.GetEnemyVector(), player, deltaTime);
		gui->UpdateTextValues(player.GetMoney(), player.GetResearchPoints(), player.GetLives(), player.GetScore());
		map.Update(deltaTime, enemyManager.GetEnemyVector(), player);
	}

	if (m_haveLost)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		if (m_continueBtn.getGlobalBounds().contains(mousePos.x, mousePos.y))
		{
			m_continueBtn.setFillColor(sf::Color::Red);
		}
		else {
			m_continueBtn.setFillColor(sf::Color::White);
		}

	}

	reseacrhTree.Update(mousePosition);
}

sf::Vector2f GameplayState::GetResolution()
{
	return m_windowResolution;
}

void GameplayState::Draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);
	map.Draw(window);
	pause->Draw(window);
	hero.Draw(window);
	enemyManager.Draw(window);
	fightingManager->Draw(window);
	reseacrhTree.Draw(window);
	gui->Draw(window);
	mouseSprite.Draw(window);

	if (m_haveLost)
	{
		window.draw(m_loseScoreText);
		window.draw(m_loseText);
		window.draw(m_continueBtn);
	}
	window.display();
}
