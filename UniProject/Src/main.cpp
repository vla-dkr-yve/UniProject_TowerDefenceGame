#include <SFML/Graphics.hpp>
#include "StateManager.h"
#include "MainMenuState.h"
#include "DataBase.h"
//#include <sqlite3.h>
//	Plans:
//
// Check corectness on different hardware
// 

int main() {
	StateManager stateManager;
	
	DataBase::CreateDB();
	DataBase::CreateTable();
	DataBase::InsertAdmin();
	
	sf::RenderWindow window(sf::VideoMode(800,600), "");
	window.setFramerateLimit(60);
	
	
	stateManager.PushState(std::make_unique<MainMenuState>(stateManager), window);
	
	while (window.isOpen())
	{
		stateManager.GetCurrentState()->HandleEvents(window);
		stateManager.GetCurrentState()->Update(window);
		stateManager.GetCurrentState()->Draw(window);
	}
}
