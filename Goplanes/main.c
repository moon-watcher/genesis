#include <genesis.h>

#include "Debug.h"
#include "Game.h"
#include "LevelManager.h"
#include "Objects.h"
#include "Physics.h"
#include "Player.h"
#include "PlayerPhysics.h"
#include "VDP_Extra.h"

#define BENCHMARK_UPDATE_OBJECTS

void SetupVDP()
{
    VDP_init();
    VDP_setScreenHeight224();
    VDP_setScreenWidth320();
}

typedef void (*FunctionType)();

void Benchmark(FunctionType function)
{
    u32 startTick = getSubTick();
    u16 loop = 0;
    for (loop = 0; loop < 100; loop++)
    {
        function();
    }
    u32 endTick = getSubTick();
    PrintNumber(endTick - startTick);

}

int main( )
{
    SetupVDP();
    JOY_init();

    VDP_setEnable(0);

    // setup game.
    gameState = GAME_STATE_SETUP_GAME;
    ObjectManager_SetupObjectCollections();
	InitGame();
    Player_SetupForGame();

    // setup level.
    gameState = GAME_STATE_SETUP_LEVEL;
    LevelManager_SetupLevel(); 
    Player_SetupForLevel();

    gameState = GAME_STATE_SETUP_SECTION;

    while (1)
    {
        // setup section.
        if (gameState == GAME_STATE_SETUP_SECTION)
        {
            LevelManager_SetupSectionResources();
        }

        ObjectManager_ClearObjectCollections();
        LevelManager_SetupSection();

        if (gameState == GAME_STATE_RESTART_SECTION_AFTER_DEATH)
        {
            Player_SetupForSectionAfterDeath();
        }

        Player_SetupForSection();
		LevelManager_SetupBackgroundPlanes();
     
        // setup main loop.
        gameState = GAME_STATE_RUNNING;

	    VDP_resetSprites();
	    VDP_updateSprites();   
        
        VDP_setEnable(1);

        currentLoopFunction = GameLoop;

        oldjoystate = 0;

        do
	    {
            joystate = JOY_readJoypad(JOY_1);
            joyButtonPressedState.start = (joystate & BUTTON_START) && ((oldjoystate & BUTTON_START) == 0);

			joyButtonPressedState.a = (joystate & BUTTON_A) && ((oldjoystate & BUTTON_A) == 0);
			joyButtonPressedState.b = (joystate & BUTTON_B) && ((oldjoystate & BUTTON_B) == 0);

            currentLoopFunction();

            oldjoystate = joystate;
        } while(gameState == GAME_STATE_RUNNING);

        VDP_setEnable(0);
    }
	return 0;
}

