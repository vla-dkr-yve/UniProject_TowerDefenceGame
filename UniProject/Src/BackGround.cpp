#include "BackGround.h"

BackGround::BackGround()
{
	m_texture.loadFromFile(m_filePath);
	m_sprite.setTexture(m_texture);
}

void BackGround::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}
