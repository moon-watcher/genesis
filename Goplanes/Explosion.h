#ifndef EXPLOSION_INCLUDE_H
#define EXPLOSION_INCLUDE_H

#include <genesis.h>

#include "ObjectStruct.h"

u16 ExplosionCreate(u16 x, u16 y);
void ExplosionUpdate(ObjectStruct* explosionObject);
void ExplosionDestroy(ObjectStruct* explosionObject);
void ExplosionDraw(ObjectStruct* explosionObject);

#endif
