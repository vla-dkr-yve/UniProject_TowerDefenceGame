#pragma once
#include "Enemy.h"

class BasicEnemy : public Enemy
{
public:
	BasicEnemy();
};

class FastEnemy : public Enemy
{
public:
	FastEnemy();
};

class SlowEnemy : public Enemy
{
public:
	SlowEnemy();
};

//class Boss : public Enemy
//{
//public:
//	Boss();
//};