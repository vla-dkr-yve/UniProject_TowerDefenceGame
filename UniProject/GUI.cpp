#include "GUI.h"

GUI::GUI()
{
	m_SriteHolderRect.setSize(sf::Vector2f(64, 64 * ArrSize));
	m_SriteHolderRect.setPosition(0, 1024 / 2 - m_SriteHolderRect.getSize().y / 2);
	m_SriteHolderRect.setFillColor(sf::Color(128,128,128));
	
	m_texture.loadFromFile("Assets/Textures/Towers/Towers-100px.png");
	for (int i = 0; i < ArrSize; i++)
	{
		m_sprites[i].setTexture(m_texture);
	}
	m_sprites[0].setTextureRect(sf::IntRect(100*2,100*1, 100,100));
	m_sprites[1].setTextureRect(sf::IntRect(100*3,100*1, 100,100));
	m_sprites[2].setTextureRect(sf::IntRect(100*0,100*2, 100,100));
	for (int i = 0; i < ArrSize; i++)
	{
		m_sprites[i].setScale(sf::Vector2f(0.64,0.64));
		m_sprites[i].setPosition(sf::Vector2f(0, m_SriteHolderRect.getPosition().y + i * 64));
	}
}

void GUI::Draw(sf::RenderWindow& window)
{
	window.draw(m_SriteHolderRect);

	for (int i = 0; i < ArrSize; i++)
	{
		window.draw(m_sprites[i]);
	}
}
