#include "Game.h"

#include <genesis.h>


#include "Debug.h"
#include "Game.h"
#include "LevelManager.h"
#include "MathUtils.h"
#include "Objects.h"
#include "Physics.h"
#include "Player.h"
#include "PlayerPhysics.h"
#include "VDP_Extra.h"

#include "SpritesAndMaps.h"

u16 gameState;
u16 joystate;
u16 oldjoystate;
ButtonPressedStateStruct joyButtonPressedState;
DebugSettingsStruct debugSettings;

LoopFunction currentLoopFunction;

void InitGame()
{
    SetupGameResources();
	debugSettings.invincibility = FALSE;
	debugSettings.waitforvsync = TRUE;
	debugSettings.showFPSCounter = TRUE;
}

void PrecacheStandardAssetsToVDP()
{
    ResetTileStartIndex();
	LoadSpriteDataToVDP(&goplanesSprite, &goplanesLoadedTileInfo);
	LoadSpriteDataToVDP(&bulletSprite, &bulletLoadedTileInfo);
	LoadSpriteDataToVDP(&explosionSprite, &explosionLoadedTileInfo);
	LoadSpriteDataToVDP(&poofSprite, &poofLoadedTileInfo);
	LoadSpriteDataToVDP(&muzzleflashSprite, &muzzleFlashLoadedTileInfo);
	LoadSpriteDataToVDP(&largeExplosionSprite, &largeExplosionLoadedTileInfo);
    LoadSpriteDataToVDP(&coinSprite, &coinLoadedTileInfo);
    LoadSpriteDataToVDP(&coinSparkleSprite, &coinSparkleLoadedTileInfo);
    LoadSpriteDataToVDP(&afterburnerSprite, &afterburnerLoadedTileInfo);
    LoadSpriteDataToVDP(&afterburnerChargeSprite, &afterburnerChargeLoadedTileInfo);
    LoadSpriteDataToVDP(&exclamationSprite, &exclamationLoadedTileInfo);
    LoadSpriteDataToVDP(&radarArrowSprite, &radarArrowLoadedTileInfo);
    LoadSpriteDataToVDP(&heartSprite, &heartLoadedTileInfo);
    LoadSpriteDataToVDP(&fireballSprite, &fireballLoadedTileInfo);
    LoadSpriteDataToVDP(&fireballPickupSprite, &fireballPickupLoadedTileInfo);
	LoadSpriteDataToVDP(&hudSprite, &hudLoadedTileInfo);
    StoreSectionTileStartIndex();
}

void SetupGameResources()
{
    PrecacheStandardAssetsToVDP();
}


void GameLoop()
{
    VDP_resetSprites();
    playerObject->updateFunction(playerObject);
    playerObject->lifetime++;
    LevelManager_UpdateSection();
                
    ObjectManager_UpdateObjects();
	LevelManager_UpdateCoinPickup();
	LevelManager_UpdateBreakableRocks();
    ObjectManager_DrawObjects();
    LevelManager_UpdateTilePlanes();     

    // wait for vsync and then draw
	if (debugSettings.waitforvsync != FALSE)
	{
		MyVDP_waitVSync();                
	}
	VDP_updateSprites();
	LevelManager_DrawTilePlanes();     

    if (joyButtonPressedState.start)
    {
        OpenInGameMenu();
    }
}

#define MENU_ITEM_RETURN			0
#define MENU_ITEM_ENABLE_DEBUG		1
#define MENU_ITEM_INVINCIBILITY		2
#define MENU_ITEM_VSYNC				3
#define MENU_ITEM_FPSCOUNTER		4
#define MAX_MENU_ITEMS 5
u16 menuItem = 0;

void joyEventCallback(u16 joy, u16 changed, u16 state)
{
    if ((changed == BUTTON_UP) && (state & BUTTON_UP))
    {
        if (menuItem == 0)
        {
            menuItem = MAX_MENU_ITEMS - 1;
        }
        else
        {
            menuItem--;
        }
    }

    if ((changed == BUTTON_DOWN) && (state & BUTTON_DOWN))
    {
        if (menuItem == MAX_MENU_ITEMS - 1)
        {
            menuItem = 0;
        }
        else
        {
            menuItem++;
        }
    }
}

