#include "EnemyTypes.h"

Ground_Scorpion::Ground_Scorpion() : Enemy(300, 100, "Assets/Textures/Enemies/Ground/Spritesheets/Scorpion.png", std::map<std::string, int> {{"bottom", 8}, { "top",8 }, { "left", 8 }, {"right", -1}},sf::Vector2i(64,64))
{
}

Ground_Leafbug::Ground_Leafbug() : Enemy(100, 50, "Assets/Textures/Enemies/Ground/Spritesheets/Leafbug.png", std::map<std::string, int> {{"bottom", 8}, { "top",8 }, { "left", -1 }, { "right", 8 }}, sf::Vector2i(64, 64))
{
}

Ground_Magma_Crab::Ground_Magma_Crab() : Enemy(400, 75, "Assets/Textures/Enemies/Ground/Spritesheets/Magma Crab.png", std::map<std::string, int> {{"bottom", 8}, { "top",8 }, { "left", 8 }, { "right", -1 }}, sf::Vector2i(64, 64))
{
}

Flying_Clampbeetle::Flying_Clampbeetle() : Enemy(200, 125, "Assets/Textures/Enemies/Flying/Spritesheets/Clampbeetle.png", std::map<std::string, int> {{"bottom", 8}, { "top",8 }, { "left", 8 }, { "right", -1 }}, sf::Vector2i(64, 64))
{
}

Flying_Locust::Flying_Locust() : Enemy(175, 150, "Assets/Textures/Enemies/Flying/Spritesheets/Flying Locust.png", std::map<std::string, int> {{"bottom", 8}, { "top",8 }, { "left", -1 }, { "right", 8 }}, sf::Vector2i(64, 64))
{
}

Flying_Voidbutterfly::Flying_Voidbutterfly() : Enemy(150, 175, "Assets/Textures/Enemies/Flying/Spritesheets/Voidbutterfly.png", std::map<std::string, int> {{"bottom", 4}, { "top", 4}, { "left", -1 }, { "right", 4 }}, sf::Vector2i(64, 64))
{
}

//Boss::Boss() : Enemy(5000, 35, 35, sf::Color::Black)
//{
//}