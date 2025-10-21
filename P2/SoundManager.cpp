#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager()
{
    if (!m_ShootBuffer.loadFromFile("sound/shoot.mp3"))
        std::cerr << "Error cargando shoot.mp3\n";
    if (!m_ZombieDeathBuffer.loadFromFile("sound/zombie_death.mp3"))
        std::cerr << "Error cargando zombie_death.wav\n";
    if (!m_PickupBuffer.loadFromFile("sound/pickup.mp3"))
        std::cerr << "Error cargando pickup.wav\n";
    if (!m_PlayerHitBuffer.loadFromFile("sound/player_hit.mp3"))
        std::cerr << "Error cargando player_hit.wav\n";

    // Create the Sounds(objects) after loading the buffers
    m_ShootSound = std::make_unique<sf::Sound>(m_ShootBuffer);
    m_ZombieDeathSound = std::make_unique<sf::Sound>(m_ZombieDeathBuffer);
    m_PickupSound = std::make_unique<sf::Sound>(m_PickupBuffer);
    m_PlayerHitSound = std::make_unique<sf::Sound>(m_PlayerHitBuffer);
}


void SoundManager::playShoot() { if (m_ShootSound) m_ShootSound->play(); }
void SoundManager::playZombieDeath() { if (m_ZombieDeathSound) m_ZombieDeathSound->play(); }
void SoundManager::playPickup() { if (m_PickupSound) m_PickupSound->play(); }
void SoundManager::playPlayerHit() { if (m_PlayerHitSound) m_PlayerHitSound->play(); }
