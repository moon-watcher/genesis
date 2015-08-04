#include "PlayerPhysics.h"

#include <genesis.h>
#include <genres.h>
#include <kdebug.h>

#include "Collisions.h"
#include "LevelManager.h"
#include "MathUtils.h"
#include "Objects.h"
#include "Player.h"
#include "Physics.h"


#define COLLIDE_LEFT_SIDE       1
#define COLLIDE_RIGHT_SIDE      2
#define COLLIDE_TOP_SIDE        3
#define COLLIDE_BOTTOM_SIDE     4
#define COLLIDE_INSIDE          5

const u16 movement_direction[32] = 
{
    FACING_RIGHT,                   // 0
    FACING_DOWN | FACING_RIGHT,     // 1
    FACING_DOWN | FACING_RIGHT,     // 2
    FACING_DOWN | FACING_RIGHT,     // 3
    FACING_DOWN | FACING_RIGHT,     // 4
    FACING_DOWN | FACING_RIGHT,     // 5
    FACING_DOWN | FACING_RIGHT,     // 6
    FACING_DOWN | FACING_RIGHT,     // 7
    FACING_DOWN,                    // 8
    FACING_DOWN | FACING_LEFT,      // 9
    FACING_DOWN | FACING_LEFT,      // 10
    FACING_DOWN | FACING_LEFT,      // 11
    FACING_DOWN | FACING_LEFT,      // 12
    FACING_DOWN | FACING_LEFT,      // 13
    FACING_DOWN | FACING_LEFT,      // 14
    FACING_DOWN | FACING_LEFT,      // 15
    FACING_LEFT,                    // 16
    FACING_UP | FACING_LEFT,        // 17
    FACING_UP | FACING_LEFT,        // 18
    FACING_UP | FACING_LEFT,        // 19
    FACING_UP | FACING_LEFT,        // 20
    FACING_UP | FACING_LEFT,        // 21
    FACING_UP | FACING_LEFT,        // 22
    FACING_UP | FACING_LEFT,        // 23
    FACING_UP,                      // 24
    FACING_UP | FACING_RIGHT,       // 25
    FACING_UP | FACING_RIGHT,       // 26
    FACING_UP | FACING_RIGHT,       // 27
    FACING_UP | FACING_RIGHT,       // 28
    FACING_UP | FACING_RIGHT,       // 29
    FACING_UP | FACING_RIGHT,       // 30
    FACING_UP | FACING_RIGHT        // 31
};

u16 reflectionPointX = 0;
u16 reflectionPointY = 0;

u16 tile_collisionx = 0;
u16 tile_collisiony = 0;
u16 tile_reflectionPointX = 0;
u16 tile_reflectionPointY = 0;
u16 collisionSide = 0;

ObjectStruct* collidedBreakable = 0;
u16 breakable_collisionx = 0;
u16 breakable_collisiony = 0;
u16 breakable_reflectionPointX = 0;
u16 breakable_reflectionPointY = 0;

s32 new_x;
s32 new_y;

u16 CastRayIntoBackground(u16 x1, u16 y1, u16 x2, u16 y2) 
{
    s16 dx = x2 - x1; s16 sx = 1;
    s16 dy = y2 - y1; s16 sy = 1;
    
    if (dx < 0)    
    {
        sx = -1;
        dx *= -1;
    }
    if (dy < 0)    
    {
        sy = -1;
        dy *= -1;
    }
    
    dx = dx << 1;
    dy = dy << 1;

    if (collidesWithTile(x1, y1))
    {
        tile_collisionx = x1;
        tile_collisiony = y1;
        tile_reflectionPointX = x1;
        tile_reflectionPointY = y1;
        //KDebug_Alert("stuck in tile");
        return 1;
    }

    u16 oldx;
    u16 oldy;

    if (dy < dx)
    {    
        s16 loop = dx>>1;
        s16 fraction = dy - loop;
        if (loop < 0)
        {
            loop = -loop;
        }
        while (loop--)
        {
            oldx = x1;
            oldy = y1;
            if (fraction >= 0)
            {
                y1 += sy;
                fraction -= dx;
            }
            fraction += dy;
            x1 += sx;

            if (collidesWithTile(x1, y1))
            {
                tile_collisionx = x1;
                tile_collisiony = y1;
                tile_reflectionPointX = oldx;
                tile_reflectionPointY = oldy;

                return 1;
            }
        }
    } 
    else 
    {
        s16 loop = (dy>>1);
        s16 fraction = dx - loop;
        if (loop < 0)
        {
            loop = -loop;
        }
        while (loop--)
        {
            oldx = x1;
            oldy = y1;

            if (fraction >= 0)
            {
                x1 += sx;
                fraction -= dy;
            }
            fraction += dx;
            y1 += sy;

            if (collidesWithTile(x1, y1))
            {
                tile_collisionx = x1;
                tile_collisiony = y1;
                tile_reflectionPointX = oldx;
                tile_reflectionPointY = oldy;
                return 1;
            }
        }    
    }


    return 0;
}

