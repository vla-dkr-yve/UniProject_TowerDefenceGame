#include "Pause.h"

Pause::Pause(sf::Vector2f window) : bIsPaused(0)
{
	font.loadFromFile("Assets/Fonts/Arial.TTF");

	pauseRect.setSize(sf::Vector2f(275, 130));
	pauseRect.setPosition(sf::Vector2f(window.x / 2 - pauseRect.getSize().x / 2, window.y / 2 - pauseRect.getSize().y / 2));
	pauseRect.setFillColor(sf::Color(0, 0, 0, 64));

	pauseText.setFont(font);
	pauseText.setString("Game is paused");
	pauseText.setPosition(sf::Vector2f(pauseRect.getPosition().x + 25, pauseRect.getPosition().y + 25));


	mainMenuText.setFont(font);
	mainMenuText.setString("To main menu");
	mainMenuText.setPosition(sf::Vector2f(pauseRect.getPosition().x + 25, pauseRect.getPosition().y + 2 * 40));
}

void Pause::Update(sf::RenderWindow& window)
{
	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
	if (mainMenuText.getGlobalBounds().contains(mousePosition))
	{
		mainMenuText.setFillColor(sf::Color::Red);
		return;
	}
	mainMenuText.setFillColor(sf::Color::White);
}

void Pause::Draw(sf::RenderWindow& window)
{
	if (bIsPaused)
	{
		window.draw(pauseRect);
		window.draw(pauseText);
		window.draw(mainMenuText);
	}
}
