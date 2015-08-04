#include "Objects.h"

#include <kdebug.h>

#include "Collisions.h"
#include "Debug.h"
#include "FunctionStubs.h"
#include "HUD.h"
#include "LevelManager.h"
#include "MathUtils.h"
#include "Player.h"

//#define DEBUG_OBJECT_MANAGEMENT
//#define DEBUG_COLLISIONS


u16 spriteDrawIndex;                // Used to set hardware sprite index numbers.
u16 totalActiveObjects = 0;


ObjectCollection playerProjectileCollection;
ObjectCollection effectCollection;
ObjectCollection enemyCollection;
ObjectCollection enemyProjectileCollection;
ObjectCollection pickupCollection;
ObjectCollection breakablesCollection;

ObjectCollection* objectCollections[MAX_OBJECT_TYPES];

ObjectStruct playerProjectileList[MAX_PLAYER_PROJECTILES];
ObjectStruct effectList[MAX_EFFECTS];
ObjectStruct enemyList[MAX_ENEMIES];
ObjectStruct enemyProjectileList[MAX_ENEMY_PROJECTILES];
ObjectStruct pickupList[MAX_PICKUPS];
ObjectStruct breakablesList[MAX_BREAKABLES];

ObjectStruct* playerProjectileVisibilityList[MAX_PLAYER_PROJECTILES];
ObjectStruct* effectVisibilityList[MAX_EFFECTS];
ObjectStruct* enemyVisibilityList[MAX_ENEMIES];
ObjectStruct* enemyProjectileVisibilityList[MAX_ENEMY_PROJECTILES];
ObjectStruct* pickupVisibilityList[MAX_PICKUPS];
ObjectStruct* breakablesVisibilityList[MAX_BREAKABLES];

ObjectStruct* playerProjectileInvisibilityList[MAX_PLAYER_PROJECTILES];
ObjectStruct* effectInvisibilityList[MAX_EFFECTS];
ObjectStruct* enemyInvisibilityList[MAX_ENEMIES];
ObjectStruct* enemyProjectileInvisibilityList[MAX_ENEMY_PROJECTILES];
ObjectStruct* pickupInvisibilityList[MAX_PICKUPS];
ObjectStruct* breakablesInvisibilityList[MAX_BREAKABLES];

void SetupObjectList(ObjectCollection* objectCollection)
{
    objectCollection->numActiveObjects = 0;
    objectCollection->numVisibleObjects = 0;
    u16 loop = objectCollection->maxActiveObjects;
    ObjectStruct* tempObject = objectCollection->objectList;
	while (loop--)
    {
        tempObject->objectState = OBJECTSTATE_FREE;
		tempObject++;
    }    
}

void ObjectManager_SetupObjectCollections()
{
    // TODO: set this up at decleration time, not as a function.
    objectCollections[TYPE_PLAYER_PROJECTILE] = &playerProjectileCollection;
    objectCollections[TYPE_EFFECT] = &effectCollection;
    objectCollections[TYPE_ENEMY] = &enemyCollection;
    objectCollections[TYPE_ENEMY_PROJECTILE] = &enemyProjectileCollection;
    objectCollections[TYPE_PICKUP] = &pickupCollection;
    objectCollections[TYPE_BREAKABLE] = &breakablesCollection;


    playerProjectileCollection.objectList = playerProjectileList;
    playerProjectileCollection.maxActiveObjects = MAX_PLAYER_PROJECTILES;
    playerProjectileCollection.objectVisibilityList = playerProjectileVisibilityList;
    playerProjectileCollection.objectInvisibilityList = playerProjectileInvisibilityList;

    effectCollection.objectList = effectList;
    effectCollection.maxActiveObjects = MAX_EFFECTS;
    effectCollection.objectVisibilityList = effectVisibilityList;
    effectCollection.objectInvisibilityList = effectInvisibilityList;

    enemyCollection.objectList = enemyList;
    enemyCollection.maxActiveObjects = MAX_ENEMIES;
    enemyCollection.objectVisibilityList = enemyVisibilityList;
    enemyCollection.objectInvisibilityList = enemyInvisibilityList;

    enemyProjectileCollection.objectList = enemyProjectileList;
    enemyProjectileCollection.maxActiveObjects = MAX_ENEMY_PROJECTILES;
    enemyProjectileCollection.objectVisibilityList = enemyProjectileVisibilityList;
    enemyProjectileCollection.objectInvisibilityList = enemyProjectileInvisibilityList;

    pickupCollection.objectList = pickupList;
    pickupCollection.maxActiveObjects = MAX_PICKUPS;
    pickupCollection.objectVisibilityList = pickupVisibilityList;
    pickupCollection.objectInvisibilityList = pickupInvisibilityList;

    breakablesCollection.objectList = breakablesList;
    breakablesCollection.maxActiveObjects = MAX_BREAKABLES;
    breakablesCollection.objectVisibilityList = breakablesVisibilityList;
    breakablesCollection.objectInvisibilityList = breakablesInvisibilityList;
}

