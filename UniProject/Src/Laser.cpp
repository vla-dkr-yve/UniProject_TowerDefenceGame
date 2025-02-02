#define _USE_MATH_DEFINES

#include "Laser.h"
#include <cmath>
#include "Math.h"
Laser::Laser(sf::Vector2f position, sf::Vector2f target , int damage): m_damage(damage)
{
	m_bIsDestroyed = false;
	line.setSize(sf::Vector2f(15, 5));
	line.setFillColor(sf::Color::Red);
	line.setPosition(position + sf::Vector2f(32, 0));

	sf::Vector2f direction = target - position;
	float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
	direction /= distance;
	m_direction = direction;


	float angle = std::atan2(direction.x, direction.y);
	float angleDegrees = angle * 180 / M_PI;
	line.setRotation(angleDegrees);

	m_fLaserSpeed = 700;
}

void Laser::Update(float deltaTime,const std::vector<Enemy*>& vecEnemies)
{
	line.setPosition(line.getPosition() + m_direction * m_fLaserSpeed * deltaTime);
	for (auto enemy: vecEnemies)
	{
		if (Math::EnemyCollision(*enemy, line.getPosition()))
		{
			enemy->TakeDamage(m_damage);
			m_bIsDestroyed = true;
		}
	}
	if (OutOfTheScreen())
	{
		m_bIsDestroyed = true;
	}
}

bool Laser::OutOfTheScreen()
{
	if (line.getPosition().x < 0 || line.getPosition().x > 1920 || line.getPosition().y < 0 || line.getPosition().y > 1024)
	{
		return true;
	}
	return false;
}

void Laser::Draw(sf::RenderWindow& window)
{
	window.draw(line);
}