#define _USE_MATH_DEFINES
#include "FightingManager.h"
#include "Math.h"
#include <cmath>
FightingManager::FightingManager(Hero& hero): m_hero(hero)
{

}

void FightingManager::HeroAttack(std::vector<Enemy*>& enemies)
{
	if (m_hero.IsAttacking())
	{
		if (m_hero.GetCurrentAnimation() == 3)
		{
			int direction;

			if (m_hero.GetCurrentSide() == 'l')
			{
				direction = -32;
			}
			else {
				direction = +32;
			}

			for (auto& enemy : enemies)
			{
				if (Math::Collision(*enemy, sf::Vector2f(m_hero.GetPosition().x + direction, m_hero.GetPosition().y)))
				{
					enemy->TakeDamage(m_hero.GetDamage());
				}
			}
		}
	}
}

void FightingManager::HeroUpdate(std::vector<Enemy*>& enemies)
{

	if (m_hero.GetTarget() != nullptr)
	{
		if (Math::Distance(m_hero.GetTarget()->GetPosition(), m_hero.GetPosition()) > 100)
		{
			m_hero.GetTarget()->ChangeFightingState(false);
			m_hero.SetTarget(nullptr);
		}
	}
	else {
		for (auto& enemy : enemies)
		{
			if (Math::Distance(enemy->GetPosition(), m_hero.GetPosition()) < 100)
			{
				//m_isTargeted = true;
				m_hero.SetTarget(enemy);
				enemy->ChangeFightingState(true);
			}
		}
	}

	HeroAttack(enemies);
}

void FightingManager::TargetEnemyUpdate(Player& player, float deltaTime)
{
	if (m_hero.GetTarget() != nullptr)
	{
		m_hero.GetTarget()->Update(deltaTime, player, m_hero.GetPosition());
		if (m_hero.GetTarget()->CanAttack())
		{
			sf::Vector2f target = m_hero.GetPosition();
			sf::Vector2f position = m_hero.GetTarget()->GetPosition();
			

			float angle = atan2(target.y - position.y, target.x - position.x) * 180 / M_PI;
			m_lightnings.push_back(new Lightning(m_hero.GetTarget()->GetPosition(), angle));
			m_hero.GetTarget()->ChangeAttackState(false);
		}
	}

}

void FightingManager::LightningUpdate(float deltaTime)
{
	for (auto it = m_lightnings.begin(); it != m_lightnings.end();)
	{
		if ((*it)->ShouldBeDestroyed())
		{
			delete* it;
			it = m_lightnings.erase(it);
		}
		else {
			(*it)->Update(deltaTime);
			it++;
		}
	}
}


void FightingManager::Update(std::vector<Enemy*>& enemies, Player& player, float deltaTime)
{
	HeroUpdate(enemies);
	TargetEnemyUpdate(player, deltaTime);
	LightningUpdate(deltaTime);
}

void FightingManager::Draw(sf::RenderWindow& window)
{
	for (auto ligtning : m_lightnings)
	{
		ligtning->Draw(window);
	}
}
