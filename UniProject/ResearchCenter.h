#pragma once
#include "CivilTower.h"
#include "Player.h"

class ResearchCenter : public CivilTower
{
	static int m_id;
	static int m_cost;
public:
	ResearchCenter(sf::Vector2f position, std::vector<MilitaryTower*>& towers);
	
	void Action(float deltaTime, Player& player) override;

	void ApplyBuffs(std::vector<MilitaryTower*>& towers) override;
	void ReapplyBuffs(MilitaryTower* newTower) override;

	static inline int GetCost() { return m_cost; };
};

