#pragma once
#include "CivilTower.h"
#include "Player.h"
class FactoryTower : public CivilTower
{
public:
	FactoryTower(sf::Vector2f position);

	void Action(float deltaTime, Player& player) override;
};

