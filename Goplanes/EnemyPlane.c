#include "EnemyPlane.h"

#include <kdebug.h>
#include <vdp_spr.h>
#include <vdp_tile.h>

#include "Coin.h"
#include "Collisions.h"
#include "Debug.h"
#include "EnemyBullet.h"
#include "Explosion.h"
#include "LargeExplosion.h"
#include "LevelManager.h"
#include "MathUtils.h"
#include "Objects.h"
#include "Physics.h"
#include "Player.h"
#include "SpritesAndMaps.h"

#define ENEMYPLANE_AI_STATE_FLYING 0
#define ENEMYPLANE_AI_STATE_DEAD   1

const u16 enemyPlaneAnimationFrames[32] =
{
    TILE_ATTR_FULL(PAL1,0,0,0,0),
    TILE_ATTR_FULL(PAL1,0,0,0,(1 * 9)),
    TILE_ATTR_FULL(PAL1,0,0,0,(2 * 9)),
    TILE_ATTR_FULL(PAL1,0,0,0,(3 * 9)),

    TILE_ATTR_FULL(PAL1,0,0,0,(4 * 9)),
    TILE_ATTR_FULL(PAL1,0,0,0,(5 * 9)),
    TILE_ATTR_FULL(PAL1,0,0,0,(6 * 9)),
    TILE_ATTR_FULL(PAL1,0,0,0,(7 * 9)),

    TILE_ATTR_FULL(PAL1,0,0,0,(8 * 9)),
    TILE_ATTR_FULL(PAL1,0,0,0,(9 * 9)),
    TILE_ATTR_FULL(PAL1,0,0,0,(10 * 9)),
    TILE_ATTR_FULL(PAL1,0,0,0,(11 * 9)),

    TILE_ATTR_FULL(PAL1,0,0,0,(12 * 9)),
    TILE_ATTR_FULL(PAL1,0,0,0,(13 * 9)),
    TILE_ATTR_FULL(PAL1,0,0,0,(14 * 9)),
    TILE_ATTR_FULL(PAL1,0,0,0,(15 * 9)),

    TILE_ATTR_FULL(PAL1,0,1,1,0),
    TILE_ATTR_FULL(PAL1,0,1,1,(1 * 9)),
    TILE_ATTR_FULL(PAL1,0,1,1,(2 * 9)),
    TILE_ATTR_FULL(PAL1,0,1,1,(3 * 9)),

    TILE_ATTR_FULL(PAL1,0,1,1,(4 * 9)),
    TILE_ATTR_FULL(PAL1,0,1,1,(5 * 9)),
    TILE_ATTR_FULL(PAL1,0,1,1,(6 * 9)),
    TILE_ATTR_FULL(PAL1,0,1,1,(7 * 9)),

    TILE_ATTR_FULL(PAL1,0,1,1,(8 * 9)),
    TILE_ATTR_FULL(PAL1,0,1,1,(9 * 9)),
    TILE_ATTR_FULL(PAL1,0,1,1,(10 * 9)),
    TILE_ATTR_FULL(PAL1,0,1,1,(11 * 9)),

    TILE_ATTR_FULL(PAL1,0,1,1,(12 * 9)),
    TILE_ATTR_FULL(PAL1,0,1,1,(13 * 9)),
    TILE_ATTR_FULL(PAL1,0,1,1,(14 * 9)),
    TILE_ATTR_FULL(PAL1,0,1,1,(15 * 9))
};

u16 EnemyPlaneCreate(s16 x, s16 y)
{
    ObjectStruct* enemyPlaneObject = CreateObject(TYPE_ENEMY,
                                                  EnemyPlaneUpdate, 
                                                  EnemyPlaneDestroy, 
                                                  EnemyPlaneDraw,
                                                  EnemyPlaneCollide);

    if (!enemyPlaneObject)
    {
#ifdef DEBUG_OBJECTS
        KDebug_Alert("EnemyPlane could not be created!");
#endif
        return 0;
    }

    enemyPlaneObject->x                 = x;
    enemyPlaneObject->y                 = y;
    enemyPlaneObject->speedx            = 0;
    enemyPlaneObject->speedy            = 0;
    enemyPlaneObject->sprite.size       = SPRITE_SIZE(3,3);
    enemyPlaneObject->spriteIndex       = random() & 31;
    enemyPlaneObject->sprite.tile_attr  = enemyPlaneAnimationFrames[enemyPlaneObject->spriteIndex] + enemyPlaneLoadedTileInfo.startIndex;
    enemyPlaneObject->aiState           = ENEMYPLANE_AI_STATE_FLYING;
    enemyPlaneObject->rectLeft          = PIXEL_TO_VIRTUAL(-12);
    enemyPlaneObject->rectRight         = PIXEL_TO_VIRTUAL(12);
    enemyPlaneObject->rectTop           = PIXEL_TO_VIRTUAL(-12);
    enemyPlaneObject->rectBottom        = PIXEL_TO_VIRTUAL(12);
    enemyPlaneObject->healthPoints      = 1;
    enemyPlaneObject->damage            = 1;
    enemyPlaneObject->visible           = 1;

#ifdef DEBUG_OBJECTS
    KDebug_Alert("EnemyPlaneCreate");
#endif
    
    return 1;
}