u16 CastRayIntoBreakable(u16 x1, u16 y1, u16 x2, u16 y2) 
{
    ObjectStruct tempObject;

    s16 dx = x2 - x1; s16 sx = 1;
    s16 dy = y2 - y1; s16 sy = 1;
    
    if (dx < 0)    
    {
        sx = -1;
        dx *= -1;
    }
    if (dy < 0)    
    {
        sy = -1;
        dy *= -1;
    }
    
    dx = dx << 1;
    dy = dy << 1;

    tempObject.x = x1;
    tempObject.y = y1;

    if (PointSquareCollision(&tempObject, collidedBreakable))
    {
        breakable_collisionx = x1;
        breakable_collisiony = y1;
        breakable_reflectionPointX = x1;
        breakable_reflectionPointY = y1;
        return 1;
    }

    u16 oldx;
    u16 oldy;

    if (dy < dx)
    {    
        s16 loop = dx>>1;
        s16 fraction = dy - loop;
        if (loop < 0)
        {
            loop = -loop;
        }
        while (loop--)
        {
            oldx = x1;
            oldy = y1;
            if (fraction >= 0)
            {
                y1 += sy;
                fraction -= dx;
            }
            fraction += dy;
            x1 += sx;

            
            tempObject.x = x1;
            tempObject.y = y1;
            if (PointSquareCollision(&tempObject, collidedBreakable))
            {
                breakable_collisionx = x1;
                breakable_collisiony = y1;
                breakable_reflectionPointX = oldx;
                breakable_reflectionPointY = oldy;

                return 1;
            }
        }
    } 
    else 
    {
        s16 loop = (dy>>1);
        s16 fraction = dx - loop;
        if (loop < 0)
        {
            loop = -loop;
        }
        while (loop--)
        {
            oldx = x1;
            oldy = y1;

            if (fraction >= 0)
            {
                x1 += sx;
                fraction -= dy;
            }
            fraction += dx;
            y1 += sy;

            tempObject.x = x1;
            tempObject.y = y1;
            if (PointSquareCollision(&tempObject, collidedBreakable))
            {
                breakable_collisionx = x1;
                breakable_collisiony = y1;
                breakable_reflectionPointX = oldx;
                breakable_reflectionPointY = oldy;

                return 1;
            }
        }    
    }
    
    return 0;
}

u16 ComputeTileCollisionSide(u16 movementDirection)
{
    if (movementDirection == FACING_DOWNRIGHT)
    {
        if (!collidesWithTile(tile_collisionx, tile_collisiony - 1))
        {
            return COLLIDE_TOP_SIDE;
        }
        
        return COLLIDE_LEFT_SIDE;
    }
    else if (movementDirection == FACING_DOWNLEFT)
    {
        if (!collidesWithTile(tile_collisionx, tile_collisiony - 1))
        {
            return COLLIDE_TOP_SIDE;
        }
        
        return COLLIDE_RIGHT_SIDE;
    }
    else if (movementDirection == FACING_UPLEFT)
    {
        if (!collidesWithTile(tile_collisionx, tile_collisiony + 1))
        {
            return COLLIDE_BOTTOM_SIDE;
        }

        return COLLIDE_RIGHT_SIDE;
    }
    else if (movementDirection == FACING_UPRIGHT)
    {
        if (!collidesWithTile(tile_collisionx, tile_collisiony + 1))
        {
            return COLLIDE_BOTTOM_SIDE;
        }

        return COLLIDE_LEFT_SIDE;
    }

    return 0;
}

