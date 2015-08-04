#ifndef VDP_EXTRA_INCLUDE
#define VDP_EXTRA_INCLUDE

#include <genesis.h>

void MyVDP_setTileMapRect(u16 plan, const u16 *data, u16 basetile, u16 x, u16 y, u16 w, u16 h);
void VDP_setAllHorizontalScrollLines(u16 plan, u16 value);
void VDP_setHorizontalScrollLines(u16 plan, u16* lines, u16 value);
void MyVDP_doDMA(u8 location, u32 from, u16 to, u16 len, u16 autoInc);
void MyVDP_doVRamDMACopy(u16 from, u16 to, u16 len, u16 autoInc);
void MyVDP_waitVSync();

#endif
