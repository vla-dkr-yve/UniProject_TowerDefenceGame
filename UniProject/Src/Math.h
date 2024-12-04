#pragma once
#include <SFML/Graphics.hpp>
class Math
{
public:
	static float Distance(sf::Vector2f target, sf::Vector2f position);
	static std::string EditString(std::string def, int characterSize, float width, sf::Font& font);
};

