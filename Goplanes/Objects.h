// TODO: rename files to ObjectManager.*


#ifndef OBJECTS_INCLUDE_H
#define OBJECTS_INCLUDE_H

#include <genesis.h>
#include <vdp_spr.h>

#include "ObjectStruct.h"

#define MAX_PLAYER_PROJECTILES  10
#define MAX_EFFECTS             25
#define MAX_ENEMIES             10
#define MAX_ENEMY_PROJECTILES   10
#define MAX_PICKUPS             20
#define MAX_BREAKABLES          20


typedef struct
{
    ObjectStruct*                   objectList;
    u16                             numActiveObjects;
    u16                             maxActiveObjects;
    ObjectStruct**                  objectVisibilityList;
    u16                             numVisibleObjects;
    ObjectStruct**                  objectInvisibilityList;
    u16                             numInvisibleObjects;
} ObjectCollection;


extern u16 spriteDrawIndex;
extern ObjectCollection breakablesCollection;
extern ObjectCollection enemyCollection;

// TODO: add ObjectManager_ prefix to function names.
u16 CanCreateObject(u16 objectType);
ObjectStruct* CreateObject(u16                          objectType, 
                           ObjectFunctionType           updateFunction, 
                           ObjectFunctionType           destroyFunction, 
                           ObjectFunctionType           drawFunction, 
                           ObjectCollisionFunctionType  collisionFunction);

void ObjectManager_SetupObjectCollections();
void ObjectManager_ClearObjectCollections();
void ObjectManager_UpdateObjects();
void ObjectManager_DrawObjects();


#endif
