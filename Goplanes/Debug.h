#ifndef DEBUG_INCLUDE_H
#define DEBUG_INCLUDE_H

#include <genesis.h>
#include <vdp_spr.h>

#include "Config.h"
#include "ObjectStruct.h"


// Prints value with KDebug_Alert
void PrintNumber(u32 value);
void PrintText(char* message);
void PrintSprite(const SpriteDef* sprite);
void PrintObjectStruct(ObjectStruct* objectStruct);

// Prints value on the APLAN
void PrintAPLAN(u32 value, u16 x, u16 y);


#ifdef PRINT_FUNCTION_NAMES
#define PRINT_FUNCTION_NAME(functionName) PrintText(functionName)
#else
#define PRINT_FUNCTION_NAME(functionName)   
#endif

#endif
