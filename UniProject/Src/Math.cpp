#include "Math.h"
#include <cmath>


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

int Math::NumberOfNewLines(std::string def)
{
	int res = 0;
	for (int i = 0; i < def.size(); i++)
	{
		if (def[i] == '\n')
		{
			res++;
		}
	}
	return res;
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

float Math::dotProduct(const sf::Vector2f& rect1, const sf::Vector2f& rect2)
{
	return rect1.x * rect2.x + rect1.y * rect2.y;
}

sf::Vector2f Math::normalize(const sf::Vector2f& vector) {
	float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
	return (length > 0) ? sf::Vector2f(vector.x / length, vector.y / length) : sf::Vector2f(0.f, 0.f);
}

bool Math::OBBCollision(const sf::RectangleShape& rect1, const sf::RectangleShape& rect2)
{
	sf::Transform t1 = rect1.getTransform();
	sf::Transform t2 = rect2.getTransform();

	sf::Vector2f points1[4] = {
		t1.transformPoint(rect1.getPoint(0)),
		t1.transformPoint(rect1.getPoint(1)),
		t1.transformPoint(rect1.getPoint(2)),
		t1.transformPoint(rect1.getPoint(3))
	};

	sf::Vector2f points2[4] = {
		t2.transformPoint(rect2.getPoint(0)),
		t2.transformPoint(rect2.getPoint(1)),
		t2.transformPoint(rect2.getPoint(2)),
		t2.transformPoint(rect2.getPoint(3))
	};

	auto overlapOnAxis = [](const sf::Vector2f& axis, const sf::Vector2f points1[4], const sf::Vector2f points2[4]) -> bool {
		float min1 = dotProduct(points1[0], axis);
		float max1 = min1;
		for (int i = 1; i < 4; ++i) {
			float projection = dotProduct(points1[i], axis);
			min1 = std::min(min1, projection);
			max1 = std::max(max1, projection);
		}

		float min2 = dotProduct(points2[0], axis);
		float max2 = min2;
		for (int i = 1; i < 4; ++i) {
			float projection = dotProduct(points2[i], axis);
			min2 = std::min(min2, projection);
			max2 = std::max(max2, projection);
		}

		return !(max1 < min2 || max2 < min1);
		};

	sf::Vector2f axes[4] = {
		normalize(points1[1] - points1[0]),
		normalize(points1[3] - points1[0]),
		normalize(points2[1] - points2[0]),
		normalize(points2[3] - points2[0])
	};

	for (int i = 0; i < 4; ++i) {
		if (!overlapOnAxis(axes[i], points1, points2)) {
			return false;
		}
	}

	return true;
}
