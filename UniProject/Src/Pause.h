#pragma once
#include "SFML/Graphics.hpp"
class Pause
{
	bool bIsPaused;
	sf::RectangleShape pauseRect;
	sf::Text pauseText;
	sf::Text mainMenuText;
	sf::Font font;
public:
	Pause(sf::Vector2f window);

	void Update(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);

	inline bool IsPaused() { return bIsPaused; };
	inline void ChangeState() { bIsPaused = !bIsPaused; };
	const inline sf::FloatRect& GetMainMenuText() { return mainMenuText.getGlobalBounds(); };
};

