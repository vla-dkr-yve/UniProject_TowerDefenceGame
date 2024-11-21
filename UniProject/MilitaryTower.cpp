#include "MilitaryTower.h"



MilitaryTower::MilitaryTower(int damage, int cost, float actionCooldown, sf::Vector2i texturePosition, sf::Vector2f position, float radius):
	Tower(cost, actionCooldown, texturePosition, position, radius), m_damage(damage)
{
}

void MilitaryTower::Update(float deltaTime, std::vector<Enemy*>& vecEnemies)
{
	m_ftimer -= deltaTime;
	if (m_ftimer <= 0)
	{
		for (auto enemy : vecEnemies)
		{
			if (m_ActionArea.getGlobalBounds().contains(enemy->GetSprite().getPosition()))
			{
				sf::Vector2f target = enemy->GetSprite().getPosition();
				sf::Vector2f direction = target - m_sprite.getPosition();
				float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
				direction /= distance;
				Action(target);
				break;
			}
		}
		m_ftimer = m_fActionCooldown;
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
	m_laser.push_back(new Laser(m_sprite.getPosition(), target,m_damage));
}
