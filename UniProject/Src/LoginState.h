#pragma once
#include "StateManager.h"
class LoginState : public State
{
private:
	StateManager& stateManager;

	const sf::Vector2f m_windowResolution = sf::Vector2f(800, 600);

	sf::Font m_font;

	sf::Text m_returnButton;
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

	bool& m_isLogined;

	sf::Text m_message;
	bool m_isMessageDisplayed;
	float m_messageTimer;
	float m_smallTimer;
public:
	LoginState(StateManager& manager, bool& isLogined);

	void HandleEvents(sf::RenderWindow& window) override;
	void Update(sf::RenderWindow& window) override; 
	void Draw(sf::RenderWindow& window) override;

	sf::Vector2f GetResolution() override;
};

