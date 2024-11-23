#include "Tower.h"


Tower::Tower(int cost, float actionCooldown, sf::Vector2i& texturePosition, sf::Vector2f& position, float radius): m_cost(cost), m_position(position), 
m_fActionCooldown(actionCooldown)
{
	m_texture.loadFromFile("Assets/Textures/Towers/Towers-100px.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(texturePosition, sf::Vector2i(100,100)));
	m_sprite.setScale(0.64, 0.64);
	m_sprite.setPosition(m_position);

	m_ftimer = 0.0f;

	m_bIsActionAreaActive = false;

	m_ActionArea.setRadius(radius);
	m_ActionArea.setOrigin(sf::Vector2f(m_ActionArea.getRadius() - 32, m_ActionArea.getRadius() - 32));
	m_ActionArea.setPosition(m_sprite.getPosition());
	m_ActionArea.setFillColor(sf::Color(255, 255, 255, 32));
	m_ActionArea.setOutlineThickness(1);
	m_ActionArea.setOutlineColor(sf::Color::Black);

	m_buildingLine.setSize(sf::Vector2f(64, 5));
	m_buildingLine.setPosition(sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y - m_buildingLine.getSize().y * 2));
	m_buildingLine.setFillColor(sf::Color::Blue);

	m_buildingBackground.setSize(sf::Vector2f(64, 5));
	m_buildingBackground.setPosition(sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y - m_buildingBackground.getSize().y * 2));

	m_fBuildTime = 3.0f;
	m_fCurrentTime = m_fBuildTime;
	m_bIsBuild = true;
}

void Tower::Build()
{
	m_fCurrentTime -= clock.restart().asSeconds();
	if (m_fCurrentTime <= 0)
	{
		m_bIsBuild = false;
	}
	else {
		float buildPercentage = m_fCurrentTime / m_fBuildTime;

		m_buildingLine.setSize(sf::Vector2f(m_buildingBackground.getSize().x * buildPercentage, m_buildingBackground.getSize().y));
	}
}

void Tower::Draw(sf::RenderWindow& window)
{
	if (m_bIsBuild)
	{
		window.draw(m_buildingLine);
	}
	if (!m_bIsBuild)
	{
		window.draw(m_sprite);
	}
	if (m_bIsActionAreaActive)
	{
		window.draw(m_ActionArea);
	}
}
