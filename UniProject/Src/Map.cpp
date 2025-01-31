#include "Map.h"

std::vector <MilitaryTower*> Map::m_militaryTowers;
std::vector <CivilTower*> Map::m_civilTowers;
Map::Map()
{
	for (int i = 0; i < TowerAmount; i++)
	{
		IsPlaceTaken[i] = false;
	}
}

void Map::AddTower(int towerType, int X, int Y, Player& player)
{
	for (int i = 0; i < TowerAmount; i++)
	{
		if (arr[i][0] == X && arr[i][1] == Y)
		{
			if (!IsPlaceTaken[i])
			{
				int cost = TowerPropertiesManager::GetStaticProperty(static_cast<TowerType>(towerType)).cost;
				if (cost > player.GetMoney()) {
					return;
				} 

				player.DecreaseMoney(cost);
				WhichTowerType[i] = TowerPropertiesManager::GetTowerTypeChar(static_cast<TowerType>(towerType));
				IsPlaceTaken[i] = true;

				sf::Vector2f position(X * 64, Y * 64);

				switch (towerType)
				{
				case Research: {
					ResearchCenter* RC = new ResearchCenter(position, m_militaryTowers);
					m_civilTowers.push_back(RC);
					for (int i = 0; i < m_civilTowers.size(); i++)
					{
						m_civilTowers[i]->ReapplyBuffs(RC);
					}
					break;
				}
				case Factory: {
					FactoryTower* FT = new FactoryTower(position);
					m_civilTowers.push_back(FT);
					for (int i = 0; i < m_civilTowers.size(); i++)
					{
						m_civilTowers[i]->ReapplyBuffs(FT);
					}
					break;
				}
				case Housing: {
					player.DecreaseMoney(TowerPropertiesManager::GetStaticProperty(Housing).cost);

					HouseTower* HT = new HouseTower(position, m_civilTowers);
					m_civilTowers.push_back(HT);
					break;
				}
				case BasicMillitaryTower: {

						m_militaryTowers.push_back(new LaserTower(position));
						for (int i = 0; i < m_civilTowers.size(); i++)
						{
							m_civilTowers[i]->ReapplyBuffs(m_militaryTowers[m_militaryTowers.size() - 1]);
						}
						break;
				}
				case UpdatedMillitaryTower: {

						m_militaryTowers.push_back(new UdvancedLaserTower(position));
						for (int i = 0; i < m_civilTowers.size(); i++)
						{
							m_civilTowers[i]->ReapplyBuffs(m_militaryTowers[m_militaryTowers.size() - 1]);
						}
						break;
				}
				case ScatterMillitaryTower: {

						m_militaryTowers.push_back(new ScatterLaserTower(position));
						for (int i = 0; i < m_civilTowers.size(); i++)
						{
							m_civilTowers[i]->ReapplyBuffs(m_militaryTowers[m_militaryTowers.size() - 1]);
						}
						break;
				}
				default:
					break;
				}
				break;
			}
		}
	}
}

void Map::DeleteTower(int X, int Y)
{
	for (int i = 0; i < TowerAmount; i++)
	{
		if (arr[i][0] == X && arr[i][1] == Y && IsPlaceTaken[i])
		{
			if (WhichTowerType[i] == 'c')
			{
				auto it = std::find_if(m_civilTowers.begin(), m_civilTowers.end(), [X, Y](CivilTower* tower)
					{return sf::Vector2f(tower->GetSprite().getPosition().x / 64, tower->GetSprite().getPosition().y / 64) == sf::Vector2f(X, Y); });

				if (it != m_civilTowers.end())
				{
					delete* it;
					m_civilTowers.erase(it);
				}
			}
			else if (WhichTowerType[i] == 'm')
			{
				auto it = std::find_if(m_militaryTowers.begin(), m_militaryTowers.end(), [X, Y](MilitaryTower* tower)
					{return sf::Vector2f(tower->GetSprite().getPosition().x / 64, tower->GetSprite().getPosition().y / 64) == sf::Vector2f(X, Y); });

				if (it != m_militaryTowers.end())
				{
					delete* it;
					m_militaryTowers.erase(it);
				}
			}
			IsPlaceTaken[i] = false;
			WhichTowerType[i] = '\0';
			return;
		}
	}
}

void Map::UpdateTowerValues(TowerType type, int value)
{
	char typeChar = TowerPropertiesManager::GetTowerTypeChar(type);

	if (typeChar == 'c')
	{
		for (auto tower: m_civilTowers)
		{
			if (tower->GetTowerType() == type)
			{
				tower->UpdateBaseValue(value);
			}
		}
	}
	else if (typeChar == 'm')
	{
		for (auto tower : m_militaryTowers)
		{
			if (tower->GetTowerType() == type)
			{
				tower->UpdateBaseValue(value);
			}
		}
	}
	TowerPropertiesManager::IncreaseTowerBaseValue(type, value);
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

void Map::Update(float deltaTime,std::vector <Enemy*>& m_vecEnemies, Player& player)
{
	for (int i = 0; i < m_militaryTowers.size(); i++)
	{
		m_militaryTowers[i]->Update(deltaTime, m_vecEnemies);
	}
	for (int i = 0; i < m_civilTowers.size(); i++)
	{
		m_civilTowers[i]->Update(deltaTime, player);
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
}