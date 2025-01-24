#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
class Math
{
private:
	static float dotProduct(const sf::Vector2f& rect1, const sf::Vector2f& rect2);
public:
	static float Distance(sf::Vector2f target, sf::Vector2f position);
	static std::string EditString(std::string def, int characterSize, float width, sf::Font& font);
	static bool EnemyCollision(Enemy& enemy, sf::Vector2f position);
	static bool Collision(sf::FloatRect rect1, sf::FloatRect rect2);
	static bool OBBCollision(const sf::RectangleShape& rect1, const sf::RectangleShape& rect2);
	static sf::Vector2f normalize(const sf::Vector2f& vector);
};

