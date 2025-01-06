#include "Hero.h"

Hero::Hero() : m_hp(m_maxHp), m_damage(25), m_stamina(100), m_animationTimer(0), m_isActive(true), m_speed(175),
m_speedMultiplier(1), m_isAttacking(false), m_isDefending(false), m_currentAttack(0), m_totalAttack(0)
{
	m_texture.loadFromFile("Assets/Textures/Hero/Knight/SpriteSheet.png");
	m_sprite.setTexture(m_texture);
	//m_sprite.setTextureRect(sf::IntRect(0 + m_offsetX, 0 + m_offsetY, m_width, m_height));
	m_sprite.setTextureRect(sf::IntRect(0 + m_offsetX, 0 + m_offsetY, m_width, m_height));
	m_sprite.setScale(1.5, 1.5);

	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);
	m_sprite.setPosition(sf::Vector2f(28 * 64, 9 * 64));

	m_currentState = "IDLE";

	m_currentSide = 'l';
	m_sprite.scale(-1, 1);
	m_isRotated = true;

	m_animationNum = { {"ATTACK1", 6},{"ATTACK2", 5},
		{"ATTACK3", 6}, {"DEATH", 12}, {"DEFEND", 6},
		{"HURT", 4}, {"IDLE", 7}, {"RUN", 8}, {"WALK", 8} };

	m_animationPosition = { {"ATTACK1", 0},{"ATTACK2", 1},
		{"ATTACK3", 2}, {"DEATH", 3}, {"DEFEND", 4},
		{"HURT", 5}, {"IDLE", 6}, {"RUN", 7}, {"WALK", 8} };

	hitbox.setSize(sf::Vector2f(m_hitboxWidth, m_hitboxHeight));
	hitbox.setFillColor(sf::Color(255, 255, 255, 0));
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(1);
	hitbox.setScale(m_sprite.getScale());
	hitbox.setPosition(sf::Vector2f(m_sprite.getPosition().x + hitbox.getGlobalBounds().getSize().x / 2, m_sprite.getPosition().y - hitbox.getGlobalBounds().getSize().y / 2));
}

void Hero::Animator(float deltaTime)
{
	if (m_animationTimer > 0.1)
	{
		m_currentAnimation++;
		if (m_currentAnimation >= m_animationNum[m_currentState])
		{
			if (m_isAttacking)
			{
				m_currentAttack++;
				if (m_currentAttack > m_totalAttack)
				{
					m_currentAttack = 0;
					m_totalAttack = 0;
					m_isAttacking = false;
				}
				else {
					ChangeState("ATTACK");
				}
			}
			if (m_isDefending)
			{
				m_isDefending = false;
			}
			m_currentAnimation = 0;
		}
		m_animationTimer = 0.0f;
	}

	m_sprite.setTextureRect(sf::IntRect(m_currentAnimation * (m_offsetX * 3) + m_offsetX - 8, m_animationPosition[m_currentState] * 84 + m_offsetY, m_width, m_height));
}

void Hero::Move(float deltaTime, char side)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		ChangeState("RUN");
	}
	else {
		ChangeState("WALK");
	}
	
	sf::Vector2f direction;

	switch (side)
	{
	case 'w':
		direction = { 0,-1 };
		break;
	case 's':
		direction = { 0,1 };
		break;
	case 'a':
		direction = { -1,0 };
		break;
	case 'd':
		direction = { 1,0 };
		break;
	default:
		break;
	}

	m_sprite.setPosition(m_sprite.getPosition() + direction * deltaTime * m_speed * m_speedMultiplier);
}

void Hero::Attack()
{
	m_totalAttack++;

	if (m_totalAttack > 3)
	{
		m_totalAttack = 3;
	}

	if (m_currentAttack == 0)
	{
		m_currentAttack = 1;
	}

	ChangeState("ATTACK");
}

void Hero::Defence()
{
}

void Hero::ChangeState(std::string newState)
{
	if (newState == "ATTACK")
	{
		newState += std::to_string(m_currentAttack);
	}


	if (m_currentState != newState)
	{
		if (newState == "ATTACK1" || newState == "ATTACK2" || newState == "ATTACK3")
		{
			m_isAttacking = true;
		}
		else if (newState == "DEFEND")
		{
			m_isDefending = true;
		}

		if (!(m_currentState == "WALK" && newState == "RUN") || !(m_currentState == "RUN" && newState == "WALK"))
		{
			m_currentAnimation = 0;
		}
		m_currentState = newState;
	}
}

void Hero::Update(float deltaTime)
{
	m_animationTimer += deltaTime;

	if (m_currentState == "RUN")
	{
		m_speedMultiplier = 2;
	}
	else {
		m_speedMultiplier = 1;
	}

	bool isMoving = false;

	if (!m_isAttacking && !m_isDefending)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			m_currentSide = 'l';
			if (!m_isRotated)
			{
				m_sprite.scale(-1, 1);
				m_isRotated = true;
			}

			isMoving = true;
			Move(deltaTime, 'a');
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_currentSide = 'r';
			if (m_isRotated)
			{
				m_sprite.scale(-1, 1);
				m_isRotated = false;
			}

			isMoving = true;
			Move(deltaTime, 'd');
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			isMoving = true;
			Move(deltaTime, 'w');
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			isMoving = true;
			Move(deltaTime, 's');
		}
		if (!isMoving)
		{
			m_currentState = "IDLE";
		}
	}

	/*if (event.type == event.MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			Attack();
		}
	}


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		Attack();
	}*/


	Animator(deltaTime);

	hitbox.setPosition(sf::Vector2f(m_sprite.getPosition().x + hitbox.getGlobalBounds().getSize().x / 2, m_sprite.getPosition().y - hitbox.getGlobalBounds().getSize().y / 2));
}

void Hero::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
	window.draw(hitbox);
}
