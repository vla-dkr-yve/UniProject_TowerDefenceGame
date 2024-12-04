#include "TowerPropertiesManager.h"

std::unordered_map<TowerType, StaticTowerProperties> TowerPropertiesManager::StaticProperties = {

	//id, cost, radius, baseValue ,cooldown, textRect, description
	{TowerType::Research, { 0 , 150 , 150 , 1 ,3.0f , sf::Vector2i(100 * 0, 100 * 0) , "Research center. \nGenerates 1 research point each 3 seconds. \nBuffs nearby military towers' damage by 25"}},

	{TowerType::Factory, { 1 , 150 , 0 , 10 , 3.0f , sf::Vector2i(100 * 3, 100 * 0), "Factory. \nProduces 25 money each 3 seconds."} },

	{TowerType::Housing, { 2 , 200 , 150 , 1 , 60.0f , sf::Vector2i(100 * 0, 100 * 1) , "Housing. \nGenerates 1 live point each 60 seconds. \nBuffs nearby research and  factory towers' production"} },

	{TowerType::BasicMillitaryTower, { 3 , 100 , 150 , 25 , 1.5f , sf::Vector2i(100 * 2, 100 * 1), "Laser tower. \nDeal 50 damage\nHas 1,5 second cooldown"}},

	{TowerType::UpdatedMillitaryTower, { 4 , 200 , 125 , 100 , 1.0f , sf::Vector2i(100 * 3, 100 * 1) ,"Advanced laser tower. \nDeal 125 damage\nHas 1 second cooldown"} },

	{TowerType::ScatterMillitaryTower, { 5 , 500 , 125 , 75 , 2.0f , sf::Vector2i(100 * 0, 100 * 2) ,"Scatter laser tower. \nShoots 5 lasers per time\nDeal 75 damage and has 2 second cooldown"} },
};

void TowerPropertiesManager::IncreaseTowerBaseValue(TowerType type, int value)
{
	StaticProperties[type].baseValue += value;
}

char TowerPropertiesManager::getTowerTypeChar(TowerType type)
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
