#include "LeaderBoardState.h"
#include "DataBase.h"
#include <unordered_map>
LeaderBoardState::LeaderBoardState(StateManager& manager): stateManager(manager), leaders(DataBase::GetLeaders())
{
    m_font.loadFromFile("Assets/Fonts/Arial.TTF");

    m_Leaders.resize(leaders.size());
    m_deleteLeader.resize(leaders.size());

    SetValues();

    m_exitText.setFont(m_font);
    m_exitText.setCharacterSize(30);
	m_exitText.setString("Return to main menu");

    m_message.setFont(m_font);
    m_message.setCharacterSize(20);
    m_message.setPosition(sf::Vector2f(0, -40) + sf::Vector2f(0, m_windowResolution.y));
    m_isMessageDisplayed = false;
    m_messageTimer = 0.0f;

    m_smallTimer = 0.0f;
}

LeaderBoardState::~LeaderBoardState()
{
    //delete[] m_deleteLeader;
}

void LeaderBoardState::HandleEvents(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    
        if (event.type == sf::Event::MouseButtonReleased) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    
            if (m_exitText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                stateManager.PopState(window);
                return;
            }
            for (auto& x: m_deleteLeader)
            {
                if (x.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    int coordY = (x.getGlobalBounds().getPosition().y - 100) / 150;
                    std::string name; 
                    int k = 0;
                    for (auto x: leaders)
                    {
                        if (coordY == k)
                        {
                            name = x.first;
                        }
                        k++;
                    }

                    if (name == DataBase::Username)
                    {
                        m_message.setString("You can't delete yourself");

                        m_isMessageDisplayed = true;
                        m_message.setFillColor(sf::Color::White);
                        m_messageTimer = 5.0f;
                    }
                    else {
                        DataBase::DeleteUser(name);
                        SetValues();
                    }
                }
            }
        }
    }
}

void LeaderBoardState::Update(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    
    float deltaTime = clock.restart().asSeconds();

    if (m_isMessageDisplayed)
    {
        m_messageTimer -= deltaTime;
        if (m_messageTimer < 0)
        {
            m_isMessageDisplayed = false;
        }
        m_smallTimer += deltaTime;
        if (m_smallTimer >= 0.1f)
        {
            sf::Color color = m_message.getFillColor();
            color.a = (0, color.a - 5);
            m_message.setFillColor(color);

            m_smallTimer = 0.0f;
        }
    }

    if (m_exitText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        m_exitText.setFillColor(sf::Color::Red);
        return;
    }
    for (auto& x: m_deleteLeader)
    {
        if (x.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            x.setFillColor(sf::Color::Red);
        }
        else {
            x.setFillColor(sf::Color::White);
        }
    }
    m_exitText.setFillColor(sf::Color::White);
}

void LeaderBoardState::SetValues()
{
    m_Leaders.resize(leaders.size());
    m_deleteLeader.resize(leaders.size());

    int i = 0;
    for (auto x : leaders)
    {
        std::string leader;
        leader = x.first;
        leader += " : ";
        leader += std::to_string(x.second);

        sf::Text leadersText;
        leadersText.setFont(m_font);
        leadersText.setCharacterSize(30);
        leadersText.setString(leader);
        leadersText.setPosition(sf::Vector2f(100, 100 + 150 * i));
        m_Leaders.push_back(leadersText);

        sf::Text deleteText;
        deleteText.setFont(m_font);
        deleteText.setCharacterSize(30);
        deleteText.setString("Delete user");
        deleteText.setPosition(leadersText.getGlobalBounds().getPosition() + sf::Vector2f(leadersText.getGlobalBounds().getSize().x, 0) + sf::Vector2f(30, -5));
        m_deleteLeader.push_back(deleteText);

        i++;
    }
}

sf::Vector2f LeaderBoardState::GetResolution()
{
    return m_windowResolution;
}

void LeaderBoardState::Draw(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);

    window.draw(m_exitText);
    for (auto& x : m_Leaders)
    {
        window.draw(x);
    }
    for (auto& x : m_deleteLeader)
    {
        if (!DataBase::IsUserAdmin)
        {
            continue;
        }
        window.draw(x);
    }

    if (m_isMessageDisplayed)
    {
        window.draw(m_message);
    }
    window.display();
}