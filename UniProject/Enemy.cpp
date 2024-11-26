#include "Enemy.h"
Enemy::Enemy(int hp, float speed, float radius, sf::Color color): m_maximumHp(hp), m_fSpeed(speed)
{
	m_currentHp = m_maximumHp;

	m_bIsDead = false;
	m_sprite.setOutlineThickness(1);
	m_sprite.setOutlineColor(sf::Color::Black);
	m_sprite.setRadius(radius);
	m_sprite.setFillColor(color);
	m_sprite.setOrigin(sf::Vector2f(radius,radius));
	m_sprite.setPosition(sf::Vector2f(256, 0));

	m_healthBar.setSize(sf::Vector2f(radius * 2, 5));
	m_healthBar.setPosition(sf::Vector2f(m_sprite.getPosition().x - radius, m_sprite.getPosition().y - radius - m_healthBar.getSize().y * 2));
	m_healthBar.setFillColor(sf::Color::Red);

	m_healthBarBackground.setSize(sf::Vector2f(radius * 2, 5));
	m_healthBarBackground.setPosition(sf::Vector2f(m_sprite.getPosition().x - radius, m_sprite.getPosition().y - radius - m_healthBarBackground.getSize().y * 2));
	m_waypointsIndex = 0;
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
	window.draw(m_healthBar);
}

void Enemy::TakeDamage(int damage)
{
	m_currentHp -= damage; 
	if (m_currentHp <= 0)
		m_currentHp = 0;

	float healthPercentage = static_cast<float>(m_currentHp) / static_cast<float>(m_maximumHp);
	m_healthBar.setSize(sf::Vector2f(m_healthBarBackground.getSize().x * healthPercentage, m_healthBarBackground.getSize().y));
}

void Enemy::Update(float fDeltaTime, Player& player)
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
		player.DecreaseLives(1);
	}
	if (m_waypointsIndex >= 6 || m_currentHp <= 0)
	{
		m_bIsDead = true;
	}
	m_healthBarBackground.setPosition(sf::Vector2f(m_sprite.getPosition().x - m_sprite.getRadius(), m_sprite.getPosition().y - m_sprite.getRadius() - m_healthBarBackground.getSize().y * 2));
	m_healthBar.setPosition(sf::Vector2f(m_sprite.getPosition().x - m_sprite.getRadius(), m_sprite.getPosition().y - m_sprite.getRadius() - m_healthBar.getSize().y * 2));
}
