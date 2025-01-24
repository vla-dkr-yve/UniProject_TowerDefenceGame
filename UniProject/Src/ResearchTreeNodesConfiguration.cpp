#include "ResearchTreeNodesConfiguration.h"
#include "ResearchEffectHandler.h"

std::vector<ResearchTreeNode> ResearchTreeNodesConfiguration::CreateResearchTreeNodes()
{
	// name, description, cost, prerequisites(vector of string), function(effect) 
	return {

		{"Research Center Efficiency I", "Increases amount of research points center generates by 1", 150, {}, 
		[] {ResearchEffectHandler::IncreaseResearchCenterEfficiency(1);
		}},
		{"Research Center Efficiency II", "Increases amount of research points center generates by 2", 200, {"Research Center Efficiency I"},
		[] {ResearchEffectHandler::IncreaseResearchCenterEfficiency(2);
		}},

		{"Factory Efficiency I", "Increases amount of money factory generates by 5", 150, {}, 
		[] {ResearchEffectHandler::IncreaseFactoryProduction(5);
		}},
		{"Factory Efficiency II", "Increases amount of money factory generates by 5", 150, {"Factory Efficiency I"},
		[] {ResearchEffectHandler::IncreaseFactoryProduction(5);
		}},

		{"Damage Upgrade I", "Increases military tower damage by 10", 150, {}, 
		[] {ResearchEffectHandler::IncreaseTowerDamage(10);
		}},
		{"Damage Upgrade II", "Increases military tower damage by 10", 175, {"Damage Upgrade I"},
		[] {ResearchEffectHandler::IncreaseTowerDamage(10);
		}},
		{"Damage Upgrade III", "Increases military tower damage by 10", 200, {"Damage Upgrade II"},
		[] {ResearchEffectHandler::IncreaseTowerDamage(10);
		}},
		{"Damage Upgrade IV", "Increases military tower damage by 10", 225, {"Damage Upgrade III"},
		[] {ResearchEffectHandler::IncreaseTowerDamage(10);
		}},
	};
}
