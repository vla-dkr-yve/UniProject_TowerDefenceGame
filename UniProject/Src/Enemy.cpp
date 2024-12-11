#include "Enemy.h"
Enemy::Enemy(int hp, float speed, std::string path, std::map<std::string, int> animationNum, sf::Vector2i textureSize):
	m_maximumHp(hp), m_fSpeed(speed)
{
	m_currentHp = m_maximumHp;
	m_animationTimer = 0.0f;
	m_currentAnimation = 0;

	m_bIsDead = false;
	m_texture.loadFromFile(path);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), textureSize));
	m_sprite.setScale(sf::Vector2f(64 / textureSize.x, 64 / textureSize.y));

	for (auto const& i: animationNum)
	{
		m_animationNum[i.first] = i.second;
	}
	//m_sprite.setOutlineThickness(1);
	//m_sprite.setOutlineColor(sf::Color::Black);
	//m_sprite.setRadius(radius);
	//m_sprite.setFillColor(color);
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getGlobalBounds().width/2, m_sprite.getGlobalBounds().height/2));
	m_sprite.setPosition(sf::Vector2f(256, 0));

	m_healthBar.setSize(sf::Vector2f(m_sprite.getGlobalBounds().width, 5));
	m_healthBar.setPosition(sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y - m_sprite.getGlobalBounds().height / 2 - m_healthBar.getSize().y * 2));
	m_healthBar.setFillColor(sf::Color::Red);

	m_healthBarBackground.setSize(sf::Vector2f(m_sprite.getGlobalBounds().width, 5));
	m_healthBarBackground.setPosition(sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y - m_sprite.getGlobalBounds().height / 2 - m_healthBarBackground.getSize().y * 2));
	m_waypointsIndex = 0;
	m_isRotated = false;
}

Enemy::~Enemy()
{
}

void Enemy::Move(float fDeltaTime, sf::Vector2f& direction)
{
	Animator(fDeltaTime,direction);
	m_sprite.setPosition(m_sprite.getPosition() + direction * fDeltaTime * m_fSpeed);
}

void Enemy::Animator(float deltaTime,sf::Vector2f& direction) 
{
	m_animationTimer += deltaTime;
	if (m_animationTimer > 0.1f)
	{
		m_currentAnimation++;
		if (m_currentAnimation >= m_animationNum[m_currentSide])
		{
			m_currentAnimation = 0;
		}
		m_animationTimer = 0;
	}
	if (direction.x > 0 && abs(direction.x) > abs(direction.y))
	{
		if (!m_isRotated)
		{
			if (m_animationNum["right"] == -1)
			{
				m_sprite.scale(-1, 1);
				m_isRotated = true;
				m_currentSide = "left";
			}
			else {
				m_currentSide = "right";
			}
		}
		m_sprite.setTextureRect(sf::IntRect(m_currentAnimation * 64, 5 * 64, 64, 64));
	}
	if (direction.x < 0 && abs(direction.x) > abs(direction.y))
	{
		if (!m_isRotated)
		{
			if (m_animationNum["left"] == -1)
			{
				m_sprite.scale(-1, 1);
				m_isRotated = true;
				m_currentSide = "right";
			}
			else {
				m_currentSide = "left";
			}
		}
		m_sprite.setTextureRect(sf::IntRect(m_currentAnimation * 64, 5 * 64, 64, 64));
	}
	if (direction.y < 0 && abs(direction.y) > abs(direction.x))
	{
		m_sprite.setTextureRect(sf::IntRect(m_currentAnimation * 64, 4 * 64, 64, 64));
		m_currentSide = "top";
	}
	if (direction.y > 0 && abs(direction.y) > abs(direction.x))
	{
		m_sprite.setTextureRect(sf::IntRect(m_currentAnimation * 64, 3 * 64, 64, 64));
		m_currentSide = "bottom";
	}
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
	m_healthBarBackground.setPosition(sf::Vector2f(m_sprite.getPosition().x - m_sprite.getGlobalBounds().width / 2, m_sprite.getPosition().y - m_sprite.getGlobalBounds().height / 2 - m_healthBarBackground.getSize().y));
	m_healthBar.setPosition(sf::Vector2f(m_sprite.getPosition().x - m_sprite.getGlobalBounds().width / 2, m_sprite.getPosition().y - m_sprite.getGlobalBounds().height / 2 - m_healthBar.getSize().y));
}
