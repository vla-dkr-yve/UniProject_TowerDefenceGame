#pragma once
#include <string>
#include <vector>
#include <functional>

struct ResearchTreeNode {
	std::string name;
	std::string description;

	int researchPointCost;

	std::vector<std::string> prerequisites;
	std::function<void()> effect;

	bool IsUnlocked = false;
};

class ResearchTreeNodesConfiguration
{
	
public:
	static std::vector<ResearchTreeNode> CreateResearchTreeNodes();
};

