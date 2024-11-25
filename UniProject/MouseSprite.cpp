#include "MouseSprite.h"

MouseSprite::MouseSprite()
{
	m_texture.loadFromFile("Assets/Textures/Towers/Towers-100px.png");
	m_sprite.setTexture(m_texture);
	m_bIsMouseSpriteActive = false;
	m_bIsRadiusvisible = false;

	m_ActionArea.setFillColor(sf::Color(255, 255, 255, 32));
	m_ActionArea.setOutlineThickness(1);
	m_ActionArea.setOutlineColor(sf::Color::Black);
}

void MouseSprite::Update(float deltaTime, GUI& gui, sf::Vector2f& mousePosition,
	Map& map, sf::Event event, std::vector <MilitaryTower*> militaryTowers, std::vector <CivilTower*> civilTowers)
{
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && gui.IsOnTheGui(mousePosition))
	{
		int ChoosenTower = (mousePosition.y - gui.GetRectPositionY()) / 64;

		m_sprite.setTextureRect(gui.GetTextureRect(ChoosenTower));
		m_sprite.setOrigin(sf::Vector2f(gui.GetTextureRect(ChoosenTower).getSize().x / 2, gui.GetTextureRect(ChoosenTower).getSize().y / 2));
		m_sprite.setScale(sf::Vector2f(0.64,0.64));

		m_bIsMouseSpriteActive = true;

		towerType = ChoosenTower;

		switch (towerType)
		{
		case Research:
			m_ActionArea.setRadius(0.0f);
			m_bIsRadiusvisible = true;
			break;
		case Factory:
			m_ActionArea.setRadius(150.0f);
			m_bIsRadiusvisible = true;
			break;
		case Housing:
			m_ActionArea.setRadius(150.0f);
			m_bIsRadiusvisible = true;
			break;
		case BasicMillitaryTower:
			m_ActionArea.setRadius(150.0f);
			m_bIsRadiusvisible = true;
			break;
		case UpdatedMillitaryTower:
			m_ActionArea.setRadius(125.0f);
			m_bIsRadiusvisible = true;
			break;
		case ScatterMillitaryTower:
			m_ActionArea.setRadius(125.0f);
			m_bIsRadiusvisible = true;
			break;
		default:
			break;
		}

		m_ActionArea.setPosition(m_sprite.getPosition());
		m_ActionArea.setOrigin(sf::Vector2f(m_ActionArea.getRadius(), m_ActionArea.getRadius()));
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		m_bIsMouseSpriteActive = false;
		m_bIsRadiusvisible = false;
	}
	if (m_bIsMouseSpriteActive)
	{
		m_sprite.setPosition(mousePosition);
	}
	if (m_bIsRadiusvisible)
	{
		m_ActionArea.setPosition(mousePosition);
	}

	for (auto tower: militaryTowers)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && tower->GetSprite().getGlobalBounds().contains(mousePosition) && !tower->IsBuilding()){
			tower->SetActionAreaActive();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !tower->GetSprite().getGlobalBounds().contains(mousePosition)) {
			tower->SetActionAreaUnActive();
		}
	}
	for (auto tower : civilTowers)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && tower->GetSprite().getGlobalBounds().contains(mousePosition) && !tower->IsBuilding()) {
			tower->SetActionAreaActive();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !tower->GetSprite().getGlobalBounds().contains(mousePosition)) {
			tower->SetActionAreaUnActive();
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && gui.IsOnTheGui(mousePosition))
	{
		int ChoosenTower = (mousePosition.y - gui.GetRectPositionY()) / 64;
		m_sprite.setTextureRect(gui.GetTextureRect(ChoosenTower));
		m_bIsMouseSpriteActive = true;
		towerType = ChoosenTower;
	}
}

void MouseSprite::Draw(sf::RenderWindow& window)
{
	if (m_bIsRadiusvisible)
	{
		window.draw(m_ActionArea);
	}
	if (m_bIsMouseSpriteActive)
	{
		window.draw(m_sprite);
	}
}
