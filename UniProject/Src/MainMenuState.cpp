#include "MainMenuState.h"
#include "Gameplaystate.h"
MainMenuState::MainMenuState(StateManager& manager): stateManager(manager)
{

    m_font.loadFromFile("Assets/Fonts/Arial.TTF");
    m_title.setFont(m_font);
    m_title.setString("Main Menu");
    m_title.setCharacterSize(50);
    m_title.setPosition(100, 50);

    m_startButton.setFont(m_font);
    m_startButton.setString("Start Game");
    m_startButton.setCharacterSize(30);
    m_startButton.setPosition(100, 150);

    m_leaderBoardButton.setFont(m_font);
    m_leaderBoardButton.setString("Leader Board");
    m_leaderBoardButton.setCharacterSize(30);
    m_leaderBoardButton.setPosition(100, 200);

    m_exitButton.setFont(m_font);
    m_exitButton.setString("Exit");
    m_exitButton.setCharacterSize(30);
    m_exitButton.setPosition(100, 250);
}

void MainMenuState::HandleEvents(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (m_startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                //window.close();
                window.create(sf::VideoMode(1920, 1024), "");
                stateManager.PushState(std::make_unique<GameplayState>(stateManager, window));
                //stateManager.PushState(std::make_unique<GameplayState>(stateManager));
            }
            else if (m_leaderBoardButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                // Change to SettingsState
            }
            else if (m_exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                window.close();
            }
        }
    }
}

void MainMenuState::Update(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    if (m_startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        m_startButton.setFillColor(sf::Color::Red);
        return;
    }
    else if (m_leaderBoardButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        m_leaderBoardButton.setFillColor(sf::Color::Red);
        return;
    }
    else if (m_exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        m_exitButton.setFillColor(sf::Color::Red);
        return;
    }
    m_startButton.setFillColor(sf::Color::White);
    m_leaderBoardButton.setFillColor(sf::Color::White);
    m_exitButton.setFillColor(sf::Color::White);
}

void MainMenuState::Draw(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);

    window.draw(m_title);
    window.draw(m_startButton);
    window.draw(m_leaderBoardButton);
    window.draw(m_exitButton);

    window.display();
}
