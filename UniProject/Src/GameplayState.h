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
class GameplayState : public State
{
private:
	StateManager& stateManager;

	Map map;
	EnemyManager enemyManager;
	Player player;
	MouseSprite mouseSprite;
	ResearchTree reseacrhTree;
	sf::Clock clock;

	GUI* gui;
	Pause* pause;
public:
	GameplayState(StateManager& manager, sf::RenderWindow& window);

	void HandleEvents(sf::RenderWindow& window) override;
	void Update(sf::RenderWindow& window) override;
	void Draw(sf::RenderWindow& window) override;
};

