#pragma once
#include<SFML/Graphics.hpp>

#define ArrSize 7
class GUI
{
	sf::Font font;

	sf::RectangleShape m_SriteHolderRect;
	sf::Texture m_texture;
	sf::Sprite m_GUISprites[ArrSize];
	sf::Text m_towerCost[ArrSize];
	const int m_offsetY = 20;

	sf::RectangleShape m_ValuesHolderRect;
	sf::Text m_moneyText;
	sf::Text m_researchPointsText;
	sf::Text m_livesText;
	
	sf::RectangleShape m_ScoreHolder;
	sf::Text m_scoreText;

	sf::Texture m_shovelTexture;

public:

	GUI(int money, int researchPoints, int lives, int score);
	void Draw(sf::RenderWindow& window);
	void UpdateTextValues(int money, int researchPoints, int lives, int score);

	sf::Texture& GetTexture(int i);
	const inline sf::Vector2f& GetScale(int i) const { return m_GUISprites[i].getScale(); };
	inline sf::IntRect GetTextureRect(int i) { return m_GUISprites[i].getTextureRect(); };
	inline bool IsOnTheGui(const sf::Vector2f& position) { return m_SriteHolderRect.getGlobalBounds().contains(position); };

	const int GetRectPositionY() { return m_SriteHolderRect.getPosition().y; };
	const int GetArrSize() const { return ArrSize; };
};