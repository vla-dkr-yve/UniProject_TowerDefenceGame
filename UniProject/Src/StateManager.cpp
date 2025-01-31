#include "StateManager.h"

void StateManager::PushState(std::unique_ptr<State> state, sf::RenderWindow& window)
{
	states.push(std::move(state));
	CheckWindowResolution(window);
}

void StateManager::PopState(sf::RenderWindow& window)
{
	if (!states.empty())
	{
		states.pop();
	}
	CheckWindowResolution(window);
}

void StateManager::CheckWindowResolution(sf::RenderWindow& window)
{
	if (!states.empty())
	{
		sf::Vector2f currentResolution;
		State* currentState = GetCurrentState();

		if (currentResolution != currentState->GetResolution())
		{
			window.create(sf::VideoMode(currentState->GetResolution().x, currentState->GetResolution().y), "");
		}
	}
}

State* StateManager::GetCurrentState()
{
	return states.empty() ? nullptr : states.top().get();
}