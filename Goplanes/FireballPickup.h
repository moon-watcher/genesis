#ifndef FIREBALL_PICKUP_INCLUDE_H
#define FIREBALL_PICKUP_INCLUDE_H

#include <genesis.h>

#include "ObjectStruct.h"

u16 FireballPickupCreate(s16 x, s16 y);
void FireballPickupUpdate(ObjectStruct* fireballPickupObject);
void FireballPickupDestroy(ObjectStruct* fireballPickupObject);
void FireballPickupDraw(ObjectStruct* fireballPickupObject);
void FireballPickupCollide(ObjectStruct* fireballPickupObject, ObjectStruct* collidedObject);

#endif
