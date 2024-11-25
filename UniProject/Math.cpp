#include "Math.h"

float Math::Distance(sf::Vector2f target, sf::Vector2f position)
{
	sf::Vector2f direction = target - position;
	float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
    return distance;
}