void RotatePlane(ObjectStruct* enemyPlaneObject)
{
    s16 tile_distance_x = VIRTUAL_TO_TILE(enemyPlaneObject->x - playerObject->x);
    s16 tile_distance_y = VIRTUAL_TO_TILE(enemyPlaneObject->y - playerObject->y);

    u16 x_is_negative = mathutils_isnegative(tile_distance_x);
    u16 y_is_negative = mathutils_isnegative(tile_distance_y);

    tile_distance_x = mathutils_abs(tile_distance_x);
    tile_distance_y = mathutils_abs(tile_distance_y);

    if (tile_distance_x > DISTANCE_ANGLE_TABLE_WIDTH - 1 || tile_distance_y > DISTANCE_ANGLE_TABLE_HEIGHT - 1)
    {
        return;
    }

    u16 angleValue = GET_ANGLE_VALUE(tile_distance_x, tile_distance_y); 

    angleValue >>= 3; // map from 0 to 63 angles to 0 to 7 animationFrames;

    // if x and y are negative, do nothing.
    // if x is negative and y is positive,  angleValue = 31 - angleValue;
    // if x is positive and y is negative, angleValue = 15 - angleValue;
    // if x and y are positive, angleValue = angleValue + 16? 

    if (x_is_negative)
    {
        if (!y_is_negative)
        {
            angleValue = 31 - angleValue;
        }
    }
    else
    {
        if (y_is_negative)
        {
            angleValue = 15 - angleValue;
        }
        else
        {
            angleValue = angleValue + 16;
        }
    }

    enemyPlaneObject->spriteIndex       = angleValue;
    enemyPlaneObject->sprite.tile_attr  = enemyPlaneAnimationFrames[enemyPlaneObject->spriteIndex] +  + enemyPlaneLoadedTileInfo.startIndex;
}


void EnemyPlaneUpdate(ObjectStruct* enemyPlaneObject)
{
    //KDebug_Alert("EnemyPlane Update");

    enemyPlaneObject->sprite.posx = VIRTUAL_TO_PIXEL(enemyPlaneObject->x) + scrollData.scrollx_vdp - 12;
    enemyPlaneObject->sprite.posy = VIRTUAL_TO_PIXEL(enemyPlaneObject->y) - scrollData.scrolly_vdp - 12;

    RotatePlane(enemyPlaneObject);


    /*
    if (enemyPlaneObject->aiState == ENEMYPLANE_AI_STATE_FLYING)
    {
        enemyPlaneObject->x += enemyPlaneObject->speedx;
        enemyPlaneObject->y += enemyPlaneObject->speedy;

        if (ObjectIsOnScreen(enemyPlaneObject->x, enemyPlaneObject->y))
        {
            if ((enemyPlaneObject->lifetime % 64) == 0)
            {
                EnemyBulletCreate(enemyPlaneObject->x, 
                                    enemyPlaneObject->y, 
                                    goplanes_costable32[enemyPlaneObject->spriteIndex],
                                    goplanes_sintable32[enemyPlaneObject->spriteIndex]);
            }
        }
    }
    else*/ if (enemyPlaneObject->aiState == ENEMYPLANE_AI_STATE_DEAD)
    {
        enemyPlaneObject->x += enemyPlaneObject->speedx;
        enemyPlaneObject->y += enemyPlaneObject->speedy >> 2;

        enemyPlaneObject->speedy++;

        if (enemyPlaneObject->visible)
        {
            if ((enemyPlaneObject->lifetime % 20) == 0)
            {
                ExplosionCreate(enemyPlaneObject->x, enemyPlaneObject->y);
            }
        }
        else
        {
            enemyPlaneObject->objectState = OBJECTSTATE_INACTIVE;
        }

        if (collidesWithTile(enemyPlaneObject->x, enemyPlaneObject->y))
        {
            enemyPlaneObject->objectState = OBJECTSTATE_INACTIVE;
            LargeExplosionCreate(enemyPlaneObject->x, enemyPlaneObject->y);
        }
    }
}

void EnemyPlaneDestroy(ObjectStruct* enemyPlaneObject)
{
#ifdef DEBUG_OBJECTS
    KDebug_Alert("EnemyPlaneDestroy");
#endif
}

void EnemyPlaneDraw(ObjectStruct* enemyPlaneObject)
{
    enemyPlaneObject->sprite.link  = spriteDrawIndex + 1;
    VDP_setSpriteP(spriteDrawIndex, &enemyPlaneObject->sprite);
    spriteDrawIndex++;
}

void EnemyPlaneCollide(ObjectStruct* enemyPlaneObject, ObjectStruct* collidedObject)
{
    if (enemyPlaneObject->aiState == ENEMYPLANE_AI_STATE_FLYING)
    {
        enemyPlaneObject->healthPoints -= collidedObject->damage;

        if (enemyPlaneObject->healthPoints <= 0)
        {
            LargeExplosionCreate(enemyPlaneObject->x, enemyPlaneObject->y);
            enemyPlaneObject->aiState   = ENEMYPLANE_AI_STATE_DEAD;
            enemyPlaneObject->speedy    = 8;
            CoinCreate(enemyPlaneObject->x, enemyPlaneObject->y);
        }
    }
}

