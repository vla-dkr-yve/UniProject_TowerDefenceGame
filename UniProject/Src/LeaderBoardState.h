#pragma once
#include "StateManager.h"
#include <SFML/Graphics.hpp>
class LeaderBoardState : public State
{
private:
	StateManager& stateManager;

	const sf::Vector2f m_windowResolution = sf::Vector2f(1920, 1024);

	sf::Font m_font;

	sf::Text m_exitText;
	sf::Text m_LeaderBoardText;
	sf::Text m_Leaders[5];
public:
	LeaderBoardState(StateManager& manager);
	~LeaderBoardState();
	void HandleEvents(sf::RenderWindow& window) override;
	void Update(sf::RenderWindow& window) override;
	sf::Vector2f GetResolution() override;
	void Draw(sf::RenderWindow& window) override;
};

