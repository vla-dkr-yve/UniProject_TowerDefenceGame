#include "FactoryTower.h"

FactoryTower::FactoryTower(sf::Vector2f position): CivilTower(1,10,150, 3.0f, sf::Vector2i(3, 0), position, 150)
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
