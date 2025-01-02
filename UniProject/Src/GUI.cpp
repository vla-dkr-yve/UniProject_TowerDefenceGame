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
GUI::GUI(int money, int researchPoints, int lives, int score)
{
	font.loadFromFile("Assets/Fonts/Arial.TTF");
	for (int i = 0; i < ArrSize - 1; i++)
	{
		m_towerCost[i].setFont(font);
		m_towerCost[i].setCharacterSize(20);
	}
	m_SriteHolderRect.setSize(sf::Vector2f(64, 64 * (ArrSize - 1) + m_offsetY * (ArrSize - 1) + 64));
	m_SriteHolderRect.setPosition(0, 1024 / 2 - m_SriteHolderRect.getSize().y / 2);
	m_SriteHolderRect.setFillColor(sf::Color(128,128,128));
	
	m_texture.loadFromFile("Assets/Textures/Towers/Towers-100px.png");
	for (int i = 0; i < ArrSize - 1; i++)
	{
		m_GUISprites[i].setTexture(m_texture);
		m_GUISprites[i].setScale(sf::Vector2f(0.64, 0.64));
	}
	for (int i = 0; i < ArrSize - 1; i++)
	{
		m_GUISprites[i].setTextureRect(sf::IntRect(
			TowerPropertiesManager::GetStaticProperty(static_cast<TowerType>(i)).texturePosition.x, 
			TowerPropertiesManager::GetStaticProperty(static_cast<TowerType>(i)).texturePosition.y, 100, 100));
		m_towerCost[i].setString(std::to_string(TowerPropertiesManager::GetStaticProperty(static_cast<TowerType>(i)).cost));
	}

	for (int i = 0; i < ArrSize - 1; i++)
	{
		if (i == 0)
		{
			m_GUISprites[i].setPosition(sf::Vector2f(0, m_SriteHolderRect.getPosition().y + i * 64));
			
		}
		else {
			m_GUISprites[i].setPosition(sf::Vector2f(0, m_SriteHolderRect.getPosition().y + i * 64 + m_offsetY * i));
		}
		m_towerCost[i].setPosition(sf::Vector2f(15, m_SriteHolderRect.getPosition().y + (i + 1) * 64 + m_offsetY * i));
	}

	m_ValuesHolderRect.setSize(sf::Vector2f(64 * 3, 64));
	m_ValuesHolderRect.setPosition(1920 - 3 * 64, 0);
	m_ValuesHolderRect.setFillColor(sf::Color(128, 128, 128));

	m_ScoreHolder.setSize(sf::Vector2f(64 * 3, 64));
	m_ScoreHolder.setPosition(1920 - 3 * 64, 64 * 1);
	m_ScoreHolder.setFillColor(sf::Color(128, 128, 128));;

	m_shovelTexture.loadFromFile("Assets/Textures/Shovel/Shovel.png");
	m_GUISprites[ArrSize - 1].setTexture(m_shovelTexture);
	m_GUISprites[ArrSize - 1].setScale(sf::Vector2f(2, 2));
	m_GUISprites[ArrSize - 1].setPosition(m_SriteHolderRect.getPosition() + sf::Vector2f(0,m_SriteHolderRect.getSize().y) - sf::Vector2f(0, 64));

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

	m_scoreText.setFont(font);
	m_scoreText.setString("Score: " + std::to_string(score));
	m_scoreText.setPosition(m_ScoreHolder.getPosition());
}

void GUI::Draw(sf::RenderWindow& window)
{

	window.draw(m_moneyText);
	window.draw(m_researchPointsText);
	window.draw(m_livesText);
	window.draw(m_scoreText);

	for (int i = 0; i < ArrSize; i++)
	{
		window.draw(m_GUISprites[i]);
	}
	for (int i = 0; i < ArrSize; i++)
	{
		window.draw(m_towerCost[i]);
	}
}

void GUI::UpdateTextValues(int money, int researchPoints, int lives, int score)
{
	m_moneyText.setString("Money\n" + std::to_string(money));
	m_researchPointsText.setString("RP\n" + std::to_string(researchPoints));
	m_livesText.setString("Lives\n" + std::to_string(lives));
	m_scoreText.setString("Score: " + std::to_string(score));
}

sf::Texture& GUI::GetTexture(int i)
{
	if (i >= 0 && i < 6)
	{
		return m_texture;
	}
	else {
		return m_shovelTexture;
	}
}
