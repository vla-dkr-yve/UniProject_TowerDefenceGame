#pragma once
#include <vector>
#include "Enemy.h"
#include "BasicEnemy.h"
#include "FastEnemy.h"
#include "SlowEnemy.h"
#include "Boss.h"

#define BOSSCOUNT 5

enum EnemyType {
	Basic,
	Fast,
	Slow,
};

class EnemyManager
{
	std::vector <Enemy*> m_vecEnemies;

	float m_cooldown;
	unsigned int m_count;

	sf::Clock clock;
public:
	EnemyManager();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	inline std::vector <Enemy*> GetEnemyVector(){ return m_vecEnemies; };
};

