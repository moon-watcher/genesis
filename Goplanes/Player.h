#ifndef PLAYER_INCLUDE_H
#define PLAYER_INCLUDE_H

#include "ObjectStruct.h"

#define AI_STATE_FLYING                     0
#define AI_STATE_CHARGING_AFTERBURNERS      1
#define AI_STATE_AFTERBURNERS               2
#define AI_STATE_FALLING                    3
#define AI_STATE_DEAD                       4
#define AI_WAITFOR_LEVEL_RESTART            5
#define AI_STATE_DEBUG                      6

#define WEAPON_BULLET       0
#define WEAPON_FIREBALL     1

void Player_SetupForGame();
void Player_SetupForLevel();
void Player_SetupForSection();
void Player_SetupForSectionAfterDeath();

void Player_StartDebugMovement();
void Player_EndDebugMovement();

extern ObjectStruct* playerObject;

typedef struct
{
    u16 frameCounter; // used to determine the spriteIndex to use when rotating the plane.
    u16 numCoins;
    u16 lives;
    u16 afterBurnerChargeUpTimer;
    u16 afterburnerTimer;
    u16 playerColliding;
    u16 currentWeapon;
} PlayerDataStruct;


extern PlayerDataStruct playerData;

#endif
