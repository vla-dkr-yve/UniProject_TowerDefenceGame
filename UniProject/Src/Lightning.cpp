#include "Lightning.h"

Lightning::Lightning(sf::Vector2f position): m_currentAnimation(0)
{
	m_texture.loadFromFile("Assets/Textures/FX/Lightning/SpriteSheet.png");
	m_sprite.setTexture(m_texture);
	
	m_sprite.setTextureRect(sf::IntRect(0, m_currentAnimation * 22, 104,22));

	//m_sprite.setScale();

	m_animationWidth = { {0,}, };



	hitbox.setSize(sf::Vector2f(m_hitboxWidth, m_hitboxHeight));
	hitbox.setFillColor(sf::Color(255, 255, 255, 0));
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(1);
	hitbox.setScale(m_sprite.getScale());
	hitbox.setPosition(sf::Vector2f(m_sprite.getPosition().x + hitbox.getGlobalBounds().getSize().x / 2, m_sprite.getPosition().y - hitbox.getGlobalBounds().getSize().y / 2));
}