void ObjectManager_ClearObjectCollections()
{
    spriteDrawIndex = 0;
    totalActiveObjects = 0;

    u16 loop = 0;
    for (;loop < MAX_OBJECT_TYPES;loop++)
    {
        SetupObjectList(objectCollections[loop]);
    }
}

u16 CanCreateObject(u16 objectType)
{
    return objectCollections[objectType]->numActiveObjects < objectCollections[objectType]->maxActiveObjects;
}

ObjectStruct* CreateObject(u16                          objectType, 
                           ObjectFunctionType           updateFunction, 
                           ObjectFunctionType           destroyFunction,
                           ObjectFunctionType           drawFunction,
                           ObjectCollisionFunctionType  collisionFunction)
{
    if (!CanCreateObject(objectType))
    {
        return 0;
    }

    // Tries to find a free slot in the object array. 
    // If there isn't, the object won't be created.

    ObjectCollection* objectCollection = objectCollections[objectType];

    u16 loop = 0;
    ObjectStruct* tempObjectList = objectCollection->objectList;
    u16 numAliveObjects = 0;
    u16 numDeadObjects = 0;
    for (; loop < objectCollection->maxActiveObjects; loop++)
    {
        ObjectStruct* object = tempObjectList;
        if (object->objectState == OBJECTSTATE_FREE)
        {
            totalActiveObjects++;
            object->updateFunction      = (ObjectFunctionTypePrototype)updateFunction;
            object->destroyFunction     = (ObjectFunctionTypePrototype)destroyFunction;
            object->drawFunction        = (ObjectFunctionTypePrototype)drawFunction;
            object->collisionFunction   = (ObjectCollisionFunctionPrototype)collisionFunction;
            object->objectState         = OBJECTSTATE_ACTIVE;
            object->objectType          = objectType;
            objectCollection->numActiveObjects++;

#ifdef DEBUG_OBJECT_MANAGEMENT
            KDebug_Alert("Created Object. Objects Total:");
            PrintNumber(totalActiveObjects);
#endif
            return object;
        }
        else if (object->objectState == OBJECTSTATE_ACTIVE)
        {
            numAliveObjects++;
        }
        else if (object->objectState == OBJECTSTATE_INACTIVE)
        {
            numDeadObjects++;
        }

        tempObjectList++;
    }
#ifdef DEBUG_OBJECT_MANAGEMENT
    KDebug_Alert("Could not add object. Too many created");
    PrintNumber(numAliveObjects);
    PrintNumber(numDeadObjects);
#endif
    PrintText("none avialable");
    return 0;
}

