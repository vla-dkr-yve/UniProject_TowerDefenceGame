#pragma once
#include <vector>
#include "Enemy.h"
#include "Enemytypes.h"

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
	void Update(float deltaTime, Player& player);
	void Draw(sf::RenderWindow& window);

	const inline std::vector <Enemy*>& GetEnemyVector() const{ return m_vecEnemies; };
};

