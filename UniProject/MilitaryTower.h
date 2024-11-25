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
	int tmp_LaserAmount;
public:
	MilitaryTower(int id, int damage, int cost, float actionCooldown, sf::Vector2i texturePosition, sf::Vector2f position, float radius, int laserAmount);

	void Update(float deltaTime, std::vector <Enemy*>& vecEnemies);
	void Action(sf::Vector2f target);
	void Draw(sf::RenderWindow& window) override;

	inline std::vector<Laser*> GetLaserVector() { return m_laser; };
	//void UpdateForce();
};

