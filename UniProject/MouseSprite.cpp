#include "MouseSprite.h"

#include <iostream>

MouseSprite::MouseSprite()
{
	m_texture.loadFromFile("Assets/Textures/Towers/Towers-100px.png");
	m_sprite.setTexture(m_texture);
	m_bIsActive = false;
}

void MouseSprite::Update(float deltaTime, GUI& gui, sf::Vector2f& mousePosition, Map& map, sf::Event event)
{
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && gui.IsOnTheGui(mousePosition))
	{
		int ChoosenTower = (mousePosition.y - gui.GetRectPositionY()) / 64;
		std::cout << ChoosenTower << std::endl;
		m_sprite.setTextureRect(gui.GetTextureRect(ChoosenTower));
		m_bIsActive = true;
		towerType = ChoosenTower;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && !gui.IsOnTheGui(mousePosition))
	{
		m_bIsActive = false;
	}
	if (m_bIsActive)
	{
		m_sprite.setPosition(mousePosition);
	}
}

void MouseSprite::Draw(sf::RenderWindow& window)
{
	if (m_bIsActive)
	{
		window.draw(m_sprite);
	}
}