void DrawText()
{
    VDP_drawText("Return", 15, 10);

    if (playerObject->aiState != AI_STATE_DEBUG)
    {
        VDP_drawText("Debug Mode: Off", 15, 11);
    }
    else
    {
        VDP_drawText("Debug Mode: On ", 15, 11);
    }

	if (debugSettings.invincibility)
	{
		VDP_drawText("Invincibility: On ", 15, 12);
	}
	else
	{
		VDP_drawText("Invincibility: Off", 15, 12);
	}

	if (debugSettings.waitforvsync)
	{
		VDP_drawText("Wait for VSync: On ", 15, 13);
	}
	else
	{
		VDP_drawText("Wait for VSync: Off", 15, 13);
	}

	if (debugSettings.showFPSCounter)
	{
		VDP_drawText("Show FPS Counter: On ", 15, 14);
	}
	else
	{
		VDP_drawText("Show FPS Counter: Off", 15, 14);
	}
}

void OpenInGameMenu()
{
    currentLoopFunction = InGameMenuLoop;

    JOY_setEventHandler(joyEventCallback);

    menuItem = 0;

    MyVDP_waitVSync();
    VDP_setEnable(0);
    VDP_setReg(0x0b, 0x00); // set scroll mode to plane/plane
    VDP_resetSprites();

    VDP_setVerticalScroll(PLAN_A, 0);
    VDP_setVerticalScroll(PLAN_B, 0);
    VDP_setHorizontalScroll(PLAN_A, 0);
    VDP_setHorizontalScroll(PLAN_B, 0);

    VDP_updateSprites();

    VDP_fillTileMapRect(APLAN, 0, 0, 0, 64, 64);
    VDP_fillTileMapRect(BPLAN, 0, 0, 0, 64, 64);

    VDP_setTextPalette(0);

	DrawText();

    VDP_setEnable(1);
}

void InGameMenuLoop()
{
    VDP_resetSprites();

    u16 tileAttr = TILE_ATTR_FULL(PAL0,0,0,0,goplanesLoadedTileInfo.startIndex);

    VDP_setSprite(0, TILE_TO_PIXEL(12), TILE_TO_PIXEL(9) + TILE_TO_PIXEL(menuItem), SPRITE_SIZE(3,3), tileAttr, 0);

    MyVDP_waitVSync();
	VDP_updateSprites();   

	if (joyButtonPressedState.b)
	{
		CloseInGameMenu(); 
		return;
	}

    if (joyButtonPressedState.start || joyButtonPressedState.a)
    {
        switch (menuItem)
        {
        case MENU_ITEM_RETURN:
			{
				CloseInGameMenu(); 
				return;
			}
			break;
        case MENU_ITEM_ENABLE_DEBUG:
            {
                if (playerObject->aiState != AI_STATE_DEBUG)
                {
                    Player_StartDebugMovement();
                }
                else
                {
                    Player_EndDebugMovement();
                }
				DrawText();
            }
            break;
		case MENU_ITEM_INVINCIBILITY:
			debugSettings.invincibility = !debugSettings.invincibility;
			DrawText();
			break;
		case MENU_ITEM_VSYNC:
			debugSettings.waitforvsync = !debugSettings.waitforvsync;
			DrawText();
			break;
		case MENU_ITEM_FPSCOUNTER:
			debugSettings.showFPSCounter = !debugSettings.showFPSCounter;
			DrawText();
			break;

        }
    }
}

void CloseInGameMenu()
{
    MyVDP_waitVSync();
    VDP_setEnable(0);
    VDP_resetSprites();
    VDP_updateSprites();
    currentLoopFunction = GameLoop;
	LevelManager_SetupBackgroundPlanes();
    LevelManager_SetScrollMode();
    LevelManager_DrawTilePlanes();
    LevelManager_UpdateTilePlanes();
    VDP_setEnable(1);
}
