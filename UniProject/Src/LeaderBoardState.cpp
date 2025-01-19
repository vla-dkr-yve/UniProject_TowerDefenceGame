#include "LeaderBoardState.h"
#include "DataBase.h"
#include <vector>

LeaderBoardState::LeaderBoardState(StateManager& manager): stateManager(manager)
{
    m_font.loadFromFile("Assets/Fonts/Arial.TTF");

    std::vector<std::string> leaders = DataBase::GetLeaders();

    int i = 0;
    for (int i = 0; i < 5; i++)
    {
        std::string leader;
        if (leaders.size() > i)
        {
            leader = leaders[i];
        }
        else {
            leader = "\0";
        }
        m_Leaders[i].setFont(m_font);
        m_Leaders[i].setCharacterSize(30);
        m_Leaders[i].setString(leader);
        m_Leaders[i].setPosition(sf::Vector2f(100, 100 + 150 * i));
    }


    m_exitText.setFont(m_font);
    m_exitText.setCharacterSize(30);
	m_exitText.setString("Return to main menu");
}

LeaderBoardState::~LeaderBoardState()
{
    //delete[] m_Leaders;
}

void LeaderBoardState::HandleEvents(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    
            if (m_exitText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                stateManager.PopState(window);
            }
        }
    }
}

void LeaderBoardState::Update(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    
    if (m_exitText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        m_exitText.setFillColor(sf::Color::Red);
        return;
    }
    m_exitText.setFillColor(sf::Color::White);
}

sf::Vector2f LeaderBoardState::GetResolution()
{
    return m_windowResolution;
}

void LeaderBoardState::Draw(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);

    window.draw(m_exitText);
    for (int i = 0; i < 5; i++)
    {
        window.draw(m_Leaders[i]);
    }
    window.display();
}
