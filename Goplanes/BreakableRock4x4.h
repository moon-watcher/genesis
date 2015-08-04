#ifndef BREAKABLE_ROCK_4X4_INCLUDE_H
#define BREAKABLE_ROCK_4X4_INCLUDE_H

#include <genesis.h>

#include "ObjectStruct.h"

u16 BreakableRock4x4Create(s16 x, s16 y);
void BreakableRock4x4Update(ObjectStruct* breakableRock4x4Object);
void BreakableRock4x4Destroy(ObjectStruct* breakableRock4x4Object);
void BreakableRock4x4Draw(ObjectStruct* breakableRock4x4Object);
void BreakableRock4x4Collide(ObjectStruct* breakableRock4x4Object, ObjectStruct* collidedObject);

#endif
