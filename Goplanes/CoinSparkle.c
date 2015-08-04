#include "CoinSparkle.h"

#include <kdebug.h>
#include <vdp_spr.h>
#include <vdp_tile.h>


#include "Debug.h"
#include "LevelManager.h"
#include "MathUtils.h"
#include "Objects.h"
#include "Player.h"
#include "SpritesAndMaps.h"

u16 CoinSparkleCreate(s16 x, s16 y)
{
    ObjectStruct* coinSparkleObject = CreateObject(TYPE_EFFECT,
                                                   CoinSparkleUpdate, 
                                                   CoinSparkleDestroy, 
                                                   CoinSparkleDraw,
                                                   CoinSparkleCollide);

    if (!coinSparkleObject)
    {
#ifdef DEBUG_OBJECTS
        KDebug_Alert("CoinSparkle could not be created!");
#endif
        return 0;
    }

    coinSparkleObject->x                 = x;
    coinSparkleObject->y                 = y;
    coinSparkleObject->speedx            = 0;
    coinSparkleObject->speedy            = 0;
    coinSparkleObject->sprite.size       = SPRITE_SIZE(1,1);
    coinSparkleObject->spriteIndex       = 0;
    coinSparkleObject->rectLeft          = 0;
    coinSparkleObject->rectRight         = 0;
    coinSparkleObject->rectTop           = 0;
    coinSparkleObject->rectBottom        = 0;
    coinSparkleObject->damage            = 0;

#ifdef DEBUG_OBJECTS
    KDebug_Alert("CoinSparkleCreate");
#endif

    return 1;
}

void CoinSparkleUpdate(ObjectStruct* coinSparkleObject)
{
    coinSparkleObject->spriteIndex++;

    if (coinSparkleObject->spriteIndex > 27)
    {
        coinSparkleObject->objectState = OBJECTSTATE_INACTIVE;
    }
    else
    {
        coinSparkleObject->sprite.posx = VIRTUAL_TO_PIXEL(coinSparkleObject->x) + scrollData.scrollx_vdp;
        coinSparkleObject->sprite.posy = VIRTUAL_TO_PIXEL(coinSparkleObject->y) - scrollData.scrolly_vdp;
        coinSparkleObject->sprite.tile_attr = TILE_ATTR_FULL(PAL0,1,0,0,coinSparkleLoadedTileInfo.startIndex + (coinSparkleObject->spriteIndex >> 2));
    }
}

void CoinSparkleDestroy(ObjectStruct* coinSparkleObject)
{
#ifdef DEBUG_OBJECTS
    KDebug_Alert("CoinSparkleDestroy");
#endif
}

void CoinSparkleDraw(ObjectStruct* coinSparkleObject)
{
    coinSparkleObject->sprite.link  = spriteDrawIndex + 1;
    VDP_setSpriteP(spriteDrawIndex, &coinSparkleObject->sprite);
    spriteDrawIndex++;
}

void CoinSparkleCollide(ObjectStruct* coinSparkleObject, ObjectStruct* collidedObject)
{
}

