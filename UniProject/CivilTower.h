#pragma once
#include <vector>
#include "Tower.h"

enum CivilTowerType {
	Research,
	Factory,
	Housing,
	Recycling,
	Construction
};
class CivilTower : public Tower
{
protected:
	int m_id;
	std::vector<Tower*> m_affectedTowers;
public:
	CivilTower(int id, int value,int cost, float actionCooldown, sf::Vector2i texturePosition, sf::Vector2f position, float radius);
	~CivilTower();

	//void 
	virtual void Action(float deltaTime);
	
	//virtual void ApplyBuffs(std::vector<Tower*>& towers);
	void RemoveBuffs();

	inline int GetId() { return m_id; };
};