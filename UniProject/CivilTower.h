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
public:
	CivilTower(int id, int value,int cost, float actionCooldown, sf::Vector2i texturePosition, sf::Vector2f position, float radius);
	~CivilTower();

	virtual void Action(float deltaTime, Player& player);
	void Update(float deltaTime, Player& player);

	virtual void ApplyBuffs(std::vector<CivilTower*>& towers);
	virtual void ApplyBuffs(std::vector<MilitaryTower*>& towers);
	virtual void ReapplyBuffs(CivilTower* newTower);
	virtual void ReapplyBuffs(MilitaryTower* newTower);
	void RemoveBuffs();


};