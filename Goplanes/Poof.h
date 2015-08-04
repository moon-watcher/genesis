#ifndef POOF_INCLUDE_H
#define POOF_INCLUDE_H

#include <genesis.h>

#include "ObjectStruct.h"

u16 PoofCreate(u16 x, u16 y);
void PoofUpdate(ObjectStruct* poofObject);
void PoofDestroy(ObjectStruct* poofObject);
void PoofDraw(ObjectStruct* poofObject);

#endif
