#ifndef SIMPLE_EFFECT_INCLUDE_H
#define SIMPLE_EFFECT_INCLUDE_H

#include <genesis.h>

#include "ObjectStruct.h"

u16 SimpleEffectCreate(u16 x, 
                       u16 y, 
                       u16 speedx, 
                       u16 speedy, 
                       u16 numSpriteFrames,
                       u16 animationSpeed,
                       u16 spriteFrameWidth,
                       u16 spriteFrameHeight,
                       u16 baseTileAttr);

void SimpleEffectUpdate(ObjectStruct* simpleEffectObject);
void SimpleEffectDestroy(ObjectStruct* simpleEffectObject);
void SimpleEffectDraw(ObjectStruct* simpleEffectObject);

#endif
