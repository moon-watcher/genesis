#ifndef PLAYER_PHYSICS_INCLUDE_H
#define PLAYER_PHYSICS_INCLUDE_H

#include <genesis.h>

#define PHYSICS_RESULTS_NONE                    0
#define PHYSICS_RESULTS_COLLIDED_WITH_TILE      1
#define PHYSICS_RESULTS_COLLIDED_WITH_BREAKABLE 2

#define FACING_RIGHT            1
#define FACING_DOWN             2
#define FACING_LEFT             4
#define FACING_UP               8

#define FACING_DOWNRIGHT        (FACING_DOWN | FACING_RIGHT)
#define FACING_DOWNLEFT         (FACING_DOWN | FACING_LEFT)
#define FACING_UPRIGHT          (FACING_UP | FACING_RIGHT)
#define FACING_UPLEFT           (FACING_UP | FACING_LEFT)


u16 UpdatePlayerPhysics();

#endif
