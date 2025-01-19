#include <SFML/Graphics.hpp>
#include "StateManager.h"
#include "MainMenuState.h"
#include "GameplayState.h"
#include "DataBase.h"
//#include <sqlite3.h>
//	Plans:
// 
// 
// Add hero +
// 
// Add fighting system {
//			-Finish lightning
// }
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
// Add bosses
//

int main() {
	StateManager stateManager;
	
	DataBase::CreateDB();
	DataBase::CreateTable();
	
	
	sf::RenderWindow window(sf::VideoMode(800,600), "");
	window.setFramerateLimit(60);
	
	
	stateManager.PushState(std::make_unique<MainMenuState>(stateManager), window);
	
	while (window.isOpen())
	{
		//State* currentState = stateManager.GetCurrentState();
	
		//if (currentState)
		//{
		stateManager.GetCurrentState()->HandleEvents(window);
		stateManager.GetCurrentState()->Update(window);
		stateManager.GetCurrentState()->Draw(window);
		//}
	}

	
	//DataBase::InsertData();
	//DataBase::UpdateData();
	//DataBase::SelectData();
	//DataBase::DeleteData();
}