u16 ComputeBreakableCollisionSide(u16 movementDirection)
{
    ObjectStruct tempObject;

    if (movementDirection == FACING_DOWNRIGHT)
    {
        tempObject.x = breakable_collisionx;
        tempObject.y = breakable_collisiony - 1;

        if (!PointSquareCollision(&tempObject, collidedBreakable))
        {
            return COLLIDE_TOP_SIDE;
        }
        
        return COLLIDE_LEFT_SIDE;
    }
    else if (movementDirection == FACING_DOWNLEFT)
    {
        tempObject.x = breakable_collisionx;
        tempObject.y = breakable_collisiony - 1;

        if (!PointSquareCollision(&tempObject, collidedBreakable))
        {
            return COLLIDE_TOP_SIDE;
        }
        
        return COLLIDE_RIGHT_SIDE;
    }
    else if (movementDirection == FACING_UPLEFT)
    {
        tempObject.x = breakable_collisionx;
        tempObject.y = breakable_collisiony + 1;

        if (!PointSquareCollision(&tempObject, collidedBreakable))
        {
            return COLLIDE_BOTTOM_SIDE;
        }

        return COLLIDE_RIGHT_SIDE;
    }
    else if (movementDirection == FACING_UPRIGHT)
    {
        tempObject.x = breakable_collisionx;
        tempObject.y = breakable_collisiony + 1;

        if (!PointSquareCollision(&tempObject, collidedBreakable))
        {
            return COLLIDE_BOTTOM_SIDE;
        }

        return COLLIDE_LEFT_SIDE;
    }

    return 0;
}



void PrintCollisionSide()
{
    if (collisionSide == COLLIDE_LEFT_SIDE) KDebug_Alert("left side collision");
    if (collisionSide == COLLIDE_RIGHT_SIDE) KDebug_Alert("right side collision");
    if (collisionSide == COLLIDE_TOP_SIDE) KDebug_Alert("top side collision");
    if (collisionSide == COLLIDE_BOTTOM_SIDE) KDebug_Alert("bottom side collision");
}

void PrintMovementDirection(u16 movementDirection)
{
    if (movementDirection == FACING_RIGHT) KDebug_Alert("right");
    if (movementDirection == FACING_LEFT) KDebug_Alert("left");
    if (movementDirection == FACING_UP) KDebug_Alert("up");
    if (movementDirection == FACING_DOWN) KDebug_Alert("down");

    if (movementDirection == FACING_DOWNLEFT) KDebug_Alert("down left");
    if (movementDirection == FACING_DOWNRIGHT) KDebug_Alert("down right");
    if (movementDirection == FACING_UPLEFT) KDebug_Alert("up left");
    if (movementDirection == FACING_UPRIGHT) KDebug_Alert("up right");
}

typedef void (*ComputePlayerResponseFunctionType)();

void ComputePlayerResponseFacingRight()
{
    playerObject->spriteIndex = 16;
}

void ComputePlayerResponseFacingLeft()
{
    playerObject->spriteIndex = 0;
}

void ComputePlayerResponseFacingDown()
{
    playerObject->spriteIndex = 24;
}

void ComputePlayerResponseFacingUp()
{
    playerObject->spriteIndex = 8;
}

void ComputePlayerResponseFacingDownRight()
{
    if (collisionSide == COLLIDE_TOP_SIDE)
    {
        playerObject->spriteIndex = 31 - (playerObject->spriteIndex - 1);
    }
    else
    {
        //KDebug_Alert("new direction down left");
        playerObject->spriteIndex = 15 - (playerObject->spriteIndex - 1);
    }
}

void ComputePlayerResponseFacingDownLeft()
{
    if (collisionSide == COLLIDE_TOP_SIDE)
    {
        playerObject->spriteIndex = 23 - (playerObject->spriteIndex - 9);
    }
    else
    {
        //KDebug_Alert("new direction down right");
        playerObject->spriteIndex = 7 - (playerObject->spriteIndex - 9);
    }
}

void ComputePlayerResponseFacingUpLeft()
{
    if (collisionSide == COLLIDE_BOTTOM_SIDE)
    {
        playerObject->spriteIndex = 15 - (playerObject->spriteIndex - 17);
    }
    else
    {
        //KDebug_Alert("new direction up right");
        playerObject->spriteIndex = 31 - (playerObject->spriteIndex - 17);
    }
}

