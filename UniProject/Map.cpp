#include "Map.h"
#include <iostream>
Map::Map()
{
	for (int i = 0; i < TowerAmount; i++)
	{
		IsPlaceTaken[i] = false;
	}
	m_towerAmount = 0;
}

void Map::AddTower(int towerType, sf::Vector2f position, int X, int Y)
{
	for (int i = 0; i < TowerAmount; i++)
	{
		if (arr[i][0] == X && arr[i][1] == Y)
		{
			if (!IsPlaceTaken[i])
			{
				switch (towerType)
				{
				case BasicTower:
					towers.push_back(new LaserTower(sf::Vector2f(X * 64, Y * 64)));
					IsPlaceTaken[i] = true;
					break;
				case UpdatedBasic:
					towers.push_back(new UdvancedLaserTower(sf::Vector2f(X * 64, Y * 64)));
					IsPlaceTaken[i] = true;
					break;
				case Scatter:
					towers.push_back(new ScatterLaserTower(sf::Vector2f(X * 64, Y * 64)));
					IsPlaceTaken[i] = true;
					break;
				default:
					break;
				}
				break;
			}
		}
	}
	std::cout << towers.size() << std::endl;
}

bool Map::IsOnThePlace(int x, int y)
{
	for (int i = 0; i < TowerAmount; i++)
	{
		if (arr[i][0] == x && arr[i][1] == y)
		{
			if (arr[i][0] > x)
			{
				return false;
			}
			return true;
		}
	}
	return false;
}

void Map::Update(float deltaTime, std::vector <Enemy*> m_vecEnemies)
{
	for (int i = 0; i < towers.size(); i++)
	{
		towers[i]->Update(deltaTime, m_vecEnemies);
	}

}

void Map::Draw(sf::RenderWindow& window)
{
	backGround.Draw(window);
	for (int i = 0; i < towers.size(); i++)
	{
		towers[i]->Draw(window);
	}
	for (int i = 0; i < towers.size(); i++)
	{
		std::vector<Laser*> lasers = towers[i]->GetLaserVector();
		for (int i = 0; i < lasers.size(); i++)
		{
			lasers[i]->Draw(window);
		}
	}
}
