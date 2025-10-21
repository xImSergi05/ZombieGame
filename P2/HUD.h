#pragma once
#include <sstream>
#include <SFML/Graphics.hpp>

using namespace sf;
class HUD
{
private:
	// For the home/game over screen
	Sprite spriteGameOver;

	// Create a sprite for the ammo icon
	Sprite spriteAmmoIcon;

	// Load the font
	Font font;

	// Paused
	Text pausedText;

	// Game Over
	Text gameOverText;

	// Levelling up
	Text levelUpText;

	// Ammo
	Text ammoText;

	// Score
	Text scoreText;

	// Hi Score
	Text hiScoreText;

	// Zombies remaining
	Text zombiesRemainingText;
	Text waveNumberText;

	// Health bar
	RectangleShape healthBar;

	// When did we last update the HUD?
	int framesSinceLastHUDUpdate ;

	// How often (in frames) should we update the HUD
	int fpsMeasurementFrameInterval ;
	std::stringstream levelUpStream;
	std::stringstream s;
	Vector2f m_Position;

public: 
	HUD(); 
	void setHealthBarSize(int health);
	void Update(int bulletsInClip, int bulletsSpare, int score, int hiScore, int wave, int numZombiesAlive);
	Sprite getSpriteGameOver(); 
	Sprite getSpriteAmmoIcon();
	Text getPausedText();
	Text getGameOverText();
	Text getLevelUpText();
	Text getAmmoText();
	Text getScoreText();
	Text getHiScoreText();
	Text getZombiesRemainingText();
	Text getWaveNumberText();
	RectangleShape getHealthBar();



};

