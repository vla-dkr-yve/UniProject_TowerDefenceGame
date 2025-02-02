#include "Player.h"

Player::Player(): m_money(300), m_researchPoints(10), m_lives(20), m_timer(m_cooldown), m_score(0)
{
}

void Player::Update(float deltaTime)
{
	m_timer -= deltaTime;
	if (m_timer <= 0)
	{
		IncreaseMoney(10);
		IncreaseResearchPoints(1);
		m_timer = m_cooldown;
	}
}
