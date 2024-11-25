#include "ResearchCenter.h"

ResearchCenter::ResearchCenter(sf::Vector2f position): CivilTower(0,1,150, 3.0f,sf::Vector2i(0,0), position, 0)
{
}

void ResearchCenter::Action(float deltaTime, Player& player)
{
	m_ftimer -= deltaTime;
	if (m_ftimer <= 0)
	{
		player.IncreaseResearchPoints(m_currentValue);
		m_ftimer = m_fActionCooldown;
	}
}