#include "ResearchCenter.h"
ResearchCenter::ResearchCenter(sf::Vector2f position, std::vector<MilitaryTower*>& towers): CivilTower(Research, position)
{
	ApplyBuffs(towers);
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

void ResearchCenter::ApplyBuffs(std::vector<MilitaryTower*>& towers)
{
	for (auto tower : towers)
	{
		if (std::find(m_affectedTowers.begin(), m_affectedTowers.end(), tower) != m_affectedTowers.end())
			continue;

		float distance = Math::Distance(tower->GetSprite().getPosition(), m_sprite.getPosition());
		if (m_ActionArea.getRadius() > distance)
		{
			Buff buff = { 25, this };
			tower->AddBuff(buff);
			m_affectedTowers.push_back(tower);
		}
	}
}

void ResearchCenter::ReapplyBuffs(MilitaryTower* newTower)
{
	float distance = Math::Distance(newTower->GetSprite().getPosition(), m_sprite.getPosition());
	if (m_ActionArea.getRadius() > distance)
	{
		Buff buff = { 25, this };
		newTower->AddBuff(buff);
		m_affectedTowers.push_back(newTower);
	}
}
