#pragma once
#include <SFML/Graphics.hpp>

class Tower
{
protected:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	sf::CircleShape m_ActionArea;

	float m_ftimer;
	float m_fActionCooldown;
	short int m_cost;
	bool m_bIsActionAreaActive;

	float m_fBuildTime;
	bool m_bIsBuild;
	sf::RectangleShape m_buildingLine;
public:

	Tower(int cost, float actionCooldown, sf::Vector2i& texturePosition, sf::Vector2f& position, float radius);
	//void Update(float deltaTime, std::vector <Enemy*>& vecEnemies);
	void Draw(sf::RenderWindow& window);

	inline sf::Sprite& GetSprite() { return m_sprite; };
	inline void SetActionAreaActive() { m_bIsActionAreaActive = true; };
	inline void SetActionAreaUnActive() { m_bIsActionAreaActive = false; };
	//virtual void Action(sf::Vector2f direction);
};

