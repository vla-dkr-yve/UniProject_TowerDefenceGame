#define _USE_MATH_DEFINES

#include "Laser.h"
#include <cmath>

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

void Laser::Update(float deltaTime, std::vector<Enemy*>& vecEnemies)
{
	line.setPosition(line.getPosition() + m_direction * m_fLaserSpeed * deltaTime);
	for (auto enemy: vecEnemies)
	{
		if (Collision(*enemy))
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

bool Laser::Collision(Enemy& enemy)
{
	sf::Vector2f circleCenter = enemy.GetSprite().getPosition();
	float circleRadius = enemy.GetRadius();

	sf::Vector2f rectPos = line.getPosition();
	sf::Vector2f rectSize = line.getSize();

	float closestX = std::max(rectPos.x, std::min(circleCenter.x, rectPos.x + rectSize.x));
	float closestY = std::max(rectPos.y, std::min(circleCenter.y, rectPos.y + rectSize.y));

	float distanceX = circleCenter.x - closestX;
	float distanceY = circleCenter.y - closestY;

	return (distanceX * distanceX + distanceY * distanceY) <= (circleRadius * circleRadius);
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