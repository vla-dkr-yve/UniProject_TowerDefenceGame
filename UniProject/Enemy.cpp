#include "Enemy.h"
Enemy::Enemy(int hp, float speed, float radius, sf::Color color): m_Hp(hp), m_fSpeed(speed)
{
	m_bIsDead = false;
	m_sprite.setOutlineThickness(1);
	m_sprite.setOutlineColor(sf::Color::Black);
	m_sprite.setRadius(radius);
	m_sprite.setFillColor(color);
	m_sprite.setOrigin(sf::Vector2f(radius,radius));
	m_sprite.setPosition(sf::Vector2f(256, 0));

	m_waypointsIndex = 0;
	/*for (int i = 0; i < 6; i++)
	{
		m_waypoints[i] = m_waypoints[i] + sf::Vector2f(0, radius);
	}*/
}

Enemy::~Enemy()
{
}

void Enemy::Move(float fDeltaTime, sf::Vector2f direction)
{
		m_sprite.setPosition(m_sprite.getPosition() + direction * fDeltaTime * m_fSpeed);
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

void Enemy::Update(float fDeltaTime)
{
	if (m_waypointsIndex < 6) {
		sf::Vector2f target = m_waypoints[m_waypointsIndex];
		sf::Vector2f direction = target - m_sprite.getPosition();
		float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
		if (distance < 5.0f) {
			m_waypointsIndex++;
		}
		else if(!m_bIsDead){
			direction /= distance;
			Move(fDeltaTime, direction);
		}
	}
	if (m_waypointsIndex >= 6)
	{
		m_bIsDead = true;
	}
}
