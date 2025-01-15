#pragma once
#include <SFML/Graphics.hpp>
class State {
public:
	State();

	virtual void HandleEvents(sf::RenderWindow& window) = 0;
	virtual void Update(sf::RenderWindow& window) = 0;
	virtual sf::Vector2f GetResolution() = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;

	virtual ~State() = default;
};