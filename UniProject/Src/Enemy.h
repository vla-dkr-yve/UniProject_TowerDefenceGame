#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "Player.h"

class Enemy
{
protected:
	int m_score;

	int m_maximumHp;
	int m_currentHp;
	float m_fSpeed;
	int m_armor;
	//sf::CircleShape m_sprite;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	//int m_animationFrames;
	std::map<std::string, int> m_animationNum;
	std::string m_currentSide;
	int m_currentAnimation;
	float m_animationTimer;
	bool m_isRotated;

	bool m_gotDamage;
	const float m_damageCooldown = 2 * 0.1;
	float m_damageTimer;

	sf::RectangleShape m_healthBar;
	sf::RectangleShape m_healthBarBackground;
	bool m_bIsDead;
	
	int m_waypointsIndex;
	sf::Vector2f m_waypoints[6] = { {256,768}, {768, 768}, {768, 256}, {1280,256}, {1280, 640}, {1982, 640}};

	bool m_isFighting;
	float m_attackCooldown = 3.0f;
	float m_attackTimer;
	bool m_canAttack;
public:
	Enemy(int score, int hp, float speed, int armor, std::string path, std::map<std::string, int> animationNum,sf::Vector2i textureSize);
	~Enemy();

	void Update(float fDeltaTime, Player& player, sf::Vector2f OpponentPosition = {-1,-1});
	void Move(float fDeltaTime, sf::Vector2f& direction);
	void Animator(float deltaTime, sf::Vector2f& direction);
	void Draw(sf::RenderWindow& window);


	inline sf::Sprite& GetSprite() { return m_sprite; };
	inline float GetSpeed() { return m_fSpeed; };
	inline int GetScore() { return m_score; };
	inline void SetSpeed(int speed) { m_fSpeed = speed; };
	inline int GetHp() { return m_currentHp; };
	inline void SetHp(int hp) { m_currentHp = hp; };
	inline bool IsDead() { return m_bIsDead; };
	inline bool CanAttack() { return m_canAttack; };
	const inline sf::Vector2f& GetPosition() { return m_sprite.getPosition(); };
	const inline sf::Vector2f& GetSize() const { return sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height); };
	inline bool IsFighting() { return m_isFighting; };
	inline void ChangeFightingState(bool state) { m_isFighting = state; };
	inline void ChangeAttackState(bool state) { m_canAttack = state; };

	void TakeDamage(int damage);
};

