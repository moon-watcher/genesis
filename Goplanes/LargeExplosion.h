#ifndef LARGE_EXPLOSION_INCLUDE_H
#define LARGE_EXPLOSION_INCLUDE_H

#include <genesis.h>

#include "ObjectStruct.h"

u16 LargeExplosionCreate(u16 x, u16 y);
void LargeExplosionUpdate(ObjectStruct* largeExplosionObject);
void LargeExplosionDestroy(ObjectStruct* largeExplosionObject);
void LargeExplosionDraw(ObjectStruct* largeExplosionObject);

#endif
