#pragma once
#include "StateManager.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
class LeaderBoardState : public State
{
private:
	StateManager& stateManager;

	std::unordered_map<std::string, int>& leaders;

	const sf::Vector2f m_windowResolution = sf::Vector2f(1920, 1024);

	sf::Font m_font;

	sf::Text m_exitText;
	sf::Text m_LeaderBoardText;
	std::vector<sf::Text> m_Leaders;

	std::vector<sf::Text> m_deleteLeader;
public:
	LeaderBoardState(StateManager& manager);
	~LeaderBoardState();

	void HandleEvents(sf::RenderWindow& window) override;
	void Update(sf::RenderWindow& window) override;
	void SetValues();
	sf::Vector2f GetResolution() override;
	void Draw(sf::RenderWindow& window) override;
};

