#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "EnemyManager.h"
#include "GUI.h"
#include "MouseSprite.h"
#include "Map.h"
#include "Player.h"
#include "ResearchTree.h"
#include "Pause.h"
#include "StateManager.h"
#include "Hero.h"
#include "FightingManager.h"
class GameplayState : public State
{
private:
	StateManager& stateManager;

	const sf::Vector2f m_windowResolution = sf::Vector2f(1920, 1024);

	const float MAX_DT = 0.1f;

	Map map;
	EnemyManager enemyManager;
	Player player;
	MouseSprite mouseSprite;
	ResearchTree reseacrhTree;
	sf::Clock clock;
	Hero hero;

	GUI* gui;
	Pause* pause;
	FightingManager* fightingManager;

	sf::Font m_font;

	sf::Text m_loseScoreText;
	sf::Text m_loseText;
	sf::Text m_continueBtn;
	bool m_haveLost;

	sf::Text researchTreeText;

	bool &m_isLogined;
public:
	GameplayState(StateManager& manager, bool& isLogined);

	void HandleEvents(sf::RenderWindow& window) override;
	void Update(sf::RenderWindow& window) override;
	sf::Vector2f GetResolution() override;
	void Draw(sf::RenderWindow& window) override;
	void Finish(sf::RenderWindow& window);
};