#include "LoginState.h"

LoginState::LoginState(StateManager& manager) : stateManager(manager), m_isUsernameInputFieldActive(false), m_isPasswordInputFieldActive(false)
{
	m_font.loadFromFile("Assets/Fonts/Arial.TTF");

    m_loginText.setFont(m_font);
    m_loginText.setString("Login");
    m_loginText.setCharacterSize(30);
    m_loginText.setPosition(0,0);


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
        else if (event.key.code == sf::Keyboard::Escape) {
            stateManager.PopState(window);
        }
    }
}

void LoginState::Update(sf::RenderWindow& window)
{

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);



    m_textEffectTime += clock.restart().asSeconds();

    if (m_textEffectTime >= 0.5)
    {
        m_showCursor = !m_showCursor;
        m_textEffectTime = 0.0f;
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
    m_submitButton.setFillColor(sf::Color::Black);
}

void LoginState::Draw(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);

    window.draw(m_loginText);
    window.draw(m_usernameText);
    window.draw(m_passwordText);
    window.draw(m_usernameInputField);
    window.draw(m_passwordInputField);
    window.draw(m_usernameInputText);
    window.draw(m_passwordInputText);
    window.draw(m_submitButton);
    window.draw(m_submitButtonText);

    window.display();
}

sf::Vector2f LoginState::GetResolution()
{
	return m_windowResolution;
}
