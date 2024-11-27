#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
enum TowerType {
	Research,
	Factory,
	Housing,
	BasicMillitaryTower,
	UpdatedMillitaryTower,
	ScatterMillitaryTower
};

struct StaticTowerProperties {
	int id;
	int cost;
	float radius;
	int baseValue;
	float actionCooldown;
	sf::Vector2i texturePosition;
};

class TowerPropertiesManager
{
public:
	static const std::unordered_map<TowerType, StaticTowerProperties> StaticProperties;

	static inline const StaticTowerProperties& GetStaticProperty(TowerType type) { return  StaticProperties.at(type); };
};

