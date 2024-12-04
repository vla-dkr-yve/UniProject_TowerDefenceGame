#pragma once
#include "CivilTower.h"
#include "Player.h"

class ResearchCenter : public CivilTower
{
public:
	ResearchCenter(sf::Vector2f position, std::vector<MilitaryTower*>& towers);
	
	void Action(float deltaTime, Player& player) override;

	void ApplyBuffs(std::vector<MilitaryTower*>& towers) override;
	void ReapplyBuffs(MilitaryTower* newTower) override;
};

