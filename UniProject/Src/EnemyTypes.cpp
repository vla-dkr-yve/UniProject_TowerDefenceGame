#include "EnemyTypes.h"

BasicEnemy::BasicEnemy() : Enemy(200, 100, "Assets/Textures/Enemies/Ground/Spritesheets/Scorpion.png", std::map<std::string, int> {{"bottom", 8}, { "top",8 }, { "left", 8 }, {"right", -1}},sf::Vector2i(64,64))
{
}

FastEnemy::FastEnemy() : Enemy(100, 50, "Assets/Textures/Enemies/Ground/Spritesheets/Leafbug.png", std::map<std::string, int> {{"bottom", 8}, { "top",8 }, { "left", -1 }, { "right", 8 }}, sf::Vector2i(64, 64))
{
}

SlowEnemy::SlowEnemy() : Enemy(350, 35, "Assets/Textures/Enemies/Ground/Spritesheets/Magma Crab.png", std::map<std::string, int> {{"bottom", 8}, { "top",8 }, { "left", 8 }, { "right", -1 }}, sf::Vector2i(64, 64))
{
}

//Boss::Boss() : Enemy(5000, 35, 35, sf::Color::Black)
//{
//}