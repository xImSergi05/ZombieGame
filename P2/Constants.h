#pragma once

//Map
const int TILE_SIZE = 50;
const int TILE_TYPES = 4;
const int VERTS_IN_QUAD = 6;

//Player
const float START_SPEED = 200;
const float START_HEALTH = 100;

//Zombies
// Zombie type speed
const float BLOATER_SPEED = 40;
const float CHASER_SPEED = 80;
const float CRAWLER_SPEED = 20;

// Zombie type HP
const float BLOATER_HEALTH = 5;
const float CHASER_HEALTH = 1;
const float CRAWLER_HEALTH = 3;

// Zombie speed variation
const int MAX_VARRIANCE = 30;
const int OFFSET = 101 - MAX_VARRIANCE;

//Pickups

//Value for health pickups
const int HEALTH_START_VALUE = 50;
const int AMMO_START_VALUE = 12;
const int START_WAIT_TIME = 10;
const int START_SECONDS_TO_LIVE = 5;


