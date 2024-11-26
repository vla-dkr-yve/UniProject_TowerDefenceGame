#pragma once
#include "MilitaryTower.h"
class LaserTower :public MilitaryTower
{
	static int m_id;
	static int m_cost;
public:
	LaserTower(sf::Vector2f position);

	static inline int GetCost() { return m_cost; };
};