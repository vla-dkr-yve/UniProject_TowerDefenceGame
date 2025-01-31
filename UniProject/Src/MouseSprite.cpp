#include "MouseSprite.h"

MouseSprite::MouseSprite()
{
	m_font.loadFromFile("Assets/Fonts/Arial.TTF");
	m_towerDescription.setFont(m_font);
	m_towerDescription.setCharacterSize(20);
	m_descriptionRect.setFillColor(sf::Color(0,0,0,64));
	m_bIsMouseSpriteActive = false;
	m_bIsRadiusvisible = false;
	m_bIsDescriptionVisible = false;
	m_ActionArea.setFillColor(sf::Color(255, 255, 255, 32));
	m_ActionArea.setOutlineThickness(1);
	m_ActionArea.setOutlineColor(sf::Color::Black);
}

void MouseSprite::Update(float deltaTime, GUI& gui, sf::Vector2f& mousePosition,
	Map& map, std::vector <MilitaryTower*> militaryTowers, std::vector <CivilTower*> civilTowers)
{
	if (gui.IsOnTheGui(mousePosition))
	{
		int ChoosenTower = (mousePosition.y - gui.GetRectPositionY()) / (64 + 20);

		if (ChoosenTower < TowerTypeLenght)
		{
			std::string newLine = Math::EditString(TowerPropertiesManager::GetStaticProperty(static_cast<TowerType>(ChoosenTower)).description,
				m_towerDescription.getCharacterSize(), m_descriptionSizeX - 45, m_font);
			m_towerDescription.setString(newLine);
			m_descriptionRect.setSize(sf::Vector2f(m_descriptionSizeX, (Math::NumberOfNewLines(newLine) + 2) * m_towerDescription.getCharacterSize()));
			m_bIsDescriptionVisible = true;
		}
		else if (ChoosenTower == TowerTypeLenght)
		{
			m_towerDescription.setString("Shovel. \nIs used for destroying towers");
			m_descriptionRect.setSize(sf::Vector2f(300, 60));
			m_bIsDescriptionVisible = true;
		}
	}
	else {
		m_bIsDescriptionVisible = false;
	}

	if (m_bIsDescriptionVisible)
	{
		m_towerDescription.setPosition(mousePosition + sf::Vector2f(10,10));
		m_descriptionRect.setPosition(mousePosition);
	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && gui.IsOnTheGui(mousePosition))
	{
		m_bIsShovelActive = false;

		int ChoosenTower = (mousePosition.y - gui.GetRectPositionY()) / (64 + 20);
		m_sprite.setTexture(gui.GetTexture(ChoosenTower));
		m_sprite.setTextureRect(gui.GetTextureRect(ChoosenTower));
		m_sprite.setOrigin(sf::Vector2f(gui.GetTextureRect(ChoosenTower).getSize().x / 2, gui.GetTextureRect(ChoosenTower).getSize().y / 2));
		m_sprite.setScale(gui.GetScale(ChoosenTower));

		m_bIsMouseSpriteActive = true;
		towerType = ChoosenTower;
		
		if (towerType < TowerTypeLenght)
		{
			SetTowerRadius(static_cast<TowerType>(towerType));
		}
		else {
			m_bIsRadiusvisible = false;
			m_bIsShovelActive = true;
		}

		m_ActionArea.setPosition(m_sprite.getPosition());
		m_ActionArea.setOrigin(sf::Vector2f(m_ActionArea.getRadius(), m_ActionArea.getRadius()));
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		m_bIsMouseSpriteActive = false;
		m_bIsRadiusvisible = false;
		m_bIsShovelActive = false;
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
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && tower->GetSprite().getGlobalBounds().contains(mousePosition) && !tower->IsBuilding() && !m_bIsShovelActive){
			tower->SetActionAreaActive();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !tower->GetSprite().getGlobalBounds().contains(mousePosition) && !m_bIsShovelActive) {
			tower->SetActionAreaUnActive();
		}
	}
	for (auto tower : civilTowers)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && tower->GetSprite().getGlobalBounds().contains(mousePosition) && !tower->IsBuilding() && !m_bIsShovelActive) {
			tower->SetActionAreaActive();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !tower->GetSprite().getGlobalBounds().contains(mousePosition) && !m_bIsShovelActive) {
			tower->SetActionAreaUnActive();
		}
	}
}

void MouseSprite::Draw(sf::RenderWindow& window)
{
	if (m_bIsRadiusvisible)
	{
		window.draw(m_ActionArea);
	}
	if (m_bIsDescriptionVisible)
	{
		window.draw(m_descriptionRect);
		window.draw(m_towerDescription);
	}
	if (m_bIsMouseSpriteActive)
	{
		window.draw(m_sprite);
	}
}

void MouseSprite::SetTowerRadius(TowerType type)
{
	m_ActionArea.setRadius(TowerPropertiesManager::GetStaticProperty(type).radius);
	m_bIsRadiusvisible = true;
}
