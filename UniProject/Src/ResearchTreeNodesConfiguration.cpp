#include "ResearchTreeNodesConfiguration.h"
#include "ResearchEffectHandler.h"

std::vector<ResearchTreeNode> ResearchTreeNodesConfiguration::CreateResearchTreeNodes()
{
	// name, description, cost, prerequisites(vector of string), function(effect) 
	return {

		{"Research Center Efficiency I", "Increases amount of research points center generates by 1", 150, {}, 
		[] {ResearchEffectHandler::IncreaseResearchCenterEfficiency(1);
		}},

		{"Factory Efficiency I", "Increases amount of money factory generates by 10%", 150, {"Research Center Efficiency I"}, 
		[] {ResearchEffectHandler::IncreaseFactoryProduction(0.1);
		}},

		{"Damage Upgrade I", "Increases military tower damage by 10%", 200, {}, 
		[] {ResearchEffectHandler::IncreaseTowerDamage(0.1);
		}}
	};
}
