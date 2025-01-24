#include "ResearchEffectHandler.h"
#include "Map.h"
void ResearchEffectHandler::IncreaseResearchCenterEfficiency(int value)
{
	Map::UpdateTowerValues(Research, value);
	return;
}

void ResearchEffectHandler::IncreaseFactoryProduction(int value)
{
	Map::UpdateTowerValues(Factory, value);
	return;
}

void ResearchEffectHandler::IncreaseTowerDamage(int value)
{
	Map::UpdateTowerValues(BasicMillitaryTower, value);
	Map::UpdateTowerValues(UpdatedMillitaryTower, value);
	Map::UpdateTowerValues(ScatterMillitaryTower, value);
	return;
}
