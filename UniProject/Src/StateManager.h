#pragma once
#include "State.h"
#include <stack>
#include <memory>
enum States {
	menu,
	game,
	leaderboard
};
class StateManager
{
private:
	std::stack<std::unique_ptr<State>> states;

public:
	void PushState(std::unique_ptr<State> state, sf::RenderWindow& window);
	void PopState(sf::RenderWindow& window);
	void CheckWindowResolution(sf::RenderWindow& window);
	State* GetCurrentState();

};

