#include "FactoryTower.h"

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