#pragma once
#include <vector>
#include "BackGround.h"
#include "Enemy.h"
#include "Tower.h"
#include "MilitaryTower.h"
#include "LaserTower.h"
#include "UdvancedLaserTower.h"
#include "ScatterLaserTower.h"
#include "Laser.h"

#define TowerAmount 62

enum Towers {
	BasicTower,
	UpdatedBasic,
	Scatter
};
class Map
{
	BackGround backGround;

	int arr[TowerAmount][2] = { { 2, 1 }, { 2, 3 },{ 2, 7 },{ 2, 9 },{ 2, 11 },{ 2, 13 },{ 4, 13 },{5, 1},{5, 3}, {5, 5},{5, 7},{5, 9},{6, 2},{6, 4},{6, 10} ,{6, 13},{7, 9},{8, 10},{8, 13},{10, 4},{10, 6},{10, 10},{10, 13},{11, 2}, { 12, 13}
	,{ 13, 6 },{ 13, 8 },{ 13, 10 },{ 13, 12 },{ 14, 5 },{ 14, 7 },{ 14, 11 },{ 15, 2 },{ 15, 6 },{ 16, 5 },{ 17, 2 },{ 18, 5 },{ 18, 7 },{ 18, 9 },{ 18, 11 },{ 19, 2 },{ 20, 11 },{ 21, 3 }
	,{ 21, 5 },{ 21, 7 },{ 21, 12 },{ 22, 4 },{ 22, 6 },{ 22, 8 },{ 22, 11 },{ 23, 7 },{ 23, 12 },{ 24, 8 },{ 24, 11 },{ 25, 7 },{ 25, 12 },{ 26, 8 },{ 26, 11 },{ 27, 7 }
	,{ 27, 12 },{ 28, 8 },{ 28, 11 } };
	bool IsPlaceTaken[TowerAmount];
	
	short int m_towerAmount;

	std::vector <MilitaryTower*> towers;
public:
	Map();
	void Draw(sf::RenderWindow& window);

	void Update(float deltaTime, std::vector <Enemy*> m_vecEnemies);

	void AddTower(int towerType, sf::Vector2f position, int X, int Y);
	bool IsOnThePlace(int x, int y);

	inline std::vector <MilitaryTower*>& GetTowers() { return towers; };
};

