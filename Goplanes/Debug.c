#include "Debug.h"

#include <kdebug.h>

void PrintNumber(u32 value)
{
	KDebug_AlertNumber(value);
}

void PrintText(char* message)
{
    KDebug_Alert(message);
}

void PrintSprite(const SpriteDef* sprite)
{
    PrintNumber(sprite->posx);
    PrintNumber(sprite->posy);
    PrintNumber(sprite->tile_attr);
    PrintNumber(sprite->size);
    PrintNumber(sprite->link);
}

void PrintObjectStruct(ObjectStruct* objectStruct)
{
    PrintText("****** OBJECT *******");
    PrintSprite(&objectStruct->sprite);
    PrintNumber(objectStruct->x);
    PrintNumber(objectStruct->y);
    PrintNumber((u32)objectStruct->updateFunction);
    PrintNumber((u32)objectStruct->destroyFunction);
    PrintNumber((u32)objectStruct->drawFunction);
    PrintNumber((u32)objectStruct->collisionFunction);
    PrintNumber(objectStruct->objectState);
    PrintNumber(objectStruct->aiState);
    PrintNumber(objectStruct->spriteIndex);
    PrintNumber(objectStruct->speedx);
    PrintNumber(objectStruct->speedy);
    PrintNumber(objectStruct->lifetime);
    PrintNumber(objectStruct->objectType);
    PrintNumber(objectStruct->rectLeft);
    PrintNumber(objectStruct->rectRight);
    PrintNumber(objectStruct->rectTop);
    PrintNumber(objectStruct->rectBottom);
    PrintNumber(objectStruct->healthPoints);
    PrintNumber(objectStruct->damage);
    PrintText("*********************");
}

void PrintAPLAN(u32 value, u16 x, u16 y)
{
    char tempString[16];
    intToStr(value, tempString, 16);
    VDP_drawText(tempString, x, y);
}

