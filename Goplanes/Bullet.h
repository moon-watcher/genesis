#ifndef BULLET_INCLUDE_H
#define BULLET_INCLUDE_H

#include <genesis.h>

#include "ObjectStruct.h"

u16 BulletCreate(s16 x, s16 y, s16 speedx, s16 speedy);
void BulletUpdate(ObjectStruct* bulletObject);
void BulletDestroy(ObjectStruct* bulletObject);
void BulletDraw(ObjectStruct* bulletObject);
void BulletCollide(ObjectStruct* bulletObject, ObjectStruct* collidedObject);

#endif
