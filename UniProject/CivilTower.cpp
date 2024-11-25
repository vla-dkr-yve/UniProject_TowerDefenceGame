#include "CivilTower.h"

CivilTower::CivilTower(int id, int value,int cost, float actionCooldown, sf::Vector2i texturePosition, sf::Vector2f position, float radius):
	Tower(value,cost,actionCooldown, texturePosition, position, radius), m_id(id)
{
}

CivilTower::~CivilTower()
{
	RemoveBuffs();
}

void CivilTower::Action(float deltaTime)
{
}

void CivilTower::RemoveBuffs()
{
	for (auto tower: m_affectedTowers)
	{
		tower->RemoveBuffBySource(this);
	}
	m_affectedTowers.clear();
}
