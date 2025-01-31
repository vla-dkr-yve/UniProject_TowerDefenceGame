#pragma once
#include <vector>
#include "Enemy.h"
#include "Enemytypes.h"

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

	inline std::vector <Enemy*>& GetEnemyVector(){ return m_vecEnemies; };
};