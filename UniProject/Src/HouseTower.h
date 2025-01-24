#pragma once
#include "CivilTower.h"
class HouseTower : public CivilTower
{
public:
	HouseTower(sf::Vector2f position,std::vector<CivilTower*>& towers);
	
	void Action(float deltaTime, Player& player) override;

	void ApplyBuffs(std::vector<CivilTower*>& towers) override;
	void ReapplyBuffs(CivilTower* newTower) override;
};