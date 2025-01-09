#include "Math.h"

float Math::Distance(sf::Vector2f target, sf::Vector2f position)
{
	sf::Vector2f direction = target - position;
	float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
    return distance;
}

std::string Math::EditString(std::string def, int characterSize, float width, sf::Font& font)
{
	std::string changed;
	float lineWidth = 0;

	sf::Text text("", font, characterSize);

	std::string word;
	for (char c: def)
	{
		text.setString(c);
		float charWidth = text.getGlobalBounds().width;
		
		if (lineWidth + charWidth * 3 > width)
		{
			changed += '\n';
			lineWidth = 0;
		}

		word += c;

		if (c == ' ')
		{
			changed += word;
			word = "";
		}
		lineWidth += charWidth;
	}
	return changed + word;
}


bool Math::Collision(Enemy& enemy, sf::Vector2f position)
{
	if (enemy.GetPosition().x - enemy.GetSize().x / 2 < position.x &&
		enemy.GetPosition().x + enemy.GetSize().x / 2 > position.x &&
		enemy.GetPosition().y - enemy.GetSize().y / 2 < position.y &&
		enemy.GetPosition().y + enemy.GetSize().y / 2 > position.y) {
		return true;
	}
	return false;
}