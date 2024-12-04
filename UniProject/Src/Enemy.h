#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "Player.h"


class Enemy
{
protected:
	int m_maximumHp;
	int m_currentHp;
	float m_fSpeed;
	//sf::CircleShape m_sprite;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	//int m_animationFrames;
	std::map<std::string, int> m_animationNum;
	int m_currentAnimation;
	float m_animationTimer;
	bool m_isRotated;

	sf::RectangleShape m_healthBar;
	sf::RectangleShape m_healthBarBackground;
	bool m_bIsDead;
	
	int m_waypointsIndex;
	sf::Vector2f m_waypoints[6] = { {256,768}, {768, 768}, {768, 256}, {1280,256}, {1280, 640}, {1982, 640}};
public:
	Enemy(int hp, float speed, std::string path, std::map<std::string, int> animationNum,sf::Vector2i textureSize);
	~Enemy();

	void Update(float fDeltaTime, Player& player);
	void Move(float fDeltaTime, sf::Vector2f& direction);
	void Animator(float deltaTime, sf::Vector2f& direction);
	void Draw(sf::RenderWindow& window);

	//inline void ChangeColor(sf::Color color) { m_sprite.setFillColor(color); };
	//inline void ChangeRadius(float radius) { m_sprite.setRadius(radius); };

	inline sf::Sprite& GetSprite() { return m_sprite; };
	inline float GetSpeed() { return m_fSpeed; };
	inline void SetSpeed(int speed) { m_fSpeed = speed; };
	inline int GetHp() { return m_currentHp; };
	inline void SetHp(int hp) { m_currentHp = hp; };
	inline bool IsDead() { return m_bIsDead; };
	const inline sf::Vector2f& GetPosition() { return m_sprite.getPosition(); };
	const inline sf::Vector2f& GetSize() const { return sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height); };
	//inline float GetRadius() { return m_sprite.getRadius(); };

	void TakeDamage(int damage);
};
