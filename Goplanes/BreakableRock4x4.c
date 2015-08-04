#include "BreakableRock4x4.h"

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
#include "Player.h"
#include "Physics.h"
#include "SpritesAndMaps.h"

u16 BreakableRock4x4Create(s16 x, s16 y)
{
    ObjectStruct* breakableRock4x4Object = CreateObject(TYPE_BREAKABLE,
                                                        BreakableRock4x4Update, 
                                                        BreakableRock4x4Destroy, 
                                                        BreakableRock4x4Draw,
                                                        BreakableRock4x4Collide);

    if (!breakableRock4x4Object)
    {
#ifdef DEBUG_OBJECTS
        KDebug_Alert("BreakableRock4x4 could not be created!");
#endif
        return 0;
    }

    breakableRock4x4Object->x                 = x;
    breakableRock4x4Object->y                 = y;
    breakableRock4x4Object->speedx            = 0;
    breakableRock4x4Object->speedy            = 0;
    breakableRock4x4Object->sprite.size       = SPRITE_SIZE(4,4);
    breakableRock4x4Object->spriteIndex       = 0;
    breakableRock4x4Object->sprite.tile_attr  = TILE_ATTR_FULL(PAL3,0,0,0,breakableRockLoadedTileInfo.startIndex);
    breakableRock4x4Object->aiState           = 0;
    breakableRock4x4Object->rectLeft          = 0;
    breakableRock4x4Object->rectRight         = PIXEL_TO_VIRTUAL(32);
    breakableRock4x4Object->rectTop           = 0;
    breakableRock4x4Object->rectBottom        = PIXEL_TO_VIRTUAL(32);
    breakableRock4x4Object->healthPoints      = 1;
    breakableRock4x4Object->damage            = 1;

#ifdef DEBUG_OBJECTS
    KDebug_Alert("BreakableRock4x4Create");
#endif
    
    return 1;
}

void BreakableRock4x4Update(ObjectStruct* breakableRock4x4Object)
{
    breakableRock4x4Object->sprite.posx = VIRTUAL_TO_PIXEL(breakableRock4x4Object->x) + scrollData.scrollx_vdp;
    breakableRock4x4Object->sprite.posy = VIRTUAL_TO_PIXEL(breakableRock4x4Object->y) - scrollData.scrolly_vdp;
}

void BreakableRock4x4Destroy(ObjectStruct* breakableRock4x4Object)
{
#ifdef DEBUG_OBJECTS
    KDebug_Alert("BreakableRock4x4Destroy");
#endif
}

void BreakableRock4x4Draw(ObjectStruct* breakableRock4x4Object)
{
    breakableRock4x4Object->sprite.link  = spriteDrawIndex + 1;
    VDP_setSpriteP(spriteDrawIndex, &breakableRock4x4Object->sprite);
    spriteDrawIndex++;
}

void BreakableRock4x4Collide(ObjectStruct* breakableRock4x4Object, ObjectStruct* collidedObject)
{
    if (collidedObject == playerObject)
    {
        if (playerObject->aiState == AI_STATE_AFTERBURNERS)
        {
            breakableRock4x4Object->objectState = OBJECTSTATE_INACTIVE;

            LargeExplosionCreate(breakableRock4x4Object->x,                        breakableRock4x4Object->y);
            LargeExplosionCreate(breakableRock4x4Object->x + PIXEL_TO_VIRTUAL(24), breakableRock4x4Object->y);
            LargeExplosionCreate(breakableRock4x4Object->x,                        breakableRock4x4Object->y + PIXEL_TO_VIRTUAL(24));
            LargeExplosionCreate(breakableRock4x4Object->x + PIXEL_TO_VIRTUAL(24), breakableRock4x4Object->y + PIXEL_TO_VIRTUAL(24));
        }
    }
}

