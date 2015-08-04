#ifndef PHYSICS_INCLUDE_H
#define PHYSICS_INCLUDE_H

#include <genesis.h>

#include "TileMap.h"

typedef u16 (*collidesWithTileFunctionType)(u16 x, u16 y);

void SetupPhysics(const TileMap* tileMap);

extern collidesWithTileFunctionType collidesWithTile;

#endif
