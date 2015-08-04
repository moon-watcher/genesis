#include "LargeExplosion.h"

#include <kdebug.h>
#include <vdp_spr.h>
#include <vdp_tile.h>

#include "Collisions.h"
#include "Debug.h"
#include "FunctionStubs.h"
#include "LevelManager.h"
#include "MathUtils.h"
#include "Objects.h"
#include "Player.h"
#include "SpritesAndMaps.h"

u16 LargeExplosionCreate(u16 x, u16 y)
{
    ObjectStruct* largeExplosionObject = CreateObject(TYPE_EFFECT,
                                                      LargeExplosionUpdate, 
                                                      LargeExplosionDestroy, 
                                                      LargeExplosionDraw, 
                                                      CollisionFunctionStub);

    if (!largeExplosionObject)
    {
#ifdef DEBUG_OBJECTS
        KDebug_Alert("LargeExplosion could not be created!");
#endif
        return 0;
    }

    largeExplosionObject->x                  = x;
    largeExplosionObject->y                  = y;
    largeExplosionObject->spriteIndex        = 0;
    largeExplosionObject->sprite.size       = SPRITE_SIZE(4,4);
    largeExplosionObject->spriteIndex       = 0;
    largeExplosionObject->rectLeft          = 0;
    largeExplosionObject->rectRight         = PIXEL_TO_VIRTUAL(32);
    largeExplosionObject->rectTop           = 0;
    largeExplosionObject->rectBottom        = PIXEL_TO_VIRTUAL(32);

#ifdef DEBUG_OBJECTS
    KDebug_Alert("LargeExplosionCreate");
#endif

    return 1;
}

void LargeExplosionUpdate(ObjectStruct* largeExplosionObject)
{
    //KDebug_Alert("LargeExplosion Update");
    largeExplosionObject->spriteIndex++;

    largeExplosionObject->sprite.posx = VIRTUAL_TO_PIXEL(largeExplosionObject->x) + scrollData.scrollx_vdp - 16;
    largeExplosionObject->sprite.posy = VIRTUAL_TO_PIXEL(largeExplosionObject->y) - scrollData.scrolly_vdp - 16;

    if (largeExplosionObject->spriteIndex >> 2 > 3)
    {
#ifdef DEBUG_OBJECTS
        KDebug_Alert("LargeExplosion Animation Done");
#endif
        largeExplosionObject->objectState = OBJECTSTATE_INACTIVE;
    }
}

void LargeExplosionDestroy(ObjectStruct* largeExplosionObject)
{
#ifdef DEBUG_OBJECTS
    KDebug_Alert("LargeExplosionDestroy");
#endif
}

void LargeExplosionDraw(ObjectStruct* largeExplosionObject)
{
    largeExplosionObject->sprite.link  = spriteDrawIndex + 1;

    largeExplosionObject->sprite.tile_attr  = TILE_ATTR_FULL(PAL0,
															 1,
															 1,
															 1,
															 largeExplosionLoadedTileInfo.startIndex + ((largeExplosionObject->spriteIndex >> 2 ) << 4));

    VDP_setSpriteP(spriteDrawIndex, &largeExplosionObject->sprite);
    spriteDrawIndex++;


	/*
    u16 spriteLink = spriteDrawIndex + 1;
    u16 animationFrame = largeExplosionLoadedTileInfo.startIndex + ((largeExplosionObject->spriteIndex >> 2 ) << 2);
    s16 x = largeExplosionObject->sprite.posx;
    s16 y = largeExplosionObject->sprite.posy;

    VDP_setSprite(spriteDrawIndex, x, y, SPRITE_SIZE(2,2), TILE_ATTR_FULL(PAL0, 1, 0, 0, animationFrame), spriteLink);
    spriteDrawIndex++;
    spriteLink++;

    VDP_setSprite(spriteDrawIndex, x + 16, y, SPRITE_SIZE(2,2), TILE_ATTR_FULL(PAL0, 1, 0, 1, animationFrame), spriteLink);

    spriteDrawIndex++;
    spriteLink++;

    VDP_setSprite(spriteDrawIndex, x, y + 16, SPRITE_SIZE(2,2), TILE_ATTR_FULL(PAL0, 1, 1, 0, animationFrame), spriteLink);

    spriteDrawIndex++;
    spriteLink++;

    VDP_setSprite(spriteDrawIndex, x + 16, y + 16, SPRITE_SIZE(2,2), TILE_ATTR_FULL(PAL0, 1, 1, 1, animationFrame), spriteLink);

    spriteDrawIndex++;
    spriteLink++;
	*/
}


