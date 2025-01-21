#include "LoginState.h"
#include "DataBase.h"
#include <iostream>
LoginState::LoginState(StateManager& manager, bool& isLogined) : stateManager(manager), m_isUsernameInputFieldActive(false), m_isPasswordInputFieldActive(false), m_isLogined(isLogined)
{
	m_font.loadFromFile("Assets/Fonts/Arial.TTF");

    m_returnButton.setFont(m_font);
    m_returnButton.setString("Return");
    m_returnButton.setCharacterSize(30);
    m_returnButton.setPosition(0,0);


    m_usernameInputField.setOutlineThickness(1);
    m_usernameInputField.setOutlineColor(sf::Color::White);
    m_usernameInputField.setPosition(100, 150);
    m_usernameInputField.setSize(sf::Vector2f(600 , 38));
    m_usernameInputField.setFillColor(sf::Color::Black);

    m_usernameInputText.setFont(m_font);
    m_usernameInputText.setString(m_usernameInputString);
    m_usernameInputText.setCharacterSize(30);
    m_usernameInputText.setPosition(m_usernameInputField.getPosition() + sf::Vector2f(5,0));

    m_usernameText.setFont(m_font);
    m_usernameText.setString("Username");
    m_usernameText.setCharacterSize(30);
    m_usernameText.setPosition(m_usernameInputField.getPosition() - sf::Vector2f(0, 35));


    m_passwordInputField.setOutlineThickness(1);
    m_passwordInputField.setOutlineColor(sf::Color::White);
    m_passwordInputField.setPosition(100, 300);
    m_passwordInputField.setSize(sf::Vector2f(600, 38));
    m_passwordInputField.setFillColor(sf::Color::Black);

    m_passwordInputText.setFont(m_font);
    m_passwordInputText.setString(m_passwordInputString);
    m_passwordInputText.setCharacterSize(30);
    m_passwordInputText.setPosition(m_passwordInputField.getPosition() + sf::Vector2f(5, 0));

    m_passwordText.setFont(m_font);
    m_passwordText.setString("Password");
    m_passwordText.setCharacterSize(30);
    m_passwordText.setPosition(m_passwordInputField.getPosition() - sf::Vector2f(0, 35));

    m_submitButton.setPosition(400 - 50, 450);
    m_submitButton.setSize(sf::Vector2f(100,40));
    m_submitButton.setOutlineThickness(1);
    m_submitButton.setOutlineColor(sf::Color::White);
    m_submitButton.setFillColor(sf::Color::Black);

    m_submitButtonText.setFont(m_font);
    m_submitButtonText.setString("Login");
    m_submitButtonText.setCharacterSize(30);
    m_submitButtonText.setPosition(m_submitButton.getPosition() + sf::Vector2f(5, 0));

    m_message.setFont(m_font);
    //m_displayedMassage.setString("Password");
    m_message.setCharacterSize(20);
    m_message.setPosition(sf::Vector2f(0, -40) + sf::Vector2f(0 ,m_windowResolution.y));
    m_isMessageDisplayed = false;
    m_messageTimer = 0.0f;

    m_smallTimer = 0.0f;
}

void LoginState::HandleEvents(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            
            if (m_returnButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                stateManager.PopState(window);
                return;
            }

            if (m_usernameInputField.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                m_isUsernameInputFieldActive = true;
                
                std::string temp = m_passwordInputText.getString();
                if (!temp.empty() && temp.back() == '_')
                {
                    temp.pop_back();
                    m_passwordInputText.setString(temp);
                }
                m_isPasswordInputFieldActive = false;
            }
            else if (m_passwordInputField.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                m_isPasswordInputFieldActive = true;
    
                std::string temp = m_usernameInputText.getString();
                if (!temp.empty() && temp.back() == '_')
                {
                    temp.pop_back();
                    m_usernameInputText.setString(temp);
                }
                m_isUsernameInputFieldActive = false;
            }

            if (m_submitButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                if (!m_usernameInputString.empty() && !m_passwordInputString.empty())
                {
                    int res = DataBase::LoginUser(m_usernameInputString, m_passwordInputString);
                    //std::cout << res;
                    if (res == 1)
                    {
                        std::cout << "Loggined successfully";

                        m_isLogined = true;
                        DataBase::Username = m_usernameInputString;
                        stateManager.PopState(window);
                        return;
                    }
                    else if (res == 2)
                    {
                        std::cout << "New user was created successfully";

                        m_isLogined = true;
                        DataBase::Username = m_usernameInputString;
                        stateManager.PopState(window);
                        return;
                    }
                    else if (res == -1)
                    {
                        std::cout << "Incorrect password. Please try again";
                        m_message.setString("Incorrect password. Please try again");

                        m_isMessageDisplayed = true;
                        m_messageTimer = 5.0f;
                        m_isLogined = false;
                    }
                }
            }
        }
    
        if (event.type == sf::Event::TextEntered) {
            if (std::isprint(event.text.unicode)) {
                if (m_isUsernameInputFieldActive)
                {
                    m_usernameInputString += event.text.unicode;
                }
                else if (m_isPasswordInputFieldActive)
                {
                    m_passwordInputString += event.text.unicode;
                }
            }
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::BackSpace) {
                if (m_isUsernameInputFieldActive)
                {
                    if (!m_usernameInputString.empty()) {
                        m_usernameInputString.pop_back();
                    }
                }
                else if (m_isPasswordInputFieldActive)
                {
                    if (!m_usernameInputString.empty()) {
                        m_passwordInputString.pop_back();
                    }
                }
            }
        }
    }
}

void LoginState::Update(sf::RenderWindow& window)
{
    float deltaTime = clock.restart().asSeconds();
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);



    m_textEffectTime += deltaTime;

    if (m_textEffectTime >= 0.5)
    {
        m_showCursor = !m_showCursor;
        m_textEffectTime = 0.0f;
    }

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

    if (m_isUsernameInputFieldActive)
    {
        m_usernameInputText.setString(m_usernameInputString + (m_showCursor ? '_' : ' '));
    }
    else if (m_isPasswordInputFieldActive)
    {
        m_passwordInputText.setString(m_passwordInputString + (m_showCursor ? '_' : ' '));
    }

    if (m_submitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        m_submitButton.setFillColor(sf::Color::Red);
        return;
    }

    if (m_returnButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        m_returnButton.setFillColor(sf::Color::Red);
        return;
    }

    m_submitButton.setFillColor(sf::Color::Black);
    m_returnButton.setFillColor(sf::Color::White);
}

void LoginState::Draw(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);

    window.draw(m_returnButton);
    window.draw(m_usernameText);
    window.draw(m_passwordText);
    window.draw(m_usernameInputField);
    window.draw(m_passwordInputField);
    window.draw(m_usernameInputText);
    window.draw(m_passwordInputText);
    window.draw(m_submitButton);
    window.draw(m_submitButtonText);

    if (m_isMessageDisplayed)
    {
        window.draw(m_message);
    }

    window.display();
}

sf::Vector2f LoginState::GetResolution()
{
	return m_windowResolution;
}
