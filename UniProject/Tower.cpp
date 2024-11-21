#include "Tower.h"

Tower::Tower(int cost, float actionCooldown, sf::Vector2i texturePosition, sf::Vector2f position, float radius): m_cost(cost), m_position(position), 
m_fActionCooldown(actionCooldown)
{
	m_ActionArea.setRadius(radius);
	m_texture.loadFromFile("Assets/Textures/Towers/Towers-100px.png");
	m_sprite.setTextureRect(sf::IntRect(texturePosition, sf::Vector2i(100,100)));
	m_sprite.setScale(0.64, 0.64);
	m_ftimer = 0.0f;
	m_sprite.setPosition(m_position);
}

void Tower::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}
