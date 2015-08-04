#ifndef SECTION_DEFINITIONS_INCLUDE_H
#define SECTION_DEFINITIONS_INCLUDE_H

#include <genesis.h>
#include "Door.h"

typedef void (*sectionFunctionType)(void);

#define MAX_DOORS 4

typedef struct
{
    sectionFunctionType setupSection;
    sectionFunctionType setupSectionResources;
    sectionFunctionType updateSection;
    sectionFunctionType closeSection;
    sectionFunctionType spawnObjects;
    u16                 numDoors;
    Door                doors[MAX_DOORS];
} SectionDefinitionStruct;

typedef struct
{
    u16 numSections;
    const SectionDefinitionStruct** sections;
} LevelDefinitionStruct;

extern const LevelDefinitionStruct level001Definition;

#endif

