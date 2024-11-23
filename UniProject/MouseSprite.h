#pragma once
#include <SFML/Graphics.hpp>
#include "GUI.h"
#include "Map.h"

class MouseSprite
{
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	int towerType;
	bool m_bIsMouseSpriteActive;
public:
	MouseSprite();


	void Update(float deltaTime, GUI& gui, sf::Vector2f& mousePosition, Map& map, sf::Event event, std::vector <MilitaryTower*> towers);
	void Draw(sf::RenderWindow& window);

	inline const bool IsActive() { return m_bIsMouseSpriteActive; };
	inline const int GetTowerType() { return towerType; };
};

