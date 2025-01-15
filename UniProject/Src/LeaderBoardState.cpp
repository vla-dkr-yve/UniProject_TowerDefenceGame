#include "LeaderBoardState.h"


LeaderBoardState::LeaderBoardState(StateManager& manager): stateManager(manager)
{
    m_font.loadFromFile("Assets/Fonts/Arial.TTF");

    m_exitText.setFont(m_font);
    m_exitText.setCharacterSize(30);
	m_exitText.setString("Return to main menu");
    m_exitText.setStyle(0);
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

    window.display();
}
