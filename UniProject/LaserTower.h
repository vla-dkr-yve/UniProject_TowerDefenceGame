#pragma once
#include "MilitaryTower.h"
class LaserTower :public MilitaryTower
{
	/*static int m_id;
	static int m_cost;
	static float m_fRadius;*/
public:
	LaserTower(sf::Vector2f position);

	/*static inline int GetCost() { return m_cost; };
	static inline int GetRadius() { return m_fRadius; };*/
};