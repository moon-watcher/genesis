#include "Poof.h"

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

u16 PoofCreate(u16 x, u16 y)
{
    ObjectStruct* poofObject = CreateObject(TYPE_EFFECT, PoofUpdate, PoofDestroy, PoofDraw, CollisionFunctionStub);

    if (!poofObject)
    {
#ifdef DEBUG_OBJECTS
        KDebug_Alert("Poof could not be created!");
#endif
        return 0;
    }

    poofObject->x                  = x;
    poofObject->y                  = y;
    poofObject->spriteIndex        = 0;

#ifdef DEBUG_OBJECTS
    KDebug_Alert("PoofCreate");
#endif

    return 1;
}

void PoofUpdate(ObjectStruct* poofObject)
{
    //KDebug_Alert("Poof Update");
    poofObject->spriteIndex++;

    poofObject->sprite.posx = VIRTUAL_TO_PIXEL(poofObject->x) + scrollData.scrollx_vdp - 16;
    poofObject->sprite.posy = VIRTUAL_TO_PIXEL(poofObject->y) - scrollData.scrolly_vdp - 16;

    if (poofObject->spriteIndex >> 2 > 3)
    {
#ifdef DEBUG_OBJECTS
        KDebug_Alert("Poof Animation Done");
#endif
        poofObject->objectState = OBJECTSTATE_INACTIVE;
    }
}

void PoofDestroy(ObjectStruct* poofObject)
{
#ifdef DEBUG_OBJECTS
    KDebug_Alert("PoofDestroy");
#endif
}

void PoofDraw(ObjectStruct* poofObject)
{
    u16 spriteLink = spriteDrawIndex + 1;
    u16 animationFrame = poofLoadedTileInfo.startIndex + ((poofObject->spriteIndex >> 2 ) << 2);
    s16 x = poofObject->sprite.posx;
    s16 y = poofObject->sprite.posy;

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
}
