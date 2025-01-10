#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Hero.h"
#include "Enemy.h"
#include "Lightning.h"
class FightingManager
{
private:
	Hero& m_hero;

	std::vector<Lightning*> m_lightnings;

private:
	void HeroAttack(std::vector<Enemy*>& enemies);
	void HeroUpdate(std::vector<Enemy*>& enemies);

	void TargetEnemyUpdate(Player& player, float deltaTime);

	void LightningUpdate(float deltaTime);
public:
	FightingManager(Hero& hero);
	void Update(std::vector<Enemy*>& enemies, Player& player,float deltaTime);
	void Draw(sf::RenderWindow& window);
};

