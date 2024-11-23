#include "MilitaryTower.h"
#include <iostream>


MilitaryTower::MilitaryTower(int damage, int cost, float actionCooldown, sf::Vector2i texturePosition, sf::Vector2f position, float radius, int laserAmount):
	Tower(cost, actionCooldown, texturePosition, position, radius), m_damage(damage), m_laserAmount(laserAmount), tmp_LaserAmount(m_laserAmount)
{
}

void MilitaryTower::Update(float deltaTime, std::vector<Enemy*>& vecEnemies)
{
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
	std::cout << m_laser.size() << std::endl;
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
	m_laser.push_back(new Laser(m_sprite.getPosition(), target,m_damage));
}
