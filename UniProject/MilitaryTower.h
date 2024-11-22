#pragma once
#include "Tower.h"
#include "Enemy.h"
#include "Laser.h"
#include <vector>
class MilitaryTower : public Tower
{
protected:
	std::vector<Laser*> m_laser;
	int m_damage;
	int m_laserAmount;
public:
	MilitaryTower(int damage, int cost, float actionCooldown, sf::Vector2i texturePosition, sf::Vector2f position, float radius, int laserAmount);

	void Update(float deltaTime, std::vector <Enemy*>& vecEnemies);
	void Action(sf::Vector2f target);

	inline std::vector<Laser*> GetLaserVector() { return m_laser; };
};

