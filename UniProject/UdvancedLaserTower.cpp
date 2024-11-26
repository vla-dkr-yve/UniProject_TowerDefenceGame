#include "UdvancedLaserTower.h"

short int UdvancedLaserTower::m_cost = 200;
int UdvancedLaserTower::m_id = 4;
UdvancedLaserTower::UdvancedLaserTower(sf::Vector2f position) : MilitaryTower(100, 1.0f, sf::Vector2i(100 * 3, 100 * 1), position, 125.0f, 1)
{
}
