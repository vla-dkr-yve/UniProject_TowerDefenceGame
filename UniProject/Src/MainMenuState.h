#pragma once
#include "StateManager.h"
#include <SFML/Graphics.hpp>
class MainMenuState : public State
{
private:
	StateManager& stateManager;

	const sf::Vector2f m_windowResolution = sf::Vector2f(800, 600);

	sf::Font m_font;
	
	std::string m_username;
	bool m_isLogined;
	sf::Text m_loginButton;

	sf::Text m_title;

	sf::Text m_startButton;
	sf::Text m_leaderBoardButton;
	sf::Text m_exitButton;
public:
	MainMenuState(StateManager& manager);

	void HandleEvents(sf::RenderWindow& window) override;
	void Update(sf::RenderWindow& window) override;
	sf::Vector2f GetResolution() override;
	void Draw(sf::RenderWindow& window) override;

};

