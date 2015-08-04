#ifndef FIREBALL_INCLUDE_H
#define FIREBALL_INCLUDE_H

#include <genesis.h>

#include "ObjectStruct.h"

u16 FireballCreate(s16 x, s16 y, s16 speedx, s16 speedy, u16 angle);
void FireballUpdate(ObjectStruct* fireballObject);
void FireballDestroy(ObjectStruct* fireballObject);
void FireballDraw(ObjectStruct* fireballObject);
void FireballCollide(ObjectStruct* fireballObject, ObjectStruct* collidedObject);

#endif
