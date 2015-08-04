#include "HUD.h"

#include <genesis.h>
#include <kdebug.h>
#include <vdp_spr.h>
#include <vdp_tile.h>

#include "Collisions.h"
#include "Debug.h"
#include "Game.h"
#include "GameFont.h"
#include "LevelManager.h"
#include "MathUtils.h"
#include "Player.h"
#include "Objects.h"
#include "SpritesAndMaps.h"

char livesString[2];
char coinString[3];
char fpsString[3];
u16 goplanesTileAttr;
u16 coinTileAttr;
u16 healthBarTopAttr;
u16 healthBarBottomAttr;
u32 oldFPS;

SpriteDef goplanesIconSprite;
SpriteDef coinIconSprite;
SpriteDef healthBarTopSprite;
SpriteDef healthBarBottomSprite;

// General sprite drawing function.
void DrawString(u16 x, u16 y, const char* string, u16 stringLength)
{
    u16 loop = 0;
    while (stringLength--)
    {
        VDP_setSprite(spriteDrawIndex, 
                      x + (loop << 3), 
                      y, 
                      SPRITE_SIZE(1,1), 
                      TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_FONTINDEX + string[loop] - 32),
                      spriteDrawIndex + 1);
        loop++;
        spriteDrawIndex++;
    }
}

inline void DrawLivesString()
{
	//DrawString(34, 204, livesString, 2);

    VDP_setSprite(spriteDrawIndex, 
                    34, 
                    204, 
                    SPRITE_SIZE(1,1), 
                    TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_FONTINDEX - 32) + *livesString,
                    spriteDrawIndex + 1);
    spriteDrawIndex++;

    VDP_setSprite(spriteDrawIndex, 
                    42, 
                    204, 
                    SPRITE_SIZE(1,1), 
                    TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_FONTINDEX - 32) + *(livesString + 1),
                    spriteDrawIndex + 1);
    spriteDrawIndex++;

}

inline void DrawCoinsString()
{
	//DrawString(272, 204, coinString, 3);

    VDP_setSprite(spriteDrawIndex, 
                    272, 
                    204, 
                    SPRITE_SIZE(1,1), 
                    TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_FONTINDEX - 32) + *coinString,
                    spriteDrawIndex + 1);
    spriteDrawIndex++;

    VDP_setSprite(spriteDrawIndex, 
                    280, 
                    204, 
                    SPRITE_SIZE(1,1), 
                    TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_FONTINDEX - 32) + *(coinString + 1),
                    spriteDrawIndex + 1);
    spriteDrawIndex++;

    VDP_setSprite(spriteDrawIndex, 
                    288, 
                    204, 
                    SPRITE_SIZE(1,1), 
                    TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_FONTINDEX - 32) + *(coinString + 2),
                    spriteDrawIndex + 1);
    spriteDrawIndex++;

}

inline void DrawFPSString()
{
	if (debugSettings.showFPSCounter == FALSE)
	{
		return;
	}

	// Draw FPS String
	uintToStr(getFPS(), fpsString, 3);

    VDP_setSprite(spriteDrawIndex, 
                    144, 
                    8, 
                    SPRITE_SIZE(1,1), 
                    TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_FONTINDEX - 32) + *fpsString,
                    spriteDrawIndex + 1);
    spriteDrawIndex++;

    VDP_setSprite(spriteDrawIndex, 
                    152, 
                    8, 
                    SPRITE_SIZE(1,1), 
                    TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_FONTINDEX - 32) + *(fpsString + 1),
                    spriteDrawIndex + 1);
    spriteDrawIndex++;

    VDP_setSprite(spriteDrawIndex, 
                    160, 
                    8, 
                    SPRITE_SIZE(1,1), 
                    TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_FONTINDEX - 32) + *(fpsString + 2),
                    spriteDrawIndex + 1);
    spriteDrawIndex++;
}

