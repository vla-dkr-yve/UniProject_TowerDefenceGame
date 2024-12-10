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
				switch (towerType)
				{
				case Research: {
					if (TowerPropertiesManager::GetStaticProperty(Research).cost <= player.GetMoney())
					{
						player.DecreaseMoney(TowerPropertiesManager::GetStaticProperty(Research).cost);

						WhichTowerType[i] = TowerPropertiesManager::GetTowerTypeChar(Research);

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
					if (TowerPropertiesManager::GetStaticProperty(Factory).cost <= player.GetMoney()) {

						player.DecreaseMoney(TowerPropertiesManager::GetStaticProperty(Factory).cost);

						WhichTowerType[i] = TowerPropertiesManager::GetTowerTypeChar(Factory);

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
					if (TowerPropertiesManager::GetStaticProperty(Housing).cost <= player.GetMoney()) {

						player.DecreaseMoney(TowerPropertiesManager::GetStaticProperty(Housing).cost);

						WhichTowerType[i] = TowerPropertiesManager::GetTowerTypeChar(Housing);

						HouseTower* HT = new HouseTower(sf::Vector2f(X * 64, Y * 64), m_civilTowers);
						//HT->ApplyBuffs(m_civilTowers);
						m_civilTowers.push_back(HT);
						IsPlaceTaken[i] = true;
						break;
					}
				}
				case BasicMillitaryTower: {
					if (TowerPropertiesManager::GetStaticProperty(BasicMillitaryTower).cost <= player.GetMoney()) {

						player.DecreaseMoney(TowerPropertiesManager::GetStaticProperty(BasicMillitaryTower).cost);

						WhichTowerType[i] = TowerPropertiesManager::GetTowerTypeChar(BasicMillitaryTower);

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
					if (TowerPropertiesManager::GetStaticProperty(UpdatedMillitaryTower).cost <= player.GetMoney()) {

						player.DecreaseMoney(TowerPropertiesManager::GetStaticProperty(UpdatedMillitaryTower).cost);

						WhichTowerType[i] = TowerPropertiesManager::GetTowerTypeChar(UpdatedMillitaryTower);

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
					if (TowerPropertiesManager::GetStaticProperty(ScatterMillitaryTower).cost <= player.GetMoney()) {

						player.DecreaseMoney(TowerPropertiesManager::GetStaticProperty(ScatterMillitaryTower).cost);

						WhichTowerType[i] = TowerPropertiesManager::GetTowerTypeChar(ScatterMillitaryTower);

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
