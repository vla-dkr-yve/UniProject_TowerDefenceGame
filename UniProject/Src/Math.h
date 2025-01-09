#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
class Math
{
public:
	static float Distance(sf::Vector2f target, sf::Vector2f position);
	static std::string EditString(std::string def, int characterSize, float width, sf::Font& font);
	static bool Collision(Enemy& enemy, sf::Vector2f position);
};