void ResetObjectValues(ObjectStruct* object)
{
    object->sprite.posx         = -64;
    object->sprite.posy         = -64;
    object->sprite.tile_attr    = (u16)-1;
    object->sprite.size         = (u8)-1;
    object->sprite.link         = (u8)-1;
    object->objectType          = TYPE_NONE;
    object->lifetime            = -1;
    object->drawFunction        = (ObjectFunctionTypePrototype)DrawFunctionStub;
    object->collisionFunction   = (ObjectCollisionFunctionPrototype)CollisionFunctionStub;
    object->destroyFunction     = (ObjectFunctionTypePrototype)DestroyFunctionStub;
    object->updateFunction      = (ObjectFunctionTypePrototype)UpdateFunctionStub;
    object->x                   = 54321;
    object->y                   = 12345;
    object->objectState         = (u16)-1;
    object->aiState             = (u16)-1;
    object->spriteIndex         = (u16)-1;
    object->numSpriteFrames     = (u16)-1;
    object->animationSpeed      = (u16)-1;
    object->numTilesInOneFrame  = (u16)-1;
    object->speedx              = 54321;
    object->speedy              = 12345;
    object->lifetime            = (u16)-1;
    object->objectType          = (u16)-1;
    object->rectLeft            = 0;
    object->rectRight           = 0;
    object->rectTop             = 0;
    object->rectBottom          = 0;
    object->healthPoints        = -1;
    object->damage              = (u16)-1;
}

void DrawObjectCollection(ObjectCollection* objectCollection)
{
    u16 loop = objectCollection->numVisibleObjects;
    ObjectStruct** tempVisibilityList = objectCollection->objectVisibilityList;

    while(loop--)
    {
        ObjectStruct* object = (*tempVisibilityList);
        object->drawFunction(object);
        tempVisibilityList++;
    }
}

void ObjectManager_DrawObjects()
{
    spriteDrawIndex = 0;

    DrawHUD();

    DrawObjectCollection(&pickupCollection);
    DrawObjectCollection(&effectCollection);

    playerObject->drawFunction(playerObject);

    DrawObjectCollection(&enemyCollection);
    DrawObjectCollection(&playerProjectileCollection);
    DrawObjectCollection(&enemyProjectileCollection);
    DrawObjectCollection(&breakablesCollection);

    // sets the last used sprite's link to 0, telling the hardware to
    // only draw the sprites we've set.
    VDP_setSprite(spriteDrawIndex, 0, 0, 0, 0, 0);
}



void ProcessCollisions(ObjectCollection* firstObjectCollection, 
                       ObjectCollection* secondObjectCollection, 
                       CollisionFunction collisionFunction)
{
    if (firstObjectCollection->numVisibleObjects == 0)
        return;
    if (secondObjectCollection->numVisibleObjects == 0)
        return;

    ObjectStruct** tempFirstList = firstObjectCollection->objectVisibilityList;

    u16 firstListCounter = firstObjectCollection->numVisibleObjects;

    while (firstListCounter--)
    {
#ifdef DEBUG_COLLISIONS
        KDebug_Alert("firstObject");
        PrintNumber((*tempFirstList)->objectType);
#endif
        // no need to do anything if we're dead.
        if ((*tempFirstList)->healthPoints > 0 &&
            (*tempFirstList)->objectState == OBJECTSTATE_ACTIVE)
        {
            u16 secondListCounter = secondObjectCollection->numVisibleObjects;
            ObjectStruct** tempSecondList = secondObjectCollection->objectVisibilityList;

            while (secondListCounter--)
            {
#ifdef DEBUG_COLLISIONS
        KDebug_Alert("secondObject");
        PrintNumber((*tempSecondList)->objectType);
#endif
                // no need to do anything if we're dead.
                if ((*tempSecondList)->healthPoints > 0 &&
                    (*tempSecondList)->objectState == OBJECTSTATE_ACTIVE)
                {
                    if (!((*tempFirstList)->x + (*tempFirstList)->rectLeft   > (*tempSecondList)->x + (*tempSecondList)->rectRight ||
                          (*tempFirstList)->x + (*tempFirstList)->rectRight  < (*tempSecondList)->x + (*tempSecondList)->rectLeft ||
                          (*tempFirstList)->y + (*tempFirstList)->rectTop    > (*tempSecondList)->y + (*tempSecondList)->rectBottom ||
                          (*tempFirstList)->y + (*tempFirstList)->rectBottom < (*tempSecondList)->y + (*tempSecondList)->rectTop))
                    {
                        (*tempFirstList)->collisionFunction(*tempFirstList, *tempSecondList);
                        (*tempSecondList)->collisionFunction(*tempSecondList, *tempFirstList);
                    }
                }

                tempSecondList++;
            }
        }

        tempFirstList++;
    }
}


