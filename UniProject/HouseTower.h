#pragma once
#include "CivilTower.h"
class HouseTower : public CivilTower
{
public:
	HouseTower(sf::Vector2f position);

	void ApplyBuffs(std::vector<CivilTower*>& towers);
};

