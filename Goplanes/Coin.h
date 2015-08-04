#ifndef COIN_INCLUDE_H
#define COIN_INCLUDE_H

#include <genesis.h>

#include "ObjectStruct.h"

u16 CoinCreate(s16 x, s16 y);
void CoinUpdate(ObjectStruct* coinObject);
void CoinDestroy(ObjectStruct* coinObject);
void CoinDraw(ObjectStruct* coinObject);
void CoinCollide(ObjectStruct* coinObject, ObjectStruct* collidedObject);

#endif
