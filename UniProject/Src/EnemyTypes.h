#pragma once
#include "Enemy.h"

enum EnemyType {
	Scorpion,
	Leafbug,
	Magma_Crab,
	Clampbeetle,
	Locust,
	Voidbutterfly
};
class Ground_Scorpion : public Enemy
{
public:
	Ground_Scorpion(int scoreMultiplier);
};

class Ground_Leafbug : public Enemy
{
public:
	Ground_Leafbug(int scoreMultiplier);
};

class Ground_Magma_Crab : public Enemy
{
public:
	Ground_Magma_Crab(int scoreMultiplier);
};

class Flying_Clampbeetle : public Enemy
{
public:
	Flying_Clampbeetle(int scoreMultiplier);
};

class Flying_Locust : public Enemy
{
public:
	Flying_Locust(int scoreMultiplier);
};

class Flying_Voidbutterfly : public Enemy
{
public:
	Flying_Voidbutterfly(int scoreMultiplier);
};