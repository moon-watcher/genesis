#ifndef ENEMY_PLANE_INCLUDE_H
#define ENEMY_PLANE_INCLUDE_H

#include <genesis.h>

#include "ObjectStruct.h"

u16 EnemyPlaneCreate(s16 x, s16 y);
void EnemyPlaneUpdate(ObjectStruct* enemyPlaneObject);
void EnemyPlaneDestroy(ObjectStruct* enemyPlaneObject);
void EnemyPlaneDraw(ObjectStruct* enemyPlaneObject);
void EnemyPlaneCollide(ObjectStruct* enemyPlaneObject, ObjectStruct* collidedObject);

#endif
