#pragma once
#include "CivilTower.h"
class HouseTower : public CivilTower
{
	static int m_id;
	static int m_cost;
public:
	HouseTower(sf::Vector2f position,std::vector<CivilTower*>& towers);
	
	void Action(float deltaTime, Player& player) override;

	void ApplyBuffs(std::vector<CivilTower*>& towers) override;
	void ReapplyBuffs(CivilTower* newTower) override;

	static inline int GetCost() { return m_cost; };
};

