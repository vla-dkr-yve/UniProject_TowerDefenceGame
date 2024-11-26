#include "Map.h"
Map::Map()
{
	for (int i = 0; i < TowerAmount; i++)
	{
		IsPlaceTaken[i] = false;
	}
	m_towerAmount = 0;
}

void Map::AddTower(int towerType, sf::Vector2f position, int X, int Y, Player& player)
{
	for (int i = 0; i < TowerAmount; i++)
	{
		if (arr[i][0] == X && arr[i][1] == Y)
		{
			if (!IsPlaceTaken[i])
			{
				switch (towerType)
				{
				case Research: {
					if (ResearchCenter::GetCost() <= player.GetMoney())
					{
						player.DecreaseMoney(ResearchCenter::GetCost());

						ResearchCenter* RC = new ResearchCenter(sf::Vector2f(X * 64, Y * 64), m_militaryTowers);
						//RC->ApplyBuffs(m_militaryTowers);
						m_civilTowers.push_back(RC);
						for (int i = 0; i < m_civilTowers.size(); i++)
						{
							m_civilTowers[i]->ReapplyBuffs(RC);
						}
						IsPlaceTaken[i] = true;
						break;
					}
				}
				case Factory: {
					if (FactoryTower::GetCost() <= player.GetMoney()) {

						player.DecreaseMoney(FactoryTower::GetCost());

						FactoryTower* FT = new FactoryTower(sf::Vector2f(X * 64, Y * 64));
						//FT->ApplyBuffs(m_towers);
						m_civilTowers.push_back(FT);
						for (int i = 0; i < m_civilTowers.size(); i++)
						{
							m_civilTowers[i]->ReapplyBuffs(FT);
						}
						IsPlaceTaken[i] = true;
						break;
					}
				}
				case Housing: {
					if (HouseTower::GetCost() <= player.GetMoney()) {

						player.DecreaseMoney(HouseTower::GetCost());

						HouseTower* HT = new HouseTower(sf::Vector2f(X * 64, Y * 64), m_civilTowers);
						//HT->ApplyBuffs(m_civilTowers);
						m_civilTowers.push_back(HT);
						IsPlaceTaken[i] = true;
						break;
					}
				}
				case BasicMillitaryTower: {
					if (LaserTower::GetCost() <= player.GetMoney()) {

						player.DecreaseMoney(LaserTower::GetCost());

						m_militaryTowers.push_back(new LaserTower(sf::Vector2f(X * 64, Y * 64)));
						IsPlaceTaken[i] = true;
						for (int i = 0; i < m_civilTowers.size(); i++)
						{
							m_civilTowers[i]->ReapplyBuffs(m_militaryTowers[m_militaryTowers.size() - 1]);
						}
						break;
					}
				}
				case UpdatedMillitaryTower: {
					if (UdvancedLaserTower::GetCost() <= player.GetMoney()) {

						player.DecreaseMoney(UdvancedLaserTower::GetCost());

						m_militaryTowers.push_back(new UdvancedLaserTower(sf::Vector2f(X * 64, Y * 64)));
						IsPlaceTaken[i] = true;
						for (int i = 0; i < m_civilTowers.size(); i++)
						{
							m_civilTowers[i]->ReapplyBuffs(m_militaryTowers[m_militaryTowers.size() - 1]);
						}
						break;
					}
				}
				case ScatterMillitaryTower: {
					if (ScatterLaserTower::GetCost() <= player.GetMoney()) {

						player.DecreaseMoney(ScatterLaserTower::GetCost());

						m_militaryTowers.push_back(new ScatterLaserTower(sf::Vector2f(X * 64, Y * 64)));
						IsPlaceTaken[i] = true;
						for (int i = 0; i < m_civilTowers.size(); i++)
						{
							m_civilTowers[i]->ReapplyBuffs(m_militaryTowers[m_militaryTowers.size() - 1]);
						}
						break;
					}
				}
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

void Map::Update(float deltaTime,std::vector <Enemy*> m_vecEnemies, Player& player)
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
