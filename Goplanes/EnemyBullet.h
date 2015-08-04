#ifndef ENEMY_BULLET_INCLUDE_H
#define ENEMY_BULLET_INCLUDE_H

#include <genesis.h>

#include "ObjectStruct.h"

u16 EnemyBulletCreate(s16 x, s16 y, s16 speedx, s16 speedy);
void EnemyBulletUpdate(ObjectStruct* enemyBulletObject);
void EnemyBulletDestroy(ObjectStruct* enemyBulletObject);
void EnemyBulletDraw(ObjectStruct* enemyBulletObject);
void EnemyBulletCollide(ObjectStruct* enemyBulletObject, ObjectStruct* collidedObject);

#endif
