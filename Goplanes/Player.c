#include "Player.h"

#include <genesis.h>
#include <kdebug.h>
#include <maths.h>

#include "AfterburnerChargeUp.h"
#include "Bullet.h"
#include "Fireball.h"
#include "FireballPickup.h"
#include "Collisions.h"
#include "Config.h"
#include "Debug.h"
#include "Explosion.h"
#include "Game.h"
#include "HUD.h"
#include "SimpleEffect.h"
#include "LargeExplosion.h"
#include "LevelManager.h"
#include "MathUtils.h"
#include "Objects.h"
#include "Physics.h"
#include "PlayerPhysics.h"
#include "Poof.h"
#include "SpritesAndMaps.h"


#define WALLS_HURT

#define MAX_HEALTH_POINTS 8

ObjectStruct player;
ObjectStruct* playerObject;
PlayerDataStruct playerData;



#define WEAPON_BULLET_COOLDOWN_TIME     15
#define WEAPON_FIREBALL_COOLDOWN_TIME   60

#define WEAPON_FIREBALL_SPEED_MULTIPLIER 1.5

#define DEBUG_MOVEMENT_SPEED        10
#define AFTERBURNER_CHARGE_TIME     60
#define AFTERBURNER_TIME            45

extern const u16 movement_direction[32];

u16 useLevelStartPosition = 1;

u16 rotateDirection = 0;
u16 muzzleFlashAnimation = 0;
u16 deathWaitTime = 0;
u16 hitTimer = 0;
u16 weaponCooldownTimer = 0;
u16 holdingAfterburnerButtonDown = 0;
u16 startButtonDown = 0;


