#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

//enum AnimationStates {
//	ATTACK1,
//	ATTACK2,
//	ATTACK3,
//	DEATH,
//	DEFEND,
//	HURT,
//	IDLE,
//	RUN,
//	WALK
//};

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
	//const int m_offsetY = 10;
	const int m_offsetY = 26;
	//const int m_offsetX = 16;
	const int m_offsetX = 32;
	const int m_width = 34;
	const int m_height = 36;

	std::unordered_map<std::string, int> m_animationNum;

	std::unordered_map<std::string, int> m_animationPosition;

	std::string m_currentState;
	char m_currentSide;

	int m_currentAnimation;
	float m_animationTimer;
	bool m_isRotated;
	bool m_isMoving;

	sf::RectangleShape hitbox;
public:
	Hero();
	void Animator(float deltaTime);
	void Move(float deltaTime, char side);
	void Attack();
	void Defence();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
};

