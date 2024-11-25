#pragma once
#include<SFML/Graphics.hpp>

#define ArrSize 6
class GUI
{
	sf::RectangleShape m_SriteHolderRect;
	sf::Texture m_texture;
	sf::Sprite m_sprites[ArrSize];
	const int m_offset = 20;
public:

	GUI();
	void Draw(sf::RenderWindow& window);

	inline sf::IntRect GetTextureRect(int i) { return m_sprites[i].getTextureRect(); };
	inline bool IsOnTheGui(const sf::Vector2f& position) { return m_SriteHolderRect.getGlobalBounds().contains(position); };

	const int GetRectPositionY() { return m_SriteHolderRect.getPosition().y; };
};

