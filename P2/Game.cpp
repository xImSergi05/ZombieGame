#include "Game.h"
#include "Constants.h"
Game::Game() :
	window(VideoMode({ 1920,1080 }), "Zombie Arena", State::Fullscreen)
	, mainView(FloatRect({ 0, 0 }, { 1920,1080 }))
	, hudView(FloatRect({ 0, 0 }, { 1920,1080 }))
	, spriteCrosshair(TextureHolder::GetTexture("graphics/crosshair.png"))
	, healthPickup(1)
	, ammoPickup(2)
	, hud()
{

	Gstate = StateGame::GAME_OVER;
	resolution = { 1920,1080 };
	textureBackground = TextureHolder::GetTexture("./graphics/background_sheet2.png");
	currentBullet = 0;
	bulletsSpare = 24;
	bulletsInClip = 6;
	clipSize = 6;
	fireRate = 1;


	spriteCrosshair.setOrigin({ 25, 25 });
}
void Game::run()
{

	//player = new Player(playerTexture);

	// The main game loop
	while (window.isOpen())
	{
		processEvents();
		update();
		render();
	}
	delete[] zombies;

}
void Game::processEvents()
{
	// Handle events
	while (const std::optional event = window.pollEvent())
	{
		// Fire a bullet
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			//if (gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds() > 100 / fireRate && bulletsInClip > 0)
			if (bulletsInClip > 0) {
				// Pass the centre of the player and the centre of the cross-hair to the shoot function
				bullets[currentBullet].shoot(player.getCenter().x, player.getCenter().y, mouseWorldPosition.x, mouseWorldPosition.y);
				m_SoundManager.playShoot();
				currentBullet++;
				if (currentBullet > 99)
				{
					currentBullet = 0;
				}
				lastPressed = gameTimeTotal;
				bulletsInClip--;
			}
		}// End fire a bullet

		if (event->is<sf::Event::Closed>())
		{
			window.close();
		}
		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) window.close();

			// Pause a game while playing
			if (keyPressed->scancode == sf::Keyboard::Scancode::Enter && Gstate == StateGame::PLAYING)
			{
				Gstate = StateGame::PAUSED;
			}
			// Restart while paused
			else if (keyPressed->scancode == sf::Keyboard::Scancode::Enter && Gstate == StateGame::PAUSED)
			{
				Gstate = StateGame::PLAYING;
				// Reset the clock so there isn't a frame jump
				clock.restart();
			}
			// Start a new game while in GAME_OVER state
			else if (keyPressed->scancode == sf::Keyboard::Scancode::Enter && Gstate == StateGame::GAME_OVER)
			{
				Gstate = StateGame::LEVELING_UP;
				currentBullet = 0;
				bulletsSpare = 24;
				bulletsInClip = 6;
				clipSize = 6;
				fireRate = 1;
				score = 0;
			}
			if (Gstate == StateGame::PLAYING)
			{


			}
			// Handle controls while playing
			if (Gstate == StateGame::PLAYING)
			{
				// Handle the pressing and releasing of the WASD keys
				if (keyPressed->scancode == sf::Keyboard::Scancode::W){player.moveUp();}
				else
				{
					player.stopUp();
				}
				if (keyPressed->scancode == sf::Keyboard::Scancode::S)
				{
					player.moveDown();
				}
				else
				{
					player.stopDown();
				}
				if (keyPressed->scancode == sf::Keyboard::Scancode::A)
				{
					player.moveLeft();
				}
				else
				{
					player.stopLeft();
				}
				if (keyPressed->scancode == sf::Keyboard::Scancode::D)
				{
					player.moveRight();
				}
				else
				{
					player.stopRight();
				}
			}
			if (keyPressed->scancode == Keyboard::Scancode::R)
			{
				if (bulletsSpare >= clipSize)
				{
					bulletsInClip = clipSize;
					bulletsSpare -= clipSize;
				}
				else if (bulletsSpare > 0)
				{
					bulletsInClip = bulletsSpare;
					bulletsSpare = 0;
				}
				else
				{
					// Sense munició de reserva
				}
			}


		}
		if (Gstate == StateGame::LEVELING_UP)
		{
			// Prepare thelevel
			// We will modify the next two lines later
			arena.size.x = 500;//arena.width = 500;
			arena.size.y = 500;//arena.height = 500;
			arena.position.x = 0;//arena.left = 0;
			arena.position.y = 0;//arena.top = 0;

			// We will modify this line of code later
			int tileSize = createBackground(background, arena);

			// Spawn the player in the middle of the arena
			player.spawn(arena, resolution, tileSize);

			// Establece el número de zombies
			numZombies = 10;  // Número de zombies a generar
			delete[] zombies;

			// Crea la horda de zombies
			zombies = createHorde(numZombies, arena);
			numZombiesAlive = numZombies;

			// Configure the pick-ups
			healthPickup.setArena(arena);
			ammoPickup.setArena(arena);

			// Reset the clock so there isn't a frame jump
			clock.restart();
			Gstate = StateGame::PLAYING;


		}
	}// End event polling
}
void Game::update()
{

	if (Gstate == StateGame::PLAYING)
	{
		// Update the delta time
		Time dt = clock.restart();
		// Update the total game time
		gameTimeTotal += dt;
		// Make a decimal fraction of 1 from the delta time
		float dtAsSeconds = dt.asSeconds();
		// Where is the mouse pointer
		mouseScreenPosition = Mouse::getPosition(); 
		// Convert mouse position to world coordinates of mainView
		mouseWorldPosition = window.mapPixelToCoords(
			Mouse::getPosition(), mainView);
		spriteCrosshair.setPosition(mouseWorldPosition);

		// Make a note of the players new position
		Vector2f playerPosition(player.getCenter());
		// Make the view centre around the player                   
		mainView.setCenter(player.getCenter());
		miniMapView.setCenter(player.getCenter());

		// Update the player
		player.update(dtAsSeconds, Mouse::getPosition());

		// Update zombies
		for (int i = 0; i < numZombies; i++)
		{
			if (zombies[i].isAlive())
			{
				zombies[i].update(dtAsSeconds, player.getCenter());
			}
		}

		// Dibujar las balas en vuelo
		for (int i = 0; i < 100; i++)
		{
			if (bullets[i].isInFlight())
			{
				bullets[i].update(dtAsSeconds);
			}
		}

		// Update the pickups
		healthPickup.update(dtAsSeconds);
		ammoPickup.update(dtAsSeconds);


		// Collision detection
		// Have any zombies been shot?
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < numZombies; j++)
			{
				if (bullets[i].isInFlight() && zombies[j].isAlive())
				{
					sf::FloatRect bulletsBox = bullets[i].getShape().getGlobalBounds();
					sf::FloatRect zombiesBox = zombies[j].getSprite().getGlobalBounds();
					if (const std::optional intersection = bulletsBox.findIntersection(zombiesBox))
					{
						// Stop the bullet
						bullets[i].stop();
						// Register the hit and see if it was a kill
						if (zombies[j].hit())
						{
							// Not just a hit but a kill too
							score += zombies[j].GetValueZombie();
							if (score >= hiScore)
							{
								hiScore = score;
							}
							numZombiesAlive--;
							m_SoundManager.playZombieDeath();
							// When all the zombies are dead (again)
							if (numZombiesAlive == 0) {
								Gstate = StateGame::LEVELING_UP;
							}
						}
					}
				}
			}
		}// End zombie being shot

		 // Have any zombies touched the player
		sf::FloatRect boundingBox = player.getSprite().getGlobalBounds();
		for (int i = 0; i < numZombies; i++)
		{
			sf::FloatRect zombiesBox = zombies[i].getSprite().getGlobalBounds();
			if (const std::optional intersection = boundingBox.findIntersection(zombiesBox))
			{
				if (zombies[i].isAlive())
				{
					if (player.hit(gameTimeTotal))
					{
						m_SoundManager.playPlayerHit();
					}
					if (player.getHealth() <= 0)
					{
						Gstate = StateGame::GAME_OVER;
					}
				}
			}
		}// End player touched

		// Has the player touched health pickup
		sf::FloatRect healthBox = healthPickup.getSprite().getGlobalBounds();
		if (const std::optional intersection = boundingBox.findIntersection(healthBox))
		{
			if (healthPickup.isSpawned())
			{
				player.increaseHealthLevel(healthPickup.gotIt());
			}
		}
		sf::FloatRect ammoBox = ammoPickup.getSprite().getGlobalBounds();
		if (const std::optional intersection = boundingBox.findIntersection(ammoBox))
		{
			if (ammoPickup.isSpawned())
			{
				bulletsSpare += ammoPickup.gotIt();  // Increase spare ammo
				m_SoundManager.playPickup();
			}
		}

		hud.Update(bulletsInClip, bulletsSpare, score, hiScore, 0, numZombiesAlive);

	}// End updating the scene
}

