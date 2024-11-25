#pragma once
class Player
{
	int m_money;
	int m_researchPoints;
	int m_lives;
public:
	inline void IncreaseMoney(int i) { m_money += i; };
	inline void DecreaseMoney(int i) { m_money -= i; };
	inline int GetMoney(int i) { return m_money; };

	inline void IncreaseResearchPoints(int i) { m_researchPoints += i; };
	inline void DecreaseResearchPoints(int i) { m_researchPoints -= i; };
	inline int GetResearchPoints(int i) { return m_researchPoints; };

	inline void IncreaseLives(int i) { m_lives += i; };
	inline void DecreaseLives(int i) { m_lives -= i; };
	inline int GetLives(int i) { return m_lives; };
};

