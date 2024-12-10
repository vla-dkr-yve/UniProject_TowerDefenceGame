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
	Ground_Scorpion();
};

class Ground_Leafbug : public Enemy
{
public:
	Ground_Leafbug();
};

class Ground_Magma_Crab : public Enemy
{
public:
	Ground_Magma_Crab();
};

class Flying_Clampbeetle : public Enemy
{
public:
	Flying_Clampbeetle();
};

class Flying_Locust : public Enemy
{
public:
	Flying_Locust();
};

class Flying_Voidbutterfly : public Enemy
{
public:
	Flying_Voidbutterfly();
};

//class Boss : public Enemy
//{
//public:
//	Boss();
//};