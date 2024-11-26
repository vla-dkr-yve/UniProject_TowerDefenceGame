#include "GUI.h"
#include "Tower.h"
#include "MilitaryTower.h"
#include "LaserTower.h"
#include "UdvancedLaserTower.h"
#include "ScatterLaserTower.h"
#include "Laser.h"
#include "CivilTower.h"
#include "ResearchCenter.h"
#include "FactoryTower.h"
#include "HouseTower.h"
#include <iostream>
GUI::GUI(int money, int researchPoints, int lives)
{
	font.loadFromFile("Assets/Fonts/Arial.TTF");
	for (int i = 0; i < ArrSize; i++)
	{
		m_towerCost[i].setFont(font);
		m_towerCost[i].setString("123");
		m_towerCost[i].setCharacterSize(20);
	}
	m_SriteHolderRect.setSize(sf::Vector2f(64, 64 * (ArrSize) + m_offsetY * ArrSize));
	m_SriteHolderRect.setPosition(0, 1024 / 2 - m_SriteHolderRect.getSize().y / 2);
	m_SriteHolderRect.setFillColor(sf::Color(128,128,128));
	
	m_texture.loadFromFile("Assets/Textures/Towers/Towers-100px.png");
	for (int i = 0; i < ArrSize; i++)
	{
		m_sprites[i].setTexture(m_texture);
		m_sprites[i].setScale(sf::Vector2f(0.64, 0.64));
	}
	m_sprites[0].setTextureRect(sf::IntRect(100 * 0, 100 * 0, 100, 100));
	m_towerCost[0].setString(std::to_string(ResearchCenter::GetCost()));
	m_sprites[1].setTextureRect(sf::IntRect(100 * 3, 100 * 0, 100, 100));
	m_towerCost[1].setString(std::to_string(FactoryTower::GetCost()));
	m_sprites[2].setTextureRect(sf::IntRect(100 * 0, 100 * 1, 100, 100));
	m_towerCost[2].setString(std::to_string(HouseTower::GetCost()));
	m_sprites[3].setTextureRect(sf::IntRect(100*2,100*1, 100,100));
	m_towerCost[3].setString(std::to_string(LaserTower::GetCost()));
	m_sprites[4].setTextureRect(sf::IntRect(100*3,100*1, 100,100));
	m_towerCost[4].setString(std::to_string(UdvancedLaserTower::GetCost()));
	m_sprites[5].setTextureRect(sf::IntRect(100*0,100*2, 100,100));
	m_towerCost[5].setString(std::to_string(ScatterLaserTower::GetCost()));
	for (int i = 0; i < ArrSize; i++)
	{
		if (i == 0)
		{
			m_sprites[i].setPosition(sf::Vector2f(0, m_SriteHolderRect.getPosition().y + i * 64));
			
		}
		else {
			//m_sprites[i].setScale(sf::Vector2f(0.64,0.64));
			m_sprites[i].setPosition(sf::Vector2f(0, m_SriteHolderRect.getPosition().y + i * 64 + m_offsetY * i));
		}
		m_towerCost[i].setPosition(sf::Vector2f(15, m_SriteHolderRect.getPosition().y + (i + 1) * 64 + m_offsetY * i));
	}

	m_ValuesHolderRect.setSize(sf::Vector2f(64 * 3, 64));
	m_ValuesHolderRect.setPosition(1920 - 3 * 64, 0);
	m_ValuesHolderRect.setFillColor(sf::Color(128, 128, 128));


	m_moneyText.setFont(font);
	m_moneyText.setString("Money\n" + std::to_string(money));
	m_moneyText.setCharacterSize(20);

	m_researchPointsText.setFont(font);
	m_researchPointsText.setString("RP\n" + std::to_string(researchPoints));
	m_researchPointsText.setCharacterSize(20);

	m_livesText.setFont(font);
	m_livesText.setString("Lives\n" + std::to_string(lives));
	m_livesText.setCharacterSize(20);

	m_moneyText.setPosition(m_ValuesHolderRect.getPosition() + sf::Vector2f(0 * 64, 0));
	m_researchPointsText.setPosition(m_ValuesHolderRect.getPosition() + sf::Vector2f(1 * 64, 0));
	m_livesText.setPosition(m_ValuesHolderRect.getPosition() + sf::Vector2f(2 * 64, 0));
}

void GUI::Draw(sf::RenderWindow& window)
{
	window.draw(m_SriteHolderRect);
	//window.draw(m_ValuesHolderRect);

	window.draw(m_moneyText);
	window.draw(m_researchPointsText);
	window.draw(m_livesText);

	for (int i = 0; i < ArrSize; i++)
	{
		window.draw(m_sprites[i]);
	}
	for (int i = 0; i < ArrSize; i++)
	{
		window.draw(m_towerCost[i]);
	}
}

void GUI::UpdateTextValues(int money, int researchPoints, int lives)
{
	m_moneyText.setString("Money\n" + std::to_string(money));
	m_researchPointsText.setString("RP\n" + std::to_string(researchPoints));
	m_livesText.setString("Lives\n" + std::to_string(lives));
}
