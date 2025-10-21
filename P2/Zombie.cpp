#include "zombie.h"
#include "Constants.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>

using namespace std;

Zombie::Zombie() :
	m_Texture(),
	m_Sprite(m_Texture)
{
	// Set the zombie to be alive when it is created
	m_Alive = true;
}

void Zombie::spawn(float startX, float startY, int type, int seed)
{
	switch (type)
	{
	case 0:
		// Bloater
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/bloater.png"));
		m_Speed = 40;
		m_Health = 5;
		m_valueZombie = 50;
		break;
	case 1:
		// Chaser
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/chaser.png"));
		m_Speed = 70;
		m_Health = 1;
		m_valueZombie = 10;
		break;
	case 2:
		// Crawler
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/crawler.png"));
		m_Speed = 20;
		m_Health = 3;
		m_valueZombie = 30;
		break;
	}

	// Modify the speed to make the zombie unique
	// Every zombie is unique. Create a speed modifier
	srand((int)time(0) * seed);
	// Somewhere between 80 an 100
	float modifier = (rand() % MAX_VARRIANCE) + OFFSET;
	// Express as a fraction of 1
	modifier /= 100; // Now equals between .7 and 1
	m_Speed *= modifier;
	m_Position.x = startX;
	m_Position.y = startY;
	m_Sprite.setOrigin({ 25, 25 });
	m_Sprite.setPosition(m_Position);
}

bool Zombie::hit()
{
	m_Health--;
	if (m_Health < 0)
	{
		// dead
		m_Alive = false;
		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/blood.png"));
		return true;
	}
	// injured but not dead yet
	return false;
}

bool Zombie::isAlive()
{
	return m_Alive;
}

FloatRect Zombie::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Sprite Zombie::getSprite()
{
	return m_Sprite;
}

void Zombie::update(float elapsedTime, Vector2f playerLocation)
{
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;
	// Updatethe zombieposition variables
	if (playerX > m_Position.x)
	{
		m_Position.x = m_Position.x + m_Speed * elapsedTime;
	}
	if (playerY > m_Position.y)
	{
		m_Position.y = m_Position.y + m_Speed * elapsedTime;
	}
	if (playerX < m_Position.x)
	{
		m_Position.x = m_Position.x - m_Speed * elapsedTime;
	}
	if (playerY < m_Position.y)
	{
		m_Position.y = m_Position.y - m_Speed * elapsedTime;
	}

	// Move the sprite
	m_Sprite.setPosition(m_Position);
	// Face the sprite in the correct direction
	float angle = atan2(playerY - m_Position.y,
		playerX - m_Position.x);
	m_Sprite.setRotation(sf::radians(angle));
}

int Zombie::GetValueZombie() {
	return m_valueZombie;
}