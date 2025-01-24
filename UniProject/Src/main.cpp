#include <SFML/Graphics.hpp>
#include "StateManager.h"
#include "MainMenuState.h"
#include "GameplayState.h"
#include "DataBase.h"
//#include <sqlite3.h>
//	Plans:
//
// Finish research tree
// 
// Clean Code
// 
// 
// Remove dispalaying console
// 
// Check corectness on different hardware
// 
//

int main() {
	StateManager stateManager;
	
	DataBase::CreateDB();
	DataBase::CreateTable();
	
	//DataBase::SelectData("Any", "123");
	
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
