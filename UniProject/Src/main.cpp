#include <SFML/Graphics.hpp>
#include "StateManager.h"
#include "MainMenuState.h"
#include "GameplayState.h"
//	Plans:
// 
// Add bosses
// 
// Add hero
// 
// Add fighting system
// 
// Recheck All state files
// 
// 
// Rewrite code to replace most of uneccesary shit with pointers etc. 
// 
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
