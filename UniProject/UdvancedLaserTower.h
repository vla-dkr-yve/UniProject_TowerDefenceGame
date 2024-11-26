#pragma once
#include "LaserTower.h"
class UdvancedLaserTower : public MilitaryTower
{
	static int m_id;
	static short int m_cost;
public:
	UdvancedLaserTower(sf::Vector2f position);
	static inline int GetCost() { return m_cost; };
};

