#include "HUD.h"
#include "TextureHolder.h"
HUD::HUD() :
	 spriteGameOver(TextureHolder::GetTexture("graphics/background.png")),
	 spriteAmmoIcon(TextureHolder::GetTexture("graphics/ammo_icon.png")),
	 font("fonts/LoveDays-2v7Oe.ttf"),
	 pausedText(font),
	 gameOverText(font),
	 levelUpText(font),
	 ammoText(font),
	 scoreText(font),
	 hiScoreText(font),
	 zombiesRemainingText(font),
	 waveNumberText(font)

{

	//spriteGameOver.setTexture(textureGameOver);
	spriteGameOver.setPosition({ 0, 0 });
	//spriteAmmoIcon.setTexture(textureAmmoIcon);
	spriteAmmoIcon.setPosition({ 20, 980 });
	pausedText.setCharacterSize(155);
	pausedText.setFillColor(Color::White);
	pausedText.setPosition({ 400, 400 });
	pausedText.setString("Press Enter \nto continue");
	gameOverText.setCharacterSize(125);
	gameOverText.setFillColor(Color::White);
	gameOverText.setPosition({ 250, 850 });
	gameOverText.setString("Press Enter to play");
	levelUpText.setCharacterSize(80);
	levelUpText.setFillColor(Color::White);
	levelUpText.setPosition({ 150, 250 });
	levelUpStream <<
		"1- Increased rate of fire" <<
		"\n2- Increased clip size(next reload)" <<
		"\n3- Increased max health" <<
		"\n4- Increased run speed" <<
		"\n5- More and better health pickups" <<
		"\n6- More and better ammo pickups";
	levelUpText.setString(levelUpStream.str());
	ammoText.setCharacterSize(55);
	ammoText.setFillColor(Color::White);
	ammoText.setPosition({ 200, 980 });
	scoreText.setCharacterSize(55);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition({ 20, 0 });
	hiScoreText.setCharacterSize(55);
	hiScoreText.setFillColor(Color::White);
	hiScoreText.setPosition({ 1400, 0 });
	s << "Hi Score:" << 0;
	hiScoreText.setString(s.str());
	zombiesRemainingText.setCharacterSize(55);
	zombiesRemainingText.setFillColor(Color::White);
	zombiesRemainingText.setPosition({ 1500, 980 });
	zombiesRemainingText.setString("Zombies: 100");
	waveNumberText.setCharacterSize(55);
	waveNumberText.setFillColor(Color::White);
	waveNumberText.setPosition({ 1250, 980 });
	waveNumberText.setString("Wave: 0");
	healthBar.setFillColor(Color::Red);
	healthBar.setPosition({ 450, 980 });

	// When did we last update the HUD?
	framesSinceLastHUDUpdate = 0;

	// How often (in frames) should we update the HUD
	fpsMeasurementFrameInterval = 1000;

}

void HUD::setHealthBarSize(int health)
{
	// size up the health bar
	m_Position.x = health * 3;
	m_Position.y = 70;
	healthBar.setSize(m_Position);
}
void HUD::Update(int bulletsInClip, int bulletsSpare, int score, int hiScore, int wave, int numZombiesAlive)
{
	// Increment the number of frames since the last HUD calculation
	framesSinceLastHUDUpdate++;
	// Calculate FPS every fpsMeasurementFrameInterval frames
	if (framesSinceLastHUDUpdate > fpsMeasurementFrameInterval)
	{

		// Update game HUD text
		std::stringstream ssAmmo;
		std::stringstream ssScore;
		std::stringstream ssHiScore;
		std::stringstream ssWave;
		std::stringstream ssZombiesAlive;

		// Update the ammo text
		ssAmmo << bulletsInClip << "/" << bulletsSpare;
		ammoText.setString(ssAmmo.str());

		// Update the score text
		ssScore << "Score:" << score;
		scoreText.setString(ssScore.str());

		// Update the high score text
		ssHiScore << "Hi Score:" << hiScore;
		hiScoreText.setString(ssHiScore.str());

		// Update the wave
		ssWave << "Wave:" << wave;
		waveNumberText.setString(ssWave.str());

		// Update the high score text
		ssZombiesAlive << "Zombies:" << numZombiesAlive;
		zombiesRemainingText.setString(ssZombiesAlive.str());

		framesSinceLastHUDUpdate = 0;
	}// End HUD update
}
Sprite HUD::getSpriteGameOver()
{
	return spriteGameOver;
}
Sprite HUD::getSpriteAmmoIcon(){
	return spriteAmmoIcon;
}
Text HUD::getPausedText(){
	return pausedText;
}
Text HUD::getGameOverText(){
	return gameOverText;
}
Text HUD::getLevelUpText(){
	return levelUpText;
}
Text HUD::getAmmoText(){
	return ammoText;
}
Text HUD::getScoreText(){
	return scoreText;
}
Text HUD::getHiScoreText(){
	return hiScoreText;
}
Text HUD::getZombiesRemainingText(){
	return zombiesRemainingText;
}
Text HUD::getWaveNumberText(){
	return waveNumberText;
}
RectangleShape HUD::getHealthBar(){
	return healthBar;
}