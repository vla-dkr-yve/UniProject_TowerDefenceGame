#include "CivilTower.h"

CivilTower::CivilTower(TowerType towerType,sf::Vector2f position):
	Tower(towerType,position)
{
	m_actionBar.setSize(sf::Vector2f(64, 5));
	m_actionBar.setPosition(sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y - m_buildingLine.getSize().y * 2));
	m_actionBar.setFillColor(sf::Color::Blue);

	m_actionBarBackground.setSize(sf::Vector2f(64, 5));
	m_actionBarBackground.setPosition(sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y - m_buildingBackground.getSize().y * 2));
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
		Build(deltaTime);
		return;
	}

	float actionPercentage = m_ftimer / m_fActionCooldown;

	m_actionBar.setSize(sf::Vector2f(m_actionBarBackground.getSize().x * actionPercentage, m_actionBarBackground.getSize().y));
	Action(deltaTime, player);
}

void CivilTower::Draw(sf::RenderWindow& window)
{
	Tower::Draw(window);
	if (!m_bIsBuild)
	{
		window.draw(m_actionBar);
	}
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