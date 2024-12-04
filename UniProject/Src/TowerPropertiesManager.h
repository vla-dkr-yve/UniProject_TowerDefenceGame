#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
enum TowerType {
	Research,
	Factory,
	Housing,
	BasicMillitaryTower,
	UpdatedMillitaryTower,
	ScatterMillitaryTower,
	//TowerTypeCount = 6
};

struct StaticTowerProperties {
	int id;
	int cost;
	float radius;
	int baseValue;
	float actionCooldown;
	sf::Vector2i texturePosition;
	std::string description;
};

class TowerPropertiesManager
{
public:
	static char getTowerTypeChar(TowerType type);
	static std::unordered_map<TowerType, StaticTowerProperties> StaticProperties;

	static void IncreaseTowerBaseValue(TowerType type, int value);

	static inline const StaticTowerProperties& GetStaticProperty(TowerType type) { return  StaticProperties.at(type); };
};

