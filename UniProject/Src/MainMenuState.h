#pragma once
#include "StateManager.h"
#include <SFML/Graphics.hpp>
class MainMenuState : public State
{
	StateManager& stateManager;

	sf::Font m_font;
	sf::Text m_title;

	sf::Text m_startButton;
	sf::Text m_leaderBoardButton;
	sf::Text m_exitButton;
public:
	MainMenuState(StateManager& manager);

	void HandleEvents(sf::RenderWindow& window) override;
	void Update(sf::RenderWindow& window) override;
	void Draw(sf::RenderWindow& window) override;

};