/*
const u16 radarArrowAnimationFrames[32] = 
{
    TILE_ATTR_FULL(PAL0,0,0,0,0),
    TILE_ATTR_FULL(PAL0,0,0,0,(1 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,0,(2 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,0,(3 * 9)),
    
    TILE_ATTR_FULL(PAL0,0,0,0,(4 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,0,(5 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,0,(6 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,0,(7 * 9)),
    
    TILE_ATTR_FULL(PAL0,0,0,1,(8 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,1,(7 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,1,(6 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,1,(5 * 9)),
    
    TILE_ATTR_FULL(PAL0,0,0,1,(4 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,1,(3 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,1,(2 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,1,(1 * 9)),
    
    TILE_ATTR_FULL(PAL0,0,1,1,0),
    TILE_ATTR_FULL(PAL0,0,1,1,(1 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,1,(2 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,1,(3 * 9)),
    
    TILE_ATTR_FULL(PAL0,0,1,1,(4 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,1,(5 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,1,(6 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,1,(7 * 9)),
    
    TILE_ATTR_FULL(PAL0,0,1,0,(8 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,0,(7 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,0,(6 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,0,(5 * 9)),
    
    TILE_ATTR_FULL(PAL0,0,1,0,(4 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,0,(3 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,0,(2 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,0,(1 * 9))
};

void PlaceIcon(ObjectStruct* enemyPlaneObject)
{
    s16 tile_distance_x = VIRTUAL_TO_TILE(-scrollData.scrollx_hires_clamped + PIXEL_TO_VIRTUAL(160) - enemyPlaneObject->x);
    s16 tile_distance_y = VIRTUAL_TO_TILE(scrollData.scrolly_hires_clamped + PIXEL_TO_VIRTUAL(124) - enemyPlaneObject->y);
    u16 x_is_negative = mathutils_isnegative(tile_distance_x);
    u16 y_is_negative = mathutils_isnegative(tile_distance_y);

    tile_distance_x = mathutils_abs(tile_distance_x);
    tile_distance_y = mathutils_abs(tile_distance_y);

    if (tile_distance_x > DISTANCE_ANGLE_TABLE_WIDTH - 1 || tile_distance_y > DISTANCE_ANGLE_TABLE_HEIGHT - 1)
    {
        return;
    }

    u16 angleValue = GET_ANGLE_VALUE(tile_distance_x, tile_distance_y); 

    u16 radarPositionIndex = angleValue;
    u16 radarArrowAnimationFrame = angleValue >> 3; // 64 -> 8

    if (x_is_negative)
    {
        if (!y_is_negative)
        {
            radarPositionIndex = 255 - radarPositionIndex;
            radarArrowAnimationFrame = 31 - radarArrowAnimationFrame;
        }
    }
    else
    {
        if (y_is_negative)
        {
            radarPositionIndex = 127 - radarPositionIndex;
            radarArrowAnimationFrame = 15 - radarArrowAnimationFrame;
        }
        else
        {
            radarPositionIndex += 128;
            radarArrowAnimationFrame += 16;
        }
    } 

    s16 posx = radar_screenpos_x[radarPositionIndex] - 12;
    s16 posy = radar_screenpos_y[radarPositionIndex] - 12;

    VDP_setSprite(spriteDrawIndex, 
                  posx, 
                  posy, 
                  SPRITE_SIZE(3,3), 
                  TILE_ATTR_FULL(PAL0,0,0,0,radarArrowAnimationFrames[radarArrowAnimationFrame] + radarArrowLoadedTileInfo.startIndex), 
                  spriteDrawIndex + 1);
    
    spriteDrawIndex++;
}

void DrawIcons()
{
    u16 counter = enemyCollection.numInvisibleObjects;
    ObjectStruct** enemyList = enemyCollection.objectInvisibilityList;
    
    while (counter--)
    {
        ObjectStruct* enemyObjectStruct = (*enemyList);
        if (enemyObjectStruct->healthPoints > 0)
        {
            PlaceIcon(enemyObjectStruct);
        }

        enemyList++;
    }    
}
*/

const u16 healthToSpriteIndexTop[9] =
{
    0,
    0,
    0,
    0,
    0,
    1 << 2,
    2 << 2,
    3 << 2,
    4 << 2    
};

const u16 healthToSpriteIndexBottom[9] =
{
    0,
    1 << 2,
    2 << 2,
    3 << 2,
    4 << 2,   
    4 << 2,        
    4 << 2,
    4 << 2,
    4 << 2
};




void DrawHUD()
{
    // Draw goplanes icon.
	goplanesIconSprite.link = spriteDrawIndex + 1;
    VDP_setSpriteP(spriteDrawIndex, &goplanesIconSprite);
    spriteDrawIndex++;

    // Draw coin icon.
	coinIconSprite.link = spriteDrawIndex + 1;
    VDP_setSpriteP(spriteDrawIndex, &coinIconSprite);
    spriteDrawIndex++;

	// Draw Health Bar (two parts)
	healthBarTopSprite.link = spriteDrawIndex + 1;
    VDP_setSpriteP(spriteDrawIndex, &healthBarTopSprite);
    spriteDrawIndex++;

	healthBarBottomSprite.link = spriteDrawIndex + 1;
    VDP_setSpriteP(spriteDrawIndex, &healthBarBottomSprite);
    spriteDrawIndex++;

    //DrawIcons(); // too heavy.
	DrawLivesString();
	DrawCoinsString();

	DrawFPSString();
}

void InitHUD()
{
	UpdateHUDHealth();
	UpdateHUDLives();
	UpdateHUDCoins();

	// init goplanes icon.
	goplanesIconSprite.posx = 10;
	goplanesIconSprite.posy = 188;
	goplanesIconSprite.tile_attr = TILE_ATTR_FULL(PAL0, 1, 0, 0, goplanesLoadedTileInfo.startIndex);
	goplanesIconSprite.size = SPRITE_SIZE(3,3);

	// init coins icon.
	coinIconSprite.posx = 294;
	coinIconSprite.posy = 190;
	coinIconSprite.tile_attr = TILE_ATTR_FULL(PAL0, 1, 0, 0, coinLoadedTileInfo.startIndex);
	coinIconSprite.size = SPRITE_SIZE(2,2);

	// init health bar.
	healthBarTopSprite.posx = 10;
	healthBarTopSprite.posy = 10;
	healthBarTopSprite.size = SPRITE_SIZE(1,4);
	healthBarBottomSprite.posx = 10;
	healthBarBottomSprite.posy = 42;	
	healthBarBottomSprite.size = SPRITE_SIZE(1,4);

	oldFPS = 0;
}

void UpdateHUDHealth()
{
	healthBarTopSprite.tile_attr = TILE_ATTR_FULL(PAL0, 1, 0, 0, heartLoadedTileInfo.startIndex + healthToSpriteIndexTop[playerObject->healthPoints]);
	healthBarBottomSprite.tile_attr = TILE_ATTR_FULL(PAL0, 1, 0, 0, heartLoadedTileInfo.startIndex + healthToSpriteIndexBottom[playerObject->healthPoints]);
}

void UpdateHUDLives()
{
    intToStr(playerData.lives, &livesString[0], 2);
}

void UpdateHUDCoins()
{
    intToStr(playerData.numCoins, &coinString[0], 3);
}
