#ifndef OBJECTSTRUCT_INCLUDE_H
#define OBJECTSTRUCT_INCLUDE_H

#include <genesis.h>
#include <vdp_spr.h>


#define OBJECTSTATE_FREE      0
#define OBJECTSTATE_ACTIVE    1
#define OBJECTSTATE_INACTIVE  2

// This is here for the compiler not to complain of incompatible function types.
// We want to work with a non-void parameter function but we don't know how to 
// forward declare the ObjectStruct.
typedef void (*ObjectFunctionTypePrototype)(void* objectStruct);
typedef void (*ObjectCollisionFunctionPrototype)(void* objectStruct, void* collidedObject);

// object types.
#define TYPE_PLAYER_PROJECTILE  0
#define TYPE_EFFECT             1
#define TYPE_ENEMY              2
#define TYPE_ENEMY_PROJECTILE   3
#define TYPE_PICKUP             4
#define TYPE_BREAKABLE          5
#define MAX_OBJECT_TYPES        6
// specially treated object types.
#define TYPE_NONE               7
#define TYPE_PLAYER             8


typedef struct
{
    SpriteDef sprite;
    s16 x;
    s16 y;
    ObjectFunctionTypePrototype updateFunction;
    ObjectFunctionTypePrototype destroyFunction;
    ObjectFunctionTypePrototype drawFunction;
    ObjectCollisionFunctionPrototype collisionFunction;
    u16 objectState;
    u16 aiState;
    u16 spriteIndex;
    u16 numSpriteFrames;
    u16 numTilesInOneFrame;
    u16 animationSpeed;
    u16 baseTileAttr;
    s16 speedx;
    s16 speedy;
    u16 lifetime; // one tick every frame. 60 ticks every second. 3600 ticks every minute. Max 18.2 minutes. only for temporary objects.
    u16 objectType;
    s16 rectLeft;
    s16 rectRight;
    s16 rectTop;
    s16 rectBottom;
    s16 healthPoints;
    u16 damage;
    u16 visible;
} ObjectStruct;

typedef void (*ObjectFunctionType)(ObjectStruct* objectStruct);
typedef void (*ObjectCollisionFunctionType)(ObjectStruct* objectStruct, ObjectStruct* collidedObject);

#endif