void Game::render()
{
	
	if (Gstate == StateGame::PLAYING)
	{
		window.clear();

		// set the mainView to be displayed in the window
		// And draw everything related to it
		window.setView(mainView);
		window.setView(miniMapView);
		window.draw(background, &textureBackground);
		// Draw the player
		window.draw(player.getSprite());
		window.draw(spriteCrosshair);
		// Draw the zombies
		for (int i = 0; i < numZombies; i++)
		{
			window.draw(zombies[i].getSprite());

		}

		// Dibujar las balas en vuelo
		for (int i = 0; i < 100; i++)
		{
			if (bullets[i].isInFlight())
			{
				window.draw(bullets[i].getShape());
			}
		}
		// Draw the pick-ups, if currently spawned
		if (ammoPickup.isSpawned())
		{
			window.draw(ammoPickup.getSprite());
		}
		if (healthPickup.isSpawned())
		{
			window.draw(healthPickup.getSprite());
		}
		
		// Switch to the HUD view
		window.setView(hudView);
		// Draw all the HUD elements
		window.draw(hud.getSpriteAmmoIcon());
		window.draw(hud.getAmmoText());
		window.draw(hud.getScoreText());
		window.draw(hud.getHiScoreText());
		window.draw(hud.getHealthBar());
		window.draw(hud.getWaveNumberText());
		window.draw(hud.getZombiesRemainingText());


	}

	if (Gstate == StateGame::LEVELING_UP)
	{
		window.draw(hud.getSpriteGameOver());
		window.draw(hud.getLevelUpText());
	}

	if (Gstate == StateGame::PAUSED)
	{
		window.draw(hud.getPausedText());
	}

	if (Gstate == StateGame::GAME_OVER)
	{
		CircleShape shape(100.f);
		shape.setFillColor(Color::Green);
		window.draw(hud.getSpriteGameOver());
		window.draw(hud.getGameOverText());
		window.draw(hud.getScoreText());
		window.draw(hud.getHiScoreText());
	}

	window.display();
}

