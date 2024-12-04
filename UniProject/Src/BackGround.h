#pragma once
#include <SFML/Graphics.hpp>
class BackGround
{
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	const std::string m_filePath = "Assets/Textures/Map/Map.png";
public:
	BackGround();
	void Draw(sf::RenderWindow& window);
};
