#include "Tower.h"

Tower::Tower(TowerType type, sf::Vector2f& position):m_position(position)
{
	towerType = type;

	const auto& properties = TowerPropertiesManager::GetStaticProperty(towerType);
	m_fActionCooldown = properties.actionCooldown;
	m_cost = properties.cost;
	m_fRadius = properties.radius;
	m_baseValue = properties.baseValue;

	m_currentValue = m_baseValue;

	m_texture.loadFromFile("Assets/Textures/Towers/Towers-100px.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(properties.texturePosition, sf::Vector2i(100,100)));
	m_sprite.setScale(0.64, 0.64);
	m_sprite.setPosition(m_position);

	m_ftimer = 0.0f;

	m_bIsActionAreaActive = false;

	m_ActionArea.setRadius(m_fRadius);
	m_ActionArea.setOrigin(sf::Vector2f(m_ActionArea.getRadius() - 32, m_ActionArea.getRadius() - 32));
	m_ActionArea.setPosition(m_sprite.getPosition());
	m_ActionArea.setFillColor(sf::Color(255, 255, 255, 32));
	m_ActionArea.setOutlineThickness(1);
	m_ActionArea.setOutlineColor(sf::Color::Black);

	m_buildingLine.setSize(sf::Vector2f(64, 5));
	m_buildingLine.setPosition(sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y - m_buildingLine.getSize().y * 2));
	m_buildingLine.setFillColor(sf::Color::Blue);

	m_buildingBackground.setSize(sf::Vector2f(64, 5));
	m_buildingBackground.setPosition(sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y - m_buildingBackground.getSize().y * 2));

	m_fBuildTime = 3.0f;
	m_fCurrentTime = m_fBuildTime;
	m_bIsBuild = true;
}

void Tower::Build(float deltaTime)
{
	m_fCurrentTime -= deltaTime;
	if (m_fCurrentTime <= 0)
	{
		m_bIsBuild = false;
	}
	else {
		float buildPercentage = m_fCurrentTime / m_fBuildTime;

		m_buildingLine.setSize(sf::Vector2f(m_buildingBackground.getSize().x * buildPercentage, m_buildingBackground.getSize().y));
	}
}

void Tower::Draw(sf::RenderWindow& window)
{
	if (m_bIsBuild)
	{
		window.draw(m_buildingLine);
	}
	if (!m_bIsBuild)
	{
		window.draw(m_sprite);
	}
	if (m_bIsActionAreaActive)
	{
		window.draw(m_ActionArea);
	}
}

void Tower::AddBuff(Buff buff)
{
	m_activeBuffs.push_back(buff);
	UpdateValue();
}

void Tower::RemoveBuffBySource(void* source)
{
	m_activeBuffs.erase(std::remove_if(m_activeBuffs.begin(), m_activeBuffs.end(),
		[source](const Buff& buff) {return buff.source == source; }), m_activeBuffs.end());
	UpdateValue();
}

void Tower::UpdateValue()
{
	m_currentValue = m_baseValue;
	for (auto buff: m_activeBuffs)
	{
		m_currentValue += buff.value;
	}
}

void Tower::UpdateBaseValue(int value)
{
	m_baseValue += value;
	UpdateValue();
}