int Game::createBackground(VertexArray& rVA, IntRect arena)
{
	// Anything we do to rVA we are actually doing to background (in the main function)
	// How big is each tile/texture
	int worldWidth = arena.size.x / TILE_SIZE;
	int worldHeight = arena.size.y / TILE_SIZE;
	// What type of primitive are we using?
	rVA.setPrimitiveType(sf::PrimitiveType::Triangles);
	// Set the size of the vertex array
	rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);
	// Start at the beginning of the vertex array
	int currentVertex = 0;
	int verticalOffset;
	for (int w = 0; w < worldWidth; w++)
	{
		for (int h = 0; h < worldHeight; h++)
		{
			// Triangle 1: v0, v1, v2
			rVA[currentVertex + 0].position = sf::Vector2f(w * TILE_SIZE, h * TILE_SIZE);
			rVA[currentVertex + 1].position = sf::Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);
			rVA[currentVertex + 2].position = sf::Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);
			
			// Triangle 2: v0, v2, v3
			rVA[currentVertex + 3].position = sf::Vector2f(w * TILE_SIZE, h * TILE_SIZE);
			rVA[currentVertex + 4].position = sf::Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);
			rVA[currentVertex + 5].position = sf::Vector2f((w * TILE_SIZE), (h * TILE_SIZE) + TILE_SIZE);
			// Define the position in the Texture to draw for current quad
			// Either mud, stone, grass or wall
			if (h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth - 1)
			{
				// Triangle 1: v0, v1, v2
				verticalOffset = TILE_TYPES * TILE_SIZE;
			}
			else
			{
				// Use a random floor texture
				srand((int)time(0) + h * w - h);
				int mOrG = (rand() % TILE_TYPES);
				verticalOffset = mOrG * TILE_SIZE;
			}
			// Triangle 1: v0, v1, v2
			rVA[currentVertex + 0].texCoords = sf::Vector2f(0, 0 + verticalOffset);
			rVA[currentVertex + 1].texCoords = sf::Vector2f(TILE_SIZE, 0 + verticalOffset);
			rVA[currentVertex + 2].texCoords = sf::Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
			// Triangle 2: v0, v2, v3
			rVA[currentVertex + 3].texCoords = sf::Vector2f(0, 0 + verticalOffset);
			rVA[currentVertex + 4].texCoords = sf::Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
			rVA[currentVertex + 5].texCoords = sf::Vector2f(0, TILE_SIZE + verticalOffset);
			// Position ready for the next for vertices
			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}
	return TILE_SIZE;
}

Zombie* Game::createHorde(int numZombies, IntRect arena)
{
	Zombie* zombies = new Zombie[numZombies];
	int maxY = arena.size.y - 20;
	int minY = arena.position.y + 20;
	int maxX = arena.size.x - 20;
	int minX = arena.position.x + 20;
	for (int i = 0; i < numZombies; i++)
	{
		// Which side should the zombie spawn
		srand((int)time(0) * i);
		int side = (rand() % 4);
		float x, y;
		switch (side)
		{
		case 0:
			// left
			x = minX;
			y = (rand() % maxY) + minY;
			break;
		case 1:
			// right
			x = maxX;
			y = (rand() % maxY) + minY;
			break;
		}
		// Bloater, crawler or runner
		srand((int)time(0) * i * 2);
		int type = (rand() % 3);
		// Spawn the new zombie into the array
		zombies[i].spawn(x, y, type, i);
	}
	return zombies;
}