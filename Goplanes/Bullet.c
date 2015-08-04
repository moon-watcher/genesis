#include "Bullet.h"

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

u16 BulletCreate(s16 x, s16 y, s16 speedx, s16 speedy)
{
    ObjectStruct* bulletObject = CreateObject(TYPE_PLAYER_PROJECTILE,
                                              BulletUpdate, 
                                              BulletDestroy, 
                                              BulletDraw,
                                              BulletCollide);

    if (!bulletObject)
    {
#ifdef DEBUG_OBJECTS
        KDebug_Alert("Bullet could not be created!");
#endif
        return 0;
    }

    bulletObject->x                 = x;
    bulletObject->y                 = y;
    bulletObject->speedx            = speedx;
    bulletObject->speedy            = speedy;
    bulletObject->sprite.size       = SPRITE_SIZE(1,1);
    bulletObject->spriteIndex       = 0;
    bulletObject->sprite.tile_attr  = TILE_ATTR_FULL(PAL0,1,0,0,bulletLoadedTileInfo.startIndex);
    bulletObject->rectLeft          = PIXEL_TO_VIRTUAL(-4);
    bulletObject->rectRight         = PIXEL_TO_VIRTUAL(4);
    bulletObject->rectTop           = PIXEL_TO_VIRTUAL(-4);
    bulletObject->rectBottom        = PIXEL_TO_VIRTUAL(4);
    bulletObject->damage            = 1;
    bulletObject->healthPoints      = 1;
    bulletObject->visible           = 1;

#ifdef DEBUG_OBJECTS
    KDebug_Alert("BulletCreate");
#endif

    return 1;
}

void BulletUpdate(ObjectStruct* bulletObject)
{
    //KDebug_Alert("Bullet Update");
    bulletObject->x += bulletObject->speedx;
    bulletObject->y += bulletObject->speedy;

    bulletObject->sprite.posx = VIRTUAL_TO_PIXEL(bulletObject->x) + scrollData.scrollx_vdp - 4;
    bulletObject->sprite.posy = VIRTUAL_TO_PIXEL(bulletObject->y) - scrollData.scrolly_vdp - 4;

    if (bulletObject->visible)
    {
        if (collidesWithTile(bulletObject->x, bulletObject->y))
        {
            bulletObject->objectState = OBJECTSTATE_INACTIVE;
#ifdef DEBUG_OBJECTS
            KDebug_Alert("Bullet Hit Background. Creating explosion");
#endif
            ExplosionCreate(bulletObject->x, bulletObject->y);
#ifdef DEBUG_OBJECTS
            KDebug_Alert("Finished creating explosion");
#endif
        }
    }
    else
    {
        bulletObject->objectState = OBJECTSTATE_INACTIVE;
    }
}

void BulletDestroy(ObjectStruct* bulletObject)
{
#ifdef DEBUG_OBJECTS
    KDebug_Alert("BulletDestroy");
#endif
}

void BulletDraw(ObjectStruct* bulletObject)
{
    bulletObject->sprite.link  = spriteDrawIndex + 1;
    VDP_setSpriteP(spriteDrawIndex, &bulletObject->sprite);
    spriteDrawIndex++;
}

void BulletCollide(ObjectStruct* bulletObject, ObjectStruct* collidedObject)
{
    bulletObject->objectState = OBJECTSTATE_INACTIVE;

    if (collidedObject->objectType == TYPE_BREAKABLE)
    {
        ExplosionCreate(bulletObject->x, bulletObject->y);
    }
}

