#include <SFML/Graphics.hpp>
#include "StateManager.h"
#include "MainMenuState.h"
#include "GameplayState.h"
//	Plans:
// 
// Recheck All state files
// 
// 
// Separate most of the code tha currently in main
// Rewrite code to replace most of uneccesary shit with pointers etc. 
// 
// Add main menu with 3 option play, leaderboard(load from file), exit
// Add kinda of score
// Add login system (username + password)?
// Save score into the file when lives go to 0/player finish the game closing the window (x button)
//
// Finish research tree
//

int main() {
	StateManager stateManager;


	
	sf::RenderWindow window(sf::VideoMode(800, 600), "main menu");
	window.setFramerateLimit(60);


	stateManager.PushState(std::make_unique<MainMenuState>(stateManager));

	while (window.isOpen())
	{
		State* currentState = stateManager.GetCurrentState();

		if (currentState)
		{
			currentState->HandleEvents(window);
			currentState->Update(window);
			currentState->Draw(window);
		}
	}

}
