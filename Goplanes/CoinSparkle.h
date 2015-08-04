#ifndef COIN_SPARKLE_INCLUDE_H
#define COIN_SPARKLE_INCLUDE_H

#include <genesis.h>

#include "ObjectStruct.h"

u16 CoinSparkleCreate(s16 x, s16 y);
void CoinSparkleUpdate(ObjectStruct* coinSparkleObject);
void CoinSparkleDestroy(ObjectStruct* coinSparkleObject);
void CoinSparkleDraw(ObjectStruct* coinSparkleObject);
void CoinSparkleCollide(ObjectStruct* coinSparkleObject, ObjectStruct* collidedObject);

#endif
