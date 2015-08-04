#ifndef MATH_UTILS_INCLUDE
#define MATH_UTILS_INCLUDE

#include <genesis.h>

// converts from one space (virtual space, screen/pixel space and tile space) to another.
#define PIXEL_TO_VIRTUAL(value) ((value) << 2) // 4 virtual pixels per on screen pixel
#define PIXEL_TO_TILE(value)    ((value) >> 3) // 8 pixels per tile

#define VIRTUAL_TO_PIXEL(value) ((value) >> 2) // 4 virtual pixels per on screen pixel
#define VIRTUAL_TO_TILE(value)  ((value) >> 5) // 4 virtual pixels per pixel, 8 pixels per tile

#define TILE_TO_PIXEL(value)    ((value) << 3) // 8 pixels per tile
#define TILE_TO_VIRTUAL(value)  ((value) << 5) // 4 virtual pixels per pixel, 8 pixels per tile

#define DOUBLE_VALUE(value)     ((value) << 1)
#define HALVE_VALUE(value)      ((value) >> 1)

#define ARRAY_ITEM_VALUE(_array, pos) *(_array + (pos))
#define ARRAY_ITEM_ADDRESS(_array, pos) (_array + (pos))

// special tables for calculating the goplane's orientation.
extern const s16 goplanes_costable32[32];
extern const s16 goplanes_sintable32[32];

extern const s16 goplanes_slow_costable32[32];
extern const s16 goplanes_slow_sintable32[32];

extern const s16 goplanes_fast_costable32[32];
extern const s16 goplanes_fast_sintable32[32];

extern const s16 radar_screenpos_x[256];
extern const s16 radar_screenpos_y[256];

#define DISTANCE_ANGLE_TABLE_WIDTH  80
#define DISTANCE_ANGLE_TABLE_HEIGHT 56

#define GET_DISTANCE_ANGLE_VALUE(x, y) \
    (*(distance_and_angles_table80x56 + tile_distance_x  + (tile_distance_y << 6) + (tile_distance_y << 4))) // (x * 80) == (x * 64) + (x * 16) == (x << 6) + (x << 4)

#define GET_DISTANCE_VALUE(x, y) \
    (GET_DISTANCE_ANGLE_VALUE(x, y) >> 6)

#define GET_ANGLE_VALUE(x, y) \
    (GET_DISTANCE_ANGLE_VALUE(x, y) & 63)

// The distance and angles table gives the distance and angles for an area of 320 x 224 pixels but
// actually in 40 x 28 tile space. 
// in each 16 bit value, the first 6 bits give an angle from 0 to 63 of a quarter circle originating
// from the top left hand corner of the table to the item in the table. 
// the remaining 10 bits gives a distance from the top left hand corner of the table to the item in
// the table.
extern const u16 distance_and_angles_table80x56[4480];

s16 mathutils_abs(s16 value); // terrible and badly implemented.
u16 mathutils_isnegative(s16 value); // terrible and badly implemented.

u16 GetShiftValueFromValue(u16 value);

#endif
