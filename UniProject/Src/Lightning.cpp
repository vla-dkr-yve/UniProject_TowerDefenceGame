#include "Lightning.h"
#include <iostream>

Lightning::Lightning(sf::Vector2f position, float rotation): m_currentAnimation(0), m_animationTimer(0.0f), m_shoodBeDestroyed(false)
{
	m_texture.loadFromFile("Assets/Textures/FX/Lightning/SpriteSheet.png");
	m_sprite.setTexture(m_texture);
	
	m_sprite.setTextureRect(sf::IntRect(0, m_currentAnimation * 22, 104,22));
	m_sprite.setPosition(position + sf::Vector2f(0, - (m_hitboxHeight / 2)));
	
	std::cout << "Angle: " << rotation << "\n";
	m_sprite.setRotation(rotation);
	//m_sprite.set
	//m_sprite.setScale();

	m_animationWidth = { {0, 13}, {0, 26}, { 0, 39 },{0, 65},{0, 78},{0, 91},{0, 91},{0, 78},{0, 65},{0, 39},{0, 26},{0, 13}, {0, 13} };
	m_animationOffset = { {0, 0}, {0, 0}, { 0, 0 },{0, 0},{0, 0},{0, 0},{0, 0},{0, 13},{0, 26},{0, 39},{0, 52},{0, 65}, {0, 78} };



	m_hitbox.setSize(sf::Vector2f(m_hitboxWidth, m_hitboxHeight));
	m_hitbox.setFillColor(sf::Color(255, 255, 255, 0));
	m_hitbox.setOutlineColor(sf::Color::Red);
	m_hitbox.setOutlineThickness(1);
	m_hitbox.setScale(m_sprite.getScale());
	m_hitbox.setPosition(m_sprite.getPosition());

	std::cout << "Created lightning\n";
}

Lightning::~Lightning()
{
	std::cout << "Destroyed lightning\n";
}

void Lightning::Animator(float deltaTime)
{
	m_animationTimer += deltaTime;
	if (m_animationTimer > 0.01667f)
	{
		m_currentAnimation++;
		if (m_currentAnimation >= 13)
		{
			m_shoodBeDestroyed = true;
			return;
		}
		else {
			m_sprite.setTextureRect(sf::IntRect(0, m_currentAnimation * 22, 104, 22));
			m_hitbox.setSize(sf::Vector2f(m_animationWidth[m_currentAnimation], 22));
			m_hitbox.setPosition(m_hitbox.getPosition() + sf::Vector2f(m_animationOffset[m_currentAnimation], 0));
		}
		m_animationTimer = 0.0f;
	}
}

void Lightning::Update(float deltaTime)
{
	Animator(deltaTime);
}

void Lightning::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
	//window.draw(m_hitbox);
}
