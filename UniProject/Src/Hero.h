#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include "Enemy.h"


class Hero
{
private:
	bool m_isActive;

	const int m_maxHp = 100;
	int m_hp;
	int m_damage;
	float m_speed;
	float m_speedMultiplier;

	int m_stamina;

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	const int m_offsetY = 26;
	const int m_offsetX = 32;
	const int m_width = 52;
	const int m_height = 36;
	const float m_scaleX = 1.75;
	const float m_scaleY = 1.75;

	std::unordered_map<std::string, int> m_animationNum;

	std::unordered_map<std::string, int> m_animationPosition;

	std::string m_currentState;
	char m_currentSide;
	short int m_currentAttack;
	short int m_totalAttack;

	int m_currentAnimation;
	float m_animationTimer;
	bool m_isRotated;
	bool m_isMoving;
	bool m_isAttacking;
	bool m_isDefending;

	//bool m_isTargeted;
	Enemy* m_target;

	sf::RectangleShape m_hitbox;
	const int m_hitboxWidth = 34;
	const int m_hitboxHeight = 36;
public:
	Hero();
	void Animator(float deltaTime);
	void Move(float deltaTime, char side);
	void Attack();
	//void Attacking(std::vector<Enemy*>& Enemies);
	void Defence();
	void ChangeState(std::string newState);
	void Damage(int damage);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	inline bool IsActive() { return m_isActive; };
	inline bool IsAttacking() { return m_isAttacking; };
	inline bool IsDefending() { return m_isDefending; };
	inline sf::Vector2f GetPosition() { return m_sprite.getPosition(); };
	inline sf::RectangleShape& GetHitBox() { return m_hitbox; };
	inline sf::Vector2f GetHitBoxPosition() { return m_hitbox.getPosition(); };
	inline sf::Vector2f GetHitBoxSize() { return m_hitbox.getSize(); };
	inline int GetCurrentAnimation() { return m_currentAnimation; };
	inline char GetCurrentSide() { return m_currentSide; };
	inline Enemy* GetTarget() { return m_target; };
	inline int GetDamage() { return m_damage; };
	inline void SetTarget(Enemy* newTarget) { m_target = newTarget; };
	inline void ChangeActivenessState() { m_isActive = !m_isActive; };
};

