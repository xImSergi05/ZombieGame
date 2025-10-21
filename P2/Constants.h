#pragma once

//Mapa
const int TILE_SIZE = 50;
const int TILE_TYPES = 4;
const int VERTS_IN_QUAD = 6;

//Jugador
const float START_SPEED = 200;
const float START_HEALTH = 100;

//Zombies
// How fast is each zombie type?
const float BLOATER_SPEED = 40;
const float CHASER_SPEED = 80;
const float CRAWLER_SPEED = 20;
// How tough is each zombie type
const float BLOATER_HEALTH = 5;
const float CHASER_HEALTH = 1;
const float CRAWLER_HEALTH = 3;
// Make each zombie vary its speed slightly
const int MAX_VARRIANCE = 30;
const int OFFSET = 101 - MAX_VARRIANCE;

//Pickups
//Start value for health pickups
const int HEALTH_START_VALUE = 50;
const int AMMO_START_VALUE = 12;
const int START_WAIT_TIME = 10;
const int START_SECONDS_TO_LIVE = 5;


