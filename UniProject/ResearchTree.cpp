#include "ResearchTree.h"

#include <iostream>
#include "Math.h"
ResearchTree::ResearchTree()
{
	isActive = false; 

	font.loadFromFile("Assets/Fonts/Arial.TTF");


	const std::vector<ResearchTreeNode> vecNodes = ResearchTreeNodesConfiguration::CreateResearchTreeNodes();

	body = new sf::RectangleShape[vecNodes.size()];
	description = new sf::Text[vecNodes.size()];
	name = new sf::Text[vecNodes.size()];
	cost = new sf::Text[vecNodes.size()];
	purchaseBtn = new sf::RectangleShape[vecNodes.size()];
	purchaseBtnText = new sf::Text[vecNodes.size()];
	keys = new std::string[vecNodes.size()];
	int i = 0;
	int LevelY = 0;
	for (auto& node: vecNodes)
	{
		keys[i] = node.name;
		nodes[keys[i]] = node;

		body[i].setFillColor(sf::Color(0, 0, 0, 128));
		body[i].setSize(sf::Vector2f(150, 200));

		//purchaseBtn[i].setFillColor(sf::Color(30, 144, 255, 192));
		//purchaseBtn[i].setFillColor(sf::Color(128,128,128,128));
		//purchaseBtn[i].setFillColor(sf::Color(0,0,0, 192));
		body[i].setFillColor(sf::Color(0, 0, 0, 128));
		purchaseBtn[i].setOutlineThickness(1);
		purchaseBtn[i].setOutlineColor(sf::Color::Green);
		purchaseBtn[i].setSize(sf::Vector2f(70, 15));
		

		description[i].setFont(font);
		description[i].setCharacterSize(15);
		std::string desc = Math::EditString(node.description, description[i].getCharacterSize(), body[i].getSize().x - offsetX, font);
		description[i].setString(desc);

		name[i].setFont(font);
		name[i].setCharacterSize(15);
		desc = Math::EditString(node.name, name[i].getCharacterSize(), body[i].getSize().x, font);
		name[i].setString(desc);


		//Placing it here because I modify the researchName
		//nodes[desc] = node;

		cost[i].setFont(font);
		cost[i].setCharacterSize(15);
		desc = Math::EditString(std::to_string(node.researchPointCost), name[i].getCharacterSize(), body[i].getSize().x, font);
		cost[i].setString("Price:" + desc);

		purchaseBtnText[i].setFont(font);
		purchaseBtnText[i].setCharacterSize(15);
		purchaseBtnText[i].setString("Activate");
		purchaseBtnText[i].setFillColor(sf::Color::White);

		
		if (nodes[node.name].prerequisites.empty())
		{
			if (LevelY == 0)
			{
				LevelY += 64;
			}
			else{
				LevelY += 256;
			}
			body[i].setPosition(sf::Vector2f(200, LevelY));
		}
		else {
			body[i].setPosition(body[i-1].getPosition() + sf::Vector2f(400,0));
		}
		name[i].setPosition(body[i].getPosition() + sf::Vector2f(offsetX, offsetY));
		description[i].setPosition(body[i].getPosition() + sf::Vector2f(offsetX, offsetY * 10));
		cost[i].setPosition(body[i].getPosition() + sf::Vector2f(offsetX,body[i].getSize().y - offsetY - name[i].getCharacterSize() * 3));
		purchaseBtn[i].setPosition(cost[i].getPosition() + sf::Vector2f(cost[i].getGlobalBounds().width + 3, 0));
		purchaseBtnText[i].setPosition(purchaseBtn[i].getPosition() + sf::Vector2f( offsetX, -2 ) );
		i++;
	}
}

ResearchTree::~ResearchTree()
{
	delete[] body;
	delete[] description;
	delete[] name;
	delete[] cost;
	delete[] keys;
}

void ResearchTree::UnlokeNode(const std::string& nodeName)
{
	if (nodes[nodeName].IsUnlocked)
		return;

	for (const auto prereq: nodes[nodeName].prerequisites)
	{
		if (!nodes[prereq].IsUnlocked)
		{
			std::cout << "Conditions are not met";
			return;
		}
	}

	nodes[nodeName].IsUnlocked = true;
	nodes[nodeName].effect();
	std::cout << "Unlocked research: " << nodeName << '\n';
}

void ResearchTree::Update(sf::Vector2f& mousePosition)
{
	if (isActive)
	{
		for (int i = 0; i < nodes.size(); i++)
		{
			if (purchaseBtn[i].getGlobalBounds().contains(mousePosition))
			{
				purchaseBtn[i].setFillColor(sf::Color::Green);
				purchaseBtnText[i].setFillColor(sf::Color::Black);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					UnlokeNode(keys[i]);
				}
			}
			else {
				//purchaseBtn[i].setFillColor(sf::Color(30, 144, 255, 192));
				purchaseBtn[i].setFillColor(sf::Color(0, 0, 0, 128));
				purchaseBtnText[i].setFillColor(sf::Color::White);
			}
		}
	}
}

void ResearchTree::Draw(sf::RenderWindow& window)
{
	if (isActive)
	{
		for (int i = 0; i < nodes.size(); i++)
		{
			window.draw(body[i]);
			window.draw(name[i]);
			window.draw(description[i]);
			window.draw(cost[i]);
			window.draw(purchaseBtn[i]);
			window.draw(purchaseBtnText[i]);
		}
	}
}
