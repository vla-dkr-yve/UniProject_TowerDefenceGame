#pragma once
#include "StateManager.h"
class LoginState : public State
{
private:
	StateManager& stateManager;

	const sf::Vector2f m_windowResolution = sf::Vector2f(800, 600);

	sf::Font m_font;

	sf::Text m_loginText;
	sf::Text m_usernameText;
	sf::Text m_passwordText;
	sf::Text m_usernameInputText;
	sf::Text m_passwordInputText;

	std::string m_usernameInputString;
	std::string m_passwordInputString;

	sf::RectangleShape m_usernameInputField;
	sf::RectangleShape m_passwordInputField;

	bool m_isUsernameInputFieldActive;
	bool m_isPasswordInputFieldActive;

	sf::Text m_submitButtonText;
	sf::RectangleShape m_submitButton;

	sf::Clock clock;

	bool m_showCursor;

	float m_textEffectTime;
public:
	LoginState(StateManager& manager);

	void HandleEvents(sf::RenderWindow& window) override;
	void Update(sf::RenderWindow& window) override; 
	void Draw(sf::RenderWindow& window) override;

	sf::Vector2f GetResolution() override;
};