const u16 animationFrames[32] = 
{
    TILE_ATTR_FULL(PAL0,0,0,0,0),
    TILE_ATTR_FULL(PAL0,0,0,0,(1 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,0,(2 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,0,(3 * 9)),

    TILE_ATTR_FULL(PAL0,0,0,0,(4 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,0,(5 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,0,(6 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,0,(7 * 9)),

    TILE_ATTR_FULL(PAL0,0,0,0,(8 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,0,(9 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,0,(10 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,0,(11 * 9)),

    TILE_ATTR_FULL(PAL0,0,0,0,(12 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,0,(13 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,0,(14 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,0,(15 * 9)),

    TILE_ATTR_FULL(PAL0,0,1,1,0),
    TILE_ATTR_FULL(PAL0,0,1,1,(1 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,1,(2 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,1,(3 * 9)),

    TILE_ATTR_FULL(PAL0,0,1,1,(4 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,1,(5 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,1,(6 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,1,(7 * 9)),

    TILE_ATTR_FULL(PAL0,0,1,1,(8 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,1,(9 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,1,(10 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,1,(11 * 9)),

    TILE_ATTR_FULL(PAL0,0,1,1,(12 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,1,(13 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,1,(14 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,1,(15 * 9))
};

const u16 afterburnerAnimationFrames[32] =
{
    TILE_ATTR_FULL(PAL0,0,0,0,(16 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,0,(17 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,0,(18 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,0,(19 * 9)),
    
    TILE_ATTR_FULL(PAL0,0,0,0,(20 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,0,(21 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,0,(22 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,0,(23 * 9)),
    
    TILE_ATTR_FULL(PAL0,0,0,1,(24 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,1,(23 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,1,(22 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,1,(21 * 9)),
    
    TILE_ATTR_FULL(PAL0,0,0,1,(20 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,1,(19 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,1,(18 * 9)),
    TILE_ATTR_FULL(PAL0,0,0,1,(17 * 9)),
    
    TILE_ATTR_FULL(PAL0,0,1,1,(16 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,1,(17 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,1,(18 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,1,(19 * 9)),
    
    TILE_ATTR_FULL(PAL0,0,1,1,(20 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,1,(21 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,1,(22 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,1,(23 * 9)),
    
    TILE_ATTR_FULL(PAL0,0,1,0,(24 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,0,(23 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,0,(22 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,0,(21 * 9)),
    
    TILE_ATTR_FULL(PAL0,0,1,0,(20 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,0,(19 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,0,(18 * 9)),
    TILE_ATTR_FULL(PAL0,0,1,0,(17 * 9)),
};

void DestroyPlane(ObjectStruct* playerObject)
{
    playerObject->healthPoints = 0;
	UpdateHUDHealth();
    playerObject->aiState = AI_STATE_FALLING;
    LargeExplosionCreate(playerObject->x, playerObject->y);
    if (movement_direction[playerObject->spriteIndex] & FACING_RIGHT)
    {
        rotateDirection = 1;
    }
    else if (movement_direction[playerObject->spriteIndex] & FACING_LEFT)
    {
        rotateDirection = -1;
    }
    else
    {
        rotateDirection = 0;
    }
}

void StartFlying()
{
    playerObject->aiState = AI_STATE_FLYING;
    playerData.afterBurnerChargeUpTimer = 0;
}

void StartChargingAfterburners()
{
    AfterburnerChargeUpCreate();
    playerObject->aiState = AI_STATE_CHARGING_AFTERBURNERS;
    playerData.afterBurnerChargeUpTimer = AFTERBURNER_CHARGE_TIME;
}

void StartAfterburners()
{
    PoofCreate(playerObject->x, playerObject->y);
    playerObject->aiState = AI_STATE_AFTERBURNERS;
    playerData.afterburnerTimer = AFTERBURNER_TIME;
}

void Player_StartDebugMovement()
{
    playerObject->aiState = AI_STATE_DEBUG;
    playerObject->speedx = 0;
    playerObject->speedy = 0;
}

void Player_EndDebugMovement()
{
    StartFlying();
}

void FireWeapon()
{
    switch (playerData.currentWeapon)
    {
    case WEAPON_BULLET:
        if (BulletCreate(playerObject->x, 
                         playerObject->y, 
                         playerObject->speedx * 1.5,
                         playerObject->speedy * 1.5))
        {
            muzzleFlashAnimation = 4;
            
            weaponCooldownTimer = WEAPON_BULLET_COOLDOWN_TIME;
        }

        break;
    case WEAPON_FIREBALL:
        {
            FireballCreate(playerObject->x, 
                           playerObject->y, 
                           goplanes_costable32[playerObject->spriteIndex] << 1, 
                           goplanes_sintable32[playerObject->spriteIndex] << 1, 
                           playerObject->spriteIndex);
        
            s16 spriteIndex = (playerObject->spriteIndex + 1) & 31;
            FireballCreate(playerObject->x, 
                           playerObject->y, 
                           goplanes_costable32[spriteIndex] << 1, 
                           goplanes_sintable32[spriteIndex] << 1, 
                           spriteIndex);
            spriteIndex = playerObject->spriteIndex;
            spriteIndex = (spriteIndex - 1) & 31;
            FireballCreate(playerObject->x, 
                           playerObject->y, 
                           goplanes_costable32[spriteIndex] << 1, 
                           goplanes_sintable32[spriteIndex] << 1, 
                           spriteIndex);
            muzzleFlashAnimation = 4;
            weaponCooldownTimer = WEAPON_FIREBALL_COOLDOWN_TIME;
        }
        break;
    }
}

void UpdateFlyingControls()
{
    if (joystate & BUTTON_LEFT)
    {
        playerData.frameCounter--;
    }

    if (joystate & BUTTON_RIGHT)
    {
        playerData.frameCounter++;
    }

    if (!(joystate & BUTTON_B))
    {
        holdingAfterburnerButtonDown = 0;
    }

    if (joystate & BUTTON_B && 
        playerData.afterBurnerChargeUpTimer == 0 &&
        holdingAfterburnerButtonDown == 0)
    {
        StartChargingAfterburners();
        holdingAfterburnerButtonDown = 1;
    }

    if ((joystate & BUTTON_A) && weaponCooldownTimer == 0)
    {
        FireWeapon();
    }

    /*
    if (!(joystate & BUTTON_START))
    {
        startButtonDown = 0;
    }

    if ((joystate & BUTTON_START) && (startButtonDown == 0))
    {
        Player_StartDebugMovement();
        startButtonDown = 1;
    }
    */
    

    if (weaponCooldownTimer > 0)
    {
        weaponCooldownTimer--;
    }

    if (joystate & BUTTON_C)
    {
        DestroyPlane(playerObject);
    }
}

void UpdateChargingAfterburnerControls()
{
    //if ((playerObject->lifetime & 1) == 0)
    {
        if (joystate & BUTTON_LEFT)
        {
            playerData.frameCounter--;
        }

        if (joystate & BUTTON_RIGHT)
        {
            playerData.frameCounter++;
        }        
    }

    if (!(joystate & BUTTON_B))
    {
        StartFlying();
        holdingAfterburnerButtonDown = 0;
    }
}

void UpdateDebugControls()
{
    /*
    if (!(joystate & BUTTON_START))
    {
        startButtonDown = 0;
    }

    if ((joystate & BUTTON_START) && (startButtonDown == 0))
    {
        StartFlying();
        startButtonDown = 1;
    }
    */

    if (joystate & BUTTON_LEFT)
    {
        playerObject->speedx = -DEBUG_MOVEMENT_SPEED;
    }
    else if (joystate & BUTTON_RIGHT)
    {
        playerObject->speedx = DEBUG_MOVEMENT_SPEED;
    }
    else
    {
        playerObject->speedx = 0;
    }

    if (joystate & BUTTON_UP)
    {
        playerObject->speedy = -DEBUG_MOVEMENT_SPEED;
    }
    else if (joystate & BUTTON_DOWN)
    {
        playerObject->speedy = DEBUG_MOVEMENT_SPEED;
    }
    else
    {
        playerObject->speedy = 0;
    }
}

void UpdateCommon()
{
    u16 physicsResults = UpdatePlayerPhysics();

    if (physicsResults == PHYSICS_RESULTS_COLLIDED_WITH_TILE)
    {
        PoofCreate(playerObject->x, playerObject->y);
#ifdef WALLS_HURT
		if (debugSettings.invincibility == FALSE)
		{
			if (hitTimer == 0)
			{
				playerObject->healthPoints--;
				UpdateHUDHealth();

				if (playerObject->healthPoints <= 0)
				{
					DestroyPlane(playerObject);
				}
				else
				{
					hitTimer = 70;
				}
			}
		}
#endif
    }

    if (hitTimer > 0)
    {
        hitTimer--;
    }

    if (playerObject->healthPoints == 1)
    {
        if ((playerObject->lifetime & 31) == 0)
        {
            ExplosionCreate(playerObject->x, playerObject->y);
        }
    }
}

void PlayerUpdate(ObjectStruct* playerObject)
{
    switch (playerObject->aiState)
    {
    case AI_STATE_FLYING: 
        {
            UpdateCommon();

            if (muzzleFlashAnimation > 0)
            {
                muzzleFlashAnimation--;
            }

            UpdateFlyingControls();
        }
        break;
    case AI_STATE_CHARGING_AFTERBURNERS:
        {
            UpdateCommon();
            UpdateChargingAfterburnerControls();

            if (playerData.afterBurnerChargeUpTimer > 0)
            {
                playerData.afterBurnerChargeUpTimer--;

                if (playerData.afterBurnerChargeUpTimer == 0)
                {
                    StartAfterburners();
                }
            }
        }
        break;
    case AI_STATE_AFTERBURNERS:
        {
            UpdateCommon();
            
            if (playerData.afterburnerTimer > 0)
            {
                playerData.afterburnerTimer--;
                if (playerData.afterburnerTimer == 0)
                {
                    PoofCreate(playerObject->x, playerObject->y);
                    StartFlying();
                }
            }
        }
        break;
    case AI_STATE_FALLING:
        {
            if ((playerObject->lifetime & 5) == 0)
            {
                playerObject->speedy += 1; // gravity.
            }

            if (playerObject->speedy > 20)
            {
                playerObject->speedy = 20;
            }

            playerData.frameCounter += rotateDirection;
            playerObject->spriteIndex = (playerData.frameCounter >> 1) & 31;

            playerObject->x += playerObject->speedx;
            playerObject->y += playerObject->speedy;

            if (OutOfBounds(playerObject->x, playerObject->y))
            {
                playerObject->aiState = AI_STATE_DEAD;
            }
            else if (collidesWithTile(playerObject->x, playerObject->y) ||
                     CollidesWithVisibleBreakables(playerObject->x, playerObject->y))
            {
                LargeExplosionCreate(playerObject->x, playerObject->y);
                playerObject->aiState = AI_STATE_DEAD;
            }
        
            if (((playerObject->lifetime + 3) & 7) == 0)
            {
                LargeExplosionCreate(playerObject->x + (random() % 64) - 32, 
                                     playerObject->y + (random() % 64) - 32);
            }
        
            if ((playerObject->lifetime & 7) == 0)
            {
                ExplosionCreate(playerObject->x, playerObject->y);
            }

            deathWaitTime = 50;
        }
        break;
    case AI_STATE_DEAD:
        {
            if (deathWaitTime > 0)
            {
                playerObject->speedx = 0;
                playerObject->speedy = 0;

                if (((playerObject->lifetime + 3) & 7) == 0)
                {
                    LargeExplosionCreate(playerObject->x + (random() % 64) - 32, 
                                         playerObject->y + (random() % 64) - 32);
                }
        
                if ((playerObject->lifetime & 7) == 0)
                {
                    ExplosionCreate(playerObject->x + (random() % 64) - 32, 
                                    playerObject->y + (random() % 64) - 32);
                }

                deathWaitTime--;
            }
            else
            {
                playerObject->aiState = AI_WAITFOR_LEVEL_RESTART;
                deathWaitTime = 50;
            }
        }
        break;
    case AI_WAITFOR_LEVEL_RESTART:
        {
            if (deathWaitTime > 0)
            {
                deathWaitTime--;
            }        
            else
            {
                if (playerData.lives > 0)
                {
                    playerData.lives--;
					UpdateHUDLives();
                    gameState = GAME_STATE_RESTART_SECTION_AFTER_DEATH;
                }
                else
                {
                    LevelManager_GoToGameOver();
                }
            }
        }
        break;
    case AI_STATE_DEBUG:
        {
            UpdateDebugControls();

            playerData.playerColliding = 0;
            playerObject->x += playerObject->speedx;
            playerObject->y += playerObject->speedy;
        }
        break;
    }


    playerObject->sprite.posx = (s16)VIRTUAL_TO_PIXEL(playerObject->x + scrollData.scrollx_hires_clamped) - 12;
    playerObject->sprite.posy = (s16)VIRTUAL_TO_PIXEL(playerObject->y - scrollData.scrolly_hires_clamped) - 12;

}

void PlayerDestroy(ObjectStruct* playerObject)
{
}

void PlayerCollide(ObjectStruct* playerObject, ObjectStruct* collidedObject)
{
    if (hitTimer > 0)
    {
        return;
    }

    switch (playerObject->aiState)
    {
    case AI_STATE_FLYING:
    case AI_STATE_CHARGING_AFTERBURNERS:
    {
        switch (collidedObject->objectType)
        {
        case TYPE_ENEMY:
        case TYPE_ENEMY_PROJECTILE:
            if (collidedObject->healthPoints > 0)
            {
				if (debugSettings.invincibility == FALSE)
				{
					playerObject->healthPoints -= collidedObject->damage;
					UpdateHUDHealth();
					hitTimer = 70;

					LargeExplosionCreate(playerObject->x, playerObject->y);

					if (playerObject->aiState == AI_STATE_CHARGING_AFTERBURNERS)
					{
						StartFlying();
					}

					if (playerObject->healthPoints <= 0)
					{
						DestroyPlane(playerObject);
					}
					else
					{
						if (playerData.currentWeapon != WEAPON_BULLET)
						{
							switch (playerData.currentWeapon)
							{
							case WEAPON_FIREBALL:
								FireballPickupCreate(playerObject->x, playerObject->y);
								break;
							}

							playerData.currentWeapon = WEAPON_BULLET;
						}
					}
				}
            }
            break;
        case TYPE_PICKUP:
            break;
        }
        break;
    }

        break;
    case AI_STATE_DEBUG:
        playerData.playerColliding = 1;
        break;
    }
    
}

void PlayerDraw(ObjectStruct* playerObject)
{
    if (playerObject->aiState == AI_STATE_DEAD ||
        playerObject->aiState == AI_WAITFOR_LEVEL_RESTART)
    {
        return;
    }

    if (hitTimer & 1)
    {
        return;
    }

    switch (playerObject->aiState)
    {
    case AI_STATE_FLYING:
        {
            if (muzzleFlashAnimation > 0)
            {
                s16 muzzleflash_x = VIRTUAL_TO_PIXEL(playerObject->x) + scrollData.scrollx_vdp - 4 + (goplanes_costable32[playerObject->spriteIndex]);
                s16 muzzleflash_y = VIRTUAL_TO_PIXEL(playerObject->y) - scrollData.scrolly_vdp - 4 + (goplanes_sintable32[playerObject->spriteIndex]);

                VDP_setSprite(spriteDrawIndex, 
                              muzzleflash_x, 
                              muzzleflash_y, 
                              SPRITE_SIZE(1,1), 
                              TILE_ATTR_FULL(PAL0, 1, 0, 1, muzzleFlashLoadedTileInfo.startIndex + (muzzleFlashAnimation >> 1)), 
                              spriteDrawIndex + 1);
                spriteDrawIndex++;
            }
        }        
        break;
    case AI_STATE_CHARGING_AFTERBURNERS:
        {

        }
        break;
    case AI_STATE_AFTERBURNERS:
        {
            if ((playerObject->lifetime & 3) == 0)
            {
                SimpleEffectCreate(playerObject->x, 
                                   playerObject->y,
                                   0,
                                   0,
                                   5,
                                   2,
                                   2,
                                   2,
                                   TILE_ATTR_FULL(PAL0, 1, 0, 0, afterburnerLoadedTileInfo.startIndex));
            }
        }
        break;
    }

    switch (playerObject->aiState)
    {
    case AI_STATE_AFTERBURNERS:
        playerObject->sprite.tile_attr = ARRAY_ITEM_VALUE(afterburnerAnimationFrames, playerObject->spriteIndex) + goplanesLoadedTileInfo.startIndex; 
        break;
    case AI_STATE_DEBUG:
        if (playerData.playerColliding == 0)
        {
            playerObject->sprite.tile_attr = TILE_ATTR_FULL(PAL0,0,0,0,goplanesLoadedTileInfo.startIndex + (25 * 9));
        }
        else
        {
            playerObject->sprite.tile_attr = TILE_ATTR_FULL(PAL0,0,0,0,goplanesLoadedTileInfo.startIndex + (26 * 9));
        }
        break;
    default:
        playerObject->sprite.tile_attr = ARRAY_ITEM_VALUE(animationFrames, playerObject->spriteIndex) + goplanesLoadedTileInfo.startIndex;
    }

    playerObject->sprite.link  = spriteDrawIndex + 1;
    VDP_setSpriteP(spriteDrawIndex, &playerObject->sprite);
    spriteDrawIndex++;
}

void PlayerCreate()
{
    playerObject = &player;
    playerObject->updateFunction    = (ObjectFunctionTypePrototype)PlayerUpdate;
    playerObject->destroyFunction   = (ObjectFunctionTypePrototype)PlayerDestroy;
    playerObject->drawFunction      = (ObjectFunctionTypePrototype)PlayerDraw;
    playerObject->collisionFunction = (ObjectCollisionFunctionPrototype)PlayerCollide;
    playerObject->objectState       = OBJECTSTATE_ACTIVE;

    playerObject->objectType        = TYPE_PLAYER;
    playerObject->sprite.size       = SPRITE_SIZE(3,3);
    playerObject->damage            = 1;
    playerObject->healthPoints      = MAX_HEALTH_POINTS;

    playerObject->rectLeft          = PIXEL_TO_VIRTUAL(-12);
    playerObject->rectRight         = PIXEL_TO_VIRTUAL(12);
    playerObject->rectTop           = PIXEL_TO_VIRTUAL(-12);
    playerObject->rectBottom        = PIXEL_TO_VIRTUAL(12);
     
    playerData.numCoins             = 0;
    playerData.lives                = 3;
    playerData.currentWeapon        = WEAPON_BULLET;

}

void Player_SetupForGame()
{
    PlayerCreate();
}

void Player_SetupForLevel()
{
    useLevelStartPosition = 1;
    playerData.frameCounter         = 0;
}

void Player_SetupForSection()
{
    if (useLevelStartPosition == 1)
    {
        LevelManager_SetupPlayerLevelStartPosition();
        useLevelStartPosition = 0;
    }
    else
    {
        LevelManager_SetupPlayerSectionStartPosition();
        playerData.frameCounter = playerObject->spriteIndex << 2;
    }
}

void Player_SetupForSectionAfterDeath()
{
    StartFlying();

    playerObject->healthPoints      = MAX_HEALTH_POINTS;
    playerData.playerColliding      = 0;
    playerData.currentWeapon        = WEAPON_BULLET;
    rotateDirection                 = 0;
    muzzleFlashAnimation            = 0;
    deathWaitTime                   = 0;
    hitTimer                        = 0;
    weaponCooldownTimer             = 0;
    holdingAfterburnerButtonDown    = 0;
    startButtonDown                 = 0;    
}
