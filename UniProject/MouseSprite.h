#pragma once
#include <SFML/Graphics.hpp>
#include "GUI.h"
#include "Map.h"

class MouseSprite
{
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	int towerType;
	bool m_bIsActive;
public:
	MouseSprite();


	void Update(float deltaTime, GUI& gui, sf::Vector2f& mousePosition, Map& map, sf::Event event);
	void Draw(sf::RenderWindow& window);

	inline const bool IsActive() { return m_bIsActive; };
	inline const int GetTowerType() { return towerType; };
};

