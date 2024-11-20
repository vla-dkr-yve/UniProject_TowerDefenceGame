#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
protected:
	int m_Hp;
	float m_fSpeed;
	sf::CircleShape m_sprite;
	bool m_bIsDead;
	
	int m_waypointsIndex;
	sf::Vector2f m_waypoints[6] = { {256,768}, {768, 768}, {768, 256}, {1280,256}, {1280, 640}, {1982, 640}};
public:
	Enemy(int hp, float speed, float radius, sf::Color color);
	~Enemy();

	void Update(float fDeltaTime);
	void Move(float fDeltaTime, sf::Vector2f direction);
	void Draw(sf::RenderWindow& window);

	void ChangeColor(sf::Color color) { m_sprite.setFillColor(color); };
	void ChangeRadius(float radius) { m_sprite.setRadius(radius); };

	sf::CircleShape& GetSprite() { return m_sprite; };
	float GetSpeed() { return m_fSpeed; };
	void SetSpeed(int speed) { m_fSpeed = speed; };
	int GetHp() { return m_Hp; };
	void SetHp(int hp) { m_Hp = hp; };
	bool IsDead() { return m_bIsDead; };
};

