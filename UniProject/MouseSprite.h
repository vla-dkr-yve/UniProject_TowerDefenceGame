#pragma once
#include <SFML/Graphics.hpp>
#include "GUI.h"
#include "Map.h"

class MouseSprite
{
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::CircleShape m_ActionArea;
	int towerType;
	bool m_bIsMouseSpriteActive;
	bool m_bIsRadiusvisible;
	bool m_bIsShovelActive;

	sf::Font m_font;
	sf::Text m_towerDescription;
	sf::RectangleShape m_descriptionRect;
	bool m_bIsDescriptionVisible;
public:
	MouseSprite();


	void Update(float deltaTime, GUI& gui, sf::Vector2f& mousePosition,
		Map& map, sf::Event event, std::vector <MilitaryTower*> towers, std::vector <CivilTower*> civilTowers);
	void Draw(sf::RenderWindow& window);
	void SetTowerRadius(TowerType type);

	inline const bool IsActive() { return m_bIsMouseSpriteActive; };
	inline const bool IsShovelActive() { return m_bIsShovelActive; };
	inline const int GetTowerType() { return towerType; };
};

