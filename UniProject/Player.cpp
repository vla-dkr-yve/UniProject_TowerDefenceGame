#include "Player.h"

Player::Player(): m_money(500), m_researchPoints(150), m_lives(20), m_timer(m_cooldown)
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
