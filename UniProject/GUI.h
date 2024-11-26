#pragma once
#include<SFML/Graphics.hpp>

#define ArrSize 6
class GUI
{
	sf::Font font;

	sf::RectangleShape m_SriteHolderRect;
	sf::Texture m_texture;
	sf::Sprite m_sprites[ArrSize];
	sf::Text m_towerCost[ArrSize];
	const int m_offsetY = 20;

	sf::RectangleShape m_ValuesHolderRect;
	sf::Text m_moneyText;
	sf::Text m_researchPointsText;
	sf::Text m_livesText;
public:

	GUI(int money, int researchPoints, int lives);
	void Draw(sf::RenderWindow& window);
	void UpdateTextValues(int money, int researchPoints, int lives);

	sf::IntRect GetTextureRect(int i) { return m_sprites[i].getTextureRect(); };
	inline bool IsOnTheGui(const sf::Vector2f& position) { return m_SriteHolderRect.getGlobalBounds().contains(position); };

	const int GetRectPositionY() { return m_SriteHolderRect.getPosition().y; };
	const int GetArrSize() const { return ArrSize; };
};

