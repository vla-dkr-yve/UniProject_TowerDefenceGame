#include "FactoryTower.h"

//int FactoryTower::m_cost = 150;
//int FactoryTower::m_id = 1;
//float FactoryTower::m_fRadius = 150;
FactoryTower::FactoryTower(sf::Vector2f position): CivilTower(Factory, position)
{
}

void FactoryTower::Action(float deltaTime, Player& player)
{
	m_ftimer -= deltaTime;
	if (m_ftimer <= 0)
	{
		player.IncreaseMoney(m_currentValue);
		m_ftimer = m_fActionCooldown;
	}
}

//void FactoryTower::ApplyBuffs(std::vector<Tower*>& towers)
//{
//	return;
//}
