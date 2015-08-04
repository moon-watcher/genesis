#include "Physics.h"

#include <kdebug.h>

#include "Collisions.h"
#include "Debug.h"
#include "LevelManager.h"
#include "SpritesAndMaps.h"

collidesWithTileFunctionType collidesWithTile;

void SetupPhysics(const TileMap* tileMap)
{
    collidesWithTile = CollidesWithTile;
}
