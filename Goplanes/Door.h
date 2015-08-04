#ifndef DOOR_INCLUDE_H
#define DOOR_INCLUDE_H

#include <genesis.h>

typedef struct
{
    s16 left;
    s16 right;
    s16 top;
    s16 bottom;
} Rect;

typedef struct 
{
    Rect doorArea;
    const void* destinationLevel; // Treated as LevelDefinitionStruct* destinationLevel. There are no foward declarations in C. 
    u16 destinationSectionDoorIndex;// the index into the destination level's door array. So we can figure out where to place the player.
} Door;

#endif
