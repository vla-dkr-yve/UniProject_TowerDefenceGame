#include "ScatterLaserTower.h"

int ScatterLaserTower::m_cost = 500;
int ScatterLaserTower::m_id = 5;
ScatterLaserTower::ScatterLaserTower(sf::Vector2f position) : MilitaryTower(75, 2.0f, sf::Vector2i(100 * 0, 100 * 2), position, 125.0f, 5)
{
}
