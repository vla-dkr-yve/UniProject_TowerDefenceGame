#pragma once
#include <SFML/Graphics.hpp>
#include "TowerPropertiesManager.h"
#include "Buff.h"

class Tower
{
protected:
	int m_id;
	int m_cost;
	float m_fRadius;

	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	sf::CircleShape m_ActionArea;

	TowerType towerType;

	float m_ftimer;
	float m_fActionCooldown;
	bool m_bIsActionAreaActive;

	float m_fBuildTime;
	float m_fCurrentTime;
	bool m_bIsBuild;
	sf::RectangleShape m_buildingLine;
	sf::RectangleShape m_buildingBackground;

	std::vector<Buff> m_activeBuffs;
	int m_baseValue;
	int m_currentValue;
public:

	Tower(TowerType type, sf::Vector2f& position);
	void Build(float deltaTime);
	virtual void Draw(sf::RenderWindow& window);

	//For Buffs
	void AddBuff(Buff buff);
	void RemoveBuffBySource(void* source);
	void UpdateValue();

	//For Research Tree
	void UpdateBaseValue(int value);

	inline sf::Sprite& GetSprite() { return m_sprite; };
	inline void SetActionAreaActive() { m_bIsActionAreaActive = true; };
	inline void SetActionAreaUnActive() { m_bIsActionAreaActive = false; };
	inline bool IsBuilding() { return m_bIsBuild; };

	inline int GetId() { return m_id; };
	inline TowerType& GetTowerType() { return towerType; };
};

