#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "TextureHolder.h"
#include "Zombie.h"
#include "Bullet.h"
#include "Pickup.h"
#include "HUD.h"
#include "SoundManager.h"

using namespace sf;

class Game
{
	public:
		Game();
		void run();
private:

		// The game will always be in one of four states
		enum class StateGame { PAUSED, LEVELING_UP, GAME_OVER, PLAYING };
		// Start with the GAME_OVER state
		StateGame Gstate;
		Vector2f resolution;
		RenderWindow window;
		View mainView;
		View miniMapView;

		// Here is our clock for timing everything
		Clock clock;
		// How long has the PLAYING state been active
		Time gameTimeTotal;

		// Where is the mouse in relation to world coordinates
		Vector2f mouseWorldPosition;

		// Where is the mouse in relation to screen coordinates
		Vector2i mouseScreenPosition;

		// Create an instance of the Player class
		Player player;
		Texture playerTexture;

		// The boundaries of the arena
		IntRect arena;

		// Create the background
		VertexArray background;
		// Load the texture for our background vertex array
		Texture textureBackground;

		TextureHolder holder;
		
		// Prepare for a horde of zombies
		int numZombies;
		int numZombiesAlive;
		Zombie* zombies;

		Bullet bullets[100];
		int currentBullet = 0;
		int bulletsSpare = 24;
		int bulletsInClip = 6;
		int clipSize = 6;
		float fireRate = 1;
		// When was the fire button last pressed?
		Time lastPressed;
		
		Sprite spriteCrosshair;

		// Create a couple of pickups
		/*Pickup healthPickup(1);
		Pickup ammoPickup(2);*/
		Pickup healthPickup;
		Pickup ammoPickup;

		int score;
		int hiScore;

		View hudView;
		HUD hud;

		SoundManager m_SoundManager;
		
		// Creating a randomly generated scrolling background
		int createBackground(VertexArray& rVA, IntRect arena);
		void update();
		void render();
		void processEvents();
		Zombie* createHorde(int numZombies, IntRect arena);
	
};
