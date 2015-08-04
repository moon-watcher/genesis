#include "Fireball.h"

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

const u16 planeAnglesToFireballAngles[32] =
{
    TILE_ATTR_FULL(PAL0,0,0,0,0),
    TILE_ATTR_FULL(PAL0,0,0,0,(1 * 4)),
    TILE_ATTR_FULL(PAL0,0,0,0,(2 * 4)),
    TILE_ATTR_FULL(PAL0,0,0,0,(3 * 4)),
    
    TILE_ATTR_FULL(PAL0,0,0,0,(4 * 4)),
    TILE_ATTR_FULL(PAL0,0,0,0,(5 * 4)),
    TILE_ATTR_FULL(PAL0,0,0,0,(6 * 4)),
    TILE_ATTR_FULL(PAL0,0,0,0,(7 * 4)),
    
    TILE_ATTR_FULL(PAL0,0,0,1,(8 * 4)),
    TILE_ATTR_FULL(PAL0,0,0,1,(7 * 4)),
    TILE_ATTR_FULL(PAL0,0,0,1,(6 * 4)),
    TILE_ATTR_FULL(PAL0,0,0,1,(5 * 4)),
    
    TILE_ATTR_FULL(PAL0,0,0,1,(4 * 4)),
    TILE_ATTR_FULL(PAL0,0,0,1,(3 * 4)),
    TILE_ATTR_FULL(PAL0,0,0,1,(2 * 4)),
    TILE_ATTR_FULL(PAL0,0,0,1,(1 * 4)),
    
    TILE_ATTR_FULL(PAL0,0,1,1,0),
    TILE_ATTR_FULL(PAL0,0,1,1,(1 * 4)),
    TILE_ATTR_FULL(PAL0,0,1,1,(2 * 4)),
    TILE_ATTR_FULL(PAL0,0,1,1,(3 * 4)),
    
    TILE_ATTR_FULL(PAL0,0,1,1,(4 * 4)),
    TILE_ATTR_FULL(PAL0,0,1,1,(5 * 4)),
    TILE_ATTR_FULL(PAL0,0,1,1,(6 * 4)),
    TILE_ATTR_FULL(PAL0,0,1,1,(7 * 4)),
    
    TILE_ATTR_FULL(PAL0,0,1,0,(8 * 4)),
    TILE_ATTR_FULL(PAL0,0,1,0,(7 * 4)),
    TILE_ATTR_FULL(PAL0,0,1,0,(6 * 4)),
    TILE_ATTR_FULL(PAL0,0,1,0,(5 * 4)),
    
    TILE_ATTR_FULL(PAL0,0,1,0,(4 * 4)),
    TILE_ATTR_FULL(PAL0,0,1,0,(3 * 4)),
    TILE_ATTR_FULL(PAL0,0,1,0,(2 * 4)),
    TILE_ATTR_FULL(PAL0,0,1,0,(1 * 4)),
};

u16 FireballCreate(s16 x, s16 y, s16 speedx, s16 speedy, u16 angle)
{
    ObjectStruct* fireballObject = CreateObject(TYPE_PLAYER_PROJECTILE,
                                                FireballUpdate, 
                                                FireballDestroy, 
                                                FireballDraw,
                                                FireballCollide);

    if (!fireballObject)
    {
#ifdef DEBUG_OBJECTS
        KDebug_Alert("Fireball could not be created!");
#endif
        return 0;
    }

    fireballObject->x                 = x;
    fireballObject->y                 = y;
    fireballObject->speedx            = speedx;
    fireballObject->speedy            = speedy;
    fireballObject->sprite.size       = SPRITE_SIZE(2,2);
    fireballObject->spriteIndex       = angle;
    fireballObject->sprite.tile_attr  = TILE_ATTR_FULL(PAL0,1,0,0,fireballLoadedTileInfo.startIndex + planeAnglesToFireballAngles[angle]);
    fireballObject->rectLeft          = PIXEL_TO_VIRTUAL(-8);
    fireballObject->rectRight         = PIXEL_TO_VIRTUAL(8);
    fireballObject->rectTop           = PIXEL_TO_VIRTUAL(-8);
    fireballObject->rectBottom        = PIXEL_TO_VIRTUAL(8);
    fireballObject->damage            = 1;
    fireballObject->healthPoints      = 1;
    fireballObject->visible           = 1;

#ifdef DEBUG_OBJECTS
    KDebug_Alert("FireballCreate");
#endif

    return 1;
}

void FireballUpdate(ObjectStruct* fireballObject)
{
    //KDebug_Alert("Fireball Update");
    fireballObject->x += fireballObject->speedx;
    fireballObject->y += fireballObject->speedy;

    fireballObject->sprite.posx = VIRTUAL_TO_PIXEL(fireballObject->x) + scrollData.scrollx_vdp - 8;
    fireballObject->sprite.posy = VIRTUAL_TO_PIXEL(fireballObject->y) - scrollData.scrolly_vdp - 8;

    if (fireballObject->visible)
    {
        if (collidesWithTile(fireballObject->x, fireballObject->y))
        {
            fireballObject->objectState = OBJECTSTATE_INACTIVE;
#ifdef DEBUG_OBJECTS
            KDebug_Alert("Fireball Hit Background. Creating explosion");
#endif
            ExplosionCreate(fireballObject->x, fireballObject->y);
#ifdef DEBUG_OBJECTS
            KDebug_Alert("Finished creating explosion");
#endif
        }
    }
    else
    {
        fireballObject->objectState = OBJECTSTATE_INACTIVE;
    }
}

void FireballDestroy(ObjectStruct* fireballObject)
{
#ifdef DEBUG_OBJECTS
    KDebug_Alert("FireballDestroy");
#endif
}

void FireballDraw(ObjectStruct* fireballObject)
{
    fireballObject->sprite.link  = spriteDrawIndex + 1;
    VDP_setSpriteP(spriteDrawIndex, &fireballObject->sprite);
    spriteDrawIndex++;
}

void FireballCollide(ObjectStruct* fireballObject, ObjectStruct* collidedObject)
{
    fireballObject->objectState = OBJECTSTATE_INACTIVE;

    if (collidedObject->objectType == TYPE_BREAKABLE)
    {
        ExplosionCreate(fireballObject->x, fireballObject->y);
    }
}

