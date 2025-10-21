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
    sf::SoundBuffer m_ShootBuffer;
    sf::SoundBuffer m_ZombieDeathBuffer;
    sf::SoundBuffer m_PickupBuffer;
    sf::SoundBuffer m_PlayerHitBuffer;


    std::unique_ptr<sf::Sound> m_ShootSound;
    std::unique_ptr<sf::Sound> m_ZombieDeathSound;
    std::unique_ptr<sf::Sound> m_PickupSound;
    std::unique_ptr<sf::Sound> m_PlayerHitSound;
};


