#pragma once
#include "SFML/Graphics.hpp"
class Pause
{
	bool bIsPaused;
	sf::RectangleShape pauseRect;
	sf::Text pauseText;
	sf::Font font;
public:
	Pause(sf::RenderWindow& window);

	void Draw(sf::RenderWindow& window);

	inline bool IsPaused() { return bIsPaused; };
	inline void ChangeState() { bIsPaused = !bIsPaused; };
};

