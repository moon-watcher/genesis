#include "Level001Section002.h"

#include <genesis.h>
#include <genres.h>

#include "Config.h"
#include "Debug.h"
#include "GameFont.h"
#include "LevelManager.h"
#include "Level001Section002Spawns.h"
#include "MathUtils.h"
#include "SpritesAndMaps.h"
#include "VDP_Extra.h"

#include "Level001Section001.h"
#include "Level001Section003.h"

void Level001Section002_PrecacheTileAssetsToVDP()
{
    SetTileStartIndexToSectionTileStartIndex();
    LoadSpriteDataToVDP(&backgroundSprite, &backgroundLoadedTileInfo);
    LoadSpriteDataToVDP(&foregroundSprite, &foregroundLoadedTileInfo);
    LoadSpriteDataToVDP(&breakableRockSprite, &breakableRockLoadedTileInfo);
    LoadSpriteDataToVDP(&enemyPlaneSprite, &enemyPlaneLoadedTileInfo);

    VDP_loadFont((const u32 *)gameFont, 1);
}

void Level001Section002_SetupPalettes()
{
    VDP_setPalette(PAL0, goplanesSprite.pal);
    VDP_setPalette(PAL1, enemyPlaneSprite.pal);
    VDP_setPalette(PAL2, backgroundSprite.pal);
    VDP_setPalette(PAL3, foregroundSprite.pal);
}

void Level001Section002_SpawnObjects()
{
    SpawnObjects(&Level001Section002Spawns);
}

void Level001Section002_SetupSection()
{

}

void Level001Section002_SetupSectionResources()
{
    LevelManager_SetTileMaps(&level001section002tilemap, &smallmap_background, grass_tiledata);
    Level001Section002_PrecacheTileAssetsToVDP();
    Level001Section002_SetupPalettes();
}

void Level001Section002_UpdateSection()
{

}

void Level001Section002_CloseSection()
{

}

const SectionDefinitionStruct level001Section002Definition =
{
    Level001Section002_SetupSection,
    Level001Section002_SetupSectionResources,
    Level001Section002_UpdateSection,
    Level001Section002_CloseSection,        
    Level001Section002_SpawnObjects,
    2,
    {
        {{TILE_TO_VIRTUAL(0),  TILE_TO_VIRTUAL(1),  TILE_TO_VIRTUAL(0), TILE_TO_VIRTUAL(63)}, &level001Section001Definition, 0},
        {{TILE_TO_VIRTUAL(62), TILE_TO_VIRTUAL(63), TILE_TO_VIRTUAL(0), TILE_TO_VIRTUAL(63)}, &level001Section003Definition, 0},
        {{0, 0, 0, 0}, 0, 0},
        {{0, 0, 0, 0}, 0, 0}
    }
};

