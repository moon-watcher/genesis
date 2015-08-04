#include "EnemyBullet.h"

#include <kdebug.h>
#include <vdp_spr.h>
#include <vdp_tile.h>


#include "Collisions.h"
#include "Debug.h"
#include "Explosion.h"
#include "LevelManager.h"
#include "MathUtils.h"
#include "Objects.h"
#include "Physics.h"
#include "SpritesAndMaps.h"

u16 EnemyBulletCreate(s16 x, s16 y, s16 speedx, s16 speedy)
{
    ObjectStruct* enemyBulletObject = CreateObject(TYPE_ENEMY_PROJECTILE,
                                                   EnemyBulletUpdate, 
                                                   EnemyBulletDestroy, 
                                                   EnemyBulletDraw,
                                                   EnemyBulletCollide);

    if (!enemyBulletObject)
    {
#ifdef DEBUG_OBJECTS
        KDebug_Alert("EnemyBullet could not be created!");
#endif
        return 0;
    }

    enemyBulletObject->x                 = x;
    enemyBulletObject->y                 = y;
    enemyBulletObject->speedx            = speedx;
    enemyBulletObject->speedy            = speedy;
    enemyBulletObject->sprite.size       = SPRITE_SIZE(1,1);
    enemyBulletObject->spriteIndex       = 0;
    enemyBulletObject->sprite.tile_attr  = TILE_ATTR_FULL(PAL0,1,0,0,bulletLoadedTileInfo.startIndex);
    enemyBulletObject->rectLeft          = PIXEL_TO_VIRTUAL(-4);
    enemyBulletObject->rectRight         = PIXEL_TO_VIRTUAL(4);
    enemyBulletObject->rectTop           = PIXEL_TO_VIRTUAL(-4);
    enemyBulletObject->rectBottom        = PIXEL_TO_VIRTUAL(4);
    enemyBulletObject->damage            = 1;
    enemyBulletObject->healthPoints      = 1;
    enemyBulletObject->visible           = 1;

#ifdef DEBUG_OBJECTS
    KDebug_Alert("EnemyBulletCreate");
#endif

    return 1;
}

void EnemyBulletUpdate(ObjectStruct* enemyBulletObject)
{
    //KDebug_Alert("EnemyBullet Update");
    enemyBulletObject->x += enemyBulletObject->speedx;
    enemyBulletObject->y += enemyBulletObject->speedy;

    enemyBulletObject->sprite.posx = VIRTUAL_TO_PIXEL(enemyBulletObject->x) + scrollData.scrollx_vdp - 4;
    enemyBulletObject->sprite.posy = VIRTUAL_TO_PIXEL(enemyBulletObject->y) - scrollData.scrolly_vdp - 4;

    if (enemyBulletObject->visible)
    {
        if (collidesWithTile(enemyBulletObject->x, enemyBulletObject->y))
        {
            enemyBulletObject->objectState = OBJECTSTATE_INACTIVE;
            ExplosionCreate(enemyBulletObject->x, enemyBulletObject->y);
        }
    }
    else
    {
        enemyBulletObject->objectState = OBJECTSTATE_INACTIVE;
    }
}

void EnemyBulletDestroy(ObjectStruct* enemyBulletObject)
{
#ifdef DEBUG_OBJECTS
    KDebug_Alert("EnemyBulletDestroy");
#endif
}

void EnemyBulletDraw(ObjectStruct* enemyBulletObject)
{
    enemyBulletObject->sprite.link  = spriteDrawIndex + 1;
    VDP_setSpriteP(spriteDrawIndex, &enemyBulletObject->sprite);
    spriteDrawIndex++;
}

void EnemyBulletCollide(ObjectStruct* enemyBulletObject, ObjectStruct* collidedObject)
{
    enemyBulletObject->objectState = OBJECTSTATE_INACTIVE;
}

