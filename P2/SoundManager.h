#pragma once
#include <SFML/Audio.hpp>
#include <memory>

class SoundManager {
public:
    SoundManager();

    void playShoot();
    void playZombieDeath();
    void playPickup();
    void playPlayerHit();

private:
    //Create buffers that load the sound file
    sf::SoundBuffer m_ShootBuffer;
    sf::SoundBuffer m_ZombieDeathBuffer;
    sf::SoundBuffer m_PickupBuffer;
    sf::SoundBuffer m_PlayerHitBuffer;

    //Create sounds
    std::unique_ptr<sf::Sound> m_ShootSound;
    std::unique_ptr<sf::Sound> m_ZombieDeathSound;
    std::unique_ptr<sf::Sound> m_PickupSound;
    std::unique_ptr<sf::Sound> m_PlayerHitSound;
};


