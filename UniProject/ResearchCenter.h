#pragma once
#include "CivilTower.h"
#include "Player.h"

class ResearchCenter : public CivilTower
{
public:
	ResearchCenter(sf::Vector2f position);
	
	void Action(float deltaTime, Player& player);
};

