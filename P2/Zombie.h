#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Constants.h"

using namespace sf;

class Zombie
{
private:
	// Zombie Position
	Vector2f m_Position;
	Texture m_Texture;

	// A sprite for the zombie
	Sprite m_Sprite;

	// Zombie speed
	float m_Speed;

	// Zombie Health Points
	float m_Health;

	// Zombie status
	bool m_Alive;

	// Zombie value
	int m_valueZombie;
	
public:
	// Constructor
	Zombie();
	// Handle when a bullet hits a zombie
	bool hit();

	// Find out if the zombie is alive
	bool isAlive();

	// Spawn a new zombie
	void spawn(float startX, float startY, int type, int seed);

	// Return a rectangle that is the position in the world
	FloatRect getPosition();

	// Get a copy of the sprite to draw
	Sprite getSprite();

	// Update the zombie each frame
	void update(float elapsedTime, Vector2f playerLocation);

	// Get zombie's value
	int GetValueZombie();
	
};

