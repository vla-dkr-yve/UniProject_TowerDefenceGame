#include "HouseTower.h"

HouseTower::HouseTower(sf::Vector2f position) : CivilTower(2,1,150,0.0f,sf::Vector2i(0,1), position, 150)
{
}

void HouseTower::ApplyBuffs(std::vector<CivilTower*>& towers)
{
	for (auto tower: towers)
	{
		if (m_ActionArea.getGlobalBounds().contains(tower->GetSprite().getPosition()))
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
