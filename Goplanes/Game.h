#ifndef GAME_INCLUDE_H
#define GAME_INCLUDE_H

#include <genesis.h>

#define GAME_STATE_SETUP_GAME                   0
#define GAME_STATE_SETUP_LEVEL                  1 
#define GAME_STATE_SETUP_SECTION                2 
#define GAME_STATE_RUNNING                      3
#define GAME_STATE_RESTART_SECTION_AFTER_DEATH  4
#define GAME_STATE_OPEN_INGAME_MENU             5
#define GAME_STATE_INGAME_MENU                  6

typedef struct 
{
	u16 invincibility;
	u16 waitforvsync;
	u16 showFPSCounter;
} DebugSettingsStruct;

extern DebugSettingsStruct debugSettings;

extern u16 gameState;


void SetupGameResources();

typedef void (*LoopFunction)();

extern u16 joystate;
extern u16 oldjoystate;

typedef struct
{
	u16 start;
	u16 a;
	u16 b;
} ButtonPressedStateStruct;

extern ButtonPressedStateStruct joyButtonPressedState;

extern LoopFunction currentLoopFunction;

void InitGame();
void GameLoop();
void OpenInGameMenu();
void InGameMenuLoop();
void CloseInGameMenu();

#endif
