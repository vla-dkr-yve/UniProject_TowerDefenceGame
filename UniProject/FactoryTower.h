#pragma once
#include "CivilTower.h"
#include "Player.h"
class FactoryTower : public CivilTower
{
	static int m_id;
	static int m_cost;
public:
	FactoryTower(sf::Vector2f position);

	void Action(float deltaTime, Player& player) override;

	static inline int GetCost() { return m_cost; };
	//void ApplyBuffs(std::vector<Tower*>& towers) override;
};

