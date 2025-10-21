#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

using namespace sf;

class Player
{
private:
	// Player position
	Vector2f m_Position;

	// Player sprite
	Texture m_Texture;
	Sprite m_Sprite;
	
	// Screen resolution
	Vector2f m_Resolution;

	// Arena size
	IntRect m_Arena;

	// Tile size
	int m_TileSize;

	// Player direction
	bool m_UpPressed;
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;

	// player HP
	int m_Health;

	// Player max HP
	int m_MaxHealth;

	// Player last hit
	Time m_LastHit;

	// Speed in pixels per second
	float m_Speed;

public:

	Player();

	// Player spawn
	void spawn(IntRect arena, Vector2f resolution, int tileSize);

	// Handle the player getting hit by a zombie
	bool hit(Time timeHit);

	// How long ago was the player last hit
	Time getLastHitTime();

	// Get player Position
	FloatRect getPosition();

	// Get player center
	Vector2f getCenter();

	// Get where is the player facing
	float getRotation();

	// Send a copy of the sprite to main
	Sprite getSprite();

	// Get player current HP
	int getHealth();

	// Move player
	void moveLeft();

	void moveRight();

	void moveUp();

	void moveDown();

	// Stop the player moving in a specific direction
	void stopLeft();

	void stopRight();

	void stopUp();

	void stopDown();

	// We will call this function once every frame
	void update(float elapsedTime, Vector2i mousePosition);

	// Give player a speed boost
	void upgradeSpeed();

	// Give the player some health
	void upgradeHealth();

	// Increase the maximum amount of health the player can have
	void increaseHealthLevel(int amount);
};



