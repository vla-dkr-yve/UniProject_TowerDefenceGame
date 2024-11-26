#include "LaserTower.h"

int LaserTower::m_cost = 100;
int LaserTower::m_id = 3;
LaserTower::LaserTower(sf::Vector2f position) : MilitaryTower(50, 1.5, sf::Vector2i(100 * 2, 100 * 1), position,150.0f, 1)
{
}
