#pragma once
#include <SFML/Graphics.hpp>
#include <map>
class Lightning
{
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	int m_currentAnimation;
	float m_animationTimer;

	std::map<int, int> m_animationWidth;

	sf::RectangleShape hitbox;
	int m_hitboxWidth;
	const int m_hitboxHeight = 22;
public:
	Lightning(sf::Vector2f position);

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
};