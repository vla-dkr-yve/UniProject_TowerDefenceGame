#include "EnemyTypes.h"

//int score, int hp, float speed, int armor, std::string path, std::map<std::string, int> animationNum,sf::Vector2i textureSize, int scoreMultiplier
Ground_Scorpion::Ground_Scorpion(int scoreMultiplier) : Enemy(30, 35, 90, 25,"Assets/Textures/Enemies/Ground/Spritesheets/Scorpion.png", std::map<std::string, int> {{"bottom", 8}, { "top",8 }, { "left", 8 }, {"right", -1}},sf::Vector2i(64,64), scoreMultiplier)
{
}

Ground_Leafbug::Ground_Leafbug(int scoreMultiplier) : Enemy(10, 30, 100, 10,"Assets/Textures/Enemies/Ground/Spritesheets/Leafbug.png", std::map<std::string, int> {{"bottom", 8}, { "top",8 }, { "left", -1 }, { "right", 8 }}, sf::Vector2i(64, 64), scoreMultiplier)
{
}

Ground_Magma_Crab::Ground_Magma_Crab(int scoreMultiplier) : Enemy(40, 40, 80, 25,"Assets/Textures/Enemies/Ground/Spritesheets/Magma Crab.png", std::map<std::string, int> {{"bottom", 8}, { "top",8 }, { "left", 8 }, { "right", -1 }}, sf::Vector2i(64, 64), scoreMultiplier)
{
}

Flying_Clampbeetle::Flying_Clampbeetle(int scoreMultiplier) : Enemy(20, 35, 125, 5,"Assets/Textures/Enemies/Flying/Spritesheets/Clampbeetle.png", std::map<std::string, int> {{"bottom", 8}, { "top",8 }, { "left", 8 }, { "right", -1 }}, sf::Vector2i(64, 64), scoreMultiplier)
{
}

Flying_Locust::Flying_Locust(int scoreMultiplier) : Enemy(15, 17, 150, 5,"Assets/Textures/Enemies/Flying/Spritesheets/Flying Locust.png", std::map<std::string, int> {{"bottom", 8}, { "top",8 }, { "left", -1 }, { "right", 8 }}, sf::Vector2i(64, 64), scoreMultiplier)
{
}

Flying_Voidbutterfly::Flying_Voidbutterfly(int scoreMultiplier) : Enemy(15, 15, 175, 5,"Assets/Textures/Enemies/Flying/Spritesheets/Voidbutterfly.png", std::map<std::string, int> {{"bottom", 4}, { "top", 4}, { "left", -1 }, { "right", 4 }}, sf::Vector2i(64, 64), scoreMultiplier)
{
}