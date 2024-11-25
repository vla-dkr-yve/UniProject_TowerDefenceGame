#include "HouseTower.h"

HouseTower::HouseTower(sf::Vector2f position, std::vector<CivilTower*>& towers) : CivilTower(2,1,150,60.0f,sf::Vector2i(100 * 0, 100 * 1), position, 150)
{
	ApplyBuffs(towers);
}

void HouseTower::Action(float deltaTime, Player& player)
{
	m_ftimer -= deltaTime;
	if (m_ftimer <= 0)
	{
		player.IncreaseLives(m_currentValue);
		m_ftimer = m_fActionCooldown;
	}
}

void HouseTower::ApplyBuffs(std::vector<CivilTower*>& towers)
{
	for (auto tower: towers)
	{
		if (std::find(m_affectedTowers.begin(), m_affectedTowers.end(), tower) != m_affectedTowers.end())
			continue;

		float distance = Math::Distance(tower->GetSprite().getPosition(), m_sprite.getPosition());
		if (m_ActionArea.getRadius() > distance)
		{
			if (tower->GetId() == 0) {
				Buff buff = { 2, this };
				tower->AddBuff(buff);
				m_affectedTowers.push_back(tower);
			}
			else if (tower->GetId() == 1) {
				Buff buff = { 10, this };
				tower->AddBuff(buff);
				m_affectedTowers.push_back(tower);
			}
		}
	}
}

void HouseTower::ReapplyBuffs(CivilTower* newTower)
{
	float distance = Math::Distance(newTower->GetSprite().getPosition(), m_sprite.getPosition());
	if (m_ActionArea.getRadius() > distance)
	{
		if (newTower->GetId() == 0) {
			Buff buff = { 2, this };
			newTower->AddBuff(buff);
			m_affectedTowers.push_back(newTower);
		}
		else if (newTower->GetId() == 1) {
			Buff buff = { 10, this };
			newTower->AddBuff(buff);
			m_affectedTowers.push_back(newTower);
		}
	}
}