void ComputePlayerResponseUpRight()
{
    if (collisionSide == COLLIDE_BOTTOM_SIDE)
    {
        playerObject->spriteIndex = 7 - (playerObject->spriteIndex - 25);
    }
    else
    {
        //KDebug_Alert("new direction up left");
        playerObject->spriteIndex = 23 - (playerObject->spriteIndex - 25);
    }
}

const ComputePlayerResponseFunctionType PlayerResponseFunctions[32] = 
{
    ComputePlayerResponseFacingRight,       // 0
    ComputePlayerResponseFacingDownRight,   // 1
    ComputePlayerResponseFacingDownRight,   // 2
    ComputePlayerResponseFacingDownRight,   // 3
    ComputePlayerResponseFacingDownRight,   // 4
    ComputePlayerResponseFacingDownRight,   // 5
    ComputePlayerResponseFacingDownRight,   // 6
    ComputePlayerResponseFacingDownRight,   // 7
    ComputePlayerResponseFacingDown,        // 8
    ComputePlayerResponseFacingDownLeft,    // 9
    ComputePlayerResponseFacingDownLeft,    // 10
    ComputePlayerResponseFacingDownLeft,    // 11
    ComputePlayerResponseFacingDownLeft,    // 12
    ComputePlayerResponseFacingDownLeft,    // 13
    ComputePlayerResponseFacingDownLeft,    // 14
    ComputePlayerResponseFacingDownLeft,    // 15
    ComputePlayerResponseFacingLeft,        // 16
    ComputePlayerResponseFacingUpLeft,      // 17
    ComputePlayerResponseFacingUpLeft,      // 18
    ComputePlayerResponseFacingUpLeft,      // 19
    ComputePlayerResponseFacingUpLeft,      // 20
    ComputePlayerResponseFacingUpLeft,      // 21
    ComputePlayerResponseFacingUpLeft,      // 22
    ComputePlayerResponseFacingUpLeft,      // 23
    ComputePlayerResponseFacingUp,          // 24
    ComputePlayerResponseUpRight,           // 25
    ComputePlayerResponseUpRight,           // 26
    ComputePlayerResponseUpRight,           // 27
    ComputePlayerResponseUpRight,           // 28
    ComputePlayerResponseUpRight,           // 29
    ComputePlayerResponseUpRight,           // 30
    ComputePlayerResponseUpRight            // 31
};

void ComputePlayerCollisionResponseToTile()
{
    //KDebug_Alert("ComputeCollisionResponse()");
    u16 movementDirection = movement_direction[playerObject->spriteIndex];
    collisionSide = ComputeTileCollisionSide(movementDirection);

    ComputePlayerResponseFunctionType computePlayerResponseFunction = PlayerResponseFunctions[playerObject->spriteIndex];
    computePlayerResponseFunction();
}

void ComputePlayerCollisionResponseToBreakable()
{
    u16 movementDirection = movement_direction[playerObject->spriteIndex];
    collisionSide = ComputeBreakableCollisionSide(movementDirection);

    ComputePlayerResponseFunctionType computePlayerResponseFunction = PlayerResponseFunctions[playerObject->spriteIndex];
    computePlayerResponseFunction();
}

u16 CollidesWithBreakables(u16 x1, u16 y1, u16 x2, u16 y2)
{
    if (breakablesCollection.numVisibleObjects == 0)
        return 0;

    u16 breakablesCounter = breakablesCollection.numVisibleObjects;
    ObjectStruct** breakablesList = breakablesCollection.objectVisibilityList;

    ObjectStruct temp;
    temp.x = x2;
    temp.y = y2;

    while (breakablesCounter--)
    {
        if (PointSquareCollision(&temp, *breakablesList))
        {
            collidedBreakable = *breakablesList;

            if (playerObject->aiState != AI_STATE_AFTERBURNERS)
            {
                CastRayIntoBreakable(x1, y1, x2, y2);
                return 1;
            }
            else
            {
                collidedBreakable->collisionFunction(collidedBreakable, playerObject);
                return 0;
            }
        }

        breakablesList++;
    }

    return 0;
}

