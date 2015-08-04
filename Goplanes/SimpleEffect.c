#include "SimpleEffect.h"

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

u16 SimpleEffectCreate(u16 x, 
                       u16 y, 
                       u16 speedx, 
                       u16 speedy, 
                       u16 numSpriteFrames,
                       u16 animationSpeed,
                       u16 spriteFrameWidth,
                       u16 spriteFrameHeight,
                       u16 baseTileAttr)
{
    ObjectStruct* simpleEffectObject = CreateObject(TYPE_EFFECT, 
                                                    SimpleEffectUpdate, 
                                                    SimpleEffectDestroy, 
                                                    SimpleEffectDraw,
                                                    CollisionFunctionStub);

    if (!simpleEffectObject)
    {
#ifdef DEBUG_OBJECTS
        KDebug_Alert("SimpleEffect could not be created!");
#endif
        return 0;
    }

    simpleEffectObject->x                  = x;
    simpleEffectObject->y                  = y;
    simpleEffectObject->speedx             = speedx;
    simpleEffectObject->speedy             = speedy;
    simpleEffectObject->sprite.size        = SPRITE_SIZE(spriteFrameWidth,spriteFrameHeight);
    simpleEffectObject->spriteIndex        = 0;
    simpleEffectObject->numSpriteFrames    = numSpriteFrames;
    simpleEffectObject->numTilesInOneFrame = spriteFrameWidth * spriteFrameHeight;
    simpleEffectObject->animationSpeed     = animationSpeed;
    simpleEffectObject->baseTileAttr       = baseTileAttr;

#ifdef DEBUG_OBJECTS
    KDebug_Alert("SimpleEffectCreate");
#endif

    return 1;
}

void SimpleEffectUpdate(ObjectStruct* simpleEffectObject)
{
    //KDebug_Alert("SimpleEffect Update");
    simpleEffectObject->spriteIndex++;

    simpleEffectObject->x += simpleEffectObject->speedx;
    simpleEffectObject->y += simpleEffectObject->speedy;

    simpleEffectObject->sprite.posx = VIRTUAL_TO_PIXEL(simpleEffectObject->x) + scrollData.scrollx_vdp - 8;
    simpleEffectObject->sprite.posy = VIRTUAL_TO_PIXEL(simpleEffectObject->y) - scrollData.scrolly_vdp - 8;


    if (simpleEffectObject->spriteIndex >> simpleEffectObject->animationSpeed > simpleEffectObject->numSpriteFrames)
    {
#ifdef DEBUG_OBJECTS
        KDebug_Alert("SimpleEffect Animation Done");
#endif
        simpleEffectObject->objectState = OBJECTSTATE_INACTIVE;
    }
}

void SimpleEffectDestroy(ObjectStruct* simpleEffectObject)
{
#ifdef DEBUG_OBJECTS
    KDebug_Alert("SimpleEffectDestroy");
#endif
}

void SimpleEffectDraw(ObjectStruct* simpleEffectObject)
{
    simpleEffectObject->sprite.link  = spriteDrawIndex + 1;
    simpleEffectObject->sprite.tile_attr = simpleEffectObject->baseTileAttr;
    simpleEffectObject->sprite.tile_attr += (simpleEffectObject->spriteIndex >> simpleEffectObject->animationSpeed) * simpleEffectObject->numTilesInOneFrame;

    VDP_setSpriteP(spriteDrawIndex, &simpleEffectObject->sprite);
    spriteDrawIndex++;
}
