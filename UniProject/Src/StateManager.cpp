#include "StateManager.h"

void StateManager::PushState(std::unique_ptr<State> state)
{
	states.push(std::move(state));
}

void StateManager::PopState()
{
	if (!states.empty())
	{
		states.pop();
	}
}

State* StateManager::GetCurrentState()
{
	return states.empty() ? nullptr : states.top().get();
}