u16 UpdatePlayerPhysics()
{
    u16 result = PHYSICS_RESULTS_NONE;

    playerObject->spriteIndex = (playerData.frameCounter >> 2) & 31;

    switch (playerObject->aiState)
    {
    case AI_STATE_FLYING:
        playerObject->speedx = goplanes_costable32[playerObject->spriteIndex];
        playerObject->speedy = goplanes_sintable32[playerObject->spriteIndex];
        break;
    case AI_STATE_CHARGING_AFTERBURNERS:
        playerObject->speedx = goplanes_slow_costable32[playerObject->spriteIndex];
        playerObject->speedy = goplanes_slow_sintable32[playerObject->spriteIndex];
        break;
    case AI_STATE_AFTERBURNERS:
        playerObject->speedx = goplanes_fast_costable32[playerObject->spriteIndex];
        playerObject->speedy = goplanes_fast_sintable32[playerObject->spriteIndex];
        break;
    }

    new_x = playerObject->x + playerObject->speedx;
    new_y = playerObject->y + playerObject->speedy;

    // level boundaries
    if (new_x < 0)
    {
        reflectionPointX = 0;

        collisionSide = COLLIDE_RIGHT_SIDE;
        ComputePlayerResponseFunctionType computePlayerResponseFunction = PlayerResponseFunctions[playerObject->spriteIndex];
        computePlayerResponseFunction();
        playerData.frameCounter = playerObject->spriteIndex << 2;
    }
    else if (new_y < 0)
    {
        reflectionPointY = 0;

        collisionSide = COLLIDE_BOTTOM_SIDE;
        ComputePlayerResponseFunctionType computePlayerResponseFunction = PlayerResponseFunctions[playerObject->spriteIndex];
        computePlayerResponseFunction();
        playerData.frameCounter = playerObject->spriteIndex << 2;
    }
    else if (new_x > TILE_TO_VIRTUAL(levelData.foreground->width) - 1)
    {
        reflectionPointX = TILE_TO_VIRTUAL(levelData.foreground->width) - 1;

        collisionSide = COLLIDE_LEFT_SIDE;
        ComputePlayerResponseFunctionType computePlayerResponseFunction = PlayerResponseFunctions[playerObject->spriteIndex];
        computePlayerResponseFunction();
        playerData.frameCounter = playerObject->spriteIndex << 2;
    }
    else if (new_y > TILE_TO_VIRTUAL(levelData.foreground->height) - 1)
    {
        reflectionPointY = TILE_TO_VIRTUAL(levelData.foreground->height) - 1;

        collisionSide = COLLIDE_TOP_SIDE;
        ComputePlayerResponseFunctionType computePlayerResponseFunction = PlayerResponseFunctions[playerObject->spriteIndex];
        computePlayerResponseFunction();
        playerData.frameCounter = playerObject->spriteIndex << 2;
    }
    else
    {
        reflectionPointX = new_x;
        reflectionPointY = new_y;

        u16 collidesWithBackground = CastRayIntoBackground(playerObject->x, playerObject->y, new_x, new_y);
        u16 collidesWithBreakables = 0;
        
        collidesWithBreakables = CollidesWithBreakables(playerObject->x, playerObject->y, new_x, new_y);

        if (collidesWithBackground == 1 && collidesWithBreakables == 1)
        {

        }
        else if (collidesWithBackground == 1)
        {
            ComputePlayerCollisionResponseToTile();
            playerData.frameCounter = playerObject->spriteIndex << 2;
            result = PHYSICS_RESULTS_COLLIDED_WITH_TILE;
            reflectionPointX = tile_reflectionPointX;
            reflectionPointY = tile_reflectionPointY;
            result = 1;
        }
        else if (collidesWithBreakables == 1)
        {
            ComputePlayerCollisionResponseToBreakable();
            playerData.frameCounter = playerObject->spriteIndex << 2;
            result = PHYSICS_RESULTS_COLLIDED_WITH_BREAKABLE;
            reflectionPointX = breakable_reflectionPointX;
            reflectionPointY = breakable_reflectionPointY;
            result = 1;
        }
    }

    playerObject->speedx = reflectionPointX - playerObject->x;
    playerObject->speedy = reflectionPointY - playerObject->y;

    // update to the new position   
    playerObject->x = reflectionPointX;
    playerObject->y = reflectionPointY;

    return result;
}


