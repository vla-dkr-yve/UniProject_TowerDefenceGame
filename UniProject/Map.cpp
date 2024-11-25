#include "Map.h"
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
				case CivilResearchCenter:
					m_civilTowers.push_back(new ResearchCenter(sf::Vector2f(X * 64, Y * 64)));
					IsPlaceTaken[i] = true;
					break;
				case CivilFactoryTower:
					m_civilTowers.push_back(new FactoryTower(sf::Vector2f(X * 64, Y * 64)));
					IsPlaceTaken[i] = true;
					break;
				case CivilHouseTower:
					m_civilTowers.push_back(new HouseTower(sf::Vector2f(X * 64, Y * 64)));
					IsPlaceTaken[i] = true;
					break;
				case BasicMillitaryTower:
					m_militaryTowers.push_back(new LaserTower(sf::Vector2f(X * 64, Y * 64)));
					IsPlaceTaken[i] = true;
					break;
				case UpdatedMillitaryTower:
					m_militaryTowers.push_back(new UdvancedLaserTower(sf::Vector2f(X * 64, Y * 64)));
					IsPlaceTaken[i] = true;
					break;
				case ScatterMillitaryTower:
					m_militaryTowers.push_back(new ScatterLaserTower(sf::Vector2f(X * 64, Y * 64)));
					IsPlaceTaken[i] = true;
					break;
				default:
					break;
				}
				break;
			}
		}
	}
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
	for (int i = 0; i < m_militaryTowers.size(); i++)
	{
		m_militaryTowers[i]->Update(deltaTime, m_vecEnemies);
	}

}

void Map::Draw(sf::RenderWindow& window)
{
	backGround.Draw(window);
	for (int i = 0; i < m_militaryTowers.size(); i++)
	{
		m_militaryTowers[i]->Draw(window);
	}
	for (int i = 0; i < m_civilTowers.size(); i++)
	{
		m_civilTowers[i]->Draw(window);
	}
	for (int i = 0; i < m_militaryTowers.size(); i++)
	{
		std::vector<Laser*> lasers = m_militaryTowers[i]->GetLaserVector();
		for (int i = 0; i < lasers.size(); i++)
		{
			lasers[i]->Draw(window);
		}
	}
}
