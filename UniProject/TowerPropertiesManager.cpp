#include "TowerPropertiesManager.h"

const std::unordered_map<TowerType, StaticTowerProperties> TowerPropertiesManager::StaticProperties = {

	//id, cost, radius, baseValue ,cooldown, textRect
	{TowerType::Research, { 0 , 150 , 150 , 1 ,3.0f , sf::Vector2i(100 * 0, 100 * 0) } },

	{TowerType::Factory, { 1 , 150 , 150 , 10 , 3.0f , sf::Vector2i(100 * 3, 100 * 0)} },

	{TowerType::Housing, { 2 , 200 , 150 , 1 , 60.0f , sf::Vector2i(100 * 0, 100 * 1) } },

	{TowerType::BasicMillitaryTower, { 3 , 100 , 150 , 50 , 1.5f , sf::Vector2i(100 * 2, 100 * 1) } },

	{TowerType::UpdatedMillitaryTower, { 4 , 200 , 125 , 100 , 1.0f , sf::Vector2i(100 * 3, 100 * 1) } },

	{TowerType::ScatterMillitaryTower, { 5 , 500 , 125 , 75 , 2.0f , sf::Vector2i(100 * 0, 100 * 2) } },
};
