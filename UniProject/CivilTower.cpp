#include "CivilTower.h"

CivilTower::CivilTower(int value,float actionCooldown, sf::Vector2i texturePosition, sf::Vector2f position, float radius):
	Tower(value,actionCooldown, texturePosition, position, radius)
{
	//ApplyBuffs(towers);
}

CivilTower::~CivilTower()
{
	RemoveBuffs();
}

void CivilTower::Action(float deltaTime, Player& player)
{
}

void CivilTower::Update(float deltaTime, Player& player)
{
	if (m_bIsBuild)
	{
		Build();
		return;
	}
	Action(deltaTime, player);
}

void CivilTower::ApplyBuffs(std::vector<CivilTower*>& towers)
{
}
void CivilTower::ApplyBuffs(std::vector<MilitaryTower*>& towers)
{
}

void CivilTower::ReapplyBuffs(CivilTower* newTower)
{
}
void CivilTower::ReapplyBuffs(MilitaryTower* newTower)
{
}

void CivilTower::RemoveBuffs()
{
	for (auto tower: m_affectedTowers)
	{
		tower->RemoveBuffBySource(this);
	}
	m_affectedTowers.clear();
}
