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
	std::map<int, int> m_animationOffset;

	sf::RectangleShape m_hitbox;
	int m_hitboxWidth;
	const int m_hitboxHeight = 22;

	bool m_shoodBeDestroyed;
public:
	Lightning(sf::Vector2f position, float rotation);

	void Animator(float deltaTime);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	inline bool ShouldBeDestroyed() { return m_shoodBeDestroyed; };
	inline sf::RectangleShape& GetHitBox() { return m_hitbox; };
	inline sf::Vector2f GetHitBoxSize() { return m_sprite.getGlobalBounds().getSize(); };
	inline sf::Vector2f GetHitBoxPosition() { return m_sprite.getGlobalBounds().getPosition(); };
};