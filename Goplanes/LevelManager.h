#ifndef LEVEL_MANAGER_INCLUDE
#define LEVEL_MANAGER_INCLUDE

#include <genesis.h>

#include "TileMap.h"

void LevelManager_SetupLevel();
void LevelManager_SetScrollMode();
void LevelManager_SetupSection();
void LevelManager_SetupSectionResources();
void LevelManager_UpdateSection();
void LevelManager_SetupPlayerLevelStartPosition();
void LevelManager_SetupPlayerSectionStartPosition();
void LevelManager_UpdateTilePlanes();
void LevelManager_DrawTilePlanes();
void LevelManager_SetupBackgroundPlanes();
void LevelManager_UpdateScroll();
void LevelManager_UpdateCoinPickup();

void LevelManager_GoToNextSection();
void LevelManager_GoToGameOver();

void LevelManager_SetTileMaps(const TileMap* foregroundTileMap, 
                              const TileMap* backgroundTileMap,
                              const unsigned short* foregroundTileData);



typedef struct
{
    s32 scrollx_hires;
    s32 scrolly_hires;
    s32 scrollx_hires_clamped;
    s32 scrolly_hires_clamped;
    s16 scrollx_vdp;
    s16 scrolly_vdp;
    s32 scrollx_hires_limit;
    s32 scrolly_hires_limit;
} ScrollDataStruct;

extern ScrollDataStruct scrollData;

typedef struct
{
    const TileMap*    foreground;
    const TileMap*    background;
    const u16*        foregroundTileData;
    u16               mapWidthAsShiftValue;
    u16               mapHeightAsShiftValue;
} LevelDataStruct;


extern LevelDataStruct levelData;
extern u16 levelRunning;
extern s16 levelStartX;
extern s16 levelStartY;

#define MAX_COINS_IN_LEVEL				256
#define MAX_BREAKABLE_ROCKS_IN_LEVEL	256

extern u16 coinMap[MAX_COINS_IN_LEVEL];
extern u16 breakableRockMap[MAX_BREAKABLE_ROCKS_IN_LEVEL];



#endif
