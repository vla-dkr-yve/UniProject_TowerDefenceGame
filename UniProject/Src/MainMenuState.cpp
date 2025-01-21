#include "MainMenuState.h"
#include "Gameplaystate.h"
#include "LeaderBoardState.h"
#include "LoginState.h"
#include "DataBase.h"
MainMenuState::MainMenuState(StateManager& manager): stateManager(manager), m_username("\0"), m_isLogined(false)
{
    m_font.loadFromFile("Assets/Fonts/Arial.TTF");

    m_loginButton.setFont(m_font);
    m_loginButton.setString("Login");
    m_loginButton.setCharacterSize(20);
    m_loginButton.setPosition(m_windowResolution.x - 100, 50);


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
                stateManager.PushState(std::make_unique<GameplayState>(stateManager, m_isLogined, window), window);
            }
            else if (m_leaderBoardButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                stateManager.PushState(std::make_unique<LeaderBoardState>(stateManager), window);
            }
            else if (m_loginButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && !m_isLogined) {
                stateManager.PushState(std::make_unique<LoginState>(stateManager, m_isLogined), window);
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

    if (m_isLogined)
    {
        m_username = DataBase::Username;
        m_loginButton.setString(m_username);
    }

    if (m_loginButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && !m_isLogined) {
        m_loginButton.setFillColor(sf::Color::Red);
        return;
    }
    
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
    m_loginButton.setFillColor(sf::Color::White);
    m_startButton.setFillColor(sf::Color::White);
    m_leaderBoardButton.setFillColor(sf::Color::White);
    m_exitButton.setFillColor(sf::Color::White);
}

sf::Vector2f MainMenuState::GetResolution()
{
    return m_windowResolution;
}

void MainMenuState::Draw(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);

    window.draw(m_title);
    window.draw(m_startButton);
    window.draw(m_leaderBoardButton);
    window.draw(m_loginButton);
    window.draw(m_exitButton);

    window.display();
}
