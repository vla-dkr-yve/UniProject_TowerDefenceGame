#include "MouseSprite.h"

#include <iostream>

MouseSprite::MouseSprite()
{
	m_texture.loadFromFile("Assets/Textures/Towers/Towers-100px.png");
	m_sprite.setTexture(m_texture);
	m_bIsMouseSpriteActive = false;
}

void MouseSprite::Update(float deltaTime, GUI& gui, sf::Vector2f& mousePosition, Map& map, sf::Event event, std::vector <MilitaryTower*> towers)
{
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && gui.IsOnTheGui(mousePosition))
	{
		int ChoosenTower = (mousePosition.y - gui.GetRectPositionY()) / 64;
		std::cout << ChoosenTower << std::endl;
		m_sprite.setTextureRect(gui.GetTextureRect(ChoosenTower));
		m_bIsMouseSpriteActive = true;
		towerType = ChoosenTower;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && !gui.IsOnTheGui(mousePosition))
	{
		m_bIsMouseSpriteActive = false;
	}
	if (m_bIsMouseSpriteActive)
	{
		m_sprite.setPosition(mousePosition);
	}
	for (auto tower:towers)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && tower->GetSprite().getGlobalBounds().contains(mousePosition)){
			tower->SetActionAreaActive();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !tower->GetSprite().getGlobalBounds().contains(mousePosition)) {
			tower->SetActionAreaUnActive();
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && gui.IsOnTheGui(mousePosition))
	{
		int ChoosenTower = (mousePosition.y - gui.GetRectPositionY()) / 64;
		std::cout << ChoosenTower << std::endl;
		m_sprite.setTextureRect(gui.GetTextureRect(ChoosenTower));
		m_bIsMouseSpriteActive = true;
		towerType = ChoosenTower;
	}
}

void MouseSprite::Draw(sf::RenderWindow& window)
{
	if (m_bIsMouseSpriteActive)
	{
		window.draw(m_sprite);
	}
}
