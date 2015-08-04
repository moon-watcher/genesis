#include "LevelDefinitions.h"

#include "Level001Section001.h"
#include "Level001Section002.h"
#include "Level001Section003.h"

#define NUM_LEVEL001_SECTIONS      3



const SectionDefinitionStruct* levelSections[NUM_LEVEL001_SECTIONS] = 
{
    &level001Section001Definition,
    &level001Section002Definition,
    &level001Section003Definition
};

const LevelDefinitionStruct level001Definition =
{
    NUM_LEVEL001_SECTIONS,
    levelSections
};

