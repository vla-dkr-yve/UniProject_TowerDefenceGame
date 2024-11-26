#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Enemy
{
protected:
	int m_maximumHp;
	int m_currentHp;
	float m_fSpeed;
	sf::CircleShape m_sprite;
	sf::RectangleShape m_healthBar;
	sf::RectangleShape m_healthBarBackground;
	bool m_bIsDead;
	
	int m_waypointsIndex;
	sf::Vector2f m_waypoints[6] = { {256,768}, {768, 768}, {768, 256}, {1280,256}, {1280, 640}, {1982, 640}};
public:
	Enemy(int hp, float speed, float radius, sf::Color color);
	~Enemy();

	void Update(float fDeltaTime, Player& player);
	void Move(float fDeltaTime, sf::Vector2f direction);
	void Draw(sf::RenderWindow& window);

	inline void ChangeColor(sf::Color color) { m_sprite.setFillColor(color); };
	inline void ChangeRadius(float radius) { m_sprite.setRadius(radius); };

	inline sf::CircleShape& GetSprite() { return m_sprite; };
	inline float GetSpeed() { return m_fSpeed; };
	inline void SetSpeed(int speed) { m_fSpeed = speed; };
	inline int GetHp() { return m_currentHp; };
	inline void SetHp(int hp) { m_currentHp = hp; };
	inline bool IsDead() { return m_bIsDead; };
	inline float GetRadius() { return m_sprite.getRadius(); };

	void TakeDamage(int damage);
};

