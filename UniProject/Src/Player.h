#pragma once
#include "GUI.h"
class Player
{
	int m_score;

	int m_money;
	int m_researchPoints;
	int m_lives;

	float m_timer;
	const float m_cooldown = 1.0f;
public:
	Player();

	void Update(float deltaTime);

	inline void IncreaseScore(int i) { m_score += i; };
	inline void DecreaseScore(int i) { m_score -= i; };
	inline int GetScore() { return m_score; };

	inline void IncreaseMoney(int i) { m_money += i;};
	inline void DecreaseMoney(int i) { m_money -= i;};
	inline int GetMoney() { return m_money; };

	inline void IncreaseResearchPoints(int i) { m_researchPoints += i;};
	inline void DecreaseResearchPoints(int i) { m_researchPoints -= i;};
	inline int GetResearchPoints() { return m_researchPoints; };

	inline void IncreaseLives(int i) { m_lives += i;};
	inline void DecreaseLives(int i) { m_lives -= i;};
	inline int GetLives() { return m_lives; };
};

