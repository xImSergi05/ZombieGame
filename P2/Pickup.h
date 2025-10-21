#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

using namespace sf;


class Pickup
{
private:

	// The sprite that represents this pickup
	Texture m_Texture;
	Sprite m_Sprite;
	Vector2f m_Position;
	// The arena it exists in
	IntRect m_Arena;

	// How much is this pickup worth?
	int m_Value;
	int offestArea = 50;

	// What type of pickup is this? 
	// 1 = health, 2 = ammo
	int m_Type;

	// Handle spawning and disappearing
	bool m_Spawned;
	float m_SecondsSinceSpawn;
	float m_SecondsSinceDeSpawn;
	float m_SecondsToLive;
	float m_SecondsToWait;

	// Public prototypes go here
public:

	Pickup(int type);

	// Prepare a new pickup
	void setArena(IntRect arena);

	void spawn();

	// Check the position of a pickup
	FloatRect getPosition();

	// Get the sprite for drawing
	Sprite getSprite();

	// Let the pickup update itself each frame
	void update(float elapsedTime);

	// Is this pickup currently spawned?
	bool isSpawned();

	// Get the goodness from the pickup
	int gotIt();

	// Upgrade the value of each pickup
	void upgrade();
};



