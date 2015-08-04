#ifndef SPRITES_AND_MAPS_INCLUDE_H
#define SPRITES_AND_MAPS_INCLUDE_H

#include <genesis.h>

#include "ObjectSpawnPoints.h"

// Tile maps.
#include "smallmap2.h"
#include "smallmap_background.h"
#include "long128x64map.h"
#include "Level001Section001Tilemap.h"
#include "Level001Section001ExtendedTilemap.h"
#include "Level001Section001Extended2Tilemap.h"
#include "Level001Section002Tilemap.h"
#include "Level001Section003Tilemap.h"
#include "largemaptest.h"

#include "big256x128map.h"

// Object spawn points.
#include "Level001Section001Spawns.h"
#include "Level001Section002Spawns.h"
#include "Level001Section003Spawns.h"
#include "Level001Section001Extended2Spawns.h"

// Sections
#include "Level001Section001.h"
#include "Level001Section002.h"
#include "Level001Section003.h"

// Tileset data.
#include "GrassTileSetData.h"

// Genres Resources
#define IMPORT_SPRITE(spritename) extern struct genresSprites spritename

IMPORT_SPRITE(foregroundSprite);
IMPORT_SPRITE(backgroundSprite);
IMPORT_SPRITE(goplanesSprite);
IMPORT_SPRITE(bulletSprite);
IMPORT_SPRITE(explosionSprite);
IMPORT_SPRITE(poofSprite);
IMPORT_SPRITE(muzzleflashSprite);
IMPORT_SPRITE(largeExplosionSprite);
IMPORT_SPRITE(coinSprite);
IMPORT_SPRITE(coinSparkleSprite);
IMPORT_SPRITE(afterburnerSprite);
IMPORT_SPRITE(afterburnerChargeSprite);
IMPORT_SPRITE(breakableRockSprite);
IMPORT_SPRITE(enemyPlaneSprite);
IMPORT_SPRITE(exclamationSprite);
IMPORT_SPRITE(radarArrowSprite);
IMPORT_SPRITE(heartSprite);
IMPORT_SPRITE(fireballSprite);
IMPORT_SPRITE(fireballPickupSprite);
IMPORT_SPRITE(hudSprite);

// data type that maps sprites or map tiles into a location in the VDP's tile memory.
typedef struct
{
    u16 startIndex;
    u16 numTiles;
} LoadedTileInfo;

// sprite to VDP tile mappings.
#define IMPORT_LTI(lti) extern LoadedTileInfo lti
IMPORT_LTI(backgroundLoadedTileInfo);
IMPORT_LTI(foregroundLoadedTileInfo);
IMPORT_LTI(goplanesLoadedTileInfo);
IMPORT_LTI(bulletLoadedTileInfo);
IMPORT_LTI(explosionLoadedTileInfo);
IMPORT_LTI(poofLoadedTileInfo);
IMPORT_LTI(muzzleFlashLoadedTileInfo);
IMPORT_LTI(largeExplosionLoadedTileInfo);
IMPORT_LTI(coinLoadedTileInfo);
IMPORT_LTI(coinSparkleLoadedTileInfo);
IMPORT_LTI(afterburnerLoadedTileInfo);
IMPORT_LTI(afterburnerChargeLoadedTileInfo);
IMPORT_LTI(breakableRockLoadedTileInfo);
IMPORT_LTI(enemyPlaneLoadedTileInfo);
IMPORT_LTI(exclamationLoadedTileInfo);
IMPORT_LTI(radarArrowLoadedTileInfo);
IMPORT_LTI(heartLoadedTileInfo);
IMPORT_LTI(fireballLoadedTileInfo);
IMPORT_LTI(fireballPickupLoadedTileInfo);
IMPORT_LTI(hudLoadedTileInfo);


// functions to loads tiles and sprites into VDP. call reset first, then loadmapdata and
// loadspritedata will fill VDP tile memory sequentially.
void ResetTileStartIndex();
void StoreSectionTileStartIndex();
void SetTileStartIndexToSectionTileStartIndex();
void LoadSpriteDataToVDP(struct genresSprites* sprite, LoadedTileInfo* loadedTileInfo);

// Spawns objects from Object Spawn Point objects.
void SpawnObjects(const ObjectSpawnPoints* objectSpawnPoints);

#endif
