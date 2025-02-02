#include "EnemyManager.h"
#include <time.h>
#include <random>
EnemyManager::EnemyManager()
{
	m_cooldown = 0.0f;
}

void EnemyManager::Update(float deltaTime, Player& player)
{
	m_cooldown -= clock.restart().asSeconds();
	if (m_cooldown <= 0)
	{
		srand(time(NULL));
		int randomValue = rand() % 6;
		EnemyType newEnemy = static_cast<EnemyType>(randomValue);

		int scoreMultiplier = player.GetScore() / 500;
		switch (newEnemy)
		{
		case Scorpion:
			m_vecEnemies.push_back(new Ground_Scorpion(scoreMultiplier));
			break;
		case Leafbug:
			m_vecEnemies.push_back(new Ground_Leafbug(scoreMultiplier));
			break;
		case Magma_Crab:
			m_vecEnemies.push_back(new Ground_Magma_Crab(scoreMultiplier));
			break;
		case Clampbeetle:
			m_vecEnemies.push_back(new Flying_Clampbeetle(scoreMultiplier));
			break;
		case Locust:
			m_vecEnemies.push_back(new Flying_Locust(scoreMultiplier));
			break;
		case Voidbutterfly:
			m_vecEnemies.push_back(new Flying_Voidbutterfly(scoreMultiplier));
			break;
		default:
			break;
		}
		m_cooldown = 3.0f;
	}
	for (auto it = m_vecEnemies.begin(); it != m_vecEnemies.end();)
	{
		if ((*it)->IsDead())
		{
			player.IncreaseScore((*it)->GetScore());
			delete* it;
			it = m_vecEnemies.erase(it);
			m_count++;
		}
		else {
			if (!(*it)->IsFighting())
			{
				(*it)->Update(deltaTime, player);
			}
			it++;
		}
	}
}

void EnemyManager::Draw(sf::RenderWindow& window)
{
	for (auto enemy : m_vecEnemies)
	{
		enemy->Draw(window);
	}
}