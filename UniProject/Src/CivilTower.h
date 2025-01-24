#pragma once
#include <vector>
#include "Tower.h"
#include "MilitaryTower.h"
#include "Player.h"
#include "Math.h"

class CivilTower : public Tower
{
protected:
	std::vector<Tower*> m_affectedTowers;
	sf::RectangleShape m_actionBar;
	sf::RectangleShape m_actionBarBackground;

public:
	CivilTower(TowerType towerType, sf::Vector2f position);
	~CivilTower();

	virtual void Action(float deltaTime, Player& player);
	void Update(float deltaTime, Player& player);
	void Draw(sf::RenderWindow& window) override;

	virtual void ApplyBuffs(std::vector<CivilTower*>& towers);
	virtual void ApplyBuffs(std::vector<MilitaryTower*>& towers);
	virtual void ReapplyBuffs(CivilTower* newTower);
	virtual void ReapplyBuffs(MilitaryTower* newTower);
	void RemoveBuffs();
};