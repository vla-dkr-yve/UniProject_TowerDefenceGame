#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "ResearchTreeNodesConfiguration.h"

class ResearchTree
{
	std::map<std::string, ResearchTreeNode> nodes;

	sf::Font font;
	
	sf::RectangleShape* body;
	sf::Text* description;
	sf::Text* name;
	sf::Text* cost;
	sf::RectangleShape* purchaseBtn;
	sf::Text* purchaseBtnText;

	std::string* keys;
	
	const float offsetX = 5.0f;
	const float offsetY = 5.0f;


	bool isActive;
public:
	ResearchTree();
	~ResearchTree();

	void UnlokeNode(const std::string& nodeName);
	void Update(sf::Vector2f& mousePosition);

	void Draw(sf::RenderWindow& window);

	inline void ChangeViewState() { isActive = !isActive; };
	inline bool IsResearchTreeActive() { return isActive; };
};

