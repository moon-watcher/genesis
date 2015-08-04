#include "Coin.h"

#include <kdebug.h>
#include <vdp_spr.h>
#include <vdp_tile.h>


#include "CoinSparkle.h"
#include "Collisions.h"
#include "Debug.h"
#include "Explosion.h"
#include "LevelManager.h"
#include "MathUtils.h"
#include "Objects.h"
#include "Player.h"
#include "SpritesAndMaps.h"

const u16 coinAnimationFrames[6] = 
{
    TILE_ATTR_FULL(PAL0,1,0,0,0),
    TILE_ATTR_FULL(PAL0,1,0,0,(1 << 2)),
    TILE_ATTR_FULL(PAL0,1,0,0,(2 << 2)),
    TILE_ATTR_FULL(PAL0,1,0,0,(3 << 2)),
    TILE_ATTR_FULL(PAL0,1,0,0,(2 << 2)),
    TILE_ATTR_FULL(PAL0,1,0,0,(1 << 2))
};

u16 CoinCreate(s16 x, s16 y)
{
    ObjectStruct* coinObject = CreateObject(TYPE_PICKUP,
                                            CoinUpdate, 
                                            CoinDestroy, 
                                            CoinDraw,
                                            CoinCollide);

    if (!coinObject)
    {
#ifdef DEBUG_OBJECTS
        KDebug_Alert("Coin could not be created!");
#endif
        return 0;
    }

    coinObject->x                 = x;
    coinObject->y                 = y;
    coinObject->speedx            = 0;
    coinObject->speedy            = 0;
    coinObject->sprite.size       = SPRITE_SIZE(2,2);
    coinObject->spriteIndex       = 0;
    coinObject->rectLeft          = 0;
    coinObject->rectRight         = PIXEL_TO_VIRTUAL(16);
    coinObject->rectTop           = 0;
    coinObject->rectBottom        = PIXEL_TO_VIRTUAL(16);
    coinObject->damage            = 0;

#ifdef DEBUG_OBJECTS
    KDebug_Alert("CoinCreate");
#endif

    return 1;
}

void CoinUpdate(ObjectStruct* coinObject)
{
    //KDebug_Alert("Coin Update");
    coinObject->x += coinObject->speedx;
    coinObject->y += coinObject->speedy;

    coinObject->spriteIndex++;

    if (coinObject->spriteIndex > 47)
    {
        coinObject->spriteIndex = 0;
    }

    coinObject->sprite.posx = VIRTUAL_TO_PIXEL(coinObject->x) + scrollData.scrollx_vdp;
    coinObject->sprite.posy = VIRTUAL_TO_PIXEL(coinObject->y) - scrollData.scrolly_vdp;
    coinObject->sprite.tile_attr = coinAnimationFrames[coinObject->spriteIndex >> 3] + coinLoadedTileInfo.startIndex;
}

void CoinDestroy(ObjectStruct* coinObject)
{
#ifdef DEBUG_OBJECTS
    KDebug_Alert("CoinDestroy");
#endif
}

void CoinDraw(ObjectStruct* coinObject)
{
    coinObject->sprite.link  = spriteDrawIndex + 1;
    VDP_setSpriteP(spriteDrawIndex, &coinObject->sprite);
    spriteDrawIndex++;
}

void CoinCollide(ObjectStruct* coinObject, ObjectStruct* collidedObject)
{
    coinObject->objectState = OBJECTSTATE_INACTIVE;

    playerData.numCoins++;
	UpdateHUDCoins();


    if (playerData.numCoins > 999)
    {
        playerData.numCoins = 999;
    }

    CoinSparkleCreate(coinObject->x + 4, coinObject->y + 4);
}
