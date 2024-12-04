#include "ResearchEffectHandler.h"
#include "Map.h"
void ResearchEffectHandler::IncreaseResearchCenterEfficiency(int value)
{
	Map::UpdateTowerValues(Research, value);
	return;
}

void ResearchEffectHandler::IncreaseFactoryProduction(float percentage)
{
	return;
}

void ResearchEffectHandler::IncreaseTowerDamage(float percentage)
{
	return;
}
