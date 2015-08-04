#include "Explosion.h"

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

u16 ExplosionCreate(u16 x, u16 y)
{
    ObjectStruct* explosionObject = CreateObject(TYPE_EFFECT,
                                                 ExplosionUpdate, 
                                                 ExplosionDestroy, 
                                                 ExplosionDraw,
                                                 CollisionFunctionStub);

    if (!explosionObject)
    {
#ifdef DEBUG_OBJECTS
        KDebug_Alert("Explosion could not be created!");
#endif
        return 0;
    }

    explosionObject->x                  = x;
    explosionObject->y                  = y;
    explosionObject->sprite.size        = SPRITE_SIZE(2,2);
    explosionObject->spriteIndex        = 0;

#ifdef DEBUG_OBJECTS
    KDebug_Alert("ExplosionCreate");
#endif

    return 1;
}

void ExplosionUpdate(ObjectStruct* explosionObject)
{
    //KDebug_Alert("Explosion Update");
    explosionObject->spriteIndex++;

    explosionObject->sprite.posx = VIRTUAL_TO_PIXEL(explosionObject->x) + scrollData.scrollx_vdp - 8;
    explosionObject->sprite.posy = VIRTUAL_TO_PIXEL(explosionObject->y) - scrollData.scrolly_vdp - 8;


    if (explosionObject->spriteIndex >> 2 > 4)
    {
#ifdef DEBUG_OBJECTS
        KDebug_Alert("Explosion Animation Done");
#endif
        explosionObject->objectState = OBJECTSTATE_INACTIVE;
    }
}

void ExplosionDestroy(ObjectStruct* explosionObject)
{
#ifdef DEBUG_OBJECTS
    KDebug_Alert("ExplosionDestroy");
#endif
}

void ExplosionDraw(ObjectStruct* explosionObject)
{
    explosionObject->sprite.link  = spriteDrawIndex + 1;
    explosionObject->sprite.tile_attr  = TILE_ATTR_FULL(PAL0,
                                                        1,
                                                        explosionObject->spriteIndex & 1,
                                                        explosionObject->spriteIndex & 3,
                                                        explosionLoadedTileInfo.startIndex + ((explosionObject->spriteIndex >> 2 ) << 2));

    VDP_setSpriteP(spriteDrawIndex, &explosionObject->sprite);
    spriteDrawIndex++;
}
