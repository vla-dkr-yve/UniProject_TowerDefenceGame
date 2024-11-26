#pragma once
#include "MilitaryTower.h"
class ScatterLaserTower : public MilitaryTower
{
	static int m_id;
	static int m_cost;
public:
	ScatterLaserTower(sf::Vector2f position);

	static inline int GetCost() { return m_cost; };
};

