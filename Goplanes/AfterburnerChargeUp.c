#include "AfterburnerChargeUp.h"

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

u16 AfterburnerChargeUpCreate()
{
    ObjectStruct* afterburnerChargeUpObject = CreateObject(TYPE_EFFECT,
                                                           AfterburnerChargeUpUpdate, 
                                                           AfterburnerChargeUpDestroy, 
                                                           AfterburnerChargeUpDraw, 
                                                           CollisionFunctionStub);

    if (!afterburnerChargeUpObject)
    {
#ifdef DEBUG_OBJECTS
        KDebug_Alert("AfterburnerChargeUp could not be created!");
#endif
        return 0;
    }

    afterburnerChargeUpObject->spriteIndex        = 0;

#ifdef DEBUG_OBJECTS
    KDebug_Alert("AfterburnerChargeUpCreate");
#endif

    return 1;
}

void AfterburnerChargeUpUpdate(ObjectStruct* afterburnerChargeUpObject)
{
    //KDebug_Alert("AfterburnerChargeUp Update");
    afterburnerChargeUpObject->spriteIndex++;

    afterburnerChargeUpObject->x = playerObject->x;
    afterburnerChargeUpObject->y = playerObject->y;

    afterburnerChargeUpObject->sprite.posx = VIRTUAL_TO_PIXEL(afterburnerChargeUpObject->x) + scrollData.scrollx_vdp - 16;
    afterburnerChargeUpObject->sprite.posy = VIRTUAL_TO_PIXEL(afterburnerChargeUpObject->y) - scrollData.scrolly_vdp - 16;

    if (afterburnerChargeUpObject->spriteIndex >> 2 > 5)
    {
#ifdef DEBUG_OBJECTS
        KDebug_Alert("AfterburnerChargeUp Animation Done");
#endif
        afterburnerChargeUpObject->spriteIndex = 0;
    }

    if (playerObject->aiState != AI_STATE_CHARGING_AFTERBURNERS)
    {
        afterburnerChargeUpObject->objectState = OBJECTSTATE_INACTIVE;
    }
}

void AfterburnerChargeUpDestroy(ObjectStruct* afterburnerChargeUpObject)
{
#ifdef DEBUG_OBJECTS
    KDebug_Alert("AfterburnerChargeUpDestroy");
#endif
}

void AfterburnerChargeUpDraw(ObjectStruct* afterburnerChargeUpObject)
{
    u16 tempSpriteIndex = afterburnerChargeUpObject->spriteIndex;
    u16 spriteLink = spriteDrawIndex + 1;
    u16 animationFrame = afterburnerChargeLoadedTileInfo.startIndex + ((tempSpriteIndex >> 2 ) << 2);
    s16 x = afterburnerChargeUpObject->sprite.posx;
    s16 y = afterburnerChargeUpObject->sprite.posy;

    VDP_setSprite(spriteDrawIndex, x, y, SPRITE_SIZE(2,2), TILE_ATTR_FULL(PAL0, 1, 0, 0, animationFrame), spriteLink);
    spriteDrawIndex++;
    spriteLink++;

    tempSpriteIndex += 4;
    tempSpriteIndex %= 24;
    animationFrame = afterburnerChargeLoadedTileInfo.startIndex + ((tempSpriteIndex >> 2 ) << 2);
    VDP_setSprite(spriteDrawIndex, x + 16, y, SPRITE_SIZE(2,2), TILE_ATTR_FULL(PAL0, 1, 0, 1, animationFrame), spriteLink);

    spriteDrawIndex++;
    spriteLink++;
    tempSpriteIndex += 4;
    tempSpriteIndex %= 24;
    animationFrame = afterburnerChargeLoadedTileInfo.startIndex + ((tempSpriteIndex >> 2 ) << 2);
    VDP_setSprite(spriteDrawIndex, x, y + 16, SPRITE_SIZE(2,2), TILE_ATTR_FULL(PAL0, 1, 1, 0, animationFrame), spriteLink);

    spriteDrawIndex++;
    spriteLink++;
    tempSpriteIndex += 4;
    tempSpriteIndex %= 24;
    animationFrame = afterburnerChargeLoadedTileInfo.startIndex + ((tempSpriteIndex >> 2 ) << 2);
    VDP_setSprite(spriteDrawIndex, x + 16, y + 16, SPRITE_SIZE(2,2), TILE_ATTR_FULL(PAL0, 1, 1, 1, animationFrame), spriteLink);

    spriteDrawIndex++;
    spriteLink++;
}