void ProcessCollisionsAgainstPlayer(ObjectCollection* objectCollection, 
                                    CollisionFunction collisionFunction)
{
    if (objectCollection->numVisibleObjects == 0)
        return;

    // no need to do anything if we're dead.
    if (playerObject->objectState == OBJECTSTATE_ACTIVE)
    {
        u16 listCounter = objectCollection->numVisibleObjects;
        ObjectStruct** tempVisibilityList = objectCollection->objectVisibilityList;

        while (listCounter--)
        {
            // no need to do anything if we're dead.
            ObjectStruct* object = (*tempVisibilityList);
            if (object->objectState == OBJECTSTATE_ACTIVE)
            {
                if (collisionFunction(playerObject, object))
                {
                    playerObject->collisionFunction(playerObject, object);
                    object->collisionFunction(object, playerObject);
                }
            }

            tempVisibilityList++;
        }
    }
}


void ProcessAllCollisions()
{
    ProcessCollisions(&playerProjectileCollection, &enemyCollection, SquareSquareCollision);
    ProcessCollisions(&playerProjectileCollection, &breakablesCollection, SquareSquareCollision);
    ProcessCollisionsAgainstPlayer(&enemyCollection, SquareSquareCollision);
    ProcessCollisionsAgainstPlayer(&enemyProjectileCollection, SquareSquareCollision);
    ProcessCollisionsAgainstPlayer(&pickupCollection, SquareSquareCollision);
}

void UpdateObjectCollection(ObjectCollection* objectCollection)
{
    u16 loop = 0;
    ObjectStruct* tempObjectList = objectCollection->objectList;
    ObjectStruct** tempObjectVisibilityList = objectCollection->objectVisibilityList;
    ObjectStruct** tempObjectInvisibilityList = objectCollection->objectInvisibilityList;
    objectCollection->numVisibleObjects = 0;
    objectCollection->numInvisibleObjects = 0;

    for (; loop < objectCollection->maxActiveObjects; loop++)
    {
        ObjectStruct* object = tempObjectList;

        if (object->objectState == OBJECTSTATE_INACTIVE)
        {
            object->destroyFunction(object);
            ResetObjectValues(object);
            objectCollection->numActiveObjects--;
            totalActiveObjects--;
            object->objectState = OBJECTSTATE_FREE;
        }
        else if (object->objectState == OBJECTSTATE_ACTIVE)
        {
            object->updateFunction(object); // update self.
            if (object->objectState == OBJECTSTATE_ACTIVE)
            {
                object->lifetime++; // loops after 65535. Maximum of 18.2 minutes.
                // replace this with an off-screen check.
                object->visible = SpriteIsOnScreen(object->sprite.posx, object->sprite.posy, 32);

                if (object->visible)
                {
                    // compute the visible objects by type so we can 
                    // process collisions with them later. We're only
                    // colliding visible objects.
                    *tempObjectVisibilityList = object;
                    tempObjectVisibilityList++;
                    objectCollection->numVisibleObjects++;
                }
                else
                {
                    *tempObjectInvisibilityList = object;
                    tempObjectInvisibilityList++;
                    objectCollection->numInvisibleObjects++;
                }
            }
        }

        tempObjectList++;
    }
}

void ObjectManager_UpdateObjects()
{
    UpdateObjectCollection(&playerProjectileCollection);
    UpdateObjectCollection(&effectCollection);
    UpdateObjectCollection(&enemyCollection);
    UpdateObjectCollection(&enemyProjectileCollection);
    UpdateObjectCollection(&pickupCollection);
    UpdateObjectCollection(&breakablesCollection);

    ProcessAllCollisions();
}

