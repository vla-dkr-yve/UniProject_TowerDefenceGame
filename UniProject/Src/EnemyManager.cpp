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
	if (m_cooldown <= 0 && m_count != BOSSCOUNT)
	{
		srand(time(NULL));
		int randomValue = rand() % 6;
		EnemyType newEnemy = static_cast<EnemyType>(randomValue);
		switch (newEnemy)
		{
		case Scorpion:
			m_vecEnemies.push_back(new Ground_Scorpion);
			break;
		case Leafbug:
			m_vecEnemies.push_back(new Ground_Leafbug);
			break;
		case Magma_Crab:
			m_vecEnemies.push_back(new Ground_Magma_Crab);
			break;
		case Clampbeetle:
			m_vecEnemies.push_back(new Flying_Clampbeetle);
			break;
		case Locust:
			m_vecEnemies.push_back(new Flying_Locust);
			break;
		case Voidbutterfly:
			m_vecEnemies.push_back(new Flying_Voidbutterfly);
			break;
		default:
			break;
		}
		m_cooldown = 3.0f;
	}
	//else if (m_count == BOSSCOUNT) {
	//	m_vecEnemies.push_back(new Boss);
	//	m_count = 0;
	//}
	for (auto it = m_vecEnemies.begin(); it != m_vecEnemies.end();)
	{
		if ((*it)->IsDead())
		{
			delete* it;
			it = m_vecEnemies.erase(it);
			m_count++;
		}
		else {
			(*it)->Update(deltaTime, player);
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
