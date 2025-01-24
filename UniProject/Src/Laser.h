#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
class Laser
{
private:
	sf::RectangleShape line;
	sf::Vector2f m_direction;

	float m_fLaserSpeed;
	int m_damage;
	bool m_bIsDestroyed;
public:
	Laser(sf::Vector2f position, sf::Vector2f target ,int damage);
	
	void Update(float deltaTime,const std::vector<Enemy*>& vecEnemies);
	void Draw(sf::RenderWindow& window);

	bool OutOfTheScreen();
	inline bool IsDestroyed(){ return m_bIsDestroyed; };
};