#include "TowerPropertiesManager.h"

std::unordered_map<TowerType, StaticTowerProperties> TowerPropertiesManager::StaticProperties = {

	//id, cost, radius, baseValue ,cooldown, textRect, description
	{TowerType::Research, { 0 , 150 , 150 , 1 ,3.0f , sf::Vector2i(100 * 0, 100 * 0) , "Research center. Generates 1 research point each 3 seconds. Buffs nearby military towers' damage by 25"}},

	{TowerType::Factory, { 1 , 150 , 0 , 10 , 3.0f , sf::Vector2i(100 * 3, 100 * 0), "Factory. Produces 10 money each 3 seconds."} },

	{TowerType::Housing, { 2 , 200 , 150 , 1 , 60.0f , sf::Vector2i(100 * 0, 100 * 1) , "Housing. Generates 1 live point each 60 seconds. Buffs nearby research and  factory towers' production"} },

	{TowerType::BasicMillitaryTower, { 3 , 100 , 125 , 25 , 1.5f , sf::Vector2i(100 * 2, 100 * 1), "Laser tower. Deal 25 damage. Has 1,5 second cooldown"}},

	{TowerType::UpdatedMillitaryTower, { 4 , 200 , 150 , 50 , 1.25f , sf::Vector2i(100 * 3, 100 * 1) ,"Advanced laser tower. Deal 50 damage. Has 1,25 second cooldown"} },

	{TowerType::ScatterMillitaryTower, { 5 , 400 , 150 , 75 , 1.0f , sf::Vector2i(100 * 0, 100 * 2) ,"Scatter laser tower. Deal 75 damage and has 1 second cooldown"} },
};

void TowerPropertiesManager::IncreaseTowerBaseValue(TowerType type, int value)
{
	StaticProperties[type].baseValue += value;
}

char TowerPropertiesManager::GetTowerTypeChar(TowerType type)
{
	switch (type) {
	case Research:
	case Factory:
	case Housing:
		return 'c'; 
	case BasicMillitaryTower:
	case UpdatedMillitaryTower:
	case ScatterMillitaryTower:
		return 'm'; 
	default:
		return '\0';
	}
}
