#include "MilitaryTower.h"

MilitaryTower::MilitaryTower(TowerType towerType,sf::Vector2f position, int laserAmount):
	Tower(towerType, position),m_laserAmount(laserAmount), tmp_LaserAmount(m_laserAmount)
{
}

void MilitaryTower::Update(float deltaTime,std::vector<Enemy*>& vecEnemies)
{

	if (m_bIsBuild)
	{
		Build(deltaTime);
		return;
	}

	if (tmp_LaserAmount <= 0)
	{
		m_ftimer -= deltaTime;
	}
	if (m_ftimer <= 0)
	{
		for (auto enemy : vecEnemies)
		{
			if (m_ActionArea.getGlobalBounds().contains(enemy->GetSprite().getPosition()))
			{
				Action(enemy->GetSprite().getPosition());
				tmp_LaserAmount--;
				if (tmp_LaserAmount <= 0)
				{
					m_ftimer = m_fActionCooldown;
					break;
				}
			}
		}
	}
	for (auto it = m_laser.begin(); it != m_laser.end();)
	{
		if ((*it)->IsDestroyed())
		{
			it = m_laser.erase(it);
		}
		else {
			(*it)->Update(deltaTime, vecEnemies);
			it++;
		}
	}
}

void MilitaryTower::Action(sf::Vector2f target)
{
	m_laser.push_back(new Laser(m_sprite.getPosition(), target, m_currentValue));
}

void MilitaryTower::Draw(sf::RenderWindow& window)
{
	Tower::Draw(window);
	for (int i = 0; i < m_laser.size(); i++)
	{
		m_laser[i]->Draw(window);
	}
}
