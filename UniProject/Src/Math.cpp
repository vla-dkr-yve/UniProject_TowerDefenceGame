#include "Math.h"
#include <cmath>

float Math::dotProduct(const sf::Vector2f& rect1, const sf::Vector2f& rect2)
{
	return rect1.x * rect2.x + rect1.y * rect2.y;
}

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


bool Math::EnemyCollision(Enemy& enemy, sf::Vector2f position)
{
	if (enemy.GetPosition().x - enemy.GetSize().x / 2 < position.x &&
		enemy.GetPosition().x + enemy.GetSize().x / 2 > position.x &&
		enemy.GetPosition().y - enemy.GetSize().y / 2 < position.y &&
		enemy.GetPosition().y + enemy.GetSize().y / 2 > position.y) {
		return true;
	}
	return false;
}

bool Math::Collision(sf::FloatRect rect1, sf::FloatRect rect2)
{
	if (rect1.left + rect1.width > rect2.left &&
		rect1.left < rect2.left + rect2.width &&
		rect1.top + rect1.height > rect2.top &&
		rect1.top < rect2.top + rect2.height)
	{
		return true;
	}
	return false;
}

bool Math::OBBCollision(const sf::RectangleShape& rect1, const sf::RectangleShape& rect2)
{
	std::vector<sf::Vector2f> vertices1(4);
	const sf::Transform& transform1 = rect1.getTransform();
	const sf::FloatRect& bounds1 = rect1.getLocalBounds();

	vertices1[0] = transform1.transformPoint(bounds1.left, bounds1.top);
	vertices1[1] = transform1.transformPoint(bounds1.left + bounds1.width, bounds1.top);
	vertices1[2] = transform1.transformPoint(bounds1.left, bounds1.top + bounds1.height);
	vertices1[3] = transform1.transformPoint(bounds1.left + bounds1.width, bounds1.top + bounds1.height);


	std::vector<sf::Vector2f> vertices2(4);
	const sf::Transform& transform2 = rect2.getTransform();
	const sf::FloatRect& bounds2 = rect2.getLocalBounds();

	vertices2[0] = transform2.transformPoint(bounds2.left, bounds2.top);
	vertices2[1] = transform2.transformPoint(bounds2.left + bounds2.width, bounds2.top);
	vertices2[2] = transform2.transformPoint(bounds2.left, bounds2.top + bounds2.height);
	vertices2[3] = transform2.transformPoint(bounds2.left + bounds2.width, bounds2.top + bounds2.height);

	std::vector<sf::Vector2f> axes;
	for (int i = 0; i < 4; i++)
	{
		sf::Vector2f edge = vertices1[ (i + 1) % 4 ] - vertices1[i];
		axes.push_back(sf::Vector2f( -edge.y, edge.x ));
	}
	for (int i = 0; i < 4; i++)
	{
		sf::Vector2f edge = vertices2[(i + 1) % 4] - vertices2[i];
		axes.push_back(sf::Vector2f(-edge.y, edge.x));
	}

	for (const auto& axis: axes)
	{
		float min1 = std::numeric_limits<float>::max();
		float max1 = std::numeric_limits<float>::lowest();
		
		for (const auto& vertex: vertices1)
		{
			float projection = dotProduct(vertex, axis);
			min1 = std::min(min1, projection);
			max1 = std::max(max1, projection);

		}

		float min2 = std::numeric_limits<float>::max();
		float max2 = std::numeric_limits<float>::lowest();
		for (const auto& vertex: vertices2)
		{
			float projection = dotProduct(vertex, axis);
			min2 = std::min(min1, projection);
			max2 = std::max(max1, projection);
		}

		if (max1 < max2 || max2 < max1)
		{
			return false;
		}


	}


	return true;
}
