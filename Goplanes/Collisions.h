#ifndef COLLISIONS_INCLUDE_H
#define COLLISIONS_INCLUDE_H

#include <genesis.h>

#include "ObjectStruct.h"

// tile types
#define TILE_NONE               0
#define TILE_SOLID              1
#define TILE_COIN_TOP_LEFT      2
#define TILE_COIN_TOP_RIGHT     3
#define TILE_COIN_BOTTOM_LEFT   4
#define TILE_COIN_BOTTOM_RIGHT  5
#define TILE_NUM_TYPES          6

#define TILE_DATA_MASK      0xFF00 // retrieve the tile's per-tile type data
#define TILE_VALUE_MASK     0x00FF // retrieve the tile number from the background tile

#define NORMAL_TILE_INDEX_MASK		    0x07FF		// 0000011111111111b
#define SPECIAL_TILE                    (1 << 10)	// 0000010000000000b
#define SPECIAL_TILE_INDEX_MASK			0xF800		// 1111100000000000b
#define SPECIAL_TILE_ARRAY_INDEX_MASK	0x00FF		// 0000000011111111b
#define SPECIAL_TILE_TYPE_MASK			0x0300		// 0000001100000000b

#define COIN_TYPE			0
#define BREAKABLE_ROCK_TYPE 1

// positions are in virtual space.

u16 CollidesWithTile(u16 x, u16 y);
u16 CollidesWithVisibleBreakables(u16 x, u16 y);
u16 TileIsCoin(u16 x, u16 y);
u16 OutOfBounds(s16 x, s16 y);
u16 ObjectIsOffScreen(s16 x, s16 y);
u16 ObjectIsOnScreen(s16 x, s16 y);
u16 SpriteIsOnScreen(s16 x, s16 y, s16 padding);


typedef u16 (*CollisionFunction)(ObjectStruct* firstObject, ObjectStruct* secondObject);

u16 PointSquareCollision(ObjectStruct* firstObject, ObjectStruct* secondObject);
u16 SquareSquareCollision(ObjectStruct* firstObject, ObjectStruct* secondObject);

#endif
