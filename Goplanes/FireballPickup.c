#include "FireballPickup.h"

#include <kdebug.h>
#include <vdp_spr.h>
#include <vdp_tile.h>


#include "Collisions.h"
#include "Debug.h"
#include "Explosion.h"
#include "LevelManager.h"
#include "MathUtils.h"
#include "Objects.h"
#include "Player.h"
#include "SpritesAndMaps.h"

#define FIREBALLPICKUP_STATE_WAIT   0
#define FIREBALLPICKUP_STATE_READY  1

u16 FireballPickupCreate(s16 x, s16 y)
{
    ObjectStruct* fireballPickupObject = CreateObject(TYPE_PICKUP,
                                            FireballPickupUpdate, 
                                            FireballPickupDestroy, 
                                            FireballPickupDraw,
                                            FireballPickupCollide);

    if (!fireballPickupObject)
    {
#ifdef DEBUG_OBJECTS
        KDebug_Alert("FireballPickup could not be created!");
#endif
        return 0;
    }

    fireballPickupObject->x                 = x;
    fireballPickupObject->y                 = y;
    fireballPickupObject->speedx            = 0;
    fireballPickupObject->speedy            = 0;
    fireballPickupObject->sprite.size       = SPRITE_SIZE(3,3);
    fireballPickupObject->sprite.tile_attr  = TILE_ATTR_FULL(PAL0,1,0,0,fireballPickupLoadedTileInfo.startIndex);
    fireballPickupObject->spriteIndex       = 0;
    fireballPickupObject->rectLeft          = 0;
    fireballPickupObject->rectRight         = PIXEL_TO_VIRTUAL(24);
    fireballPickupObject->rectTop           = 0;
    fireballPickupObject->rectBottom        = PIXEL_TO_VIRTUAL(24);
    fireballPickupObject->damage            = 0;
    fireballPickupObject->lifetime          = 0;
    fireballPickupObject->aiState           = FIREBALLPICKUP_STATE_WAIT;

#ifdef DEBUG_OBJECTS
    KDebug_Alert("FireballPickupCreate");
#endif

    return 1;
}

void FireballPickupUpdate(ObjectStruct* fireballPickupObject)
{
    if (fireballPickupObject->lifetime > 60) // one second
    {
        fireballPickupObject->aiState = FIREBALLPICKUP_STATE_READY;        
    }

    //KDebug_Alert("FireballPickup Update");
    fireballPickupObject->x += fireballPickupObject->speedx;
    fireballPickupObject->y += fireballPickupObject->speedy;

    fireballPickupObject->sprite.posx = VIRTUAL_TO_PIXEL(fireballPickupObject->x) + scrollData.scrollx_vdp;
    fireballPickupObject->sprite.posy = VIRTUAL_TO_PIXEL(fireballPickupObject->y) - scrollData.scrolly_vdp;
    
}

void FireballPickupDestroy(ObjectStruct* fireballPickupObject)
{
#ifdef DEBUG_OBJECTS
    KDebug_Alert("FireballPickupDestroy");
#endif
}

void FireballPickupDraw(ObjectStruct* fireballPickupObject)
{
    fireballPickupObject->sprite.link  = spriteDrawIndex + 1;
    VDP_setSpriteP(spriteDrawIndex, &fireballPickupObject->sprite);
    spriteDrawIndex++;
}

void FireballPickupCollide(ObjectStruct* fireballPickupObject, ObjectStruct* collidedObject)
{
    if (fireballPickupObject->aiState == FIREBALLPICKUP_STATE_READY)
    {
        playerData.currentWeapon = WEAPON_FIREBALL;
        fireballPickupObject->objectState = OBJECTSTATE_INACTIVE;
    }
}
