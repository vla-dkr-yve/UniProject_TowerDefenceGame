#include "Pause.h"

Pause::Pause(sf::RenderWindow& window) : bIsPaused(0)
{
	font.loadFromFile("Assets/Fonts/Arial.TTF");
	pauseText.setFont(font);
	pauseText.setString("Game is paused");
	pauseRect.setSize(sf::Vector2f(300, 100));
	pauseRect.setPosition(sf::Vector2f(window.getSize().x / 2 - pauseRect.getSize().x / 2, window.getSize().y / 2 - pauseRect.getSize().y / 2));
	pauseRect.setFillColor(sf::Color(0, 0, 0, 64));
	pauseText.setPosition(sf::Vector2f(pauseRect.getPosition().x + 25, pauseRect.getPosition().y + 25));
}

void Pause::Draw(sf::RenderWindow& window)
{
	if (bIsPaused)
	{
		window.draw(pauseRect);
		window.draw(pauseText);
	}
}
