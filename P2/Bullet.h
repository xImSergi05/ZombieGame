#pragma once
#include <SFML/Graphics.hpp>
//#include "definicions.h"

using namespace sf;

class Bullet
{
private:
	// Bullet position
	Vector2f m_Position;

	// What each bullet looks like
	RectangleShape m_BulletShape;

	// Is this bullet currently in the air
	bool m_InFlight = false;

	// Bullet speed
	float m_BulletSpeed = 1000;


	// Horizontally and vertically each frame?
	// These values will be derived from m_BulletSpeed
	float m_BulletDistanceX;
	float m_BulletDistanceY;

	// Bullet directions
	float m_XTarget;
	float m_YTarget;

	// Some boundaries so the bullet doesn't fly forever
	float m_MaxX;
	float m_MinX;
	float m_MaxY;
	float m_MinY;


public:
	// The constructor
	Bullet();

	// Stop the bullet
	void stop();

	// Returns the value of m_InFlight
	bool isInFlight();

	// Launch a new bullet
	void shoot(float startX, float startY,
		float xTarget, float yTarget);

	// Tell the calling code where the bullet is in the world
	FloatRect getPosition();

	// Return the actual shape (for drawing)
	RectangleShape getShape();

	// Update the bullet each frame
	void update(float elapsedTime);
};