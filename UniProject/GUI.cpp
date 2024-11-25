#include "GUI.h"
#include <iostream>
GUI::GUI(int money, int researchPoints, int lives)
{
	m_SriteHolderRect.setSize(sf::Vector2f(64, 64 * ArrSize));
	m_SriteHolderRect.setPosition(0, 1024 / 2 - m_SriteHolderRect.getSize().y / 2);
	m_SriteHolderRect.setFillColor(sf::Color(128,128,128));
	
	m_texture.loadFromFile("Assets/Textures/Towers/Towers-100px.png");
	for (int i = 0; i < ArrSize; i++)
	{
		m_sprites[i].setTexture(m_texture);
	}
	m_sprites[0].setTextureRect(sf::IntRect(100 * 0, 100 * 0, 100, 100));
	m_sprites[1].setTextureRect(sf::IntRect(100 * 3, 100 * 0, 100, 100));
	m_sprites[2].setTextureRect(sf::IntRect(100 * 0, 100 * 1, 100, 100));
	m_sprites[3].setTextureRect(sf::IntRect(100*2,100*1, 100,100));
	m_sprites[4].setTextureRect(sf::IntRect(100*3,100*1, 100,100));
	m_sprites[5].setTextureRect(sf::IntRect(100*0,100*2, 100,100));
	for (int i = 0; i < ArrSize; i++)
	{
		m_sprites[i].setScale(sf::Vector2f(0.64,0.64));
		m_sprites[i].setPosition(sf::Vector2f(0, m_SriteHolderRect.getPosition().y + i * 64));
	}

	m_ValuesHolderRect.setSize(sf::Vector2f(64 * 3, 64));
	m_ValuesHolderRect.setPosition(1920 - 3 * 64, 0);
	m_ValuesHolderRect.setFillColor(sf::Color(128, 128, 128));

	font.loadFromFile("Assets/Fonts/Arial.TTF");

	m_moneyText.setFont(font);
	m_moneyText.setString(std::to_string(money));
	m_moneyText.setCharacterSize(24);

	m_researchPointsText.setFont(font);
	m_researchPointsText.setString(std::to_string(researchPoints));
	m_researchPointsText.setCharacterSize(24);

	m_livesText.setFont(font);
	m_livesText.setString(std::to_string(lives));
	m_livesText.setCharacterSize(24);

	m_moneyText.setPosition(m_ValuesHolderRect.getPosition() + sf::Vector2f(0 * 64, 0));
	m_researchPointsText.setPosition(m_ValuesHolderRect.getPosition() + sf::Vector2f(1 * 64, 0));
	m_livesText.setPosition(m_ValuesHolderRect.getPosition() + sf::Vector2f(2 * 64, 0));
}

void GUI::Draw(sf::RenderWindow& window)
{
	//window.draw(m_SriteHolderRect);
	//window.draw(m_ValuesHolderRect);

	window.draw(m_moneyText);
	window.draw(m_researchPointsText);
	window.draw(m_livesText);

	for (int i = 0; i < ArrSize; i++)
	{
		window.draw(m_sprites[i]);
	}
}

void GUI::UpdateTextValues(int money, int researchPoints, int lives)
{
	m_moneyText.setString(std::to_string(money));
	m_researchPointsText.setString(std::to_string(researchPoints));
	m_livesText.setString(std::to_string(lives));
}
