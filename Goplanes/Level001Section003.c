#include "Level001Section003.h"

#include <genesis.h>
#include <genres.h>

#include "Config.h"
#include "Debug.h"
#include "GameFont.h"
#include "LevelManager.h"
#include "MathUtils.h"
#include "SpritesAndMaps.h"
#include "VDP_Extra.h"

#include "BreakableRock4x4.h"
#include "EnemyPlane.h"

void Level001Section003_PrecacheTileAssetsToVDP()
{
    SetTileStartIndexToSectionTileStartIndex();
    LoadSpriteDataToVDP(&backgroundSprite, &backgroundLoadedTileInfo);
    LoadSpriteDataToVDP(&foregroundSprite, &foregroundLoadedTileInfo);
    LoadSpriteDataToVDP(&breakableRockSprite, &breakableRockLoadedTileInfo);
    LoadSpriteDataToVDP(&enemyPlaneSprite, &enemyPlaneLoadedTileInfo);

    VDP_loadFont((const u32 *)gameFont, 1);
}

void Level001Section003_SetupPalettes()
{
    VDP_setPalette(PAL0, goplanesSprite.pal);
    VDP_setPalette(PAL1, enemyPlaneSprite.pal);
    VDP_setPalette(PAL2, backgroundSprite.pal);
    VDP_setPalette(PAL3, foregroundSprite.pal);
}

void Level001Section003_SpawnObjects()
{
    SpawnObjects(&level001section003spawns);
}

void Level001Section003_SetupSection()
{

}

void Level001Section003_SetupSectionResources()
{
    LevelManager_SetTileMaps(&level001section003tilemap, &smallmap_background, grass_tiledata);
    Level001Section003_PrecacheTileAssetsToVDP();
    Level001Section003_SetupPalettes();
}

void Level001Section003_UpdateSection()
{

}

void Level001Section003_CloseSection()
{

}


const SectionDefinitionStruct level001Section003Definition =
{
    Level001Section003_SetupSection,
    Level001Section003_SetupSectionResources,
    Level001Section003_UpdateSection,
    Level001Section003_CloseSection,        
    Level001Section003_SpawnObjects,
    1,
    {
        {{TILE_TO_VIRTUAL(0),  TILE_TO_VIRTUAL(1),  TILE_TO_VIRTUAL(0), TILE_TO_VIRTUAL(63)}, &level001Section002Definition, 1},
        {{0, 0, 0, 0}, 0, 0},
        {{0, 0, 0, 0}, 0, 0},
        {{0, 0, 0, 0}, 0, 0}
    }
};


