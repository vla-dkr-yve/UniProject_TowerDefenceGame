#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "BackGround.h"
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

	const sf::Vector2f m_windowResolution = sf::Vector2f(1920, 1024);;

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
public:
	GameplayState(StateManager& manager, sf::RenderWindow& window);

	void HandleEvents(sf::RenderWindow& window) override;
	void Update(sf::RenderWindow& window) override;
	sf::Vector2f GetResolution() override;
	void Draw(sf::RenderWindow& window) override;
};

