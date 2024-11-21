#include "EnemyManager.h"
#include <time.h>
#include <random>

EnemyManager::EnemyManager()
{
	m_cooldown = 0.0f;
}

void EnemyManager::Update(float deltaTime)
{

	m_cooldown -= clock.restart().asSeconds();
	if (m_cooldown <= 0 && m_count != BOSSCOUNT)
	{
		srand(time(NULL));
		int randomValue = rand() % 3;
		EnemyType newEnemy = static_cast<EnemyType>(randomValue);
		switch (newEnemy)
		{
		case Basic:
			m_vecEnemies.push_back(new BasicEnemy);
			break;
		case Fast:
			m_vecEnemies.push_back(new FastEnemy);
			break;
		case Slow:
			m_vecEnemies.push_back(new SlowEnemy);
			break;
		default:
			break;
		}
		m_count++;
		m_cooldown = 3.0f;
	}
	else if (m_count == BOSSCOUNT) {
		m_vecEnemies.push_back(new Boss);
		m_count = 0;
	}
	for (auto it = m_vecEnemies.begin(); it != m_vecEnemies.end();)
	{
		if ((*it)->IsDead())
		{
			it = m_vecEnemies.erase(it);
		}
		else {
			(*it)->Update(deltaTime);
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